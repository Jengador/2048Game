#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#define SIZE 4

//Author: Umut Guvercin
//Special thanks to Sezen.A

typedef int bool;
#define true 1
#define false 0

void printmenu();
void winprint(int puzzle[SIZE][SIZE]);
void loseprint(int puzzle[SIZE][SIZE]);
void puzzleprint(int puzzle[SIZE][SIZE]);
void puzzlestarter(int puzzle[SIZE][SIZE]);
void puzzlespawner(int puzzle[SIZE][SIZE]);
void leftcursor(int puzzle[SIZE][SIZE]);
void rightcursor(int puzzle[SIZE][SIZE]);
void upcursor(int puzzle[SIZE][SIZE]);
void downcursor(int puzzle[SIZE][SIZE]);
bool rowcheck(int puzzle[SIZE]);
bool isgameover(int puzzle[SIZE][SIZE]);
bool isleftokay(int puzzle[SIZE][SIZE]);
bool isrightokay(int puzzle[SIZE][SIZE]);
bool isupokay(int puzzle[SIZE][SIZE]);
bool isdownokay(int puzzle[SIZE][SIZE]);
int highestpoint(int puzzle[SIZE][SIZE]);
int highestlength(int highest);
void printline(int puzzle[SIZE][SIZE]);
void puzzlecursor(int puzzle[SIZE][SIZE], int cursor);


int main(int argc, char **argv)
{
	HWND wh = GetConsoleWindow();
	MoveWindow(wh, 500, 200, 300, 250, TRUE);
	int puzzle[SIZE][SIZE] = {0};
	printmenu();
	int selector;
	selector = getch();
	puzzlestarter(puzzle);
	puzzleprint(puzzle);
	while(1)
	{
		if(highestpoint(puzzle) == 2048)
		{
			winprint(puzzle);
			selector = getch();
			return 0;
		}
		
		else if(isgameover(puzzle))
		{
			loseprint(puzzle);
			selector = getch();
			return 0;
		}
		selector = getch();
		if(selector == '4' || selector == 'a')
		{
			selector = 1;
		}
		else if(selector == '8' || selector == 'w')
		{
			selector = 2;
		}
		else if(selector == '6' || selector == 'd')
		{
			selector = 3;
		}
		else if(selector == '2' || selector == 's')
		{
			selector = 4;
		}
		else if(selector == 27)
		{
			return 0;
		}
		puzzlecursor(puzzle, selector);
	}
	
	return 0;
}

void puzzleprint(int puzzle[SIZE][SIZE])
{
	int i,j;
	printf("\n\n ");
	printline(puzzle);
	for(i=0; i<SIZE; i++)
	{
		printf("|");
		for(j=0; j<SIZE; j++)
		{
			if(highestlength(highestpoint(puzzle)) == 2)
			{
				if(puzzle[i][j] != 0)
				{
					printf("%2d%c|" , puzzle[i][j], ' ');
				}
				else
				{
					printf("%3c|" , ' ');
				}
			}
			else if(highestlength(highestpoint(puzzle)) == 3)
			{
				if(puzzle[i][j] != 0)
				{
					printf("%3d%c|" , puzzle[i][j], ' ');
				}
				else
				{
					printf("%4c|" , ' ');
				}
			}
			else if(highestlength(highestpoint(puzzle)) == 4)
			{
				if(puzzle[i][j] != 0)
				{
					printf("%4d%c|" , puzzle[i][j], ' ');
				}
				else
				{
					printf("%5c|" , ' ');
				}
			}
		}
		printf("\n ");
		printline(puzzle);
	}
	printf(" \n\n");
}

void puzzlestarter(int puzzle[SIZE][SIZE])
{
	srand(time(NULL));
	int k = 0;
	while(k<SIZE-2)
	{
		int i = rand() % SIZE;
		int j = rand() % SIZE;
		if (puzzle[i][j] == 0)
		{
			int l = rand() % 4;
			if(l == 3)
			{
				puzzle[i][j] = 4;
			}
			else
			{
				puzzle[i][j] = 2;
			}		
			k++;
		}
	}
}

void puzzlespawner(int puzzle[SIZE][SIZE])
{
	srand(time(NULL));
	int k = 0;
	while(k<1)
	{
		int i = rand() % SIZE;
		int j = rand() % SIZE;
		if (puzzle[i][j] == 0)
		{
			int l = rand() % 4;
			if(l == 3)
			{
				puzzle[i][j] = 4;
			}
			else
			{
				puzzle[i][j] = 2;
			}		
			k++;
		}
	}
}

void puzzlecursor(int puzzle[SIZE][SIZE], int cursor)
{
	switch(cursor)
	{
		case 1:
			leftcursor(puzzle);
			break;
		case 2:
			upcursor(puzzle);
			break;
		case 3:
			rightcursor(puzzle);
			break;
		case 4:
			downcursor(puzzle);
			break;
		default:
			return;
			break;
	}
	
}

void leftcursor(int puzzle[SIZE][SIZE])
{
	if(isleftokay(puzzle))
	{
		int i,j;
		for(i=0;i<SIZE;i++)
		{
			for(j=0;j<SIZE;j++)
			{
				if(puzzle[i][j] == 0)
				{
					int seq = 0;
					int k = j;
					while(puzzle[i][k] == 0 && k<SIZE)
					{
						seq++;
						k++;
					}
					if(seq != 4)
					{
						int p;
						for(p=j;p<SIZE-seq;p++)
						{
							puzzle[i][p] = puzzle[i][p+seq];
							puzzle[i][p+seq] = 0;
						}
					}
				}
			}
		}
		for(i=0;i<SIZE;i++)
		{
			for(j=0;j<SIZE-1;j++)
			{
				if(puzzle[i][j] == puzzle[i][j+1])
				{
					int k;
					puzzle[i][j] *= 2;
					puzzle[i][j+1] = 0;
					for(k=j+1;k<SIZE-1;k++)
					{
						puzzle[i][k] = puzzle[i][k+1];
					}
					puzzle[i][k] = 0;
				}
			}			
		}
		puzzlespawner(puzzle);
		puzzleprint(puzzle);
	}	
}

void rightcursor(int puzzle[SIZE][SIZE])
{
	if(isrightokay(puzzle))
	{
		int i,j;
		for(i=0;i<SIZE;i++)
		{
			for(j=SIZE-1;j>=0;j--)
			{
				if(puzzle[i][j] == 0)
				{
					int seq = 0;
					int k = j;
					while(puzzle[i][k] == 0 && k>=0)
					{
						seq++;
						k--;
					}
					if(seq != 4)
					{
						int p;
						for(p=j;p>=seq;p--)
						{
							puzzle[i][p] = puzzle[i][p-seq];
							puzzle[i][p-seq] = 0;
						}
					}
				}
			}
		}
		for(i=0;i<SIZE;i++)
		{
			for(j=SIZE-1;j>0;j--)
			{
				if(puzzle[i][j] == puzzle[i][j-1])
				{
					int k;
					puzzle[i][j] *= 2;
					puzzle[i][j-1] = 0;
					for(k=j-1;k>0;k--)
					{
						puzzle[i][k] = puzzle[i][k-1];
					}
					puzzle[i][k] = 0;
				}
			}			
		}
		puzzlespawner(puzzle);
		puzzleprint(puzzle);
	}
}

void downcursor(int puzzle[SIZE][SIZE])
{
	if(isdownokay(puzzle))
	{
		int i,j;
		for(i=0;i<SIZE;i++)
		{
			for(j=SIZE-1;j>=0;j--)
			{
				if(puzzle[j][i] == 0)
				{
					int seq = 0;
					int k = j;
					while(puzzle[k][i] == 0 && k>=0)
					{
						seq++;
						k--;
					}
					if(seq != 4)
					{
						int p;
						for(p=j;p>=seq;p--)
						{
							puzzle[p][i] = puzzle[p-seq][i];
							puzzle[p-seq][i] = 0;
						}
					}
				}
			}
		}
		for(i=0;i<SIZE;i++)
		{
			for(j=SIZE-1;j>0;j--)
			{
				if(puzzle[j][i] == puzzle[j-1][i])
				{
					int k;
					puzzle[j][i] *= 2;
					puzzle[j-1][i] = 0;
					for(k=j-1;k>0;k--)
					{
						puzzle[k][i] = puzzle[k-1][i];
					}
					puzzle[k][i] = 0;
				}
			}			
		}
		puzzlespawner(puzzle);
		puzzleprint(puzzle);
	}
}

void upcursor(int puzzle[SIZE][SIZE])
{
	if(isupokay(puzzle))
	{
		int i,j;
		for(i=0;i<SIZE;i++)
		{
			for(j=0;j<SIZE;j++)
			{
				if(puzzle[j][i] == 0)
				{
					int seq = 0;
					int k = j;
					while(puzzle[k][i] == 0 && k<SIZE)
					{
						seq++;
						k++;
					}
					if(seq != 4)
					{
						int p;
						for(p=j;p<SIZE-seq;p++)
						{
							puzzle[p][i] = puzzle[p+seq][i];
							puzzle[p+seq][i] = 0;
						}
					}
				}
			}
		}
		for(i=0;i<SIZE;i++)
		{
			for(j=0;j<SIZE-1;j++)
			{
				if(puzzle[j][i] == puzzle[j+1][i])
				{
					int k;
					puzzle[j][i] *= 2;
					puzzle[j+1][i] = 0;
					for(k=j+1;k<SIZE-1;k++)
					{
						puzzle[k][i] = puzzle[k+1][i];
					}
					puzzle[k][i] = 0;
				}
			}			
		}
		puzzlespawner(puzzle);
		puzzleprint(puzzle);
	}
}

bool rowcheck(int puzzle[SIZE])
{
	int i;
	for(i=0;i<SIZE;i++)
	{
		if(puzzle[i] != 0)
		{
			return true;
		}
	}
	return false;
}

bool isgameover(int puzzle[SIZE][SIZE])
{
	int i,j;
	for(i=0;i<SIZE;i++)
	{
		for(j=0;j<SIZE;j++)
		{
			if(puzzle[i][j] == 0)
			{
				return false;
			}
			else
			{
				if(i != 0)
				{
					if(puzzle[i][j] == puzzle[i-1][j])
					{
						return false;
					}
				}
				if(i != SIZE-1)
				{
					if(puzzle[i][j] == puzzle[i+1][j])
					{
						return false;
					}
				}
				if(j != 0)
				{
					if(puzzle[i][j] == puzzle[i][j-1])
					{
						return false;
					}
				}
				if(j != SIZE -1)
				{
					if(puzzle[i][j] == puzzle[i][j+1])
					{
						return false;
					}
				}

			}
		}
	}
	return true;
}

bool isleftokay(int puzzle[SIZE][SIZE])
{
	int i,j,k;
	int rightmost;
	for(i=0;i<SIZE;i++)
	{
		rightmost = 0;
		for(j=1;j<SIZE;j++)
		{
			if(puzzle[i][j] != 0)
			{
				rightmost = j;
				for(k=0;k<j;k++)
				{
					
					if(puzzle[i][k] == 0)
					{
						return true;
					}
				}
			}
		}
		for(j=rightmost ; j>0 ; j--)
		{
			if(puzzle[i][j] == puzzle[i][j-1])
			{
				return true;
			}
		}

	}
	return false;
}

bool isrightokay(int puzzle[SIZE][SIZE])
{
	int i,j,k;
	int leftmost;
	for(i=0;i<SIZE;i++)
	{
		leftmost = SIZE-1;
		for(j=SIZE-2;j>=0;j--)
		{
			if(puzzle[i][j] != 0)
			{
				leftmost = j;
				for(k=SIZE-1;k>j;k--)
				{
					
					if(puzzle[i][k] == 0)
					{
						return true;
					}
				}
			}
		}
		for(j=leftmost ; j<SIZE-1 ; j++)
		{
			if(puzzle[i][j] == puzzle[i][j+1])
			{
				return true;
			}
		}

	}
	return false;
}

bool isupokay(int puzzle[SIZE][SIZE])
{
	int i,j,k;
	int uppermost;
	for(i=0;i<SIZE;i++)
	{
		uppermost = 0;
		for(j=1;j<SIZE;j++)
		{
			if(puzzle[j][i] != 0)
			{
				uppermost = j;
				for(k=0;k<j;k++)
				{
					
					if(puzzle[k][i] == 0)
					{
						return true;
					}
				}
			}
		}
		for(j=uppermost ; j>0 ; j--)
		{
			if(puzzle[j][i] == puzzle[j-1][i])
			{
				return true;
			}
		}

	}
	return false;
}

bool isdownokay(int puzzle[SIZE][SIZE])
{
	int i,j,k;
	int undermost;
	for(i=0;i<SIZE;i++)
	{
		undermost = SIZE-1;
		for(j=SIZE-2;j>=0;j--)
		{
			if(puzzle[j][i] != 0)
			{
				undermost = j;
				for(k=SIZE-1;k>j;k--)
				{
					
					if(puzzle[k][i] == 0)
					{
						return true;
					}
				}
			}
		}
		for(j=undermost ; j<SIZE-1 ; j++)
		{
			if(puzzle[j][i] == puzzle[j+1][i])
			{
				return true;
			}
		}

	}
	return false;
}

int highestpoint(int puzzle[SIZE][SIZE])
{
	int i,j;
	int highest = 0;
	for(i=0; i<SIZE; i++)
	{
		for(j=0; j<SIZE; j++)
		{
			if(puzzle[i][j] > highest)
			{
				highest = puzzle[i][j];
			}
		}
	}
	return highest;
}

int highestlength(int highest)
{
	int length = 2;
	if(highest / 1000 != 0)
	{
		length = 4;
		
	}
	else if(highest / 100 != 0)
	{
		length = 3;
	}
	return length;
}

void printline(int puzzle[SIZE][SIZE])
{
	int i,j;
	int length = highestlength(highestpoint(puzzle));
	for(j= 0; j<SIZE; j++)
	{
		printf("@");
		for(i=0; i<=length; i++)
		{
			printf("-");
		}
	}
	printf("@\n ");
}

void printmenu()
{
	printf("\n\n");
	printf("    @@@@@@@@@@@@@@@@@@@@@@@@@\n");
	printf("    @  Welcome to Game2048  @\n");
	printf("    @    To play 2 4 6 8    @\n");
	printf("    @    To play w a s d    @\n");
	printf("    @    To exit    esc     @\n");
	printf("    @-----------------------@\n");
	printf("    @        Game of :      @\n");
	printf("    @ Guvercin--Corparation @\n");
	printf("    @@@@@@@@@@@@@@@@@@@@@@@@@\n");
}

void winprint(int puzzle[SIZE][SIZE])
{
	printf("\n\n    @@@@@@@@@@@@@@@@@@@@@@@@@\n");
	printf("    @----CONGRATULATIONS----@\n");
	printf("    @        RISE UP        @\n");
	printf("    @      AND, SALUTE      @\n");
	printf("    @   THE NEW CHAMPION!   @\n");
	printf("    @                       @\n");
	printf("    @  Your Score is: %-4d  @\n" ,highestpoint(puzzle));
	printf("    @----CONGRATULATIONS----@\n");
	printf("    @@@@@@@@@@@@@@@@@@@@@@@@@\n\n");
}

void loseprint(int puzzle[SIZE][SIZE])
{
	printf("\n\n    @@@@@@@@@@@@@@@@@@@@@@@@@\n");
	printf("    @------GAME OVER !------@\n");
	printf("    @     SHAME ON YOU !    @\n");
	printf("    @  Your Score is: %-4d  @\n" ,highestpoint(puzzle));
	printf("    @@@@@@@@@@@@@@@@@@@@@@@@@\n\n\n\n");
}

