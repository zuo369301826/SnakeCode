
#ifndef _SNAKE_H_
#define _SNAKE_H_

#define WALL "■"
#define FOOD "●"
#define SNAKE "□"

#define INIT_X 24 //初始坐标
#define INIT_Y 3

//蛇的状态
enum Status
{	
	OK,			//正常
	KILL_BY_SELF,	//撞到自己
	KILL_BY_WALL,	//撞墙
	KILL_NORMAL     //自杀
};

//蛇得方向
enum Dir 
{	UP,DOWN,LEFT,RIGHT	};


//节点
typedef struct Node
{
	struct Node *next;//下一个节点
	int x;//该节点x坐标
	int y;//该节点y坐标
}SnakeNode,*pSnakeNode;


//蛇结构体
typedef struct Snake
{
	pSnakeNode _pSnake;//指向蛇
	pSnakeNode _pFood;//食物
	enum status _status;//蛇的状态
	enum Dir _Dir;//蛇的行走方向
	int SleepTime;//蛇的停留时长
}Snake ,*pSnake;


//1.设置坐标
void SetPos(int x, int y);
//2.建立地图
void CreateMap();
//3.初始化蛇
void InitSnake(pSnake pS);
//4.打印
void SnakePrint(pSnake pS);
void FoodPrint(pSnake pS);
//5. 设置食物
void CreadeFood(pSnake pS);
//6. 蛇移动
void SnakeMove(pSnake ps);
//7. 控制蛇运动
void SnakeRun(pSnake pS);
//8. 游戏结束
int  KillByWall(pSnake pS);
int  KillBySelf(pSnake pS);
int  KillByNo(pSnake pS);
void GomeOver(pSnake pS);
//9. 欢迎界面
void Welcome();


#endif // !_SNAKE_H_
