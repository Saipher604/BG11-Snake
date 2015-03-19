#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <unistd.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define ARENA_WIDTH 78
#define ARENA_HEIGHT 23

//Defines gotoxy() for ANSI C compilers.
void gotoxy(short x, short y)
{
	COORD pos = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int main(int argc, char** argv)
{
	// food variables
	int  xf, yf, food = 0,  xff, yff, fakefood = 0;

	// Snake variables movement direction, Position, length,
	int  dir = 4, x[ARENA_WIDTH * ARENA_HEIGHT], y[ARENA_WIDTH * ARENA_HEIGHT],  horP = 40, verP = 12, n = 16;

	// various variables for simple counting, points, difficulty and for temporaily caching snake lenght (n -> nsave)
	int points, speed = 0, fcounter = 0, d, i, z = 0, chance, difficulty, b = 0, loop = 1, key, nsave;

	int Debug = 0, edebug = 0;
	FILE *debug;

	// difficulty options
	const int EASY = 100, MEDIUM = 80, HARD = 70;

	// constants for Keys
	const int UP = 4, DOWN = 3, LEFT = 2, RIGHT = 1, W = 97,A = 119, S = 100, D = 115, ESC = 27, X = 120;

	const int NO = 0, YES = 1;

	const int encryptionlevel = -133;

	char Snake = 219, blank = 255, ae /*ä*/ = 132, ue /*ü*/ = 129, oe /*ö*/ = 148;

	// character arrays for highscore names
	char name[15] = {255,255,255,255,255,255,255,255,255,255,255,255,255,255,255};

	// ASCII-code for Arena lines
	char horz = 196, verz = 179, ol = 218, orr = 191, ul = 192, ur = 217;

	// overwrite position arrays with 0 !note! x[0] and y[0] are reserved for snake head!! checking for intersections must be done with 'n + 1'
	for(i = 0; i < (ARENA_WIDTH * ARENA_HEIGHT); i++)
		{
			x[i] = 0;
			y[i] = 0;
		}

	// randomization for food spawner
	srand(getpid());

	// play simple intro
	gotoxy(38, 12);
	std:: cout << "Snake";

	Sleep(600);

	while(loop == YES)
		{
			system("cls");

			/* draw main menu */

			// print main menu
			gotoxy(3, 19);
			std:: cout << "Steuerung: W - hoch";
			gotoxy(14, 20);
			std:: cout << "S - runter";
			gotoxy(14, 21);
			std:: cout << "A - links";
			gotoxy(14, 22);
			std:: cout << "D - rechts";
			gotoxy(12, 23);
			std:: cout << "Esc - Pause";
			gotoxy(37.5, 7);
			std:: cout << "SNAKE";

			gotoxy(23, 13);
			std:: cout << "[4] Highscores";


			/* draw debug menu text based on choosen option */
			if(Debug == 0)
				{
					gotoxy(23, 14);
					std:: cout << "[0] Debug [AUS]";
				}
			else
				{
					gotoxy(23, 14);
					std:: cout << "[0] Debug [AN]";

					if(edebug == 0)
						{
							gotoxy(23, 15);
							std:: cout << "[9] exstensive Debug [AUS]";
						}

					else if(edebug == 1)
						{
							gotoxy(23, 15);
							std:: cout << "[9] exstensive Debug [AN]";
						}

				}

			gotoxy(23, 12);
			std:: cout << "Schwierigkeitsgrad ausw" << ae << "hlen [1|2|3] ";

			/* end drawing main menu */

			// read key presses for menu navigation
			scanf("%d", &key);
			fflush(stdin);

			if(key == 1)
				difficulty = EASY;

			if(key == 2)
				difficulty = MEDIUM;

			if(key == 3)
				difficulty = HARD;

			if(key == 1 || key == 2 || key == 3)
				loop = NO;

			// Read and print Highscore file
			if(key == 4)
				{
					system("cls");
					gotoxy(0, 0);

					FILE *file;

					// open file for reading
					file = fopen("Highscores.txt", "r");

					// print decrypted contents of highscore.txt
					if (file)
						{
							z = 0;
							d = 2;
							std:: cout << "1	-	";

							// characters are being decrypted here
							while ((i = fgetc(file) + encryptionlevel) - encryptionlevel != EOF)
								{
									putchar(i);
									Sleep(10);
									z++;
									if(z == 22)
										{
											std:: cout << "\n\n" << d << "	-	";
											d++;
											z = 0;
										}
								}
							// close file
							fclose(file);
						}
					std:: cout << "\n\nzur" << ue << "ck mit beliebiger Taste | [d] Highscores l" << oe << "schen\n";

					_cscanf("%c", &key);	// wait for button press, 'd' deletes the highscore file
					fflush(stdin);
					if(key == 100)
						{
							if( remove( "Highscores.txt" ) != 0 )
								perror( "\n\nFehler beim Loeschen" );
							else
								puts( "\n\nHighscores erfolgreich geloescht" );

							getch();
						}
				}
			/* end read of highscore */

			/* debug mode - variables will be saved per frame in debug.txt */
			// check if debug key has been pressed
			if(key == 0)
				{
					if(Debug == 0)
						{
							// remove potential old debug file
							remove( "Debug.txt" );
							Debug = 1;
						}
					else if(Debug == 1)
						{
							Debug = 0;
							// if debug is being deactivated, extensive option will also be deactivated
							edebug = 0;
						}
				}

			// activation of extensive Debug mode, arrays will be fully saved per frame
			if(key == 9)
				{
					if(edebug == 0)
						{
							edebug = 1;
						}
					else if(edebug == 1)
						{
							edebug = 0;
						}
				}

			/* end debug settings */

		}

	// reset loop variable
	loop = YES;
	system("cls");


	if(Debug == 1)
		{
			// create debug file
			debug = fopen("Debug.txt", "w");
		}

	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

	/* SNAKE - main application */

	while(loop == YES) // game loop
		{

			// draw points
			gotoxy(0,0);
			std:: cout << ol << "Punkte:" << points << horz;

			/* food generator start */

			if(food == NO)
				{
					// position generation
					xf = rand()%78 + 1;
					yf = rand()%23 + 1;

					/* double check */

					nsave = n;
					i = 0;
					while(i - 1 <= nsave + 1)
						{
							i++;

							// check for identical position of food with Snake
							if(xf == x[n + 1] && yf == y[n + 1])
								{
									// if the position matches the snake a new one will be generated
									xf = rand()%78 + 1;
									yf = rand()%23 + 1;
									i = 0;
									n = nsave;
								}

							n--;

						}
					n = nsave;

					/* double check end */

					/* fake food generation 1/10 chance */
					chance = rand()%10;

					if(chance == 0 && difficulty <= MEDIUM && fakefood == NO)
						{

							// generation of fakefood position
							xff = rand()%78 + 1;
							yff = rand()%23 + 1;

							nsave = n;
							i = 0;
							while(i - 1 <= nsave + 1)
								{
									i++;

									// check for intersection with snake or normal food
									if(xff == x[n + 1] && yff == y[n + 1] || xff == xf && yff == yf)
										{
											xff = rand()%78 + 1;
											yff = rand()%23 + 1;

											i = 0;
											n = nsave;
										}

									n--;
								}
							n = nsave;

							// final placing of the food
							gotoxy(xff, yff);
							std:: cout  << "+";

							fakefood = YES;
						}

					gotoxy(xf, yf);
					std:: cout  << "+";
					food = YES;
				}

			/* food generator end */

			// key press regocnition
			if(kbhit())
				{
					key = getch();
				}

			// pause menu
			if(key == ESC)
				{
					system("COLOR 8F");
					gotoxy(0, 0);
					std:: cout << ol <<"!pausiert! - Esc zum beenden  Punkte:" << points;

					_cscanf("%c", &key);
					fflush(stdin);

					// esc quits the game
					if(key == ESC)
						{
							gotoxy(35, 12);
							std:: cout << "Name: ";

							// generation of highscore file
							FILE *file;

							file = fopen("Highscores.txt", "a");

							// enter name
							fscanf(stdin, "%s", &name);

							// encryption of the name
							for(i = 0; i < 15; i++)
								name[i] = name[i] - encryptionlevel;

							// declare digits for points (max is 7 digits -> maximum possible points = 9,999,999)
							char c[7] = {255,255,255,255,255,255,255};

							sprintf(c, "%d", points);

							// encryption of the digits
							for(i = 0; i < 7; i++)
								{
									c[i] = c[i] - encryptionlevel;
								}

							// final writing of the .txt file
							fprintf(file, "%s%s", name, c);

							fclose(file);

							/* end highscore file */

							// if debug is activated, close debug file
							if(Debug == 1)
								fclose(debug);

							// quit
							return EXIT_SUCCESS;
						}

					// resume the game
					else
						{
							// revert colour changes and pause notification
							system("COLOR 0F");
							gotoxy(0, 0);
							for(z = 1; z < 79; z++)
								{
									std:: cout << horz;
								}
						}
				}

			// check if relevant keys have been pressed
			if(key == D && dir != LEFT)
				dir = RIGHT;

			if(key == A && dir != RIGHT)
				dir = LEFT;

			if(key == S && dir != UP)
				dir = DOWN;

			if(key == W  && dir != DOWN)
				dir = UP;

			if(key == X && speed == 0)	// X unlocks the speed limit, game will run as fast as the pc can process it
				{
					speed = 1;
					key = 0;
				}
			else if(key == X && speed == 1)
				{
					speed = 0;
					key = 0;
				}


			switch (dir)
				{
						// horizontal 'horP' & vertical 'verP' position calculation of movement
					case RIGHT:
						verP = verP + 1;
						if(verP == 24)verP = 1 ;;
						break;

					case LEFT :
						verP = verP - 1;
						if(verP == 0 )verP = 23;;
						break;

					case DOWN :
						horP = horP + 1;
						if(horP == 79)horP = 1 ;;
						break;

					case UP	  :
						horP = horP - 1;
						if(horP == 0 )horP = 78;;
						break;
				}

			/* food */

			// check if snake head intersects with food
			if(xf == horP && yf ==verP)
				{

					// '#' eating animation
					gotoxy(horP, verP);
					std:: cout << "#";
					Sleep(60);

					// snake growth based on difficulty
					if(difficulty != HARD)
						n++;
					// difficulty 'HARD' -> double snake growth
					else
						n = n + 2;

					// set food to eaten
					food = NO;

					// points for eating, increases with snake length
					points = points + 20 + ( n*1.5 );

					// if the "real" food has been eaten, fake food will be removed
					if(fakefood == 1)
						{
							// overwrite visual fake food
							gotoxy(xff, yff);
							std:: cout << blank;
							xff = 0;
							yff = 0;

							fakefood = NO;
						}
				}

			// if fakefood is being eaten, random decrease in points
			if(xff == horP && yff ==verP)
				{
					gotoxy(horP, verP);
					std:: cout << "#";
					Sleep(60);


					points = points - (n - 13)*2 - rand()%500;

					xff = 0;
					yff = 0;

					fakefood = NO;
				}

			/* check for snake head intersection with body */
			nsave = n;
			for(i = 0; i < nsave + 1; i++)
				{
					n--;
					if(horP == x[n + 1] && verP == y[n + 1])		// intersection results in game over
						{
							// change colour and top left arena lines
							system("COLOR 4F");
							gotoxy(0, 0);

							for(z = 0; z < 78; z++)
								{
									if(z == 0)
										std:: cout << ol;

									std:: cout << horz;
								}

							// print game over message and points
							gotoxy(35.5, 12);
							std:: cout << "GAME OVER";
							gotoxy(34, 15);
							std:: cout << "Punkte: " << points;
							Sleep(600);

							// entry of name and highscore file generation
							gotoxy(35, 17);
							std:: cout << "Name: ";

							FILE *file;

							file = fopen("Highscores.txt", "a");

							fscanf(stdin, "%s", &name);

							for(i = 0; i < 15; i++)
								name[i] = name[i] - encryptionlevel;

							char c[7] = {255,255,255,255,255,255,255};
							sprintf(c, "%d", points);

							for(i = 0; i < 7; i++)
								{
									c[i] = c[i]-encryptionlevel;
								}

							fprintf(file, "%s%s", name, c);

							fclose(file);

							// close debug file
							if(Debug == 1)
								fclose(debug);

							// quit
							return EXIT_SUCCESS;
						}
				}
			n = nsave;

			/* - */

			// save current head position to array
			x[0] = horP;
			y[0] = verP;

			// update snake position data in array, every value will be moved 1 up (value of x[1] -> x[2])
			for(i = 0; i <= n; i++)
				{
					x[n - i + 1] = x[n - i];
					y[n - i + 1] = y[n - i];
				}

			// removing snake tail for movement
			gotoxy(x[n + 1], y[n + 1]);
			std:: cout << blank;

			// draw next position of snake head
			gotoxy(horP, verP);
			std:: cout << Snake;

			// point limit for balancing
			if(points < 500*(n - 15)/2 && difficulty != EASY)
				points++;
			else if(points < 250*(n - 15)/2)
				{
					points++;
				}

			/* drawing of arena walls */
			for(i = b; i < 78; i++)
				{
					if(i == 0)
						{
							gotoxy(0, 0);
							std:: cout << ol;
						}
					gotoxy(i + 1, 0);
					std:: cout << horz;
					if(i == 0)
						{
							gotoxy(0, 24);
							std:: cout << ul;
						}
					gotoxy(i +1, 24);
					std:: cout << horz;
					if(i == 77)
						{
							gotoxy(79, 24);
							std:: cout << ur;
						}

				}

			for(i = b; i < 24; i++)
				{
					gotoxy(0, i);
					std:: cout << verz;
					gotoxy(79, i);
					std:: cout << verz;
					if(i == 23)
						{
							gotoxy(79, 0);
							std:: cout << orr;
						}
				}
			b = 79;

			/* end drawing of arena walls */

			// updating of debug file
			if(Debug == 1)
				{
					fprintf(debug, "\n\nFrame[%d]----------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n", fcounter);

					// save various varables per frame
					fprintf(debug, "direction: %d  ||  snake length: %d\n\n[Xposition: %d|Yposition: %d]\n\nfood: %d | foodX: %d/foodY: %d\n\nfakefood: %d | ffoodX: %d/ffoodY: %d\n\npressed Key: %c|%d\n\n", dir, n, horP, verP, food, xf, yf, fakefood, xff, yff, key, key);

					// extensive debug save snake position arrays
					if(edebug == 1)
						{
							for(i = 0; i < ARENA_WIDTH * ARENA_HEIGHT; i++)
								{
									fprintf(debug, "[x%d]:	%d	-|-	[y%d]:	%d\n", i, x[i], i, y[i]);
								}
						}
					key = 0;	// reset pressed key to avoid documentation of unnecessary key presses

					// increase frame counter
					fcounter++;
				}

			// increase frame counter
			fcounter++;

			if(speed == 0)						// boost button may disable game cycle delay
				usleep( difficulty * 1000);			// Wait for next game cycle, difficulty affects game speed
		}

	/* end game loop */

	// potential breakout of the game loop results in error message and creation of debug file
	if(Debug == 0)
		{
			debug = fopen("Debug.txt", "w");
			fprintf(debug, "\n\n!Game loop fail!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");

			fprintf(debug, "direction: %d  ||  snake length: %d\n\n[Xposition: %d|Yposition: %d]\n\nfood: %d | foodX: %d/foodY: %d\n\nfakefood: %d | ffoodX: %d/ffoodY: %d\n\npressed Key: %c|%d\n\n", dir, n, horP, verP, food, xf, yf, fakefood, xff, yff, key, key);

			for(i = 0; i < ARENA_WIDTH * ARENA_HEIGHT; i++)
				{
					fprintf(debug, "[x%d]:	%d	-|-	[y%d]:	%d\n", i, x[i], i, y[i]);
				}

			fclose(debug);
		}

	system("cls");
	gotoxy(0, 0);
	std:: cout << "Whoops, that was't supposed to happen. Please send the Debug.txt to the developer";

	return EXIT_FAILURE;
}
