#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <unistd.h>


//set arena dimensions here, x78 y23 are the values of the usual console window minus the arena walls
#define ARENA_WIDTH 78
#define ARENA_HEIGHT 23

#define NAME_LENGTH 30

#define EASY 100
#define MEDIUM 80
#define HARD 70

//Defines gotoxy() for ANSI C compilers.
void gotoxy(short x, short y)
{
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//structure for player variables. unsigned since there will be no negative values in these.
typedef struct player
{
    //buffer for collision detection
    unsigned int xbuffer[ARENA_WIDTH * ARENA_HEIGHT];
    unsigned int ybuffer[ARENA_WIDTH * ARENA_HEIGHT];

    //some of these are chars for minimizing memory usage (not that it matters)
    unsigned char dir;

    //horizontal and vertical position of the head, those values are then moved upwards the buffer
    unsigned char horzP;
    unsigned char vertP;

    //length of the snake, raises with eating. The buffer is used for counting down the collision detection buffer I might replace this method of detecting
    unsigned int length;
    unsigned int length_buf;
};

typedef struct food
{
    unsigned char xPos;
    unsigned char yPos;

    bool spawned;
};


void init_gamestate(struct player *player1, struct food *realfood, struct food *fakefood);
void generate_food(struct player *player1, struct food *realfood, struct food *fakefood, int difficulty);


int main(int argc, char** argv)
{
    // food variables
//    int  xf, yf, food = 0,  xff, yff, fakefood = 0;

    // various variables for simple counting, points, difficulty
    int points = 0, fcounter = 0, d, i, z = 0, chance, difficulty, key;


    int Debug = 0, ex_debug = 0;
    FILE *debug;

    // difficulty options
//   char EASY = 100, MEDIUM = 80, HARD = 70;

    // constants for Keys and movement direction
    const unsigned char UP = 4, DOWN = 3, LEFT = 2, RIGHT = 1, W = 97,A = 119, S = 100, D = 115, ESC = 27, X = 120;

    char encryptionlevel = -55;

    char Snake = 219, blank = 255, ae /*ä*/ = 132, ue /*ü*/ = 129, oe /*ö*/ = 148;

    // character arrays for highscore names
    char name[NAME_LENGTH];

    for(i = 0; i < NAME_LENGTH; i++)
    {
        name[i] = 255;
    }

    // ASCII-code for Arena lines
    char horz = 196, verz = 179, ol = 218, orr = 191, ul = 192, ur = 217;

    //various yes or no variables. booster speeds up the game, loop controls the game loop
    bool booster = false, loop = true, arena_drawn = false;


    struct player player1;
    struct food realfood;
    struct food fakefood;

    // randomization for food spawner
    srand(time(NULL));

    // play simple intro
    gotoxy(38, 12);
    std:: cout << "Snake";

    Sleep(600);

    while(loop == true)
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
        if(Debug == false)
        {
            gotoxy(23, 14);
            std:: cout << "[0] Debug [AUS]";
        }
        else
        {
            gotoxy(23, 14);
            std:: cout << "[0] Debug [AN]";

            if(ex_debug == false)
            {
                gotoxy(23, 15);
                std:: cout << "[9] exstensive Debug [AUS]";
            }

            else if(ex_debug == true)
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
            loop = false;

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
                    if(z == 7 + NAME_LENGTH)
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
            if(Debug == false)
            {
                // remove potential old debug file
                remove( "Debug.txt" );
                Debug = true;
            }
            else if(Debug == true)
            {
                Debug = false;
                // if debug is being deactivated, extensive option will also be deactivated
                ex_debug = false;
            }
        }

        // activation of extensive Debug mode, arrays will be fully saved per frame
        if(key == 9)
        {
            if(ex_debug == false)
            {
                ex_debug = true;
            }
            else if(ex_debug == true)
            {
                ex_debug = false;
            }
        }

        /* end debug settings */

    }

    // reset loop variable
    loop = true;
    system("cls");


    if(Debug == true)
    {
        // create debug file
        debug = fopen("Debug.txt", "w");
    }

    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    /* SNAKE - main application */

    //initialize player and food variables and set the variables to start position
    init_gamestate(&player1, &realfood, &fakefood);

    while(loop == true) // game loop
    {

        // draw points
        gotoxy(0,0);
        std:: cout << ol << "Punkte:" << points << horz;

        /* food generator start */

        generate_food(&player1, &realfood, &fakefood, difficulty);

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
                for(i = 0; i < NAME_LENGTH; i++)
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
                if(Debug == true)
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
        if(key == D && player1.dir != LEFT)
            player1.dir = RIGHT;

        if(key == A && player1.dir != RIGHT)
            player1.dir = LEFT;

        if(key == S && player1.dir != UP)
            player1.dir = DOWN;

        if(key == W  && player1.dir != DOWN)
            player1.dir = UP;

        // X unlocks the speed limit, game will run as fast as the pc can process it
        if(key == X && booster == false)
        {
            booster = true;

            //key is being reset to avoid reactivation
            key = 0;
        }
        else if(key == X && booster == true)
        {
            booster = false;
            key = 0;
        }


        switch (player1.dir)
        {
        // horizontal 'player1.horzP' & vertical 'player1.vertP' position calculation of movement
        // if the player hits the wall he will reoccur on the opposite side of the map
        case RIGHT:
            player1.vertP = player1.vertP + 1;
            if(player1.vertP == 24)player1.vertP = 1 ;;
            break;

        case LEFT :
            player1.vertP = player1.vertP - 1;
            if(player1.vertP == 0 )player1.vertP = 23;;
            break;

        case DOWN :
            player1.horzP = player1.horzP + 1;
            if(player1.horzP == 79)player1.horzP = 1 ;;
            break;

        case UP	  :
            player1.horzP = player1.horzP - 1;
            if(player1.horzP == 0 )player1.horzP = 78;;
            break;
        }

        /* food */

        // check if snake head intersects with food
        if(realfood.xPos == player1.horzP && realfood.yPos == player1.vertP)
        {

            // '#' eating animation
            gotoxy(player1.horzP, player1.vertP);
            std:: cout << "#";
            Sleep(60);

            // snake growth based on difficulty
            if(difficulty != HARD)
                player1.length++;
            // difficulty 'HARD' -> double snake growth
            else
            {
                player1.length = player1.length + 2;
            }
            realfood.xPos = NULL;
            realfood.yPos = NULL;

            // set food to eaten
            realfood.spawned = false;

            // points for eating, increases with snake length
            points = points + 20 + ( player1.length*1.5 );

            // if the "real" food has been eaten, fake food will be removed
            if(fakefood.spawned == true)
            {
                // overwrite visual fake food
                gotoxy(fakefood.xPos, fakefood.yPos);
                std:: cout << blank;
                fakefood.xPos = NULL;
                fakefood.yPos = NULL;

                fakefood.spawned = false;
            }
        }

        // if fakefood is being eaten, random decrease in points
        if(fakefood.xPos == player1.horzP && fakefood.yPos ==player1.vertP)
        {
            gotoxy(player1.horzP, player1.vertP);
            std:: cout << "#";
            Sleep(60);


            points = points - (player1.length - 13)*2 - rand()%500;

            fakefood.xPos = NULL;
            fakefood.yPos = NULL;

            fakefood.spawned = false;
        }

        /* check for snake head intersection with body */
        //similar procedure as the double check function for food
        //runs down the Snake buffer and check each value
        player1.length_buf = player1.length;
        for(i = 0; i < player1.length_buf + 1; i++)
        {
            player1.length--;

            // intersection results in game over
            if(player1.horzP == player1.xbuffer[player1.length + 1] && player1.vertP == player1.ybuffer[player1.length + 1])
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

                for(i = 0; i < NAME_LENGTH; i++)
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
                if(Debug == true)
                    fclose(debug);

                // quit
                return EXIT_SUCCESS;
            }
        }
        player1.length = player1.length_buf;

        /* - */

        // save current head position to array
        player1.xbuffer[0] = player1.horzP;
        player1.ybuffer[0] = player1.vertP;

        // update snake position data in buffer, every value will be moved 1 up (value of player1.xbuffer[1] -> player1.xbuffer[2])
        for(i = 0; i <= player1.length; i++)
        {
            player1.xbuffer[player1.length - i + 1] = player1.xbuffer[player1.length - i];
            player1.ybuffer[player1.length - i + 1] = player1.ybuffer[player1.length - i];
        }

        // removing snake tail for graphical movement
        gotoxy(player1.xbuffer[player1.length + 1], player1.ybuffer[player1.length + 1]);
        std:: cout << blank;

        // draw next position of snake head
        gotoxy(player1.horzP, player1.vertP);
        std:: cout << Snake;

        // point limit for balancing
        if(points < 500*(player1.length - 15)/2 && difficulty != EASY)
            points++;
        else if(points < 250*(player1.length - 15)/2)
        {
            points++;
        }

        /* drawing of arena walls */
        if(arena_drawn == 0)
        {
            for(i = 0; i < 78; i++)
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

            for(i = 0; i < 24; i++)
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
            arena_drawn = 1;
        }

        /* end drawing of arena walls */

        // updating of debug file
        if(Debug == true)
        {
            fprintf(debug, "\n\nFrame[%d]----------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n", fcounter);

            // save various varables per frame
            fprintf(debug, "direction: %d  ||  snake length: %d\n\n[Xposition: %d|Yposition: %d]\n\nfood: %d | foodX: %d/foodY: %d\n\nfakefood: %d | ffoodX: %d/ffoodY: %d\n\npressed Key: %c|%d\n\n", player1.dir, player1.length, player1.horzP, player1.vertP, realfood.spawned, realfood.xPos, realfood.yPos, fakefood.spawned, fakefood.xPos, fakefood.yPos, key, key);

            // extensive debug save snake position arrays
            if(ex_debug == true)
            {
                for(i = 0; i < ARENA_WIDTH * ARENA_HEIGHT; i++)
                {
                    fprintf(debug, "[x%d]:	%d	-|-	[y%d]:	%d\n", i, player1.xbuffer[i], i, player1.ybuffer[i]);
                }
            }
            key = 0;	// reset pressed key to avoid documentation of unnecessary key presses

        }

        // increase frame counter
        fcounter++;

        //boost button may disable game cycle delay
        if(booster == false)
            usleep( difficulty * 1000);			// Wait for next game cycle, difficulty affects game speed
    }

    /* end game loop */

    //potential breakout of the game loop results in error message and creation of debug file. *should* be impossible
    if(Debug == false)
    {
        debug = fopen("Debug.txt", "w");
        fprintf(debug, "\n\n!Game loop fail!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");

        fprintf(debug, "direction: %d  ||  snake length: %d\n\n[Xposition: %d|Yposition: %d]\n\nfood: %d | foodX: %d/foodY: %d\n\nfakefood: %d | ffoodX: %d/ffoodY: %d\n\npressed Key: %c|%d\n\n", player1.dir, player1.length, player1.horzP, player1.vertP, realfood.spawned, realfood.xPos, realfood.yPos, fakefood.spawned, fakefood.xPos, fakefood.yPos, key, key);

        for(i = 0; i < ARENA_WIDTH * ARENA_HEIGHT; i++)
        {
            fprintf(debug, "[x%d]:	%d	-|-	[y%d]:	%d\n", i, player1.xbuffer[i], i, player1.ybuffer[i]);
        }

        fclose(debug);
    }

    system("cls");
    gotoxy(0, 0);
    std:: cout << "Whoops, that was't supposed to happen. Please send the Debug.txt to the developer";

    return EXIT_FAILURE;
}


//set starting values for the player and food
void init_gamestate(struct player *player1, struct food *realfood, struct food *fakefood)
{
    int i = 0;

    //overwrite position arrays completely with 0 to avoid potential problems, these arrays are required for collision detection and have the size of the arena
    for(i = 0; i < (ARENA_WIDTH * ARENA_HEIGHT); i++)
    {
        player1 -> xbuffer[i] = 0;
        player1 -> ybuffer[i] = 0;
    }

    player1 -> dir    = 4;

    player1 -> horzP  = 40;
    player1 -> vertP  = 12;

    player1 -> length = 16;


    realfood -> spawned = false;
    fakefood -> spawned = false;
}

void generate_food(struct player *player1, struct food *realfood, struct food *fakefood, int difficulty)
{
    int i = 0;
    int chance;

    //check if food has spawned
    if(realfood -> spawned == false)
    {
        // position generation if the food position matches the snake it will be generated again
        for(i = 0; i <= player1 -> length; i++)
        {
            if(realfood -> xPos == player1 -> xbuffer[i] && realfood -> yPos == player1 -> ybuffer[i])
            {
                i = 0;
            }
            realfood -> xPos = rand()%78 + 1;
            realfood -> yPos = rand()%23 + 1;
        }

        /* fake food generation 1/10 chance */
        chance = rand()%10;

        if(chance == 0/* && difficulty <= MEDIUM */&& fakefood -> spawned == false)
        {
            // generation of fakefood position
            for(i = 0; i <= player1 -> length; i++)
            {
                if(fakefood -> xPos == player1 -> xbuffer[i] && fakefood -> yPos == player1 -> ybuffer[i] || fakefood -> xPos == realfood -> xPos && fakefood -> yPos == realfood -> yPos)
                {
                    i = 0;
                }
                fakefood -> xPos = rand()%78 + 1;
                fakefood -> yPos = rand()%23 + 1;
            }

            // final placing of the food
            gotoxy(fakefood -> xPos, fakefood -> yPos);
            std:: cout  << "+";

            fakefood -> spawned = true;
        }

        gotoxy(realfood -> xPos, realfood -> yPos);
        std:: cout  << "+";
        realfood -> spawned = true;
    }
}
