
#ifndef _SNAKE_H_
#define _SNAKE_H_

#define WALL "��"
#define FOOD "��"
#define SNAKE "��"

#define INIT_X 24 //��ʼ����
#define INIT_Y 3

//�ߵ�״̬
enum Status
{	
	OK,			//����
	KILL_BY_SELF,	//ײ���Լ�
	KILL_BY_WALL,	//ײǽ
	KILL_NORMAL     //��ɱ
};

//�ߵ÷���
enum Dir 
{	UP,DOWN,LEFT,RIGHT	};


//�ڵ�
typedef struct Node
{
	struct Node *next;//��һ���ڵ�
	int x;//�ýڵ�x����
	int y;//�ýڵ�y����
}SnakeNode,*pSnakeNode;


//�߽ṹ��
typedef struct Snake
{
	pSnakeNode _pSnake;//ָ����
	pSnakeNode _pFood;//ʳ��
	enum status _status;//�ߵ�״̬
	enum Dir _Dir;//�ߵ����߷���
	int SleepTime;//�ߵ�ͣ��ʱ��
}Snake ,*pSnake;


//1.��������
void SetPos(int x, int y);
//2.������ͼ
void CreateMap();
//3.��ʼ����
void InitSnake(pSnake pS);
//4.��ӡ
void SnakePrint(pSnake pS);
void FoodPrint(pSnake pS);
//5. ����ʳ��
void CreadeFood(pSnake pS);
//6. ���ƶ�
void SnakeMove(pSnake ps);
//7. �������˶�
void SnakeRun(pSnake pS);
//8. ��Ϸ����
int  KillByWall(pSnake pS);
int  KillBySelf(pSnake pS);
int  KillByNo(pSnake pS);
void GomeOver(pSnake pS);
//9. ��ӭ����
void Welcome();


#endif // !_SNAKE_H_
