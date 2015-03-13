#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>

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
	
	
	int points, i, d, z = 0, chance, color = 0, difficulty, b = 0, loop = 1 , key, phan = 0, check;
	
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
	std:: cout << "MauProductions";
	
	for(i = 0; i <= 21; i++)
	{
		switch(color)
		{
			case 0:system("COLOR 0"); ;break;
			case 1:system("COLOR 1"); ;break;
			case 2:system("COLOR 2"); ;break;
			case 3:system("COLOR 3"); ;break;
			case 4:system("COLOR 4"); ;break;
			case 5:system("COLOR 5"); ;break;
			case 6:system("COLOR 6"); ;break;
			case 7:system("COLOR 7"); ;break;
			case 8:system("COLOR 8"); ;break;
			case 9:system("COLOR 9"); ;break;
			default:system("COLOR F");;
		}
		Sleep(70);
		if(color < 10 && i <10)
		{
			color++;
		}
		else
		{
			color--;
		}
	}
	
	Sleep(800);
	
	while(loop == 1)
	{
		system("cls");
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
		gotoxy(37, 7);
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
			
			z = n;
			i = 0;
			while(i - 1 <= z)
			{
				i++;
				
				// check for identical position of food with Snake
				if(xf == x[phan + n] && yf == y[phan + n])
				{
					xf = rand()%78 + 1;
					yf = rand()%23 + 1;
					
					i = 0;
					n = z;
				}			// if the position matches the snake a new one will be generated
				
				n--;
			}
			n = z;
			
			/* double check end */
			/* fake food generation 1/10 chance */
			
			chance = rand()%10;
			
			if(chance == 0 && difficulty <= MEDIUM && fakefood == NO)
			{
				
				xff = rand()%78 + 1;
				yff = rand()%23 + 1;
				
				z = n;
				i = 0;
				while(i - 1 <= z)
				{
					i++;
					
					if(xff == x[phan + n] && yff == y[phan + n] || xff == xf && yff == yf)
					{
						xff = rand()%rand()%78 + 1;
						yff = rand()%rand()%23 + 1;
						
						i = 0;
						n = z;
					}
					
					n--;
				}
				n = z;
				
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
			while(loop == YES)
			{
				
 				_cscanf("%c", &key);
 				
				if(key == ESC)
				return EXIT_SUCCESS;
				
				else
				{
  				 	system("COLOR 0F");
  					loop = NO;
  					gotoxy(0, 0);
					for(z = 1; z < 79; z++)
 		  		  	{
		  		  		std:: cout << horz;
					}
	  			}
  			}
  			loop = YES;
		}
		
		// check if relevant keys have been pressed
		if(key == D && dir != 2)
			dir = RIGHT;
			
		if(key == A && dir != 1)				// WASD change direction, != prevents the snake of going into itself (if going left, you cant go right)
			dir = LEFT;
			
		if(key == S && dir != 4)
			dir = DOWN;
			
		if(key == W && dir != 3)
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
			if(difficulty != HARD)
			n++;
			else
			{
			n = n + 2;
			}
			food = NO;	// set food to eaten
			
			// points for eating
			points = points + 20 + n;
			
			// if the "real" food has been eaten, fake food will be removed
			if(fakefood == YES)
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
			
			points = points - (n - 13)*2 - rand()%500;
			
			xff = 0;
			yff = 0;
			
			fakefood = NO;
		}
		
		/* check for snake head intersection with body */
		
		z = n;
		for(i = 0; i < z; i++)
		{
			
			n--;
			if(horP == x[phan + n] && verP == y[phan + n])		// intersection results in game over
			{
				system("COLOR 4F");
				gotoxy(0, 0);
				for(z = 0; z < 78; z++)
	  			{
	  				if(z == 0)
	  				std:: cout << ol;
	  				
		  		  	std:: cout << horz;
				}
				gotoxy(36, 12);
				std:: cout << "GAME OVER";
				gotoxy(35, 15);
				std:: cout << "Punkte: " << points;
				Sleep(600);
				getch();
				return EXIT_SUCCESS;
			}
		}
		n = z;
		
		/* - */
		
		// save current head position to array
		x[phan + n] = horP;
		y[phan + n] = verP;
		
		// removing snakes tail end
		gotoxy(x[phan], y[phan]);
		std:: cout << blank;
		
		phan = phan + 1;
		
		// draw next position of snake head
		gotoxy(horP, verP);
		std:: cout << Snake;
		
		
		if(points < 500*(n - 15)/2 && difficulty != EASY)			// point limit for balancing
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
		
		Sleep(difficulty);			// Wait for next game cycle, difficulty affects game speed
	}
	
	return EXIT_FAILURE;
}
