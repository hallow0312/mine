#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define Max_x 11 // 가로 10
#define Max_y 11  // 세로 10
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

int map[Max_x][Max_y] = { 0, }; // 2차원 배열 사용 

void CreateMine()
{
	srand(time(NULL));
	int mine  = rand();
	
	int cnt = 0;
	
	for (int i = 0; i < Max_x; i++)
	{
		for (int j = 0; j < Max_y; j++)
		{	
			if (i == 0 || i == 10)
			{
				map[i][j] = j;
			}
			else if (j == 0 || j == 10)
			{
				map[i][j] = i;
			}
			else
			{
				mine = rand() % 2;
				map[i][j] = mine;
				
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
			
			if (map[i][j]==0||map[i][j]==1)
			{
				if (i != 0 || i != 10)
				{
					printf(" □ ");
				}
			}
			else 
			
		}
		printf("\n");
	}



}


int main()
{ 
	CreateMine();
	HideMap();
	
	return 0;
}