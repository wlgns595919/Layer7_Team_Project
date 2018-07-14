#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<windows.h>

#define MAPSIZE 40
#define SPACE 0 // �����
#define WALL 1 // ��
#define BUSH 2 // Ǯ��
#define GUN 3 // ��
#define POTION 5 //  ����
#define GINP 7 // ���� ���� ������ �÷��̾� 1
#define BINP 8 // �ν��� �ִ� ������ �÷��̾� 1
#define PLAYER 9 // ���� �÷��̾� 1
#define GINP2 70 // ���� ���� ������ �÷��̾�2
#define BINP2 80 // �ν��� �ִ� ������ �÷��̾� 2
#define PLAYER2 90 // ���� �÷��̾� 2
#define COL GetStdHandle(STD_OUTPUT_HANDLE) // ���� �� ����
#define SHOOTSPEED 6 // ���� ������ �Ѿ˼ӵ�
#define BUSHSHOOTSPEED 4 // �ν����� ������ �Ѿ˼ӵ�
#define UP1 'w' // �÷��̾� 1 ����Ű
#define DOWN1 's' 
#define LEFT1 'a'
#define RIGHT1 'd'
#define P1SHOOT 'g' // �÷��̾� 1 ����Ű
#define UP2 72 // �÷��̾� 2 ����Ű
#define DOWN2 80
#define LEFT2 75
#define RIGHT2 77
#define P2SHOOT 32 // �÷��̾� 2 ����Ű
#define BULLET1 10 // p1�� �׳��Ѿ�
#define BUSHBULLET1 11 // p1�� �ν��� �ִ� �Ѿ�
#define BULLET2 12 // p2�� �׳��Ѿ�
#define BUSHBULLET2 13 // p2�� �ν��� �ִ� �Ѿ�

int playerX, playerY, playerX2, playerY2, flag = 0, flag2 = 0, gun_x, gun_y, potion_x, potion_y;
int p1 = 3, p2 = 3; // p1, p2 ���
float ginpst, ginpst2;
int p1see, p2see, p1_ShootX, p1_ShootY, p2_ShootX, p2_ShootY, Shoot_localtion1, Shoot_localtion2;

int map[MAPSIZE][MAPSIZE] = { // �� ����

	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },

};

void nocur(); // Ŀ���� �Ⱥ��̰����ִ� �Լ�
void win_lose(); // �÷��̾ �̰����� ȣ��Ǵ� �Լ�
void print_infor(); // �÷��̾��� ��� ������ ����ϴ� �Լ�
void moveplayer(int dx, int dy); // p1�� �̵��Լ�
void moveplayer2(int dx, int dy); // p2�� �̵��Լ�
void player(); // p1 �������� �Լ�
void player2(); // p2 �������� �Լ�
void wall(); // �� �������� �Լ�
void gun(); // �� �������� �Լ�
void potion(); // ���� �������� �Լ�
void bush(); // Ǯ�� �������� �Լ�
void printmap(); // ���� ����ϴ� �Լ�
void gotoxy(int x, int y); // Ư���� ��ǥ�� �̵��ϱ� ���ؼ� ����ϴ� �Լ�
void p1_print(); // p1�� ��� ���ִ� �Լ�
void bush_print(); // p1�� bush�� ��� ���ִ� �Լ�
void space_print(); // p1�� space�� ��� ���ִ� �Լ�
void binp_print(); // p1�� binp�� ��� ���ִ� �Լ�
void p2_print(); // p2�� ��� ���ִ� �Լ�
void bush2_print(); // p2�� bush�� ��� ���ִ� �Լ�
void space2_print(); // p2�� space�� ��� ���ִ� �Լ�
void binp2_print(); // p2�� binp�� ��� ���ִ� �Լ�
unsigned __stdcall shoot1(char* arg); // �÷��̾ ���� ���⿡ ���� �Ѿ��� �߻��ϴ� �Լ��� ȣ�����ִ� �Լ�(��(��)����� ����)
unsigned __stdcall shoot2(char* arg);
void printshoot(int bx, int by, int px, int py, int ShootSpeed, int player); // �Ѿ��� ��� ���ִ� �Լ�
void shootbufferdelete(int i, int player); // �Ѿ� �߻簡 �Ϸ�Ǿ����� �迭���ִ� �Ѿ˰��������� ��������
void printbullet(int bx, int by, int player);
void changebushbullet(int x, int y, int pleyer);
void clearxy(int x, int y);
void bulletspeedcontrol(int speed);
void keyinput();

int main() {
	nocur(); // Ŀ�� ����

	system("mode con cols=120 lines=41"); // �ܼ� â ũ�� ����

	srand(time(NULL)); // ��������
	int i, j;
	char playerInput;
	bush();
	wall();
	player();
	player2();
	printmap(); // �� �Լ��� ���� ���� ����ǰ� �������� ���� ���

	for (i = 0; i < MAPSIZE; i++)
	{
		for (j = 0; j < MAPSIZE; j++)
		{
			if (map[i][j] == 9) // �� ��ü�� ���ٰ� p1(9)�� ������ �׶��� i,j ��ǥ�� ���� y,x �������ٰ� ����
			{
				playerX = j;
				playerY = i;
			}
			if (map[i][j] == 90) { // ���� ���� ����� p2�� ����
				playerX2 = j;
				playerY2 = i;
			}
		}
	}

	float gunst = clock(), stpt = clock(), gunet, ginpet, ginpet2, etpt; // clock �Լ� �������� ������

	while (1) {

		print_infor(); // �÷��̾� ������ ���
		win_lose(); // � �÷��̾ �̰���� ��� ���̰����� �ƹ��͵� ��� ����

		gunet = clock() - gunst; // ���� �����ð����� �������� ���� �����Ҷ� clock ���־��� ���� clock �� ���� ó�� clock �� ���� ���ذ��� �����Ѵ�
		etpt = clock() - stpt; // ���� �����ð����� �������� ���� �����Ҷ� clock ���־��� ���� clock �� ���� ó�� clock �� ���� ���ذ��� �����Ѵ�

		if ((int)gunet >= 300) { // ���� ó���ð�~�������ð��� 15�� �̻��̸� �׶� gun�Լ��� �����ϰ� �ٽý���ǰԲ� gunst�� �ʱ�ȭ ���ش�
			for (int i = 0; i < 2; i++) {
				gun();
				gunst = clock();
			}
		}
		if ((int)etpt >= 300) { // ���� ó���ð�~�������ð��� 10�� �̻��̸� �׶� potion�Լ��� �����ϰ� �ٽý���ǰԲ� stpt�� �ʱ�ȭ ���ش�
			potion();
			stpt = clock();
		}

		ginpet = clock() - ginpst; // 15�ʰ� �Ǹ� ��ȿ���� ������Բ� �Ѱ� pinpst�� ���� �Ծ����� �Ʒ��ڵ忡�� clock�� ���־���
		if ((int)ginpet >= 15000) { // ó��~������ ������ 15���̻��̸� flag = 0 (���� ���� ����) �� �ϰ� �ٽ� ginpst �� �ʱ�ȭ ���ش�
			flag = 0;
		}
		ginpet2 = clock() - ginpst2; // ���� ���� ����� p2 ���� ����
		if ((int)ginpet2 >= 15000) {
			flag2 = 0;
		}

		playerInput = getch(); // �Է¹������� playerInput���ٰ� ����

		if (flag == 0) { // flag = 0 �϶�, �� ���� ���� �����϶�
			if (playerInput == LEFT1) {
				p1see = LEFT1;
				moveplayer(-1, 0);
			}
			else if (playerInput == RIGHT1) {
				p1see = RIGHT1;
				moveplayer(1, 0);
			}
			else if (playerInput == UP1) {
				p1see = UP1;
				moveplayer(0, -1);
			}
			else if (playerInput == DOWN1) {
				p1see = DOWN1;
				moveplayer(0, 1);
			}
		}
		else if (flag == 1) { // flag = 1 �϶�, �� ���� �ִ� �����϶�
			if (playerInput == LEFT1) {
				p1see = LEFT1;
				moveplayer(-1, 0);
			}
			else if (playerInput == RIGHT1) {
				p1see = RIGHT1;
				moveplayer(1, 0);
			}
			else if (playerInput == UP1) {
				p1see = UP1;
				moveplayer(0, -1);
			}
			else if (playerInput == DOWN1) {
				p1see = DOWN1;
				moveplayer(0, 1);
			}
			else if (playerInput == 'g') {
				if (map[playerY][playerX] == 0)
					Shoot_localtion1 = SHOOTSPEED;
				else
					Shoot_localtion1 = BUSHSHOOTSPEED;
				p1_ShootX = playerX;
				p1_ShootY = playerY;
				_beginthreadex(0, 0, shoot1, 0, 0, 0);
			}
		}
		if (flag2 == 0) { // ���� ���� ����� p2�� ����
			if (playerInput == LEFT2) {
				p2see = LEFT2;
				moveplayer2(-1, 0);
			}
			else if (playerInput == RIGHT2) {
				p2see = RIGHT2;
				moveplayer2(1, 0);
			}
			else if (playerInput == UP2) {
				p2see = UP2;
				moveplayer2(0, -1);
			}
			else if (playerInput == DOWN2) {
				p2see = DOWN2;
				moveplayer2(0, 1);
			}
		}
		else if (flag2 == 1) {
			if (playerInput == LEFT2) {
				p2see = LEFT2;
				moveplayer2(-1, 0);
			}
			else if (playerInput == RIGHT2) {
				p2see = RIGHT2;
				moveplayer2(1, 0);
			}
			else if (playerInput == UP2) {
				p2see = UP2;
				moveplayer2(0, -1);
			}
			else if (playerInput == DOWN2) {
				p2see = DOWN2;
				moveplayer2(0, 1);
			}
			else if (playerInput == P2SHOOT) {
				if (map[playerY2][playerX2] == 0)
					Shoot_localtion2 = SHOOTSPEED;
				else
					Shoot_localtion2 = BUSHSHOOTSPEED;
				p2_ShootX = playerX2;
				p2_ShootY = playerY2;
				_beginthreadex(0, 0, shoot2, 0, 0, 0);
			}
		}
	}
	return 0;
}

void nocur() {
	CONSOLE_CURSOR_INFO Cur;
	Cur.dwSize = 1;
	Cur.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Cur);
}

void moveplayer(int dx, int dy) {

	if (map[playerY + dy][playerX + dx] == SPACE) { // ���� ��ġ�� �� �����϶�

		if (map[playerY][playerX] == PLAYER || map[playerY][playerX] == GINP) { // ���� PLAYER �ų� GINP�� �����϶� (Ǯ���� �ƴҶ�)
			space_print(); // ����� ���
			playerX += dx; playerY += dy;
			p1_print(); // �״��� p1�� ��½�Ų��
			if (flag == 0)
				map[playerY][playerX] = PLAYER;
			else if (flag == 1)
				map[playerY][playerX] = GINP;
		}

		else { // ���� BINP �����ϋ� (Ǯ���϶�)
			bush_print(); // Ǯ���� ����Ѵ�
			playerX += dx; playerY += dy;
			p1_print(); // �״��� p1�� ��½�Ų��
			if (flag == 0)
				map[playerY][playerX] = PLAYER;
			else if (flag == 1)
				map[playerY][playerX] = GINP;
		}
	}

	else if (map[playerY + dy][playerX + dx] == BUSH) { // ���� ��ġ�� Ǯ���϶�

		if (map[playerY][playerX] == PLAYER || map[playerY][playerX] == GINP) { // ���� PAYER �ų� GINP �� �����϶� (Ǯ���� �ƴҶ�)
			space_print(); // �� ������ ����Ѵ�
			playerX += dx; playerY += dy;
			binp_print(); // �ʷϻ� ���� ����Ѵ�
		}

		else { // ���� BINP�� �����϶� (Ǯ���϶�)

			bush_print(); // Ǯ���� ����Ѵ�
			playerX += dx; playerY += dy;
			binp_print(); // �ʷϻ� ���� ����Ѵ�
		}
	}
	else if (map[playerY + dy][playerX + dx] == GUN) { // ���� ��ġ�� ���϶�
		if (map[playerY][playerX] == PLAYER || map[playerY][playerX] == GINP) { // ���� PAYER �ų� GINP �� �����϶� (Ǯ���� �ƴҶ�)
			space_print(); // ������� ����Ѵ�
		}
		else { // (Ǯ���϶�)
			bush_print(); // Ǯ���� ����Ѵ�
		}
		playerX += dx; playerY += dy;
		gotoxy(playerX, playerY);
		SetConsoleTextAttribute(COL, 4);
		printf("��");
		SetConsoleTextAttribute(COL, 15);
		map[playerY][playerX] = GINP;

		flag = 1; // flag �� 1�� ����
		ginpst = clock(); // �ѸԾ����� ī���� ����
	}
	else if (map[playerY + dy][playerX + dx] == POTION) { // ���� ��ġ�� �����϶�
		if (map[playerY][playerX] == PLAYER || map[playerY][playerX] == GINP) { // ���� PAYER �ų� GINP �� �����϶� (Ǯ���� �ƴҶ�)
			space_print(); // ������� ����Ѵ�
		}
		else { // (Ǯ���϶�)
			bush_print(); // Ǯ���� ����Ѵ� 
		}
		playerX += dx; playerY += dy;
		p1_print(); // p1�� ����Ѵ�
		if (flag == 0)
			map[playerY][playerX] = PLAYER;
		else if (flag == 1)
			map[playerY][playerX] = GINP;

		p1++; // ������ ������ p1 ����
	}
}

void moveplayer2(int dx, int dy) {

	if (map[playerY2 + dy][playerX2 + dx] == SPACE) { // ���� ��ġ�� �� �����϶�

		if (map[playerY2][playerX2] == PLAYER2 || map[playerY2][playerX2] == GINP2) { // ���� PLAYER �ų� GINP�� �����϶� (Ǯ���� �ƴҶ�)
			space2_print();
			playerX2 += dx; playerY2 += dy;
			p2_print();
			if (flag2 == 0)
				map[playerY2][playerX2] = PLAYER2;
			else if (flag2 == 1)
				map[playerY2][playerX2] = GINP2;
		}

		else { // ���� BINP �����ϋ� (Ǯ���϶�)
			bush2_print(); // Ǯ���� ����Ѵ�
			playerX2 += dx; playerY2 += dy;
			p2_print(); // �״��� p2�� ��½�Ų��
			if (flag2 == 0)
				map[playerY2][playerX2] = PLAYER2;
			else if (flag2 == 1)
				map[playerY2][playerX2] = GINP2;
		}
	}

	else if (map[playerY2 + dy][playerX2 + dx] == BUSH) { // ���� ��ġ�� Ǯ���϶�

		if (map[playerY2][playerX2] == PLAYER2 || map[playerY2][playerX2] == GINP2) { // ���� PAYER �ų� GINP �� �����϶� (Ǯ���� �ƴҶ�)
			space2_print(); // �� ������ ����Ѵ�
			playerX2 += dx; playerY2 += dy;
			binp2_print(); // �ʷϻ� ���� ����Ѵ�
		}

		else { // ���� BINP�� �����϶� (Ǯ���϶�)

			bush2_print(); // Ǯ���� ����Ѵ�
			playerX2 += dx; playerY2 += dy;
			binp2_print(); // �ʷϻ� ���� ����Ѵ�
		}
	}
	else if (map[playerY2 + dy][playerX2 + dx] == GUN) { // ���� ��ġ�� ���϶�
		if (map[playerY2][playerX2] == PLAYER2 || map[playerY2][playerX2] == GINP2) { // ���� PAYER �ų� GINP �� �����϶� (Ǯ���� �ƴҶ�)
			space2_print(); // ������� ����Ѵ�
		}
		else { // (Ǯ���϶�)
			bush2_print(); // Ǯ���� ����Ѵ�
		}
		playerX2 += dx; playerY2 += dy;
		gotoxy(playerX2, playerY2);
		SetConsoleTextAttribute(COL, 4);
		printf("��");
		SetConsoleTextAttribute(COL, 15);
		map[playerY2][playerX2] = GINP2;

		flag2 = 1; // flag2 �� 1�� ����
		ginpst2 = clock(); // �ѸԾ����� ī���� ����
	}
	else if (map[playerY2 + dy][playerX2 + dx] == POTION) { // ���� ��ġ�� �����϶�
		if (map[playerY2][playerX2] == PLAYER2 || map[playerY2][playerX2] == GINP2) { // ���� PAYER �ų� GINP �� �����϶� (Ǯ���� �ƴҶ�)
			space2_print(); // ������� ����Ѵ�
		}
		else { // (Ǯ���϶�)
			bush2_print(); // Ǯ���� ����Ѵ� 
		}
		playerX2 += dx; playerY2 += dy;
		p1_print(); // p2�� ����Ѵ�
		if (flag2 == 0)
			map[playerY2][playerX2] = PLAYER2;
		else if (flag2 == 1)
			map[playerY2][playerX2] = GINP2;

		p2++; // ������ ������ p2 ����
	}
}


void gotoxy(int x, int y) // Ŀ�� �̵� �Լ�
{
	COORD Pos;
	Pos.X = x * 2;
	Pos.Y = y;
	SetConsoleCursorPosition(COL, Pos);
}

void printmap() { // ���� ����ϴ� �Լ�

	int i, j;

	for (i = 0; i < MAPSIZE; i++) {
		for (j = 0; j < MAPSIZE; j++) { // �� ��ü�� �� ����
			switch (map[i][j]) { // �� ���ڿ� ���� �ٸ��� ���� ����� �ǵ��� �Ѵ�

			case WALL: printf("��"); break;
			case SPACE: printf("  "); break;
			case BUSH: SetConsoleTextAttribute(COL, 2); printf("��"); SetConsoleTextAttribute(COL, 15); break;
			case GUN: SetConsoleTextAttribute(COL, 4); printf("��"); SetConsoleTextAttribute(COL, 15); break;
			case PLAYER: SetConsoleTextAttribute(COL, 6); printf("��"); SetConsoleTextAttribute(COL, 15); break;
			case PLAYER2: SetConsoleTextAttribute(COL, 6); printf("��"); SetConsoleTextAttribute(COL, 15); break;
			}
		}
		printf("\n");
	}
}


void bush() { // Ǯ���� ���������� �ִ� �Լ�

	int i, j, k;
	srand(time(NULL)); // ������

	for (i = 0; i < 15; i++) { // Ǯ�� �� 15���� ����

		int random_x = (rand() % 33) + 1; // ������ ����ü�� �Ѿ�� �ʰ� ����
		int random_y = (rand() % 33) + 1; // ������ ����ü�� �Ѿ�� �ʰ� ����
		int dir = rand() % 2; // ���� �Ұ����� ���� �Ұ����� ����
		if (dir == 0) { // 0�϶�
			for (j = 0; j < 6; j++) {
				for (k = 0; k < 3; k++) {
					map[random_x + j][random_y + k] = 2; // ���� 3 * ���� 6ĭ�� Ǯ���� ���
				}
			}
		}
		else if (dir == 1) { // 1�϶�
			for (j = 0; j < 3; j++) {
				for (k = 0; k < 6; k++) {
					map[random_x + j][random_y + k] = 2; // ���� 6ĭ * ���� 3ĭ�� Ǯ���� ���
				}
			}
		}

	}
}

void wall() { // ���� ���������� �ִ� �Լ�

	int i, j, k, l = 0, ll = 0;
	srand(time(NULL)); // ������

	for (i = 0; i < 12; i++) {

		int random_x = (rand() % 31) + 1; // �� �ۿ� �������� �ʵ��� �صа�
		int random_y = (rand() % 31) + 1;// �� �ۿ� �������� �ʵ��� �صа�
		int dir = rand() % 4; // 4���� ���� ����
		if (dir == 0) {
			for (j = 0; j < 8; j++) {
				map[random_x + j][random_y] = 1; // ���η� 8ĭ ������
			}
		}
		else if (dir == 1) {
			for (j = 0; j < 8; j++) {
				map[random_x][random_y + j] = 1; // ���η� 8ĭ ������
			}
		}
		else if (dir == 2) {
			l = k = 0;
			for (j = 0; j < 4; j++) {
				for (k = 0; k < 2; k++) {
					map[random_x + l][random_y + ll] = 1; // ������� ��->�� ����
					l++;
				}
				ll++;
				l--;
			}
		}
		else if (dir == 3) {
			l = k = 0;
			for (j = 0; j < 4; j++) {
				for (k = 0; k < 2; k++) {
					map[random_x + l][random_y + ll] = 1; // ������� ��->�� ����
					l++;
				}
				ll--;
				l--;
			}
		}
	}
}

void gun() { // ���� ����ϴ� �Լ�

	int i;
	srand(time(NULL)); // ������

	while (1) {
		gun_x = (rand() % 38) + 1; // �� �ۿ� �������� �ʵ��� �صа�
		gun_y = (rand() % 38) + 1; // �� �ۿ� �������� �ʵ��� �صа�
		if (map[gun_y][gun_x] == SPACE) { // ������ ������϶��� ������ �ǵ�����
			map[gun_y][gun_x] = 3;
			gotoxy(gun_x, gun_y);
			SetConsoleTextAttribute(COL, 4); printf("��"); SetConsoleTextAttribute(COL, 15);
			break;
		}
		else
			continue;
	}
}

void potion() { // ������ ����ϴ� �Լ�

	int i;
	srand(time(NULL)); // ������

	while (1) {
		potion_x = (rand() % 38) + 1; // �� �ۿ� �������� �ʵ��� �صа�
		potion_y = (rand() % 38) + 1; // �� �ۿ� �������� �ʵ��� �صа�
		if (map[potion_y][potion_x] == SPACE) { // ������ ������϶��� ������ �ǵ�����
			map[potion_y][potion_x] = 5;
			gotoxy(potion_x, potion_y);
			SetConsoleTextAttribute(COL, 3); printf("��"); SetConsoleTextAttribute(COL, 15);
			break;
		}
		else
			continue;
	}
}

void player() { // p1 ���������� �ִ� �Լ�

	int i;
	srand(time(NULL));
	while (1) {
		int random_x = (rand() % 38) + 1;
		int random_y = (rand() % 38) + 1;
		if (map[random_y][random_x] == SPACE) { // ������� ����
			map[random_y][random_x] = PLAYER;
			break;
		}
		else
			continue;
	}

}

void player2() { // p2 ���������� �ִ� �Լ�

	int i;
	srand(time(NULL));
	while (1) {
		int random_x = (rand() % 38) + 1;
		int random_y = (rand() % 38) + 1;
		if (map[random_y][random_x] == SPACE) { // ������� ����
			map[random_y][random_x] = PLAYER2;
			break;
		}
		else
			continue;
	}

}

void p1_print() { // p1�� ������ִ� �Լ�
	gotoxy(playerX, playerY);
	if (flag == 0) {
		SetConsoleTextAttribute(COL, 6);
		printf("��"); // ���� �ȸ��� �����϶��� �����
		SetConsoleTextAttribute(COL, 15);
	}
	else if (flag == 1) {
		SetConsoleTextAttribute(COL, 4);
		printf("��"); // ���� ���� �����϶��� ������
		SetConsoleTextAttribute(COL, 15);
	}
}

void bush_print() {
	SetConsoleTextAttribute(COL, 2);
	gotoxy(playerX, playerY);
	printf("��"); // Ǯ�� ����� ���ش�
	SetConsoleTextAttribute(COL, 15);
	map[playerY][playerX] = BUSH;
}

void space_print() {
	gotoxy(playerX, playerY);
	printf("  "); // ������� ����� ���ش�
	map[playerY][playerX] = SPACE;
}

void binp_print() {
	gotoxy(playerX, playerY);
	SetConsoleTextAttribute(COL, 2);
	printf("��"); // �ʷϻ� ���� ���
	SetConsoleTextAttribute(COL, 15);
	map[playerY][playerX] = BINP;
}

void p2_print() {
	gotoxy(playerX2, playerY2);
	if (flag2 == 0) { // p2�� ������ִ� �Լ�
		SetConsoleTextAttribute(COL, 6);
		printf("��"); // ���� �ȸ��� �����϶��� �����
		SetConsoleTextAttribute(COL, 15);
	}
	else if (flag2 == 1) {
		SetConsoleTextAttribute(COL, 4);
		printf("��"); // ���� ���� �����϶��� ������
		SetConsoleTextAttribute(COL, 15);
	}
}

void bush2_print() {
	SetConsoleTextAttribute(COL, 2);
	gotoxy(playerX2, playerY2);
	printf("��"); // Ǯ�� ����� ���ش�
	SetConsoleTextAttribute(COL, 15);
	map[playerY2][playerX2] = BUSH;
}

void space2_print() {
	gotoxy(playerX2, playerY2);
	printf("  "); // ������� ����� ���ش�
	map[playerY2][playerX2] = SPACE;
}

void binp2_print() {
	gotoxy(playerX2, playerY2);
	SetConsoleTextAttribute(COL, 2);
	printf("��"); // �ʷϻ� ���� ���
	SetConsoleTextAttribute(COL, 15);
	map[playerY2][playerX2] = BINP2;
}

void print_infor() {
	int i;
	gotoxy(43, 6);
	printf("������ �� �÷��̾� ���� �� ������"); // UI ����
	for (i = 7; i <= 32; i++) {
		gotoxy(43, i);
		printf("��                       ��");
	}
	gotoxy(43, 33);
	printf("��������������������������������������������������");
	gotoxy(46, 15);
	printf("P1 ��� : %d", p1); // p1 ��� ���
	gotoxy(46, 20);
	printf("P2 ��� : %d", p2); // p2 ��� ���
}

void win_lose() {
	int i;
	if (p1 == 0) { // p1�� ����� 0�̸�
		gotoxy(43, 6);
		printf("������ �� �÷��̾� ���� �� ������"); // UI ����
		for (i = 7; i <= 32; i++) {
			gotoxy(43, i);
			printf("��                       ��");
		}
		gotoxy(43, 33);
		printf("��������������������������������������������������");
		gotoxy(47, 19);
		printf("P2 Winner!!        "); // p2 �¸� ���
		exit(0);
	}
	else if (p2 == 0) {
		gotoxy(43, 6);
		printf("������ �� �÷��̾� ���� �� ������"); // UI ����
		for (i = 7; i <= 32; i++) {
			gotoxy(43, i);
			printf("��                       ��");
		}
		gotoxy(43, 33);
		printf("��������������������������������������������������");
		gotoxy(47, 19);
		printf("P1 Winner!!        "); // p1 �¸� ���
		exit(0);
	}
}

unsigned __stdcall shoot1(char* arg) {
	int i, playersee = p1see, PX = p1_ShootX, PY = p1_ShootY, ShootSpeed = Shoot_localtion1;
	if (playersee == LEFT1) {
		printshoot(-1, 0, PX, PY, ShootSpeed, 1);
	}
	else if (playersee == RIGHT1) {
		printshoot(1, 0, PX, PY, ShootSpeed, 1);
	}
	else if (playersee == UP1) {
		printshoot(0, -1, PX, PY, ShootSpeed, 1);
	}
	else if (playersee == DOWN1) {
		printshoot(0, 1, PX, PY, ShootSpeed, 1);
	}
}

unsigned __stdcall shoot2(char* arg) {
	int i, playersee = p2see, PX = p2_ShootX, PY = p2_ShootY, ShootSpeed = Shoot_localtion2;
	if (playersee == LEFT2) {
		printshoot(-1, 0, PX, PY, ShootSpeed, 2);
	}
	else if (playersee == RIGHT2) {
		printshoot(1, 0, PX, PY, ShootSpeed, 2);
	}
	else if (playersee == UP2) {
		printshoot(0, -1, PX, PY, ShootSpeed, 2);
	}
	else if (playersee == DOWN2) {
		printshoot(0, 1, PX, PY, ShootSpeed, 2);
	}
}

void printshoot(int bx, int by, int px, int py, int ShootSpeed, int player) {
	if (player == 1) {
		while (1) {
			bulletspeedcontrol(ShootSpeed);
			if (map[py][px] == BULLET1) {
				clearxy(px, py);
				py += by;
				px += bx;
				if (map[py][px] == SPACE)
					printbullet(px, py, 1);
				else if (map[py][px] == BUSH)
					changebushbullet(px, py, 1);
				else if (map[py][px] == PLAYER2) {
					p2--;
					break;
				}
				else
					break;
			}
			else if (map[py][px] == BUSHBULLET1) {
				map[py][px] = BUSH;
				py += by;
				px += bx;
				if (map[py][px] == SPACE)
					printbullet(px, py, 1);
				else if (map[py][px] == BUSH)
					changebushbullet(px, py, 1);
				else if (map[py][px] == PLAYER2) {
					p2--;
					break;
				}
				else
					break;
			}
			else {
				py += by;
				px += bx;
				if (map[py][px] == SPACE)
					printbullet(px, py, 1);
				else if (map[py][px] == BUSH)
					changebushbullet(px, py, 1);
				else if (map[py][px] == PLAYER2) {
					p2--;
					break;
				}
				else
					break;
			}
		}
	}
	else {
		while (1) {
			bulletspeedcontrol(ShootSpeed);
			if (map[py][px] == BULLET2) {
				clearxy(px, py);
				py += by;
				px += bx;
				if (map[py][px] == SPACE)
					printbullet(px, py, 2);
				else if (map[py][px] == BUSH)
					changebushbullet(px, py, 2);
				else if (map[py][px] == PLAYER) {
					p1--;
					break;
				}
				else
					break;
			}
			else if (map[py][px] == BUSHBULLET2) {
				map[py][px] = BUSH;
				py += by;
				px += bx;
				if (map[py][px] == SPACE)
					printbullet(px, py, 2);
				else if (map[py][px] == BUSH)
					changebushbullet(px, py, 2);
				else if (map[py][px] == PLAYER) {
					p1--;
					break;
				}
				else
					break;
			}
			else {
				py += by;
				px += bx;
				if (map[py][px] == SPACE)
					printbullet(px, py, 2);
				else if (map[py][px] == BUSH)
					changebushbullet(px, py, 2);
				else if (map[py][px] == PLAYER) {
					p1--;
					break;
				}
				else
					break;
			}
		}
	}
}

void printbullet(int bx, int by, int player) {
	if (player == 1)
		map[by][bx] = BULLET1;
	else
		map[by][bx] = BULLET2;
	gotoxy(bx, by);
	printf("��");
}

void changebushbullet(int x, int y, int player) {
	if (player == 1)
		map[y][x] = BUSHBULLET1;
	else
		map[y][x] = BUSHBULLET2;
}

void clearxy(int x, int y) {
	gotoxy(x, y);
	printf("  "); // ������� ����� ���ش�
	map[y][x] = SPACE;
}

void bulletspeedcontrol(int speed) {
	int i;
	for (i = 0; i < 4; i++) {
		Sleep(speed);
		//keyinput();
	}
}