#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>

#define Max_x 15 // ���� 10
#define Max_y 15 // ���� 10
#define MineCount 40 


void CreateMineTable(char map[][Max_x] ,char checkmap[Max_y][Max_x])
{
	
	int x, y, mine_cnt,countmine;
	// mine ������ ������ �޸𸮿� ��� 0�� ä��
	memset(map, 0, Max_y * Max_x);
	// ����ڰ� �����ϰԵǴ� ������ ������ �޸𸮿� ��� 0�� ä��.
	memset(checkmap, 0, Max_y * Max_x);
	 
	 
	for (mine_cnt = 0; mine_cnt < MineCount; mine_cnt++)
	{
		
		//��ź ��ġ ���� ���� 
		//������ ����Ͽ� ��ź�� ��ġ�Ұ� ����
		x = rand() % Max_x;
		y = rand() % Max_y;

		if (map[y][x] == 0)
		{
			map[y][x] = 'a'; //���� ��ġ���� char ���� 1byte�� �ޱ⿡ �켱 'a'��� ǥ�� 
		}
		else if(map[y][x]!=0) // ���ڰ� �̹� ��ġ�� ������ �ߺ� �ɽ� �ٽ� ������ ���� 
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
					//���� ��ġ �߽����� ��ź�� � �ִ��� ī��Ʈ 
					// 1 2 3
					// 4 0 5   0�� ������ �������� 1~8����ġ�� ���� ������ ī��Ʈ 
					// 6 7 8
					
					if ((y - 1) >= 0) //������ ������ �ʰ� ��
					{
						if ((x - 1) >= 0 && map[y - 1][x - 1] == 'a')countmine++; //1��
						if (map[y - 1][x] == 'a')countmine++;  //2�� 
						if ((x + 1) < Max_x && map[y - 1][x + 1] == 'a')countmine++;  //3�� 
					}
					if ((x - 1) >= 0 && map[y][x - 1] == 'a')countmine++; //4��
					if ((x + 1) < Max_x  && map[y][x + 1] == 'a')countmine++; //5��
					if ((y + 1) < Max_y )
					{
						if ((y + 1) < Max_y)
						{
							if ((x - 1) >= 0 && map[y+1][x - 1] == 'a')countmine++; //6��
							if (map[y + 1][x] == 'a')countmine++; //7��
							if ((x + 1) < Max_x && map[y + 1][x + 1] == 'a')countmine++; //8��
						}
					}
					map[y][x] = '0' + countmine; // ������ countmine �� ���������� ����

				}
				
				  
			}
		}
	
}
	

void ShowMap(char map[][Max_x])
{
	printf("\n\n        <<���� ��ġ>>");
	printf("\n\n"); //�ٹٲ�
	for (int y = 0; y < Max_y; y++)
	{
		for ( int x = 0; x < Max_x; x++)
		{
			if (map[y][x] == 'a')
			{
				printf("��");
			}
			else
			{
				printf("%c ", map[y][x]);
			}
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
				printf("%c ", map[y][x]);  
			else
				printf("��");
		}
		printf("\n");
	}
	printf("\n");
}
				

int main()
{ 
	// ��ź�� ��ġ�� ������ �����ϰԵ� ���� 
	char map[Max_y][Max_x];
	// ����ڰ� ������ ��ġ�� ����� ���� 
	char checkmap[Max_y][Max_x];
	//���� ���� 
	srand((unsigned)time(NULL));  
	CreateMineTable(map, checkmap);
	
	//���� ������ �ݿ��Ͽ� ���� ���� ���
	ShowCurrentMapState(map, checkmap);
	
	int x, y;
	while (1)
	{
		printf("Ȯ���� ��ġ�� x, y��ǥ�� �Է��Ͻÿ�(���� �Ұ�).\n"); 
		printf("X��ǥ �Է� : ");
		scanf_s("%d", &x); 
		

		if (x < 0) break;

		printf("y��ǥ �Է� : ");
		scanf_s("%d", &y);
		if (y < 0) break;

		if (x < Max_x  && y < Max_y )
		{
			if (checkmap[y][x] == 0)
			{
				//����ڰ� ��ź�� �������� ��� 
				if (map[y][x] == 'a')
				{
					printf("\n\n�ءءء����ڸ� �����Ͽ����ϴ�.�ءءء�");
					break; //���� �ߴ� 
				}
				else
				{
					//����ڰ� ��ǥ�� ���������� ���� 
					checkmap[y][x] = 1;
					// ���� ������ �ݿ��Ͽ� ���� ��� 
					// �� ���ڷ� ��� �Ȱ��� ���� Ȯ�ε��� ���� �׸� 
					system("cls"); 
					ShowCurrentMapState(map, checkmap); 

				}

			}
			else printf("�̹� Ȯ�ε� ��ġ�Դϴ�.\n\n"); 
		}
		else printf("�߸��� ��ġ�� �����Ͽ����ϴ�.\n\n");
	}
		
		
	//��ü ��ġ ���� Ȯ�� 
	ShowMap(map); 
	
	return 0;
}
		



	




	
	

		
	

		