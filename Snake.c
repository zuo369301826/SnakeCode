#include <windows.h> 
#include <stdio.h> 
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "Snake.h"

//1.��������
void SetPos(int x,int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//��þ��
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);//���ù��λ��
}

//2.������ͼ
void CreateMap()
{
	int i;
	for ( i = 0; i <= 56; i+=2)
	{
		SetPos(i, 0);
		printf(WALL);
		SetPos(i, 26);
		printf(WALL);
	}
	for (i = 1; i <= 25; i++)
	{
		SetPos(0, i);
		printf(WALL);
		SetPos(56, i);
		printf(WALL);
	}
}

//3.��ʼ����
void InitSnake(pSnake pS)
{
	pSnakeNode Cur = malloc(sizeof(SnakeNode));
	Cur->x = INIT_X;
	Cur->y = INIT_Y;
	Cur->next = NULL;
	//����ͷ��
	for (size_t i = 1; i <= 4; i++)
	{
		//ͷ���һ���µĽڵ�
		pS->_pSnake = malloc(sizeof(SnakeNode));
		pS->_pSnake->next = Cur;//ʹ�½ڵ�������֮ǰ�Ľڵ�
		pS->_pSnake->x = INIT_X + i * 2;//�½ڵ㸳ֵ
		pS->_pSnake->y = INIT_Y;
	
		Cur = pS->_pSnake;	//ʹCurָ���һ���ڵ�
	}
	pS->_Dir = RIGHT;
	pS->_status = OK;
}

//4.��ӡ��
void SnakePrint(pSnake pS)
{
	pSnakeNode Cur = NULL;
	pSnakeNode pFood = NULL;
	assert(pS);
	//��ӡ��
	Cur = pS->_pSnake;
	while (Cur)
	{
		SetPos(Cur->x, Cur->y);
		printf(SNAKE);
		Cur = Cur->next;
	}
	SetPos(60, 20);
}
//��ӡʳ��
void FoodPrint(pSnake pS)
{
	SetPos(pS->_pFood->x, pS->_pFood->y);
	printf(FOOD);
}


//5. ����ʳ��
void GetRandFood(pSnakeNode pFood)//�������ʳ��
{
	srand((unsigned)time(NULL));
	do
	{
	pFood->x = rand() % 53 + 2;
	} while (pFood->x % 2 != 0);
	pFood->y = rand() % 25 + 1;
}
void CreadeFood(pSnake pS)
{
	pSnakeNode pFood = malloc(sizeof(SnakeNode));
	pSnakeNode Cur = NULL;
	assert(pS);
	int flag = 1;
	while (flag)
	{
		GetRandFood(pFood);
		Cur = pS->_pSnake;
		while (Cur != NULL)
		{
			if (Cur->x != pFood->x && Cur->y != pFood->y)
				Cur = Cur->next;
			else break;
		}
		if(Cur == NULL)
		flag = 0;
	}
	pS->_pFood = pFood;
}

//6. �ߵ��ƶ�
int HasFood( pSnake pS , pSnakeNode pNextNode)
{
	if (pNextNode->x == pS->_pFood->x &&  pNextNode->y == pS->_pFood->y)
		return 1;
	else return 0;
}

void EatFood(pSnake pS, pSnakeNode pNextNode)
{
	assert(pS);
	assert(pNextNode);

	pNextNode->next = pS->_pSnake;
	pS->_pSnake = pNextNode;

	CreadeFood(pS);
	FoodPrint(pS);
}

void NEatFood(pSnake pS, pSnakeNode pNextNode)
{
	pSnakeNode Cur = NULL;

	assert(pS);
	assert(pNextNode);

	pNextNode->next = pS->_pSnake;
	pS->_pSnake = pNextNode;

	Cur = pS->_pSnake;
	while (Cur && Cur->next != NULL )
	{
		if (Cur->next->next == NULL)
		{
			SetPos(Cur->next->x, Cur->next->y);
			printf(" ");
			free(Cur->next);
			Cur->next = NULL;
			break;
		}
		Cur = Cur->next;
	}
}

void SnakeMove(pSnake pS)
{
	pSnakeNode NextNode = malloc(sizeof(SnakeNode));
	NextNode->x = pS->_pSnake->x;
	NextNode->y = pS->_pSnake->y;

	switch (pS->_Dir)
	{
	case UP: 
		NextNode->y -= 1;
		break;
	case DOWN:
		NextNode->y += 1;
		break;
	case LEFT:
		NextNode->x -= 2;
		break;
	case RIGHT:
		NextNode->x += 2;
		break;
	}

	if (HasFood(pS, NextNode))
		EatFood(pS, NextNode);
	else NEatFood(pS, NextNode);
}

//7. �������˶�
void SnakeRun(pSnake pS)
{
	do{
		if (GetAsyncKeyState(VK_UP) && pS->_Dir != DOWN)
			pS->_Dir = UP;
		if (GetAsyncKeyState(VK_DOWN) && pS->_Dir != UP)
			pS->_Dir = DOWN;
		if (GetAsyncKeyState(VK_LEFT) && pS->_Dir != RIGHT)
			pS->_Dir = LEFT;
		if (GetAsyncKeyState(VK_RIGHT) && pS->_Dir != LEFT)
			pS->_Dir = RIGHT;
		SnakeMove(pS);
		SnakePrint(pS);
		GomeOver(pS);
		Sleep(300);
	} while (pS->_status == OK);
}

//8. ��Ϸ����
int KillByWall(pSnake pS)
{
	if (pS->_pSnake->x == 0 || pS->_pSnake->x == 56 ||
		pS->_pSnake->y == 0 || pS->_pSnake->y == 27)
		return 1;
	else return 0;
}
int  KillBySelf(pSnake pS)
{
	pSnakeNode pCur = NULL;
	assert(pS);

	pCur = pS->_pSnake->next;
	while (pCur)
	{
		if(pS->_pSnake->x == pCur->x && pS->_pSnake->y == pCur->y)
		{
			return 1;
		}
		pCur = pCur->next;
	}
	return 0;
}
int KillByNo(pSnake pS)
{
	if (GetAsyncKeyState(VK_F1))
	{
		return 1;
	}
	else return 0;
}
void GomeOver(pSnake pS)
{
	if (KillByWall(pS))
	{
		pS->_status = KILL_BY_WALL;
		SetPos(22,13);
		printf("ײǽ����\n");
	}
	else if (KillBySelf(pS))
	{
		pS->_status = KILL_BY_WALL;
		SetPos(22, 13);
		printf("ײ���Լ�\n");
	}
	else if (KillByNo(pS))
	{
		pS->_status = KILL_NORMAL;
		SetPos(22, 13);
		printf("��ɱ\n");
	}
}

void SnakeStart(pSnake pS)
{
	CreateMap();
	InitSnake(pS);
	CreadeFood(pS);
	FoodPrint(pS);
	SnakePrint(pS);
	SnakeRun(pS);
}

//9. ��ӭ����
void Welcome()
{
	CreateMap();
	SetPos(14, 10);
	printf("*********************************\n");
	SetPos(14, 14);
	printf("*********************************\n");
	SetPos(16, 11);
	printf("�� ӭ �� �� ̰ �� �� �� Ϸ...\n");
	SetPos(20, 13);
	system("pause");
	system("cls");
	Sleep(500);
}
//��Ϸ
void game()
{
	Snake snake;
	pSnake pS = &snake;

	Welcome();
	SnakeStart(pS);
}



