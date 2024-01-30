#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>		// rand() 함수사용하기 위함 
#include <time.h>       // time 코드 사용하기 위함 
#include <memory.h>     //memset 함수를 사용하기 위함 
#include <windows.h>	//색상변경을 위함 

#define Max_x 15 // 가로 15
#define Max_y 15 // 세로 15
#define MineCount 40 //지뢰 40개

void textcolor(int color_number) //색상변경 함수 
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}




void CreateMineTable(char map[][Max_x] ,char checkmap[Max_y][Max_x])
{	
	
	int x, y, mine_cnt, countmine;
	// mine 정보를 저장할 메모리에 모두 0을 채움
	memset(map, 0, Max_y * Max_x);
	// 사용자가 선택하게되는 정보를 저장할 메모리에 모두 0을 채움.
	memset(checkmap, 0, Max_y * Max_x);
	 
	 
	for (mine_cnt = 0; mine_cnt < MineCount; mine_cnt++)
	{
		
		//폭탄 설치 정보 구성 
		//난수를 사용하여 폭탄이 위치할곳 생성
		x = rand() % Max_x;
		y = rand() % Max_y;
		
		if (map[y][x] == 0)
		{
			map[y][x] = 'a'; //지뢰 설치구간 char 형은 1byte만 받기에 우선 'a'라고 표기 
		}
		else if(map[y][x]!=0) // 지뢰가 이미 설치된 구간이 중복 될시 다시 난수를 설정 
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
					//현재 위치 중심으로 폭탄이 몇개 있는지 카운트 
					// 1 2 3
					// 4 0 5   0인 구간을 기준으로 1~8번위치의 지뢰 개수를 카운트 
					// 6 7 8
					
					if ((y - 1) >= 0) //음수가 나오지 않게 함
					{
						if ((x - 1) >= 0 && map[y - 1][x - 1] == 'a')countmine++; //1번
						if (map[y - 1][x] == 'a')countmine++;  //2번 
						if ((x + 1) < Max_x && map[y - 1][x + 1] == 'a')countmine++;  //3번 
					}
					if ((x - 1) >= 0 && map[y][x - 1] == 'a')countmine++; //4번
					if ((x + 1) < Max_x  && map[y][x + 1] == 'a')countmine++; //5번
					if ((y + 1) < Max_y )
					{
						if ((y + 1) < Max_y)
						{
							if ((x - 1) >= 0 && map[y+1][x - 1] == 'a')countmine++; //6번
							if (map[y + 1][x] == 'a')countmine++; //7번
							if ((x + 1) < Max_x && map[y + 1][x + 1] == 'a')countmine++; //8번
						}
					}
				
					map[y][x] = '0' + countmine; // 정수형 countmine 을 문자형으로 받음

				}
				
				  
			}
		}
	
}
	

void ShowMap(char map[][Max_x]) //죽고 나서 지뢰 위치를 알려주는 함수 
{	
	textcolor(15);
	printf("\n\n   <<남아있는 지뢰 위치>>");
	printf("\n\n"); //줄바꿈
	for (int y = 0; y < Max_y; y++)
	{
		
		for ( int x = 0; x < Max_x; x++)
		{
			
			if (map[y][x] == 'a')
			{
				textcolor(4);
				printf("※");
			}
			else if (map[y][x] == 'f')
			{
				textcolor(3);
				printf("▶"); 
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

		
void ShowCurrentMapState(int countflag,int countmine,int block,char map[][Max_x], char checkmap[][Max_x]) //사용자가 보게될 함수 
{
	
	printf("\n");
	for (int y = 0; y < Max_y; y++)
	{
		for (int x = 0; x < Max_x; x++)
		{
			
			if (map[y][x] != 'f')
			{
				if (checkmap[y][x])
				{
					textcolor(15);
					printf("%c ", map[y][x]);
				}
				else
				{
					textcolor(8);
					printf("■");
				}
			}
			else if (map[y][x] == 'f')
			{
				if (checkmap[y][x])
				{
					textcolor(3);
					printf("▶");
				}
				else
				{
					textcolor(8);
					printf("■");
				}
			}
			
			
				
			
		}
		printf("\n");
		
	}	
	//현재 폭탄이 있는 개수 , 남은 깃발 개수 UI
	printf("\n");	
	textcolor(4);
	printf("※");
	textcolor(15);
	printf(" : %d", countmine);
	textcolor(3);
	printf(" ▶");
	textcolor(15);
	printf(" : %d", countflag);
	textcolor(8);
	printf(" ■");
	textcolor(15);
	printf(" : %d\n\n", block);
	
	
}	
int main()
{ 
	// 폭탄이 설치된 정보를 저장하게될 변수 
	char map[Max_y][Max_x];
	// 사용자가 선택할 위치를 기억할 변수 
	char checkmap[Max_y][Max_x];
	//난수 설정 
	srand((unsigned)time(NULL));  
	CreateMineTable(map, checkmap);
	int countflag, countmine;
	countflag = MineCount; //지뢰 개수와 같음
	countmine = MineCount;
	int block = (Max_y) * (Max_x)-(MineCount); //지뢰 제외 모든 블럭 
	//선택 정보를 반영하여 지뢰 정보 출력
	ShowCurrentMapState(countflag,countmine,block,map, checkmap);
	
	int x, y,flag;
	
	 
	while (1)
	{
		textcolor(15);
		printf("확인할 위치의 x, y좌표를 입력하시오(음수 불가).\n"); 
		printf("X좌표 입력 : ");
		scanf_s("%d", &x); 
		if (x < 0) break;

        printf("y좌표 입력 : ");
		scanf_s("%d", &y);
		if (y < 0) break;
		
		if (countflag > 0) //깃발 세우기 
		{
			printf("깃발을 세우시겠습니까? (YES:1  NO:2)\n");
			scanf_s("%d", &flag);
			if (checkmap[y][x] != 1)
			{
					if (flag == 1)
					{
						if (map[y][x] == 'a')
						{
							map[y][x] = 'f';
							countflag--;
							countmine--;
						}
						else
						{
							map[y][x] = 'f';
							countflag--;
							
						}
					}
				
				
			}
		}
		if (countmine <= 0 && countflag <= 0)break; //지뢰 및 깃발이 없어졌을때 승리조건 (2)
		
			
		
		

		
			if (x < Max_x && y < Max_y)
			{
				if (checkmap[y][x] == 0)
				{
					//사용자가 폭탄을 선택했을 경우 
					if (map[y][x] == 'a')
					{

						break; //게임 중단 
					}
					else
					{
						//사용자가 좌표를 선택했음을 설정 
						checkmap[y][x] = 1;
						block--;
						// 선택 정보를 반영하여 블럭 내 정보를 출력
						// □ 문자로 출력 된것은 아직 확인되지 않은 항목 
						system("cls");
						
						ShowCurrentMapState(countflag,countmine,block,map, checkmap);
						if (block <= 0)
						{
							break;
						}
						

					}

				}
				else printf("이미 확인된 위치입니다.\n\n");
			}
			else printf("잘못된 위치를 선택하였습니다.\n\n");
		
	}
	if (block <= 0) //승리조건 (1): 지뢰를 제외한 모든블럭을 깼을때 
	{
		system("cls");
		printf("\n\n      모든지뢰를 찾으셨습니다.");
	}
	else if (countflag <= 0 && countmine <= 0) //승리조건 (2): 지뢰위치에 깃발이 모두 꽂혔을때
	{
		system("cls");
		printf("\n\n      모든지뢰를 찾으셨습니다.");
		ShowMap(map);
	}
	else //패배 조건 
	{
		textcolor(4);
		system("cls");
		
		printf("\n\n※※※※지뢰를 선택하였습니다.※※※※");

		ShowMap(map); //전체 설치 정보 확인
		textcolor(15);
	}
	
	
	return 0;
}
	
	
		
	

				
	
	
		
				

		

		



	




	
	

		
	

		