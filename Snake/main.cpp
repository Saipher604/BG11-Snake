#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#define BUFFER 16


//Defines gotoxy() for ANSI C compilers.
void gotoxy(short x, short y) {
COORD pos = {x, y};
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int main(int argc, char** argv) {
	
	int  xf, yf, food = 0,  xff, yff, fakefood = 0,  x[10000], y[10000],  horP = 40, verP = 12, points, i, d, z = 0, chance, color = 0, difficulty, b = 0, n = 16, loop , key[BUFFER], dir = 4, phan = 0, check;
	int  dir2 = 3, x2[10000], y2[10000], n2 = 16, horP2 = 40, verP2 = 7, esc;
	
	char Snake2 = 177, Snake = 219, blank = 255, a = 132, horz = 196, verz = 179, ol = 218, orr = 191, ul = 192, ur = 217;
	
	srand(time(NULL));
	
	gotoxy(34, 12);
	std:: cout << "Multiplayer - ALPHA";
	
	
	for(z = 0; z < 300000000; z++);
	
	for(loop = 0; loop < 1; loop++)
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
		gotoxy(65, 19);
		std:: cout << "8 - hoch";
		gotoxy(65, 20);
		std:: cout << "5 - runter";
		gotoxy(65, 21);
		std:: cout << "4 - links";
		gotoxy(65, 22);
		std:: cout << "5 - recht";
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
	 	 	loop = -1;
		}
	}
	
	system("cls");
	
	/* SNAKE - main application */
	
	for(loop = 1; loop == 1;)
	{
		gotoxy(0,0);
		std:: cout << "Punkte:" << points << horz;
		
		/* food generator start */
		
		if(food == 0)
		{
			xf = rand()%78 + 1;									// position generation
			yf = rand()%23 + 1;
			
			/* double check */
			
			z = n;
			i = 0;
			while(i <= z)
			{
				
				check = 0;
		  		while(check < 1)						// check for same positon with snake body
		  		{
					if(xf == x[phan + n] && yf == y[phan + n] || xf == x2[phan + n2] && yf == y2[phan + n2])
					{
						xf = rand()%78 + 1;
						yf = rand()%23 + 1;
						check = 0;
						i = 0;
						n = z;
					}
					else										// if the position matches the snake a new one will be generated
					 {
					 	check = 2;
					 }
					 i++;
				}
				n--;
			}
			n = z;
			
			/* double check end */
			/* fake food generation 1/10 chance */
			
			chance = rand()%10;
			
			if(chance == 0 && difficulty <= 40000000 && fakefood == 0)
			{
				
				xff = rand()%78 + 1;
				yff = rand()%23 + 1;
				
				z = n;
				i = 0;
				while(i <= z)
				{
					check = 0;
		  			while(check < 1)
		  			{
						if(xff == x[phan + n] && yff == y[phan + n] || xff == xf && yff == yf || xff == x2[phan + n2] && yff == y2[phan + n2])
						{
							xff = rand()%rand()%78 + 1;
							yff = rand()%rand()%23 + 1;
						}
						if(xff != x[phan + n] && yff != y[phan + n] && xff != xf && yff != yf && xff != x2[phan + n2] && yff != y2[phan + n2])
			  			{
					 		check = 2;
						}
						else
						{
							xff = x[phan + n];
							yff = y[phan + n];
							check = 0;
							i = 0;
							n = z;
						}
						i++;
					}
					n--;
				}
				n = z;
				
				gotoxy(xff, yff);							// final placing of the food
				std:: cout  << "+";
				fakefood = 1;
			}
			
			gotoxy(xf, yf);
			std:: cout  << "+";
			food = 1;
		}
		
		/* food generator end */
		z++;
		if(z == BUFFER)
		z = 0;
		if(kbhit())
		{
			key[z] = esc = getch();							// key press regocnition
		}
	 	
	 	
		if(esc == 27)								// pause menu
		{
			system("COLOR 8F");
			gotoxy(0, 0);
			std:: cout << ol <<"!pausiert! - Esc zum beenden  Punkte:" << points;
 				_cscanf("%c", &esc);
 				fflush(stdin);
				if(esc == 27)
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
		
		
		for(i = 0; i <BUFFER; i++)
		{
			if(key[z] == 115 || key[z] == 119 || key[z] == 100 || key[z] == 97)
			{
				d = 0;
				while(d < 1)
				{
					
					if(key[z] == 115 && dir != 2)
					{
						dir = 1;
						d = 1;
					}
					if(key[z] == 119 && dir != 1)							// WASD change direction, != prevents the snake of going into itself (if going left, you cant go right)
					{
						dir = 2;
						d = 1;
					}
					if(key[z] == 100 && dir != 4)
					{
						dir = 3;
						d = 1;
					}
					if(key[z] == 97  && dir != 3)
					{
	 					dir = 4;
				 		d = 1;
					}
					else
					{
						d = 1;
					}
				}
			}
			else if(key[z] == 56 || key[z] == 53 || key[z] == 52 || key[z] == 54)
			{
				d = 0;
				while(d < 1)
				{
	 				if(key[z] == 53 && dir2 != 2)
					{
						dir2 = 1;
						d = 1;
					}
					if(key[z] == 56 && dir2 != 1)
					{
						dir2 = 2;
						d = 1;
					}
					if(key[z] == 54 && dir2 != 4)
					{
				 		dir2 = 3;
						d = 1;
					}
					if(key[z] == 52 && dir2 != 3)
					{
						dir2 = 4;
						d = 1;
					}
					else
					{
						d = 1;
					}
				}
			}
			z++;
			if(z == BUFFER)
			{
				z = 0;
			}
		}
		
		switch (dir)
		{
			case 1:verP = verP + 1; if(verP == 24)verP = 1 ;;break;			// horizontal 'horP' & vertical 'verP' calculation of the snakes  movement
			case 2:verP = verP - 1; if(verP == 0 )verP = 23;;break;
			case 3:horP = horP + 1; if(horP == 79)horP = 1 ;;break;
			case 4:horP = horP - 1; if(horP == 0 )horP = 78;;break;
		}
		
		switch (dir2)
		{
			case 1:verP2 = verP2 + 1; if(verP2 == 24)verP2 = 1 ;;break;
			case 2:verP2 = verP2 - 1; if(verP2 == 0 )verP2 = 23;;break;
			case 3:horP2 = horP2 + 1; if(horP2 == 79)horP2 = 1 ;;break;
			case 4:horP2 = horP2 - 1; if(horP2 == 0 )horP2 = 78;;break;
		}
		
		/* food */
		
		if(xf == horP && yf ==verP || xf == horP2 && yf ==verP2)										// check if snake head has the same position as food
		{
			if(xf == horP && yf ==verP)
			{
				gotoxy(horP, verP);
				std:: cout << "#";											// '#' eating animation
			}
			for(i = 0; i < difficulty; i++);
			
			if(difficulty != 30000000)									// snake growth 'n' based on difficulty
			{
				if(xf == horP && yf ==verP)
				n++;
				else
				n2++;
			}
			else
			{
			if(xf == horP && yf ==verP)
			n = n + 2;
			else
			n2 = n2 + 2;
			}
			food = 0;													// set food to eaten
			
			points = points + 20 + n;									// points for eating
			
			if(fakefood == 1)											// if the "real" food has been eaten, fake food will be removed
			{
		 		gotoxy(xff, yff);
				std:: cout << blank;
		  		xff = 0;
	   			yff = 0;
	   			
	   			fakefood = 0;
			}
		}
		if(xff == horP && yff ==verP)										// if fakefood is being eaten, random decrease in points
		{
			gotoxy(horP, verP);
			std:: cout << "#";
			for(i = 0; i < difficulty; i++);
			
			xff = 0;
			yff = 0;
			
			fakefood = 0;
		}
		
		/* check for snake head intersection with body */
		
		d = n2;
		z = n;
		for(i = 0; i < z; i++)
		{
			n2--;
			n--;
			if(horP2 == x2[phan + n] && verP2 == y2[phan + n] || horP2 == x[phan + n] && verP2 == y[phan + n])				// intersection results in game over
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
				std:: cout << "GAME OVER - Spieler 1 gewinnt";
				gotoxy(35, 15);
				std:: cout << "Punkte: " << points;
				for(i = 0; i < 500000000; i++);
				getch();
				return EXIT_SUCCESS;
			}
		}
		n = z;
		n2 = d;
		
		d = n;
		z = n2;
		for(i = 0; i < z; i++)
		{
			n--;
			n2--;
			if(horP == x[phan + n] && verP == y[phan + n]  || horP == x2[phan + n2] && verP == y2[phan + n2])				// intersection results in game over
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
				std:: cout << "GAME OVER - Spieler 2 gewinnt";
				gotoxy(35, 15);
				std:: cout << "Punkte: " << points;
				for(i = 0; i < 500000000; i++);
				getch();
				return EXIT_SUCCESS;
			}
		}
		n2 = z;
		n = d;
		
		/* - */
		
		x[phan + n] = horP;							//| save current head position to array
		y[phan + n] = verP;							//|
		
		x2[phan + n2] = horP2;
		y2[phan + n2] = verP2;
		
		gotoxy(x[phan], y[phan]);					// removing snakes tail for movement
		std:: cout << blank;
		
		gotoxy(x2[phan], y2[phan]);
		std:: cout << blank;
		
		phan = phan + 1;
		
		gotoxy(horP, verP);							// drawing next position of snake head
		std:: cout << Snake;
		
		gotoxy(horP2, verP2);
		std:: cout << Snake2;
		
		
		if(points < 500*(n - 15)/2 && difficulty != 50000000)			// point limit for balancing
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
		
		for(i = 0; i < difficulty; i++);						// Wait for next game cycle, different based on difficulty
	}
	
	return EXIT_FAILURE;
}
