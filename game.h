#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <time.h>
#define MAP_X 15
#define MAP_Y 15

//坐标
struct Position
{
    int x;
    int y;
};

//身躯位置
struct body
{
    Position position;
    body* next;
};

//蛇的数据
class  Snake
{
public:
    int snakelength;
    Position snakehead;
    //指向最靠近头的一节身躯
    body* first;
    //指向身躯最后一节
    body* last;
    //吃到物品后头向前运动，身躯长度不变
    void Add_Length();
    //移动时身躯的调整
    void Move_Body();
    //移动时头部的调整
    void Move_head(char arrow);
    Snake()
    {
        snakelength=0;
        snakehead.x=8;
        snakehead.y=8;
        last=new body;
        last->next=nullptr;
        last->position.x=-1;
        last->position.y=-1;
        first=last;
    }
};

//游戏规则
class Game
{
public:
//游戏主体
void Start();
//判断是否撞墙
bool issnakeBitWall(Position snakehead, char arrow);
//判断是否撞到身躯
bool issnakeBitBody(body* head, Position snakehead);
//判断是否吃到食物
bool isTouchFood(Position snakehead);
//绘制图像
void Draw(body* last, Position snakehead);
//随机生成食物
std::vector <int> CreateFood();
//构造函数
Game()
{
    std::vector <int> temp=CreateFood();
    food.x=temp[0];
    food.y=temp[1];
    score=0;
}

private:
//得分
long long score;
Position food;
};

#endif GAME_H