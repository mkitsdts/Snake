#include <game.h>

//隐藏光标
void HideCursor()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
	CursorInfo.bVisible = false; //隐藏控制台光标
	SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态
}


void Snake::Add_Length()
{

    snakelength=snakelength+1;
    body* nr=new body;
    nr->next=last;
    nr->position.x=snakehead.x;
    nr->position.y=snakehead.y;
    last=nr;

}

void Snake::Move_Body()
{

    if(last->next==nullptr)
    {
        last->position.x=snakehead.x;
        last->position.y=snakehead.y;
        return;
    }
    first->next=last;
    last=last->next;
    first->position.x=snakehead.x;
    first->position.y=snakehead.y;
    first=first->next;
    first->next=nullptr;

}

void Snake::Move_head(char arrow)
{

    if(arrow=='w'||arrow=='W')
    {
        snakehead.y=snakehead.y+1;
    }
    else if(arrow=='d'||arrow=='D')
    {
        snakehead.x=snakehead.x+1;
    }
    else if(arrow=='a'||arrow=='A')
    {
        snakehead.y=snakehead.y-1;
    }
    else if(arrow=='s'||arrow=='S')
    {
        snakehead.y=snakehead.y-1;
    }

}

bool Game::isTouchFood(Position snakehead)
{

    if(snakehead.x==food.x&&snakehead.y==food.y)
    {
        return true;
    }
    return false;

}

void Game::Draw(body* last, Position snakehead)
{

    system("cls");

    if(last==nullptr)
    {
        return;
    }
    
    std::vector <std::vector<char>> data(15,std::vector<char>(15,' '));
    body* current=last;
    data[snakehead.x][snakehead.y]='@';
    data[food.x][food.y]='$';
    while(current!=nullptr)
    {
        data[current->position.x][current->position.y]='^';
        current=current->next;
    }
    for(int i=0;i<MAP_X+2;++i)
    {
        for(int j=0;j<MAP_Y+2;++j)
        {
            if(i==0||j==0||j==16||i==16)
            {
                std::cout<<"#";
                continue;
            }
            std::cout<<data[i][j];
        }
        std::cout<<"\n";
    }
}

bool Game::issnakeBitWall(Position snakehead, char arrow)
{
   if((snakehead.x<0||snakehead.x>15||snakehead.y<0||snakehead.y>15)||(snakehead.x==0&&(arrow=='S'||arrow=='s'))||
   (snakehead.y==0&&(arrow=='A'||arrow=='a'))||(snakehead.x==15&&(arrow=='W'||arrow=='w'))||(snakehead.y==0&&(arrow=='A'||arrow=='a')))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Game::issnakeBitBody(body* last, Position snakehead)
{

    body* current=last;
    while(current!=nullptr)
    {
        if(current->position.x== snakehead.x&&current->position.y== snakehead.y)
        {
            return true;
        }
        current=current->next;
    }
    return false;
}

std::vector <int> CreateFood()
{
    //生成一个0-14范围的随机数
    srand(time(0));
    std::vector<int> num;
    int random_num=rand();
    num.push_back(random_num);
    srand(time(0));
    random_num=rand();
    num.push_back(random_num);
    return num;
}

void Game::Start()
{
    //通过是否撞墙判断游戏是否继续运行
    bool isGameOver=false;
    std::vector <int> food=Game::CreateFood();
    Snake mysnake;
    HideCursor();
    Draw(mysnake.last, mysnake.snakehead);
    if(_kbhit)
    {
        while(!isGameOver)
        {
            char arrow=_getch();
            while(1)
            {
                if(mysnake.snakelength==225)
                {
                    std::cout<<"You are winner"<<std::endl;
                }
                if(_kbhit())
                {
                    arrow=_getch();
                    mysnake.Move_head(arrow);
                    mysnake.Move_Body();
                    //判断是否撞墙
                    if(issnakeBitWall(mysnake.snakehead,arrow)||issnakeBitBody(mysnake.last,mysnake.snakehead))
                    {
                        isGameOver=true;
                        system("cls");
                        std::cout<<"Game Over"<<std::endl;
                        break;
                    }
                    if(Game::isTouchFood(mysnake.snakehead))
                    {
                        mysnake.Add_Length();
                        mysnake.Move_head(arrow);
                        food=Game::CreateFood();
                    }
                    Draw(mysnake.last,mysnake.snakehead);
                    //绘制图后暂停1s
                    Sleep(1000);
                }
                else
                {
                    mysnake.Move_head(arrow);
                    mysnake.Move_Body();
                    if(issnakeBitWall(mysnake.snakehead,arrow)||issnakeBitBody(mysnake.last,mysnake.snakehead))
                    {
                    isGameOver=true;
                    system("cls");
                    std::cout<<"Game Over"<<std::endl;
                    break;
                    }
                    if(Game::isTouchFood(mysnake.snakehead))
                    {
                        mysnake.Add_Length();
                        food=Game::CreateFood();
                    }
                    Draw(mysnake.last,mysnake.snakehead);
                    Sleep(1000);
                }

            }
        }
    }

}
