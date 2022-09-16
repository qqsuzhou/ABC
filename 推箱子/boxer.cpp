/****************推箱子游戏DEMO*******************
 *
 * 功能：1.实现基于easyx轻量级桌面图形处理
 *		 2.实现根据地图的设置，显示推箱子游戏界面
 *       3.推箱子游戏控制:第一步
 *		   1）通过按键，控制小人，在地图内行走
 *         2) 行走方向是墙壁，不能走
 *         3）行走方向是箱子，（暂时）不能走
 *
 * 输入：无
 *
 * 输出：实现推箱子游戏
 *
 **************************************************/

#include <graphics.h>
#include <windows.h>
#include <conio.h>

//宏定义
#define SCREEN_WIDTH  800	//屏幕宽度
#define SCREEN_HEIGHT 650	//屏幕高度
#define LINE	9			//行数
#define COLUMNS 12			//列数
#define RATIO	50			//每个图标大小
#define START_X 100			//偏移量X
#define START_Y 100			//偏移量Y

//宏定义控制键 
#define KEY_UP		'w'
#define KEY_LEFT	'a'
#define KEY_RIGHT	'd'
#define KEY_DOWN	'x'
#define KEY_QUIT	'q'

typedef enum _PROPS {
	WALL,     //墙
	FLOOR,    //地板
	BOX_DES,  //箱子目的地
	MAN,      //小人
	BOX,      //箱子
	HIT,      //箱子命中目标
	MAN_DES,  //人站在箱子目的地上
	ALL
}PROPS;

typedef struct _POS POS;
struct _POS {
	int line;	//游戏小人的行
	int column;	//游戏小人的列
};
#define isValid(pos)  pos.line>=0 && pos.line < LINE && pos.column >=0 && pos.column < COLUMNS

//游戏控制方向定义
typedef enum _DIRECTION
{
	UP,
	DOWN,
	LEFT,
	RIGHT
}DIRECTION;

//游戏地图定义：0:墙；1：地板；2：箱子目的地；3：小人；4：箱子;5:命中目标；6：人站在目的地上
int map[LINE][COLUMNS] = {
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
{ 0, 1, 4, 1, 0, 2, 1, 0, 2, 1, 0, 0 },
{ 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0 },
{ 0, 1, 0, 2, 0, 1, 1, 4, 1, 1, 1, 0 },
{ 0, 1, 1, 1, 0, 3, 1, 1, 1, 4, 1, 0 },
{ 0, 1, 2, 1, 1, 4, 1, 1, 1, 1, 1, 0 },
{ 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },

};

//定义全局变量
IMAGE images[ALL];	//显示的图片类型
POS man;			//人的位置

//函数声明
void changeMap(POS pos, PROPS prop);
void gameControl(DIRECTION direct);

int main(void) {
	//1. 初始化窗口
	initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);

	//2. 加载素材定义
	IMAGE img;
	loadimage(&images[WALL], "wall_right.bmp", RATIO, RATIO, true);
	loadimage(&images[FLOOR], "floor.bmp", RATIO, RATIO, true);
	loadimage(&images[BOX_DES], "des.bmp", RATIO, RATIO, true);
	loadimage(&images[MAN], "man.bmp", RATIO, RATIO, true);
	loadimage(&images[BOX], "box.bmp", RATIO, RATIO, true);
	loadimage(&images[HIT], "box.bmp", RATIO, RATIO, true);
	loadimage(&images[MAN_DES], "man.bmp", RATIO, RATIO, true);

	//3. 根据地图定义，填充对应的图片
	for (int i = 0; i < LINE; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			if (map[i][j] == 3) {
				man.line   = i;
				man.column = j;
			}
			putimage(START_X+j* RATIO, START_Y+i* RATIO, &images[map[i][j]]);
		}
	}
	
	//3. 热键控制（conio.h）
	bool quit = false;
	do {
		if (_kbhit()) { //玩家按键
			char ch = _getch();
			if (ch == KEY_UP) {
				gameControl(UP);
			}
			else if (ch == KEY_DOWN) {
				gameControl(DOWN);
			}
			else if (ch == KEY_LEFT) {
				gameControl(LEFT);
			}
			else if (ch == KEY_RIGHT) {
				gameControl(RIGHT);
			}
			else if (ch == KEY_QUIT) {
				quit = true;
			}
		}
		Sleep(100);	//100ms
	} while (quit == false);

	system("pause");
	return 0;

}

void changeMap(POS pos, PROPS prop) {
	map[pos.line][pos.column] = prop;
	putimage(START_X + pos.column * RATIO, START_Y + pos.line * RATIO, &images[prop]);
}

void gameControl(DIRECTION direct) {
	POS next_pos = man;
	switch (direct) {
	case UP:
		next_pos.line--;
		//next_next_pos.x -= 2;
		break;
	case DOWN:
		next_pos.line++;
		//next_next_pos.x += 2;
		break;
	case LEFT:
		next_pos.column--;
		//next_next_pos.y -= 2;
		break;
	case RIGHT:
		next_pos.column++;
		//next_next_pos.y += 2;
		break;
	}
	if (isValid(next_pos) && map[next_pos.line][next_pos.column] == FLOOR) {	//小人移动的前方是:地板,并且不是边界
		if (map[man.line][man.column] == MAN_DES) {
			changeMap(man, BOX_DES);
			changeMap(next_pos, MAN);
			man = next_pos;
		}
		else {
			changeMap(next_pos, MAN);					//小人前进一格,原来地板图片,改为小人图片
			changeMap(man, FLOOR);						//原来小人地方的图片,改为地板
			man = next_pos;								//更新小人的坐标
		}

	}
	else if (isValid(next_pos) && map[next_pos.line][next_pos.column] == BOX_DES) {	//小人移动的前方:是箱子目的地,并且不是边界
		changeMap(next_pos, MAN_DES);					//小人前进一格,原来箱子目的地图片,改为小人在目的地的图片
		changeMap(man, FLOOR);							//原来小人地方的图片,改为地板
		man = next_pos;									//更新小人的坐标
	}

}
