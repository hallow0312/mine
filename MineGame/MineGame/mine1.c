#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>
#include <windows.h>

#define Max_x 16 // ���� 10
#define Max_y 16 // ���� 10
#define MineCount 40 

void CreateMineTable(char map[][Max_x] ,char checkmap[Max_y][Max_x])
{
	int object  = rand();
	int x, y, mine_cnt,countmine;
	// mine ������ ������ �޸𸮿� ��� 0�� ä��
	memset(map,  0, Max_y * Max_x);
	// ����ڰ� �����ϰԵǴ� ������ ������ �޸𸮿� ��� 0�� ä��.
	memset(checkmap, 0, Max_y * Max_x);
	 
	 
	for (mine_cnt = 0; mine_cnt < MineCount; mine_cnt++)
	{
		//������ ����Ͽ� ��ź�� ��ġ�Ұ� ����
		x = object % (Max_x);
		y = object % (Max_y);

		if (map[y][x] == 0)
		{
			map[y][x] = '��';		//���� ��ġ���� 
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
					
					if ((y - 1) >= 0) //���� �� 0�� ������ �ʰ� �Ѵ�.
					{
						if ((x - 1) >= 0 && map[y - 1][x - 1] == '��')countmine++;
						if (map[y - 1][x] == '��')countmine++;
						if ((x + 1) < Max_x && map[y - 1][x + 1] == '��')countmine++;
					}
					if ((x - 1) >= 0 && map[y][x - 1] == '��')countmine++;
					if ((x + 1) < Max_x  && map[y][x + 1] == '��')countmine++;
					if ((y + 1) < Max_y )
					{
						if ((y + 1) < Max_y)
						{
							if ((x - 1) >= 0 && map[y+1][x - 1] == '��')countmine++;
							if (map[y + 1][x] == '��')countmine++;
							if ((x + 1) < Max_x && map[y + 1][x + 1] == '��')countmine++;
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
				printf(" �� ");
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
		printf("Ȯ���� ��ġ�� x, y��ǥ�� �Է��Ͻÿ�(���� �Ұ�).\n");
		printf("X��ǥ �Է� : ");
		scanf_s("%d", &x);
		

		if (x <= 0) break;

		printf("y��ǥ �Է� : ");
		scanf_s("%d", &y);
		if (y <= 0) break;

		if (x < Max_x - 1 && Max_y - 1)
		{
			if (checkmap[y][x] == 0)
			{
				if (map[y][x] == '��')
				{
					printf("���ڸ� �����Ͽ����ϴ�.");
					break;
				}
				else
				{
					checkmap[y][x] = 1;
					
					ShowCurrentMapState(map, checkmap);

				}

			}
			else printf("�̹� Ȯ�ε� ��ġ�Դϴ�.\n\n");
		}
		else printf("�߸��� ��ġ�� �����Ͽ����ϴ�.\n\n");
	}
		
		
	
	ShowMap(map);
	
	return 0;
}
		



	




	
	

		
	

		