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
#define SHOOTSPEED 5 // ���� ������ �Ѿ˼ӵ�
#define BUSHSHOOTSPEED 3 // �ν����� ������ �Ѿ˼ӵ�
#define UP1 'w' // �÷��̾� 1 ����Ű
#define DOWN1 's' 
#define LEFT1 'a'
#define RIGHT1 'd'
#define P1SHOOT 32 // �÷��̾� 1 ����Ű
#define UP2 72 // �÷��̾� 2 ����Ű
#define DOWN2 80
#define LEFT2 75
#define RIGHT2 77
#define P2SHOOT '+' // �÷��̾� 2 ����Ű
#define BULLETS 20 // �ִ� �Ѿ� ����
#define BULLET1 10 // p1�� �׳��Ѿ�
#define BUSHBULLET1 11 // p1�� �ν��� �ִ� �Ѿ�
#define BULLET2 12 // p2�� �׳��Ѿ�
#define BUSHBULLET2 13 // p2�� �ν��� �ִ� �Ѿ�
#define P1BULLETCOLOR 5 // p1�� �Ѿ� ��
#define P2BULLETCOLOR 6 // p2�� �Ѿ� ��
#define DISTANCEATTACK 0.5 // �Ѿ� ����(���ݼӵ�)
#define MAP_RESET 'y' // ���¹�ư

int playerX, playerY, playerX2, playerY2, flag = 0, flag2 = 0, gun_x, gun_y, potion_x, potion_y;
int p1 = 3, p2 = 3; // p1, p2 ���
float ginpst, ginpst2;
int p1_ShootX[BULLETS], p1_ShootY[BULLETS], p1_Shoot_See[BULLETS], p1_Now_See, p1_ShootSpeed[BULLETS], p1Bullets = 0, p1DeleteBullets = 0;// �÷��̾���� �Ѿ��� x, y��ǥ, �����ִ¹���, �Ѿ˼ӵ�, �Ѿ˰���
int p2_ShootX[BULLETS], p2_ShootY[BULLETS], p2_Shoot_See[BULLETS], p2_Now_See, p2_ShootSpeed[BULLETS], p2Bullets = 0, p2DeleteBullets = 0;
int breakshoot = 0; // Shoot�Լ� �ߺ����� ����
float gundis1_st, gundis2_st; // �Ѿ� ������� ���� �ð��� �����ϴ� ����
int bulletload1 = 1, bulletload2 = 1; // ���ݼӵ����� ���� �� ��� �ϴ� ����
float gunst, stpt; // ������ ���� �ð��� ��� �Լ�

int map[MAPSIZE][MAPSIZE];

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
void shoot1(); // �÷��̾ ���� ���⿡ ���� �Ѿ��� �߻��ϴ� �Լ��� ȣ�����ִ� �Լ�
void printshoot(int i, int bx, int by, int player); // �Ѿ��� ��� ���ִ� �Լ�
void shootbufferdelete(int i, int player); // �Ѿ� �߻簡 �Ϸ�Ǿ����� �迭���ִ� �Ѿ˰��������� ��������
void printbullet(int i, int player); // �Ѿ��� ������ִ� �Լ�
void clearxy(int x, int y); // (x, y)�� �����ִ� �Լ�
void bulletspeedcontrol(int speed); // �Ѿ��� �ӵ��� �������ִ� �Լ�
void keyinput(); // �÷��̾ �Է��� ������ ó�����ִ� �Լ�
void bulletload(double dissave1, double dissave2); // �Ѿ� ���ݼӵ��� �������ִ� �Լ�
void itemrespawn(int repeat); // �������� �����ð����� �������ִ��Լ�
void map_reset(); // Ȥ�ö� ������� �̻��ϰ� �ɰ�� ���� �ʱ�ȭ �����ִ� �Լ�
void gameplay(); // ��ü���� ������ ��ϴ� �Լ�

int main() {
	nocur(); // Ŀ�� ����

	system("mode con cols=120 lines=41"); // �ܼ� â ũ�� ����

	gunst = clock(); // ������ ���� �ð��� ��������
	stpt = clock();

	srand(time(NULL)); // ��������
	map_reset();
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
		print_infor();
		win_lose();
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
		p2_print(); // p2�� ����Ѵ�
		if (flag2 == 0)
			map[playerY2][playerX2] = PLAYER2;
		else if (flag2 == 1)
			map[playerY2][playerX2] = GINP2;

		p2++; // ������ ������ p2 ����
		print_infor();
		win_lose();
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
		Sleep(3000);
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
		Sleep(3000);
		exit(0);
	}
}

void shoot1() {
	breakshoot = 0; // �Լ��� ù��°�� ���������� breakshoot������ 0���ιٲ�
	int i, j;
	while (1) {
		if (breakshoot == 1 || (p1Bullets == 0 && p2Bullets == 0)) // �ٸ��Լ��� ������������ ���÷��̾� �Ѿ��� ��� �ʿ��� ��������� �ݺ��� ����
			break;
		for (i = 0; i < p1Bullets; i++) { // �Ѿ� ������ŭ �ݺ�
			bulletspeedcontrol(p1_ShootSpeed[i] / (p1Bullets + p2Bullets)); // �Ѿ��� ���󰡴� �ӵ� ����
			if (p1_Shoot_See[i] == LEFT1) { // �÷��̾ �����ִ� ���⿡ ���� �Ѿ��� ���󰡴� ���� ����
				printshoot(i, -1, 0, 1);
			}
			else if (p1_Shoot_See[i] == RIGHT1) {
				printshoot(i, 1, 0, 1);
			}
			else if (p1_Shoot_See[i] == UP1) {
				printshoot(i, 0, -1, 1);
			}
			else if (p1_Shoot_See[i] == DOWN1) {
				printshoot(i, 0, 1, 1);
			}
			i -= p1DeleteBullets; // �Ѿ��� �ε��ļ� �������� ���� �Ѿ��� ����ǵ��� ��
			p1DeleteBullets = 0;
		}
		for (j = 0; j < p2Bullets; j++) { // p1�� ����
			bulletspeedcontrol(p2_ShootSpeed[i] / (p1Bullets + p2Bullets));
			if (p2_Shoot_See[i] == LEFT2) {
				printshoot(j, -1, 0, 2);
			}
			else if (p2_Shoot_See[i] == RIGHT2) {
				printshoot(j, 1, 0, 2);
			}
			else if (p2_Shoot_See[i] == UP2) {
				printshoot(j, 0, -1, 2);
			}
			else if (p2_Shoot_See[i] == DOWN2) {
				printshoot(j, 0, 1, 2);
			}
			j -= p2DeleteBullets;
			p2DeleteBullets = 0;
		}
	}
	if (breakshoot == 0) // ���� �Ѿ��� ��� �ʿ��� ����� ����Ǿ��� �� ������ ������ ����
		itemrespawn(1);
}

void printshoot(int i, int bx, int by, int player) {
	if (player == 1) {
		if (map[p1_ShootY[i]][p1_ShootX[i]] == BULLET1) {
			clearxy(p1_ShootX[i], p1_ShootY[i]); // �ϴ� �Ѿ��� ����
			map[p1_ShootY[i]][p1_ShootX[i]] = SPACE; // ���� �ڸ��� ������� �־���
			p1_ShootY[i] += by; // �Ѿ��� ���⿡ ���� ��ǥ�� ������
			p1_ShootX[i] += bx;
			if (map[p1_ShootY[i]][p1_ShootX[i]] == SPACE) {
				printbullet(i, 1); // �����ڸ��� �Ѿ� ���
				map[p1_ShootY[i]][p1_ShootX[i]] = BULLET1; // �ʿ��� �Ѿ˷� �ٲ���
			}
			else if (map[p1_ShootY[i]][p1_ShootX[i]] == BUSH) {
				map[p1_ShootY[i]][p1_ShootX[i]] = BUSHBULLET1; // �� ���� �Ѿ˷� �ٲ���
			}
			else if (map[p1_ShootY[i]][p1_ShootX[i]] == PLAYER2 || map[p1_ShootY[i]][p1_ShootX[i]] == GINP2 || map[p1_ShootY[i]][p1_ShootX[i]] == BINP2) {
				p2--; // p2�� ����� 1���ҽ�Ŵ
				print_infor(); // �÷��̾� ������ ���
				win_lose(); // � �÷��̾ �̰���� ��� ���̰����� �ƹ��͵� ��� ����
				shootbufferdelete(i, 1); // �Ѿ� ����
			}
			else
				shootbufferdelete(i, 1); // �Ѿ� ����
		}
		else if (map[p1_ShootY[i]][p1_ShootX[i]] == BUSHBULLET1) {
			map[p1_ShootY[i]][p1_ShootX[i]] = BUSH; // �׳� �ν��� �ٲ���
			p1_ShootY[i] += by; // �Ѿ��� ���⿡ ���� ��ǥ�� ������
			p1_ShootX[i] += bx;
			if (map[p1_ShootY[i]][p1_ShootX[i]] == SPACE) {
				printbullet(i, 1); // �����ڸ��� �Ѿ� ���
				map[p1_ShootY[i]][p1_ShootX[i]] = BULLET1; // �ʿ��� �Ѿ˷� �ٲ���
			}
			else if (map[p1_ShootY[i]][p1_ShootX[i]] == BUSH) {
				map[p1_ShootY[i]][p1_ShootX[i]] = BUSHBULLET1; // �� ���� �Ѿ˷� �ٲ���
			}
			else if (map[p1_ShootY[i]][p1_ShootX[i]] == PLAYER2 || map[p1_ShootY[i]][p1_ShootX[i]] == GINP2 || map[p1_ShootY[i]][p1_ShootX[i]] == BINP2) {
				p2--; // p2�� ����� 1���ҽ�Ŵ
				print_infor(); // �÷��̾� ������ ���
				win_lose(); // � �÷��̾ �̰���� ��� ���̰����� �ƹ��͵� ��� ����
				shootbufferdelete(i, 1); // �Ѿ� ����
			}
			else
				shootbufferdelete(i, 1); // �Ѿ� ����
		}
		else {
			p1_ShootY[i] += by; // �Ѿ��� ���⿡ ���� ��ǥ�� ������
			p1_ShootX[i] += bx;
			if (map[p1_ShootY[i]][p1_ShootX[i]] == SPACE) {
				printbullet(i, 1); // �����ڸ��� �Ѿ� ���
				map[p1_ShootY[i]][p1_ShootX[i]] = BULLET1; // �ʿ��� �Ѿ˷� �ٲ���
			}
			else if (map[p1_ShootY[i]][p1_ShootX[i]] == BUSH) {
				map[p1_ShootY[i]][p1_ShootX[i]] = BUSHBULLET1; // �� ���� �Ѿ˷� �ٲ���
			}
			else if (map[p1_ShootY[i]][p1_ShootX[i]] == PLAYER2 || map[p1_ShootY[i]][p1_ShootX[i]] == GINP2 || map[p1_ShootY[i]][p1_ShootX[i]] == BINP2) {
				p2--; // p2�� ����� 1���ҽ�Ŵ
				print_infor(); // �÷��̾� ������ ���
				win_lose(); // � �÷��̾ �̰���� ��� ���̰����� �ƹ��͵� ��� ����
				shootbufferdelete(i, 1); // �Ѿ� ����
			}
			else
				shootbufferdelete(i, 1); // �Ѿ� ����
		}
	}
	else { // p1�� ����
		if (map[p2_ShootY[i]][p2_ShootX[i]] == BULLET2) {
			clearxy(p2_ShootX[i], p2_ShootY[i]);
			map[p2_ShootY[i]][p2_ShootX[i]] = SPACE;
			p2_ShootY[i] += by;
			p2_ShootX[i] += bx;
			if (map[p2_ShootY[i]][p2_ShootX[i]] == SPACE) {
				printbullet(i, 2);
				map[p2_ShootY[i]][p2_ShootX[i]] = BULLET2;
			}
			else if (map[p2_ShootY[i]][p2_ShootX[i]] == BUSH) {
				map[p2_ShootY[i]][p2_ShootX[i]] = BUSHBULLET2;
			}
			else if (map[p2_ShootY[i]][p2_ShootX[i]] == PLAYER || map[p2_ShootY[i]][p2_ShootX[i]] == GINP || map[p2_ShootY[i]][p2_ShootX[i]] == BINP) {
				p1--;
				print_infor(); // �÷��̾� ������ ���
				win_lose(); // � �÷��̾ �̰���� ��� ���̰����� �ƹ��͵� ��� ����
				shootbufferdelete(i, 2);
			}
			else
				shootbufferdelete(i, 2);
		}
		else if (map[p2_ShootY[i]][p2_ShootX[i]] == BUSHBULLET2) {
			map[p2_ShootY[i]][p2_ShootX[i]] = BUSH;
			p2_ShootY[i] += by;
			p2_ShootX[i] += bx;
			if (map[p2_ShootY[i]][p2_ShootX[i]] == SPACE) {
				printbullet(i, 2);
				map[p2_ShootY[i]][p2_ShootX[i]] = BULLET2;
			}
			else if (map[p2_ShootY[i]][p2_ShootX[i]] == BUSH) {
				map[p2_ShootY[i]][p2_ShootX[i]] = BUSHBULLET2;
			}
			else if (map[p2_ShootY[i]][p2_ShootX[i]] == PLAYER || map[p2_ShootY[i]][p2_ShootX[i]] == GINP || map[p2_ShootY[i]][p2_ShootX[i]] == BINP) {
				p1--;
				print_infor(); // �÷��̾� ������ ���
				win_lose(); // � �÷��̾ �̰���� ��� ���̰����� �ƹ��͵� ��� ����
				shootbufferdelete(i, 2);
			}
			else
				shootbufferdelete(i, 2);
		}
		else {
			p2_ShootY[i] += by;
			p2_ShootX[i] += bx;
			if (map[p2_ShootY[i]][p2_ShootX[i]] == SPACE) {
				printbullet(i, 2);
				map[p2_ShootY[i]][p2_ShootX[i]] = BULLET2;
			}
			else if (map[p2_ShootY[i]][p2_ShootX[i]] == BUSH) {
				map[p2_ShootY[i]][p2_ShootX[i]] = BUSHBULLET2;
			}
			else if (map[p2_ShootY[i]][p2_ShootX[i]] == PLAYER || map[p2_ShootY[i]][p2_ShootX[i]] == GINP || map[p2_ShootY[i]][p2_ShootX[i]] == BINP) {
				p1--;
				print_infor(); // �÷��̾� ������ ���
				win_lose(); // � �÷��̾ �̰���� ��� ���̰����� �ƹ��͵� ��� ����
				shootbufferdelete(i, 2);
			}
			else
				shootbufferdelete(i, 2);
		}
	}
}

void shootbufferdelete(int i, int player) {
	if (player == 1) {
		for (; i < p1Bullets - 1; i++) { // ���� i������ �Ѿ��� ����-1���� �ݺ����� ����
			p1_ShootX[i] = p1_ShootX[i + 1]; // �Ѿ��� X, Y��ǥ�� �ô� ����� �Ѿ˼ӵ��� 1ĭ�� �մ��
			p1_ShootY[i] = p1_ShootY[i + 1];
			p1_Shoot_See[i] = p1_Shoot_See[i + 1];
			p1_ShootSpeed[i] = p1_ShootSpeed[i + 1];
		}
		p1Bullets--; // �Ѿ� ���� 1������
		p1DeleteBullets++; // �Ѿ� ������ 1�� �����߱� ������ Shoot1�Լ��� �ִ� i���� 1���� ��Ű������ �۾�
	}
	else { // p1������
		for (; i < p2Bullets - 1; i++) {
			p2_ShootX[i] = p2_ShootX[i + 1];
			p2_ShootY[i] = p2_ShootY[i + 1];
			p2_Shoot_See[i] = p2_Shoot_See[i + 1];
			p2_ShootSpeed[i] = p2_ShootSpeed[i + 1];
		}
		p2Bullets--;
		p2DeleteBullets++;
	}
}

void printbullet(int i, int player) {
	if (player == 1) {
		gotoxy(p1_ShootX[i], p1_ShootY[i]); // �Ѿ��� ��ǥ�� Ŀ���� �Ǳ�
		map[p1_ShootY[i]][p1_ShootX[i]] = BULLET1; // map�� �Ѿ��� ��ǥ�� p1�� �Ѿ˷� �ٲ�
		SetConsoleTextAttribute(COL, P1BULLETCOLOR); // ���� p1�Ѿ� ������ �ٲ�
	}
	else { // p1�� ����
		gotoxy(p2_ShootX[i], p2_ShootY[i]);
		map[p2_ShootY[i]][p2_ShootX[i]] = BULLET2;
		SetConsoleTextAttribute(COL, P2BULLETCOLOR);
	}
	printf("��"); // �Ѿ� ���
	SetConsoleTextAttribute(COL, 15); // �� ���󺹱�
}

void clearxy(int x, int y) {
	gotoxy(x, y);
	printf("  "); // ������� ����� ����
	map[y][x] = SPACE; // map�� ��ǥ�� ��������� �ٲ�
}

void bulletspeedcontrol(int speed) {
	int i;
	for (i = 0; i < 4; i++) {
		Sleep(speed); // �ӵ���ŭ Sleep����
		itemrespawn(0); // ������ �����ð��� ����� Ȯ��
	}
}

void keyinput() {
	float dissave1, dissave2;
	if (_kbhit()) {
		char playerInput;
		playerInput = getch(); // �Է¹������� playerInput���ٰ� ����

		dissave1 = clock() - gundis1_st; // ���ݽð� - �Ѿ��� �߻������� �ð��� �ؼ� �߻��� ���� �ð��� ���Ѵ�
		dissave2 = clock() - gundis2_st;
		bulletload(dissave1, dissave2);

		if (flag == 0) { // flag = 0 �϶�, �� ���� ���� �����϶�
			if (playerInput == LEFT1) {
				p1_Now_See = LEFT1;
				moveplayer(-1, 0);
			}
			else if (playerInput == RIGHT1) {
				p1_Now_See = RIGHT1;
				moveplayer(1, 0);
			}
			else if (playerInput == UP1) {
				p1_Now_See = UP1;
				moveplayer(0, -1);
			}
			else if (playerInput == DOWN1) {
				p1_Now_See = DOWN1;
				moveplayer(0, 1);
			}
			else if (playerInput == 'y') {
				map_reset();
			}
		}
		else if (flag == 1) { // flag = 1 �϶�, �� ���� �ִ� �����϶�
			if (playerInput == LEFT1) {
				p1_Now_See = LEFT1;
				moveplayer(-1, 0);
			}
			else if (playerInput == RIGHT1) {
				p1_Now_See = RIGHT1;
				moveplayer(1, 0);
			}
			else if (playerInput == UP1) {
				p1_Now_See = UP1;
				moveplayer(0, -1);
			}
			else if (playerInput == DOWN1) {
				p1_Now_See = DOWN1;
				moveplayer(0, 1);
			}
			else if (playerInput == P1SHOOT) {
				if (bulletload1 == 1) {
					gundis1_st = clock(); // ���� �� �������� �ð��� ��
					bulletload1 = 0; // ���� ���ٴ� ���� �ǹ�
					p1_ShootX[p1Bullets] = playerX; // �÷��̾��� ���� x, y��ǥ�� ���¹����� �Ѿ˿� ���� ������ ������ �迭�� �־���
					p1_ShootY[p1Bullets] = playerY;
					p1_Shoot_See[p1Bullets] = p1_Now_See;
					if (map[playerY][playerX] == BUSH) // �÷��̾��� ���� ��ġ�� ���� �Ѿ� �ӵ��� �޶���
						p1_ShootSpeed[p1Bullets] = BUSHSHOOTSPEED;
					else
						p1_ShootSpeed[p1Bullets] = SHOOTSPEED;
					breakshoot = 1; // Shoot�Լ��� 2���̻� ������� �ʵ��� ��
					p1Bullets++; // �Ѿ� ������ �ø�
					shoot1(); // �ѽ�� �Լ� ����
				}
			}
			else if (playerInput == 'y') {
				map_reset();
			}
		}
		if (flag2 == 0) { // ���� ���� ����� p2�� ����
			if (playerInput == LEFT2) {
				p2_Now_See = LEFT2;
				moveplayer2(-1, 0);
			}
			else if (playerInput == RIGHT2) {
				p2_Now_See = RIGHT2;
				moveplayer2(1, 0);
			}
			else if (playerInput == UP2) {
				p2_Now_See = UP2;
				moveplayer2(0, -1);
			}
			else if (playerInput == DOWN2) {
				p2_Now_See = DOWN2;
				moveplayer2(0, 1);
			}
			else if (playerInput == 'y') {
				map_reset();
			}
		}
		else if (flag2 == 1) {
			if (playerInput == LEFT2) {
				p2_Now_See = LEFT2;
				moveplayer2(-1, 0);
			}
			else if (playerInput == RIGHT2) {
				p2_Now_See = RIGHT2;
				moveplayer2(1, 0);
			}
			else if (playerInput == UP2) {
				p2_Now_See = UP2;
				moveplayer2(0, -1);
			}
			else if (playerInput == DOWN2) {
				p2_Now_See = DOWN2;
				moveplayer2(0, 1);
			}
			else if (playerInput == P2SHOOT) {
				if (bulletload2 == 1) {
					gundis2_st = clock();
					bulletload2 = 0;
					p2_ShootX[p2Bullets] = playerX2;
					p2_ShootY[p2Bullets] = playerY2;
					p2_Shoot_See[p2Bullets] = p2_Now_See;
					if (map[playerY2][playerX2] == BUSH)
						p2_ShootSpeed[p2Bullets] = BUSHSHOOTSPEED;
					else
						p2_ShootSpeed[p2Bullets] = SHOOTSPEED;
					breakshoot = 1;
					p2Bullets++;
					shoot1();
				}
			}
			else if (playerInput == 'y') {
				map_reset();
			}
		}
	}
}

void bulletload(double dissave1, double dissave2) {
	if ((int)dissave1 >= DISTANCEATTACK * 1000) { // ���� ���� �ð��� ����ð��� �Ѿ˰���(���ݼӵ�)���� �涧 ���� ��� �ֵ��� ��
		bulletload1 = 1;
	}
	if ((int)dissave2 >= DISTANCEATTACK * 1000) { // p1������
		bulletload2 = 1;
	}
}

void itemrespawn(int repeat) {
	float gunet, ginpet, ginpet2, etpt; // clock �Լ� �������� ������

	if (repeat == 1) { // �ݺ��� �ִ� �����ۻ���
		while (1) {
			gunet = clock() - gunst; // ���� �����ð����� �������� ���� �����Ҷ� clock ���־��� ���� clock �� ���� ó�� clock �� ���� ���ذ��� �����Ѵ�
			etpt = clock() - stpt; // ���� �����ð����� �������� ���� �����Ҷ� clock ���־��� ���� clock �� ���� ó�� clock �� ���� ���ذ��� �����Ѵ�

			if ((int)gunet >= 15000) { // ���� ó���ð�~�������ð��� 15�� �̻��̸� �׶� gun�Լ��� �����ϰ� �ٽý���ǰԲ� gunst�� �ʱ�ȭ ���ش�
				for (int i = 0; i < 2; i++) {
					gun();
					gunst = clock();
				}
			}
			if ((int)etpt >= 15000) { // ���� ó���ð�~�������ð��� 10�� �̻��̸� �׶� potion�Լ��� �����ϰ� �ٽý���ǰԲ� stpt�� �ʱ�ȭ ���ش�
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
			keyinput();
		}
	}

	else if (repeat == 0) { // �ݺ��� ���� ������ ����
		gunet = clock() - gunst; // ���� �����ð����� �������� ���� �����Ҷ� clock ���־��� ���� clock �� ���� ó�� clock �� ���� ���ذ��� �����Ѵ�
		etpt = clock() - stpt; // ���� �����ð����� �������� ���� �����Ҷ� clock ���־��� ���� clock �� ���� ó�� clock �� ���� ���ذ��� �����Ѵ�

		if ((int)gunet >= 15000) { // ���� ó���ð�~�������ð��� 15�� �̻��̸� �׶� gun�Լ��� �����ϰ� �ٽý���ǰԲ� gunst�� �ʱ�ȭ ���ش�
			for (int i = 0; i < 2; i++) {
				gun();
				gunst = clock();
			}
		}
		if ((int)etpt >= 15000) { // ���� ó���ð�~�������ð��� 10�� �̻��̸� �׶� potion�Լ��� �����ϰ� �ٽý���ǰԲ� stpt�� �ʱ�ȭ ���ش�
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
		keyinput();
	}
}

void map_reset() {
	system("cls");
	int i, j;
	for (i = 0; i < 39; i++) {
		for (j = 0; j < 39; j++) {
			map[i][j] = 0;
		}
	}
	for (i = 0; i <= 39; i++) {
		map[0][i] = 1;
		map[i][0] = 1;
		map[39][i] = 1;
		map[i][39] = 1;
	}

	gameplay();
}

void gameplay() {
	int i, j;
	bush();
	wall();
	player();
	player2();
	printmap(); // �� �Լ��� ���� ���� ����ǰ� �������� ���� ���

	print_infor(); // �÷��̾� ������ ���

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

	gundis1_st = clock(); //�Ѿ��� ���ݼӵ��� �����ϴ� ������ ����ð��� ����
	gundis2_st = clock();

	itemrespawn(1); // ������ �����Լ� ����
	keyinput();
}