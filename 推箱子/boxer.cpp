/****************��������ϷDEMO*******************
 *
 * ���ܣ�1.ʵ�ֻ���easyx����������ͼ�δ���
 *		 2.ʵ�ָ��ݵ�ͼ�����ã���ʾ��������Ϸ����
 *       3.��������Ϸ����:��һ��
 *		   1��ͨ������������С�ˣ��ڵ�ͼ������
 *         2) ���߷�����ǽ�ڣ�������
 *         3�����߷��������ӣ�����ʱ��������
 *
 * ���룺��
 *
 * �����ʵ����������Ϸ
 *
 **************************************************/

#include <graphics.h>
#include <windows.h>
#include <conio.h>

//�궨��
#define SCREEN_WIDTH  800	//��Ļ���
#define SCREEN_HEIGHT 650	//��Ļ�߶�
#define LINE	9			//����
#define COLUMNS 12			//����
#define RATIO	50			//ÿ��ͼ���С
#define START_X 100			//ƫ����X
#define START_Y 100			//ƫ����Y

//�궨����Ƽ� 
#define KEY_UP		'w'
#define KEY_LEFT	'a'
#define KEY_RIGHT	'd'
#define KEY_DOWN	'x'
#define KEY_QUIT	'q'

typedef enum _PROPS {
	WALL,     //ǽ
	FLOOR,    //�ذ�
	BOX_DES,  //����Ŀ�ĵ�
	MAN,      //С��
	BOX,      //����
	HIT,      //��������Ŀ��
	MAN_DES,  //��վ������Ŀ�ĵ���
	ALL
}PROPS;

typedef struct _POS POS;
struct _POS {
	int line;	//��ϷС�˵���
	int column;	//��ϷС�˵���
};
#define isValid(pos)  pos.line>=0 && pos.line < LINE && pos.column >=0 && pos.column < COLUMNS

//��Ϸ���Ʒ�����
typedef enum _DIRECTION
{
	UP,
	DOWN,
	LEFT,
	RIGHT
}DIRECTION;

//��Ϸ��ͼ���壺0:ǽ��1���ذ壻2������Ŀ�ĵأ�3��С�ˣ�4������;5:����Ŀ�ꣻ6����վ��Ŀ�ĵ���
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

//����ȫ�ֱ���
IMAGE images[ALL];	//��ʾ��ͼƬ����
POS man;			//�˵�λ��

//��������
void changeMap(POS pos, PROPS prop);
void gameControl(DIRECTION direct);

int main(void) {
	//1. ��ʼ������
	initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);

	//2. �����زĶ���
	IMAGE img;
	loadimage(&images[WALL], "wall_right.bmp", RATIO, RATIO, true);
	loadimage(&images[FLOOR], "floor.bmp", RATIO, RATIO, true);
	loadimage(&images[BOX_DES], "des.bmp", RATIO, RATIO, true);
	loadimage(&images[MAN], "man.bmp", RATIO, RATIO, true);
	loadimage(&images[BOX], "box.bmp", RATIO, RATIO, true);
	loadimage(&images[HIT], "box.bmp", RATIO, RATIO, true);
	loadimage(&images[MAN_DES], "man.bmp", RATIO, RATIO, true);

	//3. ���ݵ�ͼ���壬����Ӧ��ͼƬ
	for (int i = 0; i < LINE; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			if (map[i][j] == 3) {
				man.line   = i;
				man.column = j;
			}
			putimage(START_X+j* RATIO, START_Y+i* RATIO, &images[map[i][j]]);
		}
	}
	
	//3. �ȼ����ƣ�conio.h��
	bool quit = false;
	do {
		if (_kbhit()) { //��Ұ���
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
	if (isValid(next_pos) && map[next_pos.line][next_pos.column] == FLOOR) {	//С���ƶ���ǰ����:�ذ�,���Ҳ��Ǳ߽�
		if (map[man.line][man.column] == MAN_DES) {
			changeMap(man, BOX_DES);
			changeMap(next_pos, MAN);
			man = next_pos;
		}
		else {
			changeMap(next_pos, MAN);					//С��ǰ��һ��,ԭ���ذ�ͼƬ,��ΪС��ͼƬ
			changeMap(man, FLOOR);						//ԭ��С�˵ط���ͼƬ,��Ϊ�ذ�
			man = next_pos;								//����С�˵�����
		}

	}
	else if (isValid(next_pos) && map[next_pos.line][next_pos.column] == BOX_DES) {	//С���ƶ���ǰ��:������Ŀ�ĵ�,���Ҳ��Ǳ߽�
		changeMap(next_pos, MAN_DES);					//С��ǰ��һ��,ԭ������Ŀ�ĵ�ͼƬ,��ΪС����Ŀ�ĵص�ͼƬ
		changeMap(man, FLOOR);							//ԭ��С�˵ط���ͼƬ,��Ϊ�ذ�
		man = next_pos;									//����С�˵�����
	}

}
