#include<stdio.h>
#include<conio.h> 
#include <windows.h>
#include <time.h>
#define RED "\033[0;31m"

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70 
struct player_details
{
	char first_name[35];
	char last_name[35];
	int score;
};

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int enemyY[2];
int enemyX[2];
//int enemyFlag[2];
char car[4][4] = { { ' ','*','*',' '},
	{'*','*','*','*'},
	{' ','*','*',' '},

	{'*','*','*','*' } };

int carPos = WIN_WIDTH / 2;
player_details x = { "Ammar","Amin",0 };

void gotoxy(int x, int y) {
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}
void setcursor(bool visible, DWORD size) {
	if (size == 0)
		size = 20;
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console, &lpCursor);

}
void drawBorder() {
	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		for (int j = 0; j < 17; j++) {
			gotoxy(j, i); printf("*");
			gotoxy(WIN_WIDTH - j, i); printf("*");
		}
	}
	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		gotoxy(SCREEN_WIDTH, i); printf("*");
	}
}
void genEnemy0(int i) {
	enemyX[i] = 17 + rand() % (33);
}
void genEnemy1(int ind,int *enemyX,int size) {
	enemyX[ind] = 17 + rand() % (33);
    if (enemyX[ind] >= enemyX[0]+8 || enemyX[ind]<= enemyX[0]-8)
		return;
	else
		genEnemy1(1, enemyX,2);

}
void drawEnemy0(int ind) {
	//if (enemyFlag[ind] == true) {
		
	gotoxy(enemyX[ind], enemyY[ind]);     printf("****");
	gotoxy(enemyX[ind], enemyY[ind] + 1); printf(" ** ");
	gotoxy(enemyX[ind], enemyY[ind] + 2); printf("****");
	gotoxy(enemyX[ind], enemyY[ind] + 3); printf(" ** ");
	
}
void drawEnemy1(int ind) {
	//if (enemyFlag[ind] == true) {

	gotoxy(enemyX[ind], enemyY[ind]);     printf("****");
	gotoxy(enemyX[ind], enemyY[ind] + 1); printf(" ** ");
	gotoxy(enemyX[ind], enemyY[ind] + 2); printf("****");
	gotoxy(enemyX[ind], enemyY[ind] + 3); printf(" ** ");

}
void eraseEnemy0(int ind) {
	//if (enemyFlag[ind] == true) {
		
	gotoxy(enemyX[ind], enemyY[ind]);     printf("    ");
	gotoxy(enemyX[ind], enemyY[ind] + 1); printf("    ");
	gotoxy(enemyX[ind], enemyY[ind] + 2); printf("    ");
	gotoxy(enemyX[ind], enemyY[ind] + 3); printf("    ");
	
}
void eraseEnemy1(int ind) {
	//if (enemyFlag[ind] == true) {

	gotoxy(enemyX[ind], enemyY[ind]);     printf("    ");
	gotoxy(enemyX[ind], enemyY[ind] + 1); printf("    ");
	gotoxy(enemyX[ind], enemyY[ind] + 2); printf("    ");
	gotoxy(enemyX[ind], enemyY[ind] + 3); printf("    ");

}
void resetEnemy0(int ind) {
	eraseEnemy0(ind);
	enemyY[ind] = 1;
	genEnemy0(ind);
	
}
void resetEnemy1(int ind) {
	eraseEnemy1(ind);
	enemyY[ind] = 1;
	genEnemy1(ind,enemyX,2);

}
void drawCar() {
	gotoxy(carPos,22); printf(" ** ");
	gotoxy(carPos,23); printf("****");
	gotoxy(carPos,24); printf(" ** ");
	gotoxy(carPos,25); printf("****");
}
void eraseCar() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			gotoxy(j + carPos, i + 22);
			printf(" ");
		}
	}
}

int collision0() {
	if (enemyY[0] + 4 >= 23) {
		if (enemyX[0] + 4 - carPos >= 0 && enemyX[0] + 4 - carPos < 9) {
			return 1;
		}
	}
	return 0;
}
int collision1()
{
	if (enemyY[1] + 4 >= 23) {
		if (enemyX[1] + 4 - carPos >= 0 && enemyX[1] + 4 - carPos < 9) {
			return 1;
		}
	}
	return 0;
}
void gameover() {
	system("cls");
	printf("\n");
	printf("\t\t--------------------------\n");
	printf("\t\t-------- Game Over -------\n");
	printf("\t\t--------------------------\n\n");
	printf("\t\t\t Score: %d\n\n", x.score);
	printf("\t\tPress Enter to go back to menu.");


	char c=_getch();
	if (c == '\r' || c == 'm')
		return;
	else
		gameover();

}
void updateScore() {

	gotoxy(WIN_WIDTH + 7, 5);
	printf("Score: %d\n", x.score);
}


void play(int finish) {

	system("color a");
	x.score = 0;
	carPos = -1 + WIN_WIDTH / 2;

	enemyY[0] = enemyY[1] = 1;

	system("cls");
	drawBorder();
	updateScore();
	genEnemy0(0);
	genEnemy1(1,enemyX,2);

	gotoxy(WIN_WIDTH + 7, 2); printf("Car Game");
	gotoxy(WIN_WIDTH + 6, 4); printf("----------");
	gotoxy(WIN_WIDTH + 6, 6); printf("----------");
	gotoxy(WIN_WIDTH + 7, 12); printf("Control ");
	gotoxy(WIN_WIDTH + 7, 13); printf("-------- ");
	gotoxy(WIN_WIDTH + 2, 14); printf(" A Key - Left");
	gotoxy(WIN_WIDTH + 2, 15); printf(" D Key - Right");

	gotoxy(18, 5); printf("Press any key to start");
	_getch();
	gotoxy(18, 5); printf("                      ");

	while (1) {

		if (_kbhit()) {
			char ch = _getch();
			if (ch == 'a' || ch == 'A') {
				if (carPos > 18)
					carPos -= 4;
			}
			if (ch == 'd' || ch == 'D') {
				if (carPos < 50)
					carPos += 4;
			}
			if (ch == 27) // esc
			{
				x.score = 0;
				break;
			}

		}

		drawCar();
		drawEnemy0(0);
		drawEnemy1(1);
		if (collision1() == 1 || collision0()==1) {
			// PlaySound("mixkit-arcade-game-explosion-1699.wav", NULL, SND_ASYNC);
			gameover();
			return;
		}
		Sleep(30);
		eraseCar();
		eraseEnemy0(0);
		eraseEnemy1(1);

		enemyY[0] += 1;

		enemyY[1] += 1;

		if (enemyY[0]+4 > SCREEN_HEIGHT && enemyY[1]+4>SCREEN_HEIGHT ) {
			resetEnemy0(0);
			resetEnemy1(1);
			x.score++;
			updateScore();
		}
		if (x.score == finish)
		{
			// PlaySound("mixkit-game-level-completed-2059.wav", NULL, SND_SYNC);
			gameover();
			return;
		}

	}
}
int search(char op, char key)
{
	if (op == key)
		return 1;
	return 0;
}

int main()
{
	system("color a"); // change color to green
	int finish = 200, max = 0,s;
	char key = '1';
	printf("\n Enter First Name: ");
	scanf("%s", x.first_name);
	printf("\n Enter Last Name: ");
	scanf("%s", x.last_name);
	FILE* f;
	f = fopen("cargame.txt", "a");
	if (f == NULL)
	{
		printf("error");
		return 0;
	}

	setcursor(0, 0);
	srand((unsigned)time(NULL));

	do {
		system("cls");
		// PlaySound("mixkit-arcade-game-opener-222.wav", NULL, SND_ASYNC);
		gotoxy(10, 5); printf(" -------------------------- ");
		gotoxy(10, 6); printf(" |        Car Game        | ");
		gotoxy(10, 7); printf(" --------------------------");
		gotoxy(10, 9); printf(" Press 1 to Start Game");
		gotoxy(10, 10); printf(" Press Any Key to Quit");
		gotoxy(10, 13);printf(" Instructions");
		gotoxy(10, 14);printf(" ----------------");
		gotoxy(10, 15);printf(" Avoid cars by moving left or right. ");
		gotoxy(10, 16);printf(" Press 'a' to move left");
		gotoxy(10, 17);printf(" Press 'd' to move right");
		gotoxy(10, 18);printf(" Press 'escape' to exit");
		gotoxy(10, 19);printf(" **To finish this game, your score must reach 200**");
		gotoxy(10, 20);printf(RED" **WARNING: If you quit the game improperly, your High Score will not be saved**\n"); // change color to red for the warning



		char op = _getch();
		s=search(op, key);

		if (s == 1)
			play(finish);
		else
		{
			if (max < finish)
			{
				fprintf(f, "\n **High Score for This Round is %d**\n", max);
				fprintf(f, "\n -----------------------------------\n");
			}
			exit(0);


		}
		if (x.score > max)
			max = x.score;
		
		fprintf(f, "\n Name: % s % s\tScore : % d\n", x.first_name, x.last_name, x.score);
		if (x.score==finish)
			fprintf(f, "\n **%s %s Completed the Game**\n", x.first_name, x.last_name);
		

	} while (1);
	fclose(f);
	
	
	return 0;
}