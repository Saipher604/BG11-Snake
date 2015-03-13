#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <unistd.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */


//Defines gotoxy() for ANSI C compilers.
void gotoxy(short x, short y) {
COORD pos = {x, y};
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int main(int argc, char** argv) {
	
	// food variables
	int  xf, yf, food = 0,  xff, yff, fakefood = 0;
	
	// Snake variables movement direction, Position, length
	int  dir = 4, x[10000], y[10000],  horP = 40, verP = 12, n = 16;
	
	
	int points, i, d, z = 0, chance, color = 0, difficulty, b = 0, loop = 1, key, phan = 0, check, nsave;
	
	
	// difficulty options
	const int EASY = 100, MEDIUM = 80, HARD = 65;
	// constants for Keys for better readability
	const int UP = 4, DOWN = 3, LEFT = 2, RIGHT = 1, W = 97,A = 119, S = 100, D = 115, ESC = 27;
	
	const int NO = 0, YES = 1;
	
	
	char Snake = 219, blank = 255, ae /*ä*/ = 132;
	
	// ASCII-code for Arena lines
	char horz = 196, verz = 179, ol = 218, orr = 191, ul = 192, ur = 217;
	
	
	srand(time(NULL));
	
	gotoxy(34, 12);
	std:: cout << "Multiplayer - ALPHA";
	
	
	Sleep(600);
	
	while(loop == YES)
	{
		system("cls");
		gotoxy(3, 19);
		std:: cout << "Steuerung: W - hoch 56";
		gotoxy(14, 20);
		std:: cout << "S - runter 53";
		gotoxy(14, 21);
		std:: cout << "A - links 52";
		gotoxy(14, 22);
		std:: cout << "D - rechts 54";
		gotoxy(12, 23);
		std:: cout << "Esc - Pause";
		std:: cout << "SNAKE";
		
		gotoxy(23, 12);
		std:: cout << "Schwierigkeitsgrad ausw" << ae << "hlen [1|2|3] ";
		scanf("%d", &z);
		fflush(stdin);
		
		if(z == 1)
		difficulty = EASY;
		if(z == 2)
		difficulty = MEDIUM;
		if(z == 3)
		difficulty = HARD;
 		if(z == 1 || z == 2 || z == 3)
	 	 	loop = NO;
	}
	
	loop = YES;
	system("cls");
	
	/* SNAKE - main application */
	
	while(loop == YES)
	{
		gotoxy(0,0);
		std:: cout << "Punkte:" << points << horz;
		
		/* food generator start */
		
		if(food == NO)
		{
			xf = rand()%78 + 1;		// position generation
			yf = rand()%23 + 1;
			
			/* double check */
			
			nsave = n;
			i = 0;
			while(i - 1 <= nsave || i - 1 <= n2save)
			{
				i++;
				
				// check for identical position of food with Snake
				if(xf == x[phan + n] && yf == y[phan + n])
				{
					xf = rand()%78 + 1;
					yf = rand()%23 + 1;
					i = 0;
					n = nsave;
				}
									// if the position matches the snake a new one will be generated
				n--;
				
			}
			n = nsave;
			
			/* double check end */
			/* fake food generation 1/10 chance */
			
			chance = rand()%10;
			
			if(chance == 0 && difficulty <= 80 && fakefood == NO)
			{
				
				xff = rand()%78 + 1;
				yff = rand()%23 + 1;
				
				nsave = n;
				i = 0;
				while(i - 1 <= nsave)
				{
					i++;
					
					if(xff == x[phan + n] && yff == y[phan + n] || xff == xf && yff == yf)
					{
						xff = rand()%rand()%78 + 1;
						yff = rand()%rand()%23 + 1;
						
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
				if(key == ESC)
				return EXIT_SUCCESS;
				else
				{
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
			
		if(key == 97  && dir != DOWN)
	 		dir = UP;
	 		
	 		
		switch (dir)
		{
			case RIGHT:verP = verP + 1; if(verP == 24)verP = 1 ;;break;			// horizontal 'horP' & vertical 'verP' position calculation
			case LEFT :verP = verP - 1; if(verP == 0 )verP = 23;;break;
			case DOWN :horP = horP + 1; if(horP == 79)horP = 1 ;;break;
			case UP	  :horP = horP - 1; if(horP == 0 )horP = 78;;break;
		}
		
		/* food */
		
		// check if snake head has the same position as food
		if(xf == horP && yf ==verP)
		{
			
			// '#' eating animation
			gotoxy(horP, verP);
			std:: cout << "#";
			Sleep(60);
			
			// snake growth based on difficulty
			if(difficulty != 60)
				n++;
				
			else
				n = n + 2;
			
			food = NO;	// set food to eaten
			
			// points for eating
			points = points + 20 + n;
			
			// if the "real" food has been eaten, fake food will be removed
			if(fakefood == 1)
			{
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
			for(i = 0; i < difficulty; i++);
			
			xff = 0;
			yff = 0;
			
			fakefood = NO;
		}
		
		/* check for snake head intersection with body */
		
		nsave = n;
		for(i = 0; i < z; i++)
		{
			n--;
			if(horP == x[phan + n] && verP == y[phan + n])				// intersection results in game over
			{
				system("COLOR 4F");
				gotoxy(0, 0);
				for(z = 0; z < 78; z++)
	  			{
	  				if(z == 0)
	  				std:: cout << ol;
	  				
		  		  	std:: cout << horz;
				}
				gotoxy(15, 12);
				std:: cout << "GAME OVER";
				gotoxy(35, 15);
				std:: cout << "Punkte: " << points;
				Sleep(600);
				getch();
				return EXIT_SUCCESS;
			}
		}
		n = nsave;
		
		/* - */
		
		// save current head position to array
		x[phan + n] = horP;
		y[phan + n] = verP;
		
		// removing snakes tail for movement
		gotoxy(x[phan], y[phan]);
		std:: cout << blank;
		
		phan = phan + 1;
		
		// draw next position of snake head
		gotoxy(horP, verP);
		std:: cout << Snake;
		
		
		if(points < 500*(n - 15)/2 && difficulty != 100)			// point limit for balancing
		points++;
		else if(points < 250*(n - 15)/2)
		{
			points++;
		}
		
		/* drawing of map walls */
		
		for(i = b; i < 80; i++)
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
			if(i == 79)
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
		b = 81;
		
		/* - */
		
		usleep(difficulty*1000);			// Wait for next game cycle, difficulty affects game speed
	}
	
	return EXIT_FAILURE;
}
