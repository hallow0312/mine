#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>
#include <windows.h>

#define Max_x 16 // 가로 10
#define Max_y 16 // 세로 10
#define MineCount 40 

void CreateMineTable(char map[][Max_x] ,char checkmap[Max_y][Max_x])
{
	int object  = rand();
	int x, y, mine_cnt,countmine;
	// mine 정보를 저장할 메모리에 모두 0을 채움
	memset(map,  0, Max_y * Max_x);
	// 사용자가 선택하게되는 정보를 저장할 메모리에 모두 0을 채움.
	memset(checkmap, 0, Max_y * Max_x);
	 
	 
	for (mine_cnt = 0; mine_cnt < MineCount; mine_cnt++)
	{
		//난수를 사용하여 폭탄이 위치할곳 생성
		x = object % (Max_x);
		y = object % (Max_y);

		if (map[y][x] == 0)
		{
			map[y][x] = '※';		//지뢰 설치구간 
		}
		else
		{
			mine_cnt--;
		}
	}
		for ( y = 0; y < Max_y; y++)
		{
			for ( x = 0; x < Max_x; x++)
			{
				countmine = 0;

				if (map[y][x] == 0)
				{
					
					if ((y - 1) >= 0) //음수 및 0이 나오지 않게 한다.
					{
						if ((x - 1) >= 0 && map[y - 1][x - 1] == '※')countmine++;
						if (map[y - 1][x] == '※')countmine++;
						if ((x + 1) < Max_x && map[y - 1][x + 1] == '※')countmine++;
					}
					if ((x - 1) >= 0 && map[y][x - 1] == '※')countmine++;
					if ((x + 1) < Max_x  && map[y][x + 1] == '※')countmine++;
					if ((y + 1) < Max_y )
					{
						if ((y + 1) < Max_y)
						{
							if ((x - 1) >= 0 && map[y+1][x - 1] == '※')countmine++;
							if (map[y + 1][x] == '※')countmine++;
							if ((x + 1) < Max_x && map[y + 1][x + 1] == '※')countmine++;
						}
					}

				}
				map[y][x] = '0' + countmine;
			}
		}
	
}
	

void ShowMap(char map[][Max_x])
{
	
	printf("\n");
	for (int y = 0; y < Max_y; y++)
	{
		for ( int x = 0; x < Max_x; x++)
		{
			printf("%c", map[y][x]);
		}
		printf("\n");
	}
	printf("\n");
	
}
void ShowCurrentMapState(char map[][Max_x], char checkmap[][Max_x])
{
	printf("\n");
	for (int y = 0; y < Max_y; y++)
	{
		for (int x = 0; x < Max_x; x++)
		{
			if (checkmap[y][x])
				printf("%c", map[y][x]);
			else
				printf(" □ ");
		}
		printf("\n");
	}
	printf("\n");
}
				

int main()
{ 
	char map[Max_y][Max_x];
	char checkmap[Max_y][Max_x];

	srand((unsigned)time(NULL)); 
	CreateMineTable(map, checkmap);
	ShowCurrentMapState(map, checkmap);
	
	int x, y;
	while (1)
	{
		printf("확인할 위치의 x, y좌표를 입력하시오(음수 불가).\n");
		printf("X좌표 입력 : ");
		scanf_s("%d", &x);
		

		if (x <= 0) break;

		printf("y좌표 입력 : ");
		scanf_s("%d", &y);
		if (y <= 0) break;

		if (x < Max_x - 1 && Max_y - 1)
		{
			if (checkmap[y][x] == 0)
			{
				if (map[y][x] == '※')
				{
					printf("지뢰를 선택하였습니다.");
					break;
				}
				else
				{
					checkmap[y][x] = 1;
					
					ShowCurrentMapState(map, checkmap);

				}

			}
			else printf("이미 확인된 위치입니다.\n\n");
		}
		else printf("잘못된 위치를 선택하였습니다.\n\n");
	}
		
		
	
	ShowMap(map);
	
	return 0;
}
		



	




	
	

		
	

		