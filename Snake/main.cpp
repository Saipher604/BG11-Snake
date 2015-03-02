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
	
 	
	
	int points, i, z, xb, yb, zufall, color = 0, difficulty, b = 0, n = 16, food = 0, restart , x, y, x2[10000], y2[10000], Taste, hor = 40, ver = 12, dir = 4, phan = 0, check;
	
	char Snake = 219, blank = 255, a = 132, horz = 196, verz = 179, ol = 218, orr = 191, ul = 192, ur = 217;
	
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
		for(z = 0; z < 40000000; z++);
		if(color < 10 && i <10)
		{
			color++;
		}
		else
		{
			color--;
		}
	}
	
	for(z = 0; z < 300000000; z++);
	
	for(restart = 0; restart < 1; restart++)
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
		std:: cout << "Schwierigkeitsgrad ausw" << a << "hlen [1|2|3] ";
		scanf("%d", &z);
		fflush(stdin);
		
		if(z == 1)
		difficulty = 50000000;
		if(z == 2)
		difficulty = 40000000;
		if(z == 3)
		difficulty = 30000000;
 		if(z != 1 && z != 2 && z != 3)
	 	{
	 	 	restart = -1;
		}
	}
	
	system("cls");
	
	/* SNAKE - Hauptprogram */
	
	for(restart = 1; restart == 1;)
	{
		gotoxy(0,0);
		std:: cout << "Punkte:" << points << horz;
		
		/* food generator start */
		
		if(food == 0)
		{
			x = rand()%78 + 1;
			y = rand()%23 + 1;
			
			z = n;
			for(i = 0; i <= z; i++)
			{
				
		  		for(check = 0; check < 1;)
		  		{
					if(x == x2[phan + n] && y == y2[phan + n])
					{
						x = rand()%78 + 1;
						y = rand()%23 + 1;
						check = 0;
					}
					else
					 {
					 	check = 2;
					 }
			/*		if(x != x2[phan + n] && y != y2[phan + n])
					{
					check = 2;
					}
					else
					{
						x = x2[phan + n];
						y = y2[phan + n];
					 	check = 0;
					}*/
				}
				n--;
			}
			n = z;
			
			zufall = rand()%10;
			
			if(zufall == 0 && difficulty <= 40000000)
			{
				xb = rand()%78 + 1;
				yb = rand()%23 + 1;
				
				z = n;
				for(i = 0; i <= z; i++)
				{
					
		  			for(check = 0; check < 1;)
		  			{
						if(xb == x2[phan + n] && yb == y2[phan + n] || xb == x && yb == y)
						{
							xb = rand()%rand()%78 + 1;
							yb = rand()%rand()%23 + 1;
						}
						if(xb != x2[phan + n] && yb != y2[phan + n] && xb != x && yb != y)
			  			{
					 		check = 2;
						}
						else
						{
							xb = x2[phan + n];
							yb = y2[phan + n];
							check = 0;
						}
					}
					n--;
				}
				n = z;
				
				gotoxy(xb, yb);
				std:: cout  << "+";
			}
			
			gotoxy(x, y);
			std:: cout  << "+";
			food = 1;
		}
		
		/* food generator end */
		
		if(kbhit())
		{
			Taste = getch();
		}
		
		if(Taste == 27)
		{
			system("COLOR 8F");
			gotoxy(0, 0);
			std:: cout << ol <<"!pausiert! - Esc zum beenden  Punkte:" << points;
			for(i = 1;i == 1;)
			{
					
 				_cscanf("%c", &Taste);
				if(Taste == 27)
				return EXIT_SUCCESS;
				else
				{
  				 	system("COLOR 0F");
  					i = 0;
  					gotoxy(0, 0);
					for(z = 1; z < 79; z++)
 		  		  	{
		  		  		std:: cout << horz;
					}
	  			}
  			}
		}
		
		if(Taste == 115 && dir != 2)
		{
			dir = 1;
		}
		if(Taste == 119 && dir != 1)
		{
			dir = 2;
		}
		if(Taste == 100 && dir != 4)
		{
			dir = 3;
		}
		if(Taste == 97  && dir != 3)
		{
	 		dir = 4;
		}
		
		
		switch (dir)
		{
			case 1:ver = ver + 1; if(ver == 24)ver = 1 ;;break;
			case 2:ver = ver - 1; if(ver == 0 )ver = 23;;break;
			case 3:hor = hor + 1; if(hor == 79)hor = 1 ;;break;
			case 4:hor = hor - 1; if(hor == 0 )hor = 78;;break;
		}
		
		
		if(x == hor && y ==ver)
		{
			gotoxy(hor, ver);
			std:: cout << "#";
			for(i = 0; i < difficulty; i++);
			if(difficulty != 30000000)
			n++;
			else
			{
			n = n + 2;
			}
			food = 0;
			
			points = points + 20 + n;
			
			if(xb != 0 && yb != 0)
			{
		 		gotoxy(xb, yb);
				std:: cout << blank;
		  		xb = 0;
	   			yb = 0;
			}
		}
		if(xb == hor && yb ==ver)
		{
			gotoxy(hor, ver);
			std:: cout << "#";
			for(i = 0; i < difficulty; i++);
			
			points = points - (n - 13)*2 - rand()%500;
			
			xb = 0;
			yb = 0;
		}
		
		z = n;
		for(i = 0; i < z; i++)
		{
			
			n--;
			if(hor == x2[phan + n] && ver == y2[phan + n])
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
				for(i = 0; i < 500000000; i++);
				getch();
				return EXIT_SUCCESS;
			}
		}
		n = z;
		
		x2[phan + n] = hor;
		y2[phan + n] = ver;
		
		gotoxy(x2[phan], y2[phan]);
		std:: cout << blank;
		
		phan = phan + 1;
		
		gotoxy(hor, ver);
		std:: cout << Snake;
		
		if(points < 500*(n - 15)/2 && difficulty != 50000000)
		points++;
		else if(points < 250*(n - 15)/2)
		{
			points++;
		}
		
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
		
		for(i = 0; i < difficulty; i++);
	}
	
	return EXIT_FAILURE;
}
