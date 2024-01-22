#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define Max_x 16 // 가로 10
#define Max_y 16  // 세로 10
#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80

void GotoXY(int x, int y)
{
	// x , y 좌표 설정
	COORD position = { x,y };

	// 커서 이동 함수 
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);

}

int map[Max_y][Max_x] = { 0, }; // 2차원 배열 사용
char* openmap[Max_y][Max_x] = { NULL, };

void CreateMine()
{
	srand(time(NULL));
	int object  = rand();
	
	
	for (int i = 0; i < Max_x; i++)
	{
		object = rand()%2;

		for (int j = 0; j < Max_y; j++)
		{	
			if (i == 0 || i == Max_x-1)
			{
				map[i][j] = j;
			}
			else if (j == 0 || j == Max_y-1)
			{
				map[i][j] = i;
			}
			else
			{
				map[i][j] = object;
			}
		}
		printf("\n");
		
	}
}

void  HideMap()
{

	for (int i = 0; i < Max_x; i++)
	{
		for (int j = 0; j < Max_y; j++)
		{
			if (i == 0 || i == Max_x-1)
			{
				if (j >= 10)
				{
					printf(" %d ", map[i][j]);
				}
				else
				{
					printf(" %d  ", map[i][j]); 
				}
			}
			else if (j == 0 || j == Max_y-1)
			{
				if (i >= 10)
				{
					printf(" %d ", map[i][j]);
				}
				else
				{
					printf(" %d  ", map[i][j]);
				}
				
			}

			else
			{
				printf(" □ ");
			}
			

			
		}
		printf("\n\n");
	}

}
void CountMine()
{
	
	for (int x = 0; x < Max_x; x++)
	{
		int mine_cnt = 0;

		for (int y = 0; y < Max_y; y++)
		{
			if (map[y][x]==0 && y-1>0)
			{
				if ((x - 1) > 0 && map[y+1][x - 1] == 1) mine_cnt++; //1
				if ((x - 1) > 0 && map[y][x - 1] == 1)mine_cnt++;//2
				if ((x - 1) > 0 && map[y - 1][x - 1] == 1)mine_cnt++;//3
				if ((y - 1) > 0 && map[y - 1][x] == 1)mine_cnt++;//4
				if ( (y - 1) > 0 && map[y - 1][x + 1] == 1)mine_cnt++;//5
				if ((y - 1) > 0 && map[y - 1][x] == 1)mine_cnt++;//6
				if (map[y + 1][x + 1] == 1)mine_cnt++;//7
				if (map[y][x + 1] == 1)mine_cnt++; //8 

				
			}
		
			map[y][x] = mine_cnt;
			printf(" %d ", map[y][x]);

		}
		printf("\n");
		
		
	}
	
		
}





int main()
{ 
	
	CreateMine();
	CountMine();
	
	while (1)
	{
		
	}

		
	
	return 0;
}