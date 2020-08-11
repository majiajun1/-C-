#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#define MAX 100
void suiji()
{
	srand((unsigned int)time(NULL));
}
typedef class pointXY
{
public:
	int x, y;

}MYPOINT;

HWND hwnd = NULL;

class mySnake
{
private:
	
	int num;
	MYPOINT xy[MAX];
	char position;
public:
	 mySnake()  ;
	 int sudu;
	 void drawSnake();
	void movesnake();
	void keyDown();
	int snakedie();
	friend class myFood;
	


}snake;


class myFood
{
private:
	MYPOINT foodxy;
	
	int eatGrade;
public:
	int flag;
	myFood();
	void drawfood();
	void eatfood();
	void beichi();
	friend class mySnake;
}food;

enum movPosition{right,left,down,up};


mySnake::mySnake()
{
	snake.xy[2].x = 0;
	snake.xy[2].y = 0;
	snake.xy[1].x = 10;
	snake.xy[1].y = 0;
	snake.xy[0].x = 20;
	snake.xy[0].y = 0;
	snake.num = 3;
	snake.position = right;
	snake.sudu = 250;
}


void mySnake::drawSnake()
{
	for (int i = 0; i < snake.num; i++)  //节数
	{
		setlinecolor(RED);
		setfillcolor(GREEN);
		fillrectangle(snake.xy[i].x, snake.xy[i].y, snake.xy[i].x + 10, snake.xy[i].y + 10);  //这一段是一个正方形
	}

}


void mySnake::movesnake()
{
	for (int i = snake.num - 1; i > 0; i--)
	{
		snake.xy[i].x = snake.xy[i - 1].x;
		snake.xy[i].y = snake.xy[i - 1].y;


	}
	switch (snake.position)
	{
	case right:
		snake.xy[0].x += 10;
		break;
	case left:snake.xy[0].x -= 10;
		break;
	case down:snake.xy[0].y += 10;

		break;
	case up:snake.xy[0].y -= 10;
		break;

	}

}


void mySnake::keyDown()
{
	char userkey = '\0';
	userkey = _getch();
	switch (userkey)
	{
	case 'w':
	case'W':
	case 38:
		if (snake.position != down)
		{
			snake.position = up;

		}
		break;
	case's':
	case'S':
	case 40:
		if (snake.position != up)
		{
			snake.position = down;
		}
		break;
	case 'a':
	case 'A':
	case 37:
		if (snake.position != right)
		{
			snake.position = left;

		}
		break;
	case 'd':
	case'D':
	case 39:
		if (snake.position != left)
		{
			snake.position = right;

		}

	}



}

myFood::myFood()
{
	food.flag = 1;
	food.foodxy.x = rand() % 64 * 10;
	food.foodxy.y = rand() % 48 * 10;
	
	for (int i = 0; i < snake.num; i++)
	{
		if (food.foodxy.x == snake.xy[i].x && food.foodxy.y == snake.xy[i].y)
		{
			food.foodxy.x = rand() % 64 * 10;
			food.foodxy.y = rand() % 48 * 10;
		}

	}

}


void myFood::drawfood()
{

	fillrectangle(food.foodxy.x,food.foodxy.y, food.foodxy.x + 10,food.foodxy.y + 10);


}

void myFood::eatfood()
{

	if (snake.xy[0].x == food.foodxy.x && food.foodxy.y == snake.xy[0].y)
	{
		snake.num++;
		snake.sudu -= 5;
		food.eatGrade += 100;
		food.flag = 0;

	}


}



int mySnake::snakedie()
{
	char grade[100] = { 0 };
	sprintf_s(grade, "%d", food.eatGrade);
	setbkmode(TRANSPARENT);
	settextcolor(RED);
	outtextxy(580, 20, "分数：");
	outtextxy(620, 20, grade);


	if (snake.xy[0].x > 640 || snake.xy[0].x < 0 || snake.xy[0].y>480 || snake.xy[0].y < 0)
	{
		MessageBox(hwnd, "GG，你没了", "撞墙死亡", 0);
		return 1;
	}
	for (int i = 1; i < snake.num; i++)
	{
		if (snake.xy[0].x == snake.xy[i].x && snake.xy[i].y == snake.xy[0].y)
		{
			MessageBox(hwnd, "GG，你没了", "你吃到自己了", 0);
			return 1;

		}

	}
	return 0;
}

void myFood::beichi()
{
	 
	 
		food.foodxy.x = rand() % 64 * 10;
		food.foodxy.y = rand() % 48 * 10;
		food.flag = 1;
		for (int i = 0; i < snake.num; i++)
		{
			if (food.foodxy.x == snake.xy[i].x && food.foodxy.y == snake.xy[i].y)
			{
				food.foodxy.x = rand() % 64 * 10;
				food.foodxy.y = rand() % 48 * 10;
			}

		}
	 
	 


}


int main()
{
	suiji();
	hwnd = initgraph(640, 480);
	setbkcolor(WHITE);
	cleardevice();
	
	 
	while (1)
	{
		cleardevice(); //路径刷掉
	
		
		food.drawfood();
		snake.drawSnake();
		snake.movesnake();
		food.eatfood();
		if (food.flag == 0)
		{
			food.beichi();
		}
		if (snake.snakedie())
		{
			break;

		}
		Sleep(100);
		while (_kbhit())
		{

			snake.keyDown();

		}



	}


	getchar();
	closegraph();

	system("Pause");
	return 0;
}