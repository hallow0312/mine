#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>		// ���� ����ϱ� ���� 
#include <time.h>       // time �ڵ� ����ϱ� ���� 
#include <memory.h>     //memset �Լ��� ����ϱ� ���� 
#include <windows.h>

#define Max_x 15 // ���� 10
#define Max_y 15 // ���� 10
#define MineCount 40 

void textcolor(int color_number)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}




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
	

void ShowMap(char map[][Max_x]) //�װ� ���� ���� ��ġ�� �˷��ִ� �Լ� 
{	
	textcolor(15);
	printf("\n\n        <<���� ��ġ>>");
	printf("\n\n"); //�ٹٲ�
	for (int y = 0; y < Max_y; y++)
	{
		
		for ( int x = 0; x < Max_x; x++)
		{
			
			if (map[y][x] == 'a')
			{
				textcolor(4);
				printf("��");
			}
			else
			{
				textcolor(15);
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
			{	
				textcolor(15);
				printf("%c ", map[y][x]);
			}
			
			else 
			{
				textcolor(8);
					printf("��");		
			}		
				
				
			
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
	
	int x, y, block;
	block = (Max_y) * (Max_x)-(MineCount); //���� ���� ��� �� 
	 
	while (1)
	{
		textcolor(15);
		printf("Ȯ���� ��ġ�� x, y��ǥ�� �Է��Ͻÿ�(���� �Ұ�).\n"); 
		printf("X��ǥ �Է� : ");
		scanf_s("%d", &x); 
		if (x < 0) break;

        printf("y��ǥ �Է� : ");
		scanf_s("%d", &y);
		if (y < 0) break;
		
		
		
			if (x < Max_x && y < Max_y)
			{
				if (checkmap[y][x] == 0)
				{
					//����ڰ� ��ź�� �������� ��� 
					if (map[y][x] == 'a')
					{

						break; //���� �ߴ� 
					}
					else
					{
						//����ڰ� ��ǥ�� ���������� ���� 
						checkmap[y][x] = 1;
						block--;
						// ���� ������ �ݿ��Ͽ� ���� ��� 
						// �� ���ڷ� ��� �Ȱ��� ���� Ȯ�ε��� ���� �׸� 
						system("cls");
						ShowCurrentMapState(map, checkmap);
						if (block <= 0)
						{
							break;
						}
						

					}

				}
				else printf("�̹� Ȯ�ε� ��ġ�Դϴ�.\n\n");
			}
			else printf("�߸��� ��ġ�� �����Ͽ����ϴ�.\n\n");
		
	}
	if (block <= 0) //�¸����� 
	{
		system("cls");
		printf("\n\n      ������ڸ� ã���̽��ϴ�.");
	}
	else //�й� ���� 
	{
		textcolor(4);
		system("cls");
		
		printf("\n\n�ءءء����ڸ� �����Ͽ����ϴ�.�ءءء�");

		ShowMap(map); //��ü ��ġ ���� Ȯ�� 
		textcolor(15);
	}
	
	
	
	return 0;
}
		

		



	




	
	

		
	

		