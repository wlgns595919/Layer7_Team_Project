#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<windows.h>

#define MAPSIZE 40
#define SPACE 0 // 빈공간
#define WALL 1 // 벽
#define BUSH 2 // 풀숲
#define GUN 3 // 총
#define POTION 5 //  포션
#define GINP 7 // 총을 먹은 상태의 플레이어 1
#define BINP 8 // 부쉬에 있는 상태의 플레이어 1
#define PLAYER 9 // 평상시 플레이어 1
#define GINP2 70 // 총을 먹은 상태의 플레이어2
#define BINP2 80 // 부쉬에 있는 상태의 플레이어 2
#define PLAYER2 90 // 평상시 플레이어 2
#define COL GetStdHandle(STD_OUTPUT_HANDLE) // 글자 색 지정
#define SHOOTSPEED 5 // 평상시 쐈을때 총알속도
#define BUSHSHOOTSPEED 3 // 부쉬에서 쐈을때 총알속도
#define UP1 'w' // 플레이어 1 방향키
#define DOWN1 's' 
#define LEFT1 'a'
#define RIGHT1 'd'
#define P1SHOOT 32 // 플레이어 1 공격키
#define UP2 72 // 플레이어 2 방향키
#define DOWN2 80
#define LEFT2 75
#define RIGHT2 77
#define P2SHOOT '+' // 플레이어 2 공격키
#define BULLETS 20 // 최대 총알 갯수
#define BULLET1 10 // p1의 그냥총알
#define BUSHBULLET1 11 // p1의 부쉬에 있는 총알
#define BULLET2 12 // p2의 그냥총알
#define BUSHBULLET2 13 // p2의 부쉬에 있는 총알
#define P1BULLETCOLOR 5 // p1의 총알 색
#define P2BULLETCOLOR 6 // p2의 총알 색
#define DISTANCEATTACK 0.5 // 총알 간격(공격속도)
#define MAP_RESET 'y' // 리셋버튼

int playerX, playerY, playerX2, playerY2, flag = 0, flag2 = 0, gun_x, gun_y, potion_x, potion_y;
int p1 = 3, p2 = 3; // p1, p2 목숨
float ginpst, ginpst2;
int p1_ShootX[BULLETS], p1_ShootY[BULLETS], p1_Shoot_See[BULLETS], p1_Now_See, p1_ShootSpeed[BULLETS], p1Bullets = 0, p1DeleteBullets = 0;// 플레이어들의 총알의 x, y좌표, 보고있는방향, 총알속도, 총알갯수
int p2_ShootX[BULLETS], p2_ShootY[BULLETS], p2_Shoot_See[BULLETS], p2_Now_See, p2_ShootSpeed[BULLETS], p2Bullets = 0, p2DeleteBullets = 0;
int breakshoot = 0; // Shoot함수 중복실행 방지
float gundis1_st, gundis2_st; // 총알 간격제어를 위한 시간을 저장하는 변수
int bulletload1 = 1, bulletload2 = 1; // 공격속도보다 빨리 못 쏘게 하는 변수
float gunst, stpt; // 아이템 생성 시간을 재는 함수

int map[MAPSIZE][MAPSIZE];

void nocur(); // 커서를 안보이게해주는 함수
void win_lose(); // 플레이어가 이겼을때 호출되는 함수
void print_infor(); // 플레이어의 목숨 정보를 출력하는 함수
void moveplayer(int dx, int dy); // p1의 이동함수
void moveplayer2(int dx, int dy); // p2의 이동함수
void player(); // p1 랜덤생성 함수
void player2(); // p2 랜덤생성 함수
void wall(); // 벽 랜덤생성 함수
void gun(); // 총 랜덤생성 함수
void potion(); // 포션 랜덤생성 함수
void bush(); // 풀숲 랜덤생성 함수
void printmap(); // 맵을 출력하는 함수
void gotoxy(int x, int y); // 특정한 좌표로 이동하기 위해서 사용하는 함수
void p1_print(); // p1을 출력 해주는 함수
void bush_print(); // p1의 bush를 출력 해주는 함수
void space_print(); // p1의 space를 출력 해주는 함수
void binp_print(); // p1의 binp를 출력 해주는 함수
void p2_print(); // p2을 출력 해주는 함수
void bush2_print(); // p2의 bush를 출력 해주는 함수
void space2_print(); // p2의 space를 출력 해주는 함수
void binp2_print(); // p2의 binp를 출력 해주는 함수
void shoot1(); // 플레이어에 보는 방향에 따라 총알을 발사하는 함수를 호출해주는 함수
void printshoot(int i, int bx, int by, int player); // 총알을 출력 해주는 함수
void shootbufferdelete(int i, int player); // 총알 발사가 완료되었을때 배열에있던 총알관련정보를 삭제해줌
void printbullet(int i, int player); // 총알을 출력해주는 함수
void clearxy(int x, int y); // (x, y)를 지워주는 함수
void bulletspeedcontrol(int speed); // 총알의 속도를 제어해주는 함수
void keyinput(); // 플레이어가 입력을 했을때 처리해주는 함수
void bulletload(double dissave1, double dissave2); // 총알 공격속도를 제어해주는 함수
void itemrespawn(int repeat); // 아이템을 일정시간마다 생성해주는함수
void map_reset(); // 혹시라도 맵출력이 이상하게 될경우 맵을 초기화 시켜주는 함수
void gameplay(); // 전체적인 게임을 운영하는 함수

int main() {
	nocur(); // 커서 숨김

	system("mode con cols=120 lines=41"); // 콘솔 창 크기 지정

	gunst = clock(); // 아이템 생성 시간을 재기시작함
	stpt = clock();

	srand(time(NULL)); // 랜덤생성
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

	if (map[playerY + dy][playerX + dx] == SPACE) { // 다음 위치가 빈 공간일때

		if (map[playerY][playerX] == PLAYER || map[playerY][playerX] == GINP) { // 내가 PLAYER 거나 GINP인 상태일때 (풀숲이 아닐때)
			space_print(); // 빈공간 출력
			playerX += dx; playerY += dy;
			p1_print(); // 그다음 p1을 출력시킨다
			if (flag == 0)
				map[playerY][playerX] = PLAYER;
			else if (flag == 1)
				map[playerY][playerX] = GINP;
		}

		else { // 내가 BINP 상태일떄 (풀숲일때)
			bush_print(); // 풀숲을 출력한다
			playerX += dx; playerY += dy;
			p1_print(); // 그다음 p1을 출력시킨다
			if (flag == 0)
				map[playerY][playerX] = PLAYER;
			else if (flag == 1)
				map[playerY][playerX] = GINP;
		}
	}

	else if (map[playerY + dy][playerX + dx] == BUSH) { // 다음 위치가 풀숲일때

		if (map[playerY][playerX] == PLAYER || map[playerY][playerX] == GINP) { // 내가 PAYER 거나 GINP 인 상태일때 (풀숲이 아닐때)
			space_print(); // 빈 공간을 출력한다
			playerX += dx; playerY += dy;
			binp_print(); // 초록색 공을 출력한다
		}

		else { // 내가 BINP인 상태일때 (풀숲일때)

			bush_print(); // 풀숲을 출력한다
			playerX += dx; playerY += dy;
			binp_print(); // 초록색 공을 출력한다
		}
	}
	else if (map[playerY + dy][playerX + dx] == GUN) { // 다음 위치가 총일때
		if (map[playerY][playerX] == PLAYER || map[playerY][playerX] == GINP) { // 내가 PAYER 거나 GINP 인 상태일때 (풀숲이 아닐때)
			space_print(); // 빈공간을 출력한다
		}
		else { // (풀숲일때)
			bush_print(); // 풀숲을 출력한다
		}
		playerX += dx; playerY += dy;
		gotoxy(playerX, playerY);
		SetConsoleTextAttribute(COL, 4);
		printf("●");
		SetConsoleTextAttribute(COL, 15);
		map[playerY][playerX] = GINP;

		flag = 1; // flag 를 1로 변경
		ginpst = clock(); // 총먹었을때 카운터 시작
	}
	else if (map[playerY + dy][playerX + dx] == POTION) { // 다음 위치가 포션일때
		if (map[playerY][playerX] == PLAYER || map[playerY][playerX] == GINP) { // 내가 PAYER 거나 GINP 인 상태일때 (풀숲이 아닐때)
			space_print(); // 빈공간을 출력한다
		}
		else { // (풀숲일때)
			bush_print(); // 풀숲을 출력한다 
		}
		playerX += dx; playerY += dy;
		p1_print(); // p1을 출력한다
		if (flag == 0)
			map[playerY][playerX] = PLAYER;
		else if (flag == 1)
			map[playerY][playerX] = GINP;

		p1++; // 포션을 먹으면 p1 증가
		print_infor();
		win_lose();
	}
}

void moveplayer2(int dx, int dy) {

	if (map[playerY2 + dy][playerX2 + dx] == SPACE) { // 다음 위치가 빈 공간일때

		if (map[playerY2][playerX2] == PLAYER2 || map[playerY2][playerX2] == GINP2) { // 내가 PLAYER 거나 GINP인 상태일때 (풀숲이 아닐때)
			space2_print();
			playerX2 += dx; playerY2 += dy;
			p2_print();
			if (flag2 == 0)
				map[playerY2][playerX2] = PLAYER2;
			else if (flag2 == 1)
				map[playerY2][playerX2] = GINP2;
		}

		else { // 내가 BINP 상태일떄 (풀숲일때)
			bush2_print(); // 풀숲을 출력한다
			playerX2 += dx; playerY2 += dy;
			p2_print(); // 그다음 p2을 출력시킨다
			if (flag2 == 0)
				map[playerY2][playerX2] = PLAYER2;
			else if (flag2 == 1)
				map[playerY2][playerX2] = GINP2;
		}
	}

	else if (map[playerY2 + dy][playerX2 + dx] == BUSH) { // 다음 위치가 풀숲일때

		if (map[playerY2][playerX2] == PLAYER2 || map[playerY2][playerX2] == GINP2) { // 내가 PAYER 거나 GINP 인 상태일때 (풀숲이 아닐때)
			space2_print(); // 빈 공간을 출력한다
			playerX2 += dx; playerY2 += dy;
			binp2_print(); // 초록색 별을 출력한다
		}

		else { // 내가 BINP인 상태일때 (풀숲일때)

			bush2_print(); // 풀숲을 출력한다
			playerX2 += dx; playerY2 += dy;
			binp2_print(); // 초록색 별을 출력한다
		}
	}
	else if (map[playerY2 + dy][playerX2 + dx] == GUN) { // 다음 위치가 총일때
		if (map[playerY2][playerX2] == PLAYER2 || map[playerY2][playerX2] == GINP2) { // 내가 PAYER 거나 GINP 인 상태일때 (풀숲이 아닐때)
			space2_print(); // 빈공간을 출력한다
		}
		else { // (풀숲일때)
			bush2_print(); // 풀숲을 출력한다
		}
		playerX2 += dx; playerY2 += dy;
		gotoxy(playerX2, playerY2);
		SetConsoleTextAttribute(COL, 4);
		printf("★");
		SetConsoleTextAttribute(COL, 15);
		map[playerY2][playerX2] = GINP2;

		flag2 = 1; // flag2 를 1로 변경
		ginpst2 = clock(); // 총먹었을때 카운터 시작
	}
	else if (map[playerY2 + dy][playerX2 + dx] == POTION) { // 다음 위치가 포션일때
		if (map[playerY2][playerX2] == PLAYER2 || map[playerY2][playerX2] == GINP2) { // 내가 PAYER 거나 GINP 인 상태일때 (풀숲이 아닐때)
			space2_print(); // 빈공간을 출력한다
		}
		else { // (풀숲일때)
			bush2_print(); // 풀숲을 출력한다 
		}
		playerX2 += dx; playerY2 += dy;
		p2_print(); // p2을 출력한다
		if (flag2 == 0)
			map[playerY2][playerX2] = PLAYER2;
		else if (flag2 == 1)
			map[playerY2][playerX2] = GINP2;

		p2++; // 포션을 먹으면 p2 증가
		print_infor();
		win_lose();
	}
}

void gotoxy(int x, int y) // 커서 이동 함수
{
	COORD Pos;
	Pos.X = x * 2;
	Pos.Y = y;
	SetConsoleCursorPosition(COL, Pos);
}

void printmap() { // 맵을 출력하는 함수

	int i, j;

	for (i = 0; i < MAPSIZE; i++) {
		for (j = 0; j < MAPSIZE; j++) { // 맵 전체를 다 돈다
			switch (map[i][j]) { // 각 숫자에 따라서 다르게 값이 출력이 되도록 한다

			case WALL: printf("■"); break;
			case SPACE: printf("  "); break;
			case BUSH: SetConsoleTextAttribute(COL, 2); printf("■"); SetConsoleTextAttribute(COL, 15); break;
			case GUN: SetConsoleTextAttribute(COL, 4); printf("☞"); SetConsoleTextAttribute(COL, 15); break;
			case PLAYER: SetConsoleTextAttribute(COL, 6); printf("●"); SetConsoleTextAttribute(COL, 15); break;
			case PLAYER2: SetConsoleTextAttribute(COL, 6); printf("★"); SetConsoleTextAttribute(COL, 15); break;
			}
		}
		printf("\n");
	}
}


void bush() { // 풀숲을 랜덤값으로 주는 함수

	int i, j, k;
	srand(time(NULL)); // 랜덤값

	for (i = 0; i < 15; i++) { // 풀숲 총 15개를 생성

		int random_x = (rand() % 33) + 1; // 범위가 맵전체를 넘어가지 않게 설정
		int random_y = (rand() % 33) + 1; // 범위가 맵전체를 넘어가지 않게 설정
		int dir = rand() % 2; // 세로 할것인지 가로 할것인지 결정
		if (dir == 0) { // 0일때
			for (j = 0; j < 6; j++) {
				for (k = 0; k < 3; k++) {
					map[random_x + j][random_y + k] = 2; // 가로 3 * 세로 6칸의 풀숲을 출력
				}
			}
		}
		else if (dir == 1) { // 1일때
			for (j = 0; j < 3; j++) {
				for (k = 0; k < 6; k++) {
					map[random_x + j][random_y + k] = 2; // 가로 6칸 * 세로 3칸의 풀숲을 출력
				}
			}
		}

	}
}

void wall() { // 벽을 랜덤값으로 주는 함수

	int i, j, k, l = 0, ll = 0;
	srand(time(NULL)); // 랜덤값

	for (i = 0; i < 12; i++) {

		int random_x = (rand() % 31) + 1; // 맵 밖에 생성되지 않도록 해둔것
		int random_y = (rand() % 31) + 1;// 맵 밖에 생성되지 않도록 해둔것
		int dir = rand() % 4; // 4가지 경우로 나눔
		if (dir == 0) {
			for (j = 0; j < 8; j++) {
				map[random_x + j][random_y] = 1; // 세로로 8칸 벽생성
			}
		}
		else if (dir == 1) {
			for (j = 0; j < 8; j++) {
				map[random_x][random_y + j] = 1; // 가로로 8칸 벽생성
			}
		}
		else if (dir == 2) {
			l = k = 0;
			for (j = 0; j < 4; j++) {
				for (k = 0; k < 2; k++) {
					map[random_x + l][random_y + ll] = 1; // 지그재그 왼->오 방향
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
					map[random_x + l][random_y + ll] = 1; // 지그재그 오->왼 방향
					l++;
				}
				ll--;
				l--;
			}
		}
	}
}

void gun() { // 총을 출력하는 함수

	srand(time(NULL)); // 랜덤값

	while (1) {
		gun_x = (rand() % 38) + 1; // 맵 밖에 생성되지 않도록 해둔것
		gun_y = (rand() % 38) + 1; // 맵 밖에 생성되지 않도록 해둔것
		if (map[gun_y][gun_x] == SPACE) { // 공간이 빈공간일때만 저장이 되도록함
			map[gun_y][gun_x] = 3;
			gotoxy(gun_x, gun_y);
			SetConsoleTextAttribute(COL, 4); printf("☞"); SetConsoleTextAttribute(COL, 15);
			break;
		}
		else
			continue;
	}
}

void potion() { // 포션을 출력하는 함수

	srand(time(NULL)); // 랜덤값

	while (1) {
		potion_x = (rand() % 38) + 1; // 맵 밖에 생성되지 않도록 해둔것
		potion_y = (rand() % 38) + 1; // 맵 밖에 생성되지 않도록 해둔것
		if (map[potion_y][potion_x] == SPACE) { // 공간이 빈공간일때만 저장이 되도록함
			map[potion_y][potion_x] = 5;
			gotoxy(potion_x, potion_y);
			SetConsoleTextAttribute(COL, 3); printf("♠"); SetConsoleTextAttribute(COL, 15);
			break;
		}
		else
			continue;
	}
}

void player() { // p1 랜덤값으로 주는 함수

	srand(time(NULL));
	while (1) {
		int random_x = (rand() % 38) + 1;
		int random_y = (rand() % 38) + 1;
		if (map[random_y][random_x] == SPACE) { // 빈공간일 때만
			map[random_y][random_x] = PLAYER;
			break;
		}
		else
			continue;
	}

}

void player2() { // p2 랜덤값으로 주는 함수

	srand(time(NULL));
	while (1) {
		int random_x = (rand() % 38) + 1;
		int random_y = (rand() % 38) + 1;
		if (map[random_y][random_x] == SPACE) { // 빈공간일 때만
			map[random_y][random_x] = PLAYER2;
			break;
		}
		else
			continue;
	}

}

void p1_print() { // p1을 출력해주는 함수
	gotoxy(playerX, playerY);
	if (flag == 0) {
		SetConsoleTextAttribute(COL, 6);
		printf("●"); // 총을 안먹은 상태일때는 노란색
		SetConsoleTextAttribute(COL, 15);
	}
	else if (flag == 1) {
		SetConsoleTextAttribute(COL, 4);
		printf("●"); // 총을 먹은 상태일때는 빨간색
		SetConsoleTextAttribute(COL, 15);
	}
}

void bush_print() {
	SetConsoleTextAttribute(COL, 2);
	gotoxy(playerX, playerY);
	printf("■"); // 풀을 출력을 해준다
	SetConsoleTextAttribute(COL, 15);
	map[playerY][playerX] = BUSH;
}

void space_print() {
	gotoxy(playerX, playerY);
	printf("  "); // 빈공간을 출력을 해준다
	map[playerY][playerX] = SPACE;
}

void binp_print() {
	gotoxy(playerX, playerY);
	SetConsoleTextAttribute(COL, 2);
	printf("●"); // 초록색 공을 출력
	SetConsoleTextAttribute(COL, 15);
	map[playerY][playerX] = BINP;
}

void p2_print() {
	gotoxy(playerX2, playerY2);
	if (flag2 == 0) { // p2을 출력해주는 함수
		SetConsoleTextAttribute(COL, 6);
		printf("★"); // 총을 안먹은 상태일때는 노란색
		SetConsoleTextAttribute(COL, 15);
	}
	else if (flag2 == 1) {
		SetConsoleTextAttribute(COL, 4);
		printf("★"); // 총을 먹은 상태일때는 빨간색
		SetConsoleTextAttribute(COL, 15);
	}
}

void bush2_print() {
	SetConsoleTextAttribute(COL, 2);
	gotoxy(playerX2, playerY2);
	printf("■"); // 풀을 출력을 해준다
	SetConsoleTextAttribute(COL, 15);
	map[playerY2][playerX2] = BUSH;
}

void space2_print() {
	gotoxy(playerX2, playerY2);
	printf("  "); // 빈공간을 출력을 해준다
	map[playerY2][playerX2] = SPACE;
}

void binp2_print() {
	gotoxy(playerX2, playerY2);
	SetConsoleTextAttribute(COL, 2);
	printf("★"); // 초록색 별을 출력
	SetConsoleTextAttribute(COL, 15);
	map[playerY2][playerX2] = BINP2;
}

void print_infor() {
	int i;
	gotoxy(43, 6);
	printf("┏━━ ┃ 플레이어 정보 ┃ ━━┓"); // UI 구현
	for (i = 7; i <= 32; i++) {
		gotoxy(43, i);
		printf("┃                       ┃");
	}
	gotoxy(43, 33);
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━┛");
	gotoxy(46, 15);
	printf("P1 목숨 : %d", p1); // p1 목숨 출력
	gotoxy(46, 20);
	printf("P2 목숨 : %d", p2); // p2 목숨 출력
}

void win_lose() {
	int i;
	if (p1 == 0) { // p1의 목숨이 0이면
		gotoxy(43, 6);
		printf("┏━━ ┃ 플레이어 정보 ┃ ━━┓"); // UI 구현
		for (i = 7; i <= 32; i++) {
			gotoxy(43, i);
			printf("┃                       ┃");
		}
		gotoxy(43, 33);
		printf("┗━━━━━━━━━━━━━━━━━━━━━━━┛");
		gotoxy(47, 19);
		printf("P2 Winner!!        "); // p2 승리 출력
		Sleep(3000);
		exit(0);
	}
	else if (p2 == 0) {
		gotoxy(43, 6);
		printf("┏━━ ┃ 플레이어 정보 ┃ ━━┓"); // UI 구현
		for (i = 7; i <= 32; i++) {
			gotoxy(43, i);
			printf("┃                       ┃");
		}
		gotoxy(43, 33);
		printf("┗━━━━━━━━━━━━━━━━━━━━━━━┛");
		gotoxy(47, 19);
		printf("P1 Winner!!        "); // p1 승리 출력
		Sleep(3000);
		exit(0);
	}
}

void shoot1() {
	breakshoot = 0; // 함수가 첫번째로 실행됬을때 breakshoot변수를 0으로바꿈
	int i, j;
	while (1) {
		if (breakshoot == 1 || (p1Bullets == 0 && p2Bullets == 0)) // 다른함수가 실행됬을때나 양플레이어 총알이 모두 맵에서 사라졌을때 반복문 종료
			break;
		for (i = 0; i < p1Bullets; i++) { // 총알 갯수만큼 반복
			bulletspeedcontrol(p1_ShootSpeed[i] / (p1Bullets + p2Bullets)); // 총알이 날라가는 속도 제어
			if (p1_Shoot_See[i] == LEFT1) { // 플레이어가 보고있던 방향에 따라 총알이 날라가는 방향 변경
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
			i -= p1DeleteBullets; // 총알이 부딪쳐서 없어지면 다음 총알이 실행되도록 함
			p1DeleteBullets = 0;
		}
		for (j = 0; j < p2Bullets; j++) { // p1과 같음
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
	if (breakshoot == 0) // 만약 총알이 모두 맵에서 사라져 종료되었을 때 아이템 생성을 실행
		itemrespawn(1);
}

void printshoot(int i, int bx, int by, int player) {
	if (player == 1) {
		if (map[p1_ShootY[i]][p1_ShootX[i]] == BULLET1) {
			clearxy(p1_ShootX[i], p1_ShootY[i]); // 일단 총알을 지움
			map[p1_ShootY[i]][p1_ShootX[i]] = SPACE; // 지운 자리에 빈공간을 넣어줌
			p1_ShootY[i] += by; // 총알의 방향에 따라 좌표를 변경함
			p1_ShootX[i] += bx;
			if (map[p1_ShootY[i]][p1_ShootX[i]] == SPACE) {
				printbullet(i, 1); // 다음자리에 총알 출력
				map[p1_ShootY[i]][p1_ShootX[i]] = BULLET1; // 맵에도 총알로 바꿔줌
			}
			else if (map[p1_ShootY[i]][p1_ShootX[i]] == BUSH) {
				map[p1_ShootY[i]][p1_ShootX[i]] = BUSHBULLET1; // 맵 값만 총알로 바꿔줌
			}
			else if (map[p1_ShootY[i]][p1_ShootX[i]] == PLAYER2 || map[p1_ShootY[i]][p1_ShootX[i]] == GINP2 || map[p1_ShootY[i]][p1_ShootX[i]] == BINP2) {
				p2--; // p2의 목숨을 1감소시킴
				print_infor(); // 플레이어 정보를 출력
				win_lose(); // 어떤 플레이어가 이겼는지 출력 안이겼으면 아무것도 출력 안함
				shootbufferdelete(i, 1); // 총알 삭제
			}
			else
				shootbufferdelete(i, 1); // 총알 삭제
		}
		else if (map[p1_ShootY[i]][p1_ShootX[i]] == BUSHBULLET1) {
			map[p1_ShootY[i]][p1_ShootX[i]] = BUSH; // 그냥 부쉬로 바꿔줌
			p1_ShootY[i] += by; // 총알의 방향에 따라 좌표를 변경함
			p1_ShootX[i] += bx;
			if (map[p1_ShootY[i]][p1_ShootX[i]] == SPACE) {
				printbullet(i, 1); // 다음자리에 총알 출력
				map[p1_ShootY[i]][p1_ShootX[i]] = BULLET1; // 맵에도 총알로 바꿔줌
			}
			else if (map[p1_ShootY[i]][p1_ShootX[i]] == BUSH) {
				map[p1_ShootY[i]][p1_ShootX[i]] = BUSHBULLET1; // 맵 값만 총알로 바꿔줌
			}
			else if (map[p1_ShootY[i]][p1_ShootX[i]] == PLAYER2 || map[p1_ShootY[i]][p1_ShootX[i]] == GINP2 || map[p1_ShootY[i]][p1_ShootX[i]] == BINP2) {
				p2--; // p2의 목숨을 1감소시킴
				print_infor(); // 플레이어 정보를 출력
				win_lose(); // 어떤 플레이어가 이겼는지 출력 안이겼으면 아무것도 출력 안함
				shootbufferdelete(i, 1); // 총알 삭제
			}
			else
				shootbufferdelete(i, 1); // 총알 삭제
		}
		else {
			p1_ShootY[i] += by; // 총알의 방향에 따라 좌표를 변경함
			p1_ShootX[i] += bx;
			if (map[p1_ShootY[i]][p1_ShootX[i]] == SPACE) {
				printbullet(i, 1); // 다음자리에 총알 출력
				map[p1_ShootY[i]][p1_ShootX[i]] = BULLET1; // 맵에도 총알로 바꿔줌
			}
			else if (map[p1_ShootY[i]][p1_ShootX[i]] == BUSH) {
				map[p1_ShootY[i]][p1_ShootX[i]] = BUSHBULLET1; // 맵 값만 총알로 바꿔줌
			}
			else if (map[p1_ShootY[i]][p1_ShootX[i]] == PLAYER2 || map[p1_ShootY[i]][p1_ShootX[i]] == GINP2 || map[p1_ShootY[i]][p1_ShootX[i]] == BINP2) {
				p2--; // p2의 목숨을 1감소시킴
				print_infor(); // 플레이어 정보를 출력
				win_lose(); // 어떤 플레이어가 이겼는지 출력 안이겼으면 아무것도 출력 안함
				shootbufferdelete(i, 1); // 총알 삭제
			}
			else
				shootbufferdelete(i, 1); // 총알 삭제
		}
	}
	else { // p1과 같음
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
				print_infor(); // 플레이어 정보를 출력
				win_lose(); // 어떤 플레이어가 이겼는지 출력 안이겼으면 아무것도 출력 안함
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
				print_infor(); // 플레이어 정보를 출력
				win_lose(); // 어떤 플레이어가 이겼는지 출력 안이겼으면 아무것도 출력 안함
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
				print_infor(); // 플레이어 정보를 출력
				win_lose(); // 어떤 플레이어가 이겼는지 출력 안이겼으면 아무것도 출력 안함
				shootbufferdelete(i, 2);
			}
			else
				shootbufferdelete(i, 2);
		}
	}
}

void shootbufferdelete(int i, int player) {
	if (player == 1) {
		for (; i < p1Bullets - 1; i++) { // 들어온 i값부터 총알의 개수-1까지 반복문을 돌림
			p1_ShootX[i] = p1_ShootX[i + 1]; // 총알의 X, Y좌표와 봤던 방향과 총알속도를 1칸씩 앞당김
			p1_ShootY[i] = p1_ShootY[i + 1];
			p1_Shoot_See[i] = p1_Shoot_See[i + 1];
			p1_ShootSpeed[i] = p1_ShootSpeed[i + 1];
		}
		p1Bullets--; // 총알 갯수 1개감소
		p1DeleteBullets++; // 총알 갯수가 1개 감소했기 때문에 Shoot1함수에 있는 i값도 1감소 시키기위한 작업
	}
	else { // p1과같음
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
		gotoxy(p1_ShootX[i], p1_ShootY[i]); // 총알의 좌표로 커서를 옳김
		map[p1_ShootY[i]][p1_ShootX[i]] = BULLET1; // map의 총알의 좌표를 p1의 총알로 바꿈
		SetConsoleTextAttribute(COL, P1BULLETCOLOR); // 색을 p1총알 색으로 바꿈
	}
	else { // p1과 동일
		gotoxy(p2_ShootX[i], p2_ShootY[i]);
		map[p2_ShootY[i]][p2_ShootX[i]] = BULLET2;
		SetConsoleTextAttribute(COL, P2BULLETCOLOR);
	}
	printf("＠"); // 총알 출력
	SetConsoleTextAttribute(COL, 15); // 색 원상복귀
}

void clearxy(int x, int y) {
	gotoxy(x, y);
	printf("  "); // 빈공간을 출력을 해줌
	map[y][x] = SPACE; // map에 좌표를 빈공간으로 바꿈
}

void bulletspeedcontrol(int speed) {
	int i;
	for (i = 0; i < 4; i++) {
		Sleep(speed); // 속도만큼 Sleep해줌
		itemrespawn(0); // 아이템 생성시간이 됬는지 확인
	}
}

void keyinput() {
	float dissave1, dissave2;
	if (_kbhit()) {
		char playerInput;
		playerInput = getch(); // 입력받은것을 playerInput에다가 저장

		dissave1 = clock() - gundis1_st; // 지금시간 - 총알을 발사했을때 시간을 해서 발사한 후의 시간을 구한다
		dissave2 = clock() - gundis2_st;
		bulletload(dissave1, dissave2);

		if (flag == 0) { // flag = 0 일때, 즉 총이 없는 상태일때
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
		else if (flag == 1) { // flag = 1 일때, 즉 총이 있는 상태일때
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
					gundis1_st = clock(); // 총을 쏜 순간부터 시간을 잼
					bulletload1 = 0; // 총을 쐈다는 것을 의미
					p1_ShootX[p1Bullets] = playerX; // 플레이어의 현재 x, y좌표와 보는방향을 총알에 대한 정보를 가지는 배열에 넣어줌
					p1_ShootY[p1Bullets] = playerY;
					p1_Shoot_See[p1Bullets] = p1_Now_See;
					if (map[playerY][playerX] == BUSH) // 플레이어의 현재 위치에 따라서 총알 속도가 달라짐
						p1_ShootSpeed[p1Bullets] = BUSHSHOOTSPEED;
					else
						p1_ShootSpeed[p1Bullets] = SHOOTSPEED;
					breakshoot = 1; // Shoot함수가 2개이상 실행되지 않도록 함
					p1Bullets++; // 총알 갯수를 늘림
					shoot1(); // 총쏘는 함수 실행
				}
			}
			else if (playerInput == 'y') {
				map_reset();
			}
		}
		if (flag2 == 0) { // 위와 같은 방법을 p2에 적용
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
	if ((int)dissave1 >= DISTANCEATTACK * 1000) { // 총을 쐈던 시간과 현재시간이 총알간격(공격속도)보다 길때 총을 쏠수 있도록 함
		bulletload1 = 1;
	}
	if ((int)dissave2 >= DISTANCEATTACK * 1000) { // p1과같음
		bulletload2 = 1;
	}
}

void itemrespawn(int repeat) {
	float gunet, ginpet, ginpet2, etpt; // clock 함수 쓰기위한 변수들

	if (repeat == 1) { // 반복이 있는 아이템생성
		while (1) {
			gunet = clock() - gunst; // 총이 일정시간마다 나오도록 변수 선언할때 clock 해주었고 지금 clock 한 값에 처음 clock 한 것을 빼준것을 저장한다
			etpt = clock() - stpt; // 총이 일정시간마다 나오도록 변수 선언할때 clock 해주었고 지금 clock 한 값에 처음 clock 한 것을 빼준것을 저장한다

			if ((int)gunet >= 15000) { // 만약 처음시간~마지막시간이 15초 이상이면 그때 gun함수를 실행하고 다시실행되게끔 gunst를 초기화 해준다
				for (int i = 0; i < 2; i++) {
					gun();
					gunst = clock();
				}
			}
			if ((int)etpt >= 15000) { // 만약 처음시간~마지막시간이 10초 이상이면 그때 potion함수를 실행하고 다시실행되게끔 stpt를 초기화 해준다
				potion();
				stpt = clock();
			}
			ginpet = clock() - ginpst; // 15초가 되면 총효과가 사라지게끔 한것 pinpst는 총을 먹었을때 아래코드에서 clock을 해주었다
			if ((int)ginpet >= 15000) { // 처음~마지막 간격이 15초이상이면 flag = 0 (총이 없는 상태) 로 하고 다시 ginpst 를 초기화 해준다
				flag = 0;
			}
			ginpet2 = clock() - ginpst2; // 위와 같은 방식을 p2 에게 적용
			if ((int)ginpet2 >= 15000) {
				flag2 = 0;
			}
			keyinput();
		}
	}

	else if (repeat == 0) { // 반복이 없는 아이템 생성
		gunet = clock() - gunst; // 총이 일정시간마다 나오도록 변수 선언할때 clock 해주었고 지금 clock 한 값에 처음 clock 한 것을 빼준것을 저장한다
		etpt = clock() - stpt; // 총이 일정시간마다 나오도록 변수 선언할때 clock 해주었고 지금 clock 한 값에 처음 clock 한 것을 빼준것을 저장한다

		if ((int)gunet >= 15000) { // 만약 처음시간~마지막시간이 15초 이상이면 그때 gun함수를 실행하고 다시실행되게끔 gunst를 초기화 해준다
			for (int i = 0; i < 2; i++) {
				gun();
				gunst = clock();
			}
		}
		if ((int)etpt >= 15000) { // 만약 처음시간~마지막시간이 10초 이상이면 그때 potion함수를 실행하고 다시실행되게끔 stpt를 초기화 해준다
			potion();
			stpt = clock();
		}
		ginpet = clock() - ginpst; // 15초가 되면 총효과가 사라지게끔 한것 pinpst는 총을 먹었을때 아래코드에서 clock을 해주었다
		if ((int)ginpet >= 15000) { // 처음~마지막 간격이 15초이상이면 flag = 0 (총이 없는 상태) 로 하고 다시 ginpst 를 초기화 해준다
			flag = 0;
		}
		ginpet2 = clock() - ginpst2; // 위와 같은 방식을 p2 에게 적용
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
	printmap(); // 위 함수로 맵의 값이 변경되고 마지막에 맵을 출력

	print_infor(); // 플레이어 정보를 출력

	for (i = 0; i < MAPSIZE; i++)
	{
		for (j = 0; j < MAPSIZE; j++)
		{
			if (map[i][j] == 9) // 맵 전체를 돌다가 p1(9)가 있으면 그때의 i,j 좌표를 각각 y,x 변수에다가 저장
			{
				playerX = j;
				playerY = i;
			}
			if (map[i][j] == 90) { // 위와 같은 방법을 p2에 적용
				playerX2 = j;
				playerY2 = i;
			}
		}
	}

	gundis1_st = clock(); //총알의 공격속도를 제어하는 변수에 현재시간을 넣음
	gundis2_st = clock();

	itemrespawn(1); // 아이템 생성함수 실행
	keyinput();
}