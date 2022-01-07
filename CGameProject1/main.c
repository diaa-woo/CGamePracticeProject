#include "main.h"

player Player;

void setcursortype(CURSOR_TYPE c) {
	CONSOLE_CURSOR_INFO CurInfo;
	/*
		�ܼ� Ŀ���� ���� ���� ǥ��

		�ڵ�:
		typedef struct _CONSOLE_CURSOR_INFO {
			DWORD dwSize;
			BOOL ?bVisible;
		} CONSOLE_CURSOR_INFO, *PCONSOLE_CURSOR_INFO;	

		dwSize: Ŀ���� ä���� ���� ���� �����(����: 1~100)(���ܷ�, ������Ʈ���� CursorSize�� 0���� ������ ��� dwSize�� 0 ��ȯ) Ŀ�� ����� �پ��� 
		bVisible: Ŀ���� ǥ�� ����, Ŀ�� ǥ�ý� TRUE;
	*/
	switch (c) {
	case NOCURSOR:
		CurInfo.dwSize = 1; 
		CurInfo.bVisible = FALSE;
		break;
	case SOLIDCURSOR:
		CurInfo.dwSize = 100;
		CurInfo.bVisible = TRUE;
		break;
	case NORMALCURSOR:
		CurInfo.dwSize = 20;
		CurInfo.bVisible = TRUE;
		break;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
	/*
		������ �ܼ� ȭ�� ���ۿ� ���� Ŀ���� ũ��� ǥ�� ������ ����

		�ڵ�:
		BOOL WINAPI SetConsoleCursorInfo(
			 _In_	HANDLE		hConsoleOutput,  // (�ܼ� ȭ�� ���ۿ� ���� �ڵ�)
			_In_ const CONSOLE_CURSOR_INFO *lpConsoleCursorInfo  // (�ܼ� ȭ�� ������ Ŀ���� ���� �� ��� ����)
		);

		�� �Լ����� �ڵ�� �ܼ� Ŀ���� ����ü�� �ּҰ��� ����

	*/
}

void gotoxy(int x, int y) {
	COORD CursorPosition = { x,y };
	/*
		COORD�� ������ ȯ��, �ܼ� ȭ�� ���ۿ��� ���� ���� ��ǥ �������ִ� ����ü
		����ü�� ������ �ʿ� ���� CursorPosition���� �ѹ��� x,y ���� �������� �� ����.
	*/
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
	/*
		�������α׷��� ���� Ŀ�� �κ��� �޸𸮸� ������ �� ����ũ �߻� ����, �̿� �ּҸ� ����ϴ� ������ ��� �ڵ��� ���

		�ڵ�(Handle): �ü�� ���ο� �ִ� � ���ҽ��� �ּҸ� ������ ġȯ�� ��

		�ü���� ���ҽ��� �ּҿ� �ڵ� ���� �� ������ ���� �����ϴ� '�ڵ� ���̺�' ����
		�������α׷����� �� ���̺� �ڵ� ���� ������ �ְ�, �� ���̺��� �ؽ��� ����, �ش� ���̺� �ּҿ� ����ִ� ���ҽ��� �ּҷ� �̵��� ��.

		Win32 ���α׷������� �ڵ� ���� ������ ��� HANDLE��� �ڷ����� �⺻������ ���, �� �ڷ����� ũ��� 32��Ʈ �ü���� ��� 'unsigned int' �ڷ����� ����

		'GetStdHandle'�� �ڵ� ���� ��ȯ���ִ� �Լ��̸�, 'STD_OUTPUT_HANDLE'�� ǥ���ܼ������ �ڵ��� �ǹ�

		�������, �� �ڵ�� ��ġ���� �ܼ� �ڵ��� �ش� �Լ��� �������־� �ܼ��� ��ġ�� �̵�������.
	*/
}

void End() {
	system("cls");
	gotoxy(30, 10);
	printf("==========================GAME OVER============================\n\n");
	gotoxy(58, 15);
	printf("����=%d\n\n\n\n\n\n\n\n\n\n\n", score);
	setcursortype(NORMALCURSOR);
	getchar();
	return;
}

int main() {
	setcursortype(NOCURSOR);
	int x = 0, y = 0;
	int fx = 60;
	int bx = 0, by = 0;
	int i = 0, j = 0;
	boolean checkShoot = 0, bFound;
	char ch;
	Player.x = 63;
	while (TRUE) {
		gotoxy(Player.x, Player.y);
		printf(" ");

		ch = '\0';
		if(_kbhit()) ch = _getch();
		/*
			* _kbhit() �Լ��� Ű������ Ű�� ���� ������ 0�� �ƴ� ����, ���� ���� ������ 0�� ��ȯ
			�̸� �̿��� Ű������ Ű�� ������ ���� ���� �Է��� ���� �� ����

			* _getch()�� ����ڿ��� Ű����� �ϳ��� Ű�� �Է¹޴� �Լ� �� �ϳ�
			��������, �ٸ� �Է� �Լ����� ���� 'ǥ�� �Է�' ������� ǥ�� �Է� ���ۿ� ����Ǵµ�, �� �Լ��� '�ܼ� �Է�'���� ���ۿ� ������� �ʰ� �ش� �Է°��� ��� ��ȯ �� ���� �ȴ�.
			���� ������ �� �Է°��� �ֿܼ� ����������� ����
			�ﰢ���� ������ �ؾ��� �� �ʿ���
		*/
		switch (ch)  //Ű �Է� ó��
		{
		case 75: 
			if (Player.x > 2) {
				Player.x--;
			}
			break;
		case 77:
			if (Player.x < 77) {
				Player.x++;
			}
			break;
		case ' ':
			if (checkShoot == 0) {
				checkShoot = 1;
				bx = Player.x;
				by = 23;
			}
			break;
		case ESC:
			End();
			return 0;
		}

		//���� ����
		if (rand() % 50 == 0) {
			for (i = 0; i < MAXENEMY && Enemy[i].ifAlive == 1; i++) { ; }
			if (i != MAXENEMY) {
				if ((rand() % 2) + 1 == 1) {
					Enemy[i].x = 5;
					Enemy[i].Delta = 1;
				}

				else {
					Enemy[i].x = 75;
					Enemy[i].Delta = -1;
				}

				for (;;) {
					Enemy[i].y = rand() % 10 + 1;
					for (bFound = 0, j = 0; j < MAXENEMY; j++) {
						if (Enemy[j].ifAlive == 1 && Enemy[j].y == Enemy[i].y) {
							bFound = 1;
							break;
						}
					}
					if (bFound == 0) {
						break;
					}
				} 
				Enemy[i].nFrame = Enemy[i].nStay = rand() % 6 + 1;
				Enemy[i].Type = rand() % (sizeof(arEnemy) / sizeof(arEnemy[0]));
				Enemy[i].ifAlive = 1;
			}
		}


		//�Ѿ� �߻�
		if (checkShoot == 1) {
			gotoxy(bx, by);
			_putch(' ');
			/*
				�� ���ڸ� ����Ͽ� �ش�.
				�긦 ���Ϸ� ���� �Ͱ����� �켱 ���۸� ��ġ�� �ʰ� �ٷ� ����ϱ⿡ ��� �ӵ��� ����� ������, ���� ����� �����ϰ� �ִ� printf�� ���� �� ���� �ӵ��� ��Ÿ���� �ش�
			*/
			if (by == 0) {
				checkShoot = 0;
			}
			else {
				by--;
				gotoxy(bx, by);
				_putch('i');
			}
		}


		// ���� �Ѿ� �̵�
		for (i = 0; i < MAXBALL; i++)
		{
			if (Ball[i].ifExist == FALSE)
				continue;

			if (--Ball[i].nStay == 0)
			{
				Ball[i].nStay = Ball[i].nFrame;
				gotoxy(Ball[i].x, Ball[i].y); _putch(' ');

				if (Ball[i].y >= 23)
				{
					Ball[i].ifExist = FALSE;
				}
				else
				{
					Ball[i].y++;
					gotoxy(Ball[i].x, Ball[i].y); _putch('*');
				}
			}
		}

		//������ �Ʊ� �Ѿ��� �浹 ����
		for (i = 0; i < MAXENEMY; i++) {
			if (!Enemy[i].ifAlive) continue;
			if (Enemy[i].y == by && abs(Enemy[i].x - bx) <= 2) {
				/*
					abs() �Լ�
					�������: <stdlib.h>
					�Լ�����: int abs(int num)
					�Լ�����: ���ڷ� ���� int Ÿ���� num�� ���밪�� ��ȯ�ϴ� �Լ�
				*/
				gotoxy(bx, by); _putch(' ');
				bx = -1;
				Enemy[i].ifAlive = 0;
				gotoxy(Enemy[i].x - 3, Enemy[i].y);
				puts("       ");
				score += 7 - Enemy[i].nFrame;
				break;
			}
		}

		// ���� �Ѿ˰� �Ʊ��� �浹 ����
		for (i = 0; i < MAXBALL; i++) {
			if (Ball[i].ifExist == FALSE) continue;
			if (Ball[i].y == 23 && abs(Ball[i].x - Player.x) <= 2) {
				gotoxy(Player.x - 3, 21); puts("   .   ");
				gotoxy(Player.x - 3, 22); puts(" .  . .");
				gotoxy(Player.x - 3, 23); puts("..:V:..");
				Sleep(1000);

				End();
				return 0;
			}
		}

		//���� �̵� �� ���
		for (i = 0; i < MAXENEMY; i++) {
			if (Enemy[i].ifAlive == 0) continue;
			if (--Enemy[i].nStay == 0) {
				Enemy[i].nStay = Enemy[i].nFrame;
				if (Enemy[i].x >= 76 || Enemy[i].x <= 4) {
					Enemy[i].ifAlive = FALSE;
					gotoxy(Enemy[i].x - 3, Enemy[i].y);
					puts("       ");
				}
			}
			else {
				Enemy[i].x += Enemy[i].Delta;
				gotoxy(Enemy[i].x - 3, Enemy[i].y);
				puts(arEnemy[Enemy[i].Type]);
				//�Ѿ� �߻�
				if (rand() % 20 == 0) {
					for (j = 0; j < MAXBALL && Ball[j].ifExist == 1; j++) {;}
					if (j != MAXBALL) {
						Ball[j].x = Enemy[i].x + 1;
						Ball[j].y = Enemy[i].y + 1;
						Ball[j].nFrame = Ball[j].nStay = Enemy[i].nFrame * 6;
						Ball[j].ifExist = 1;
					}
				}
			}
		}

		// ������ �� ���� ���
		gotoxy(Player.x - 3, 23);
		puts(" <<A>> ");
		gotoxy(0, 24);
		printf("����=%d", score);

		Sleep(1000 / refreshRate);
	}
	return 0;
}








/*
	�ο�:
	https://cosmosscoding.tistory.com/12
	https://m.blog.naver.com/PostView.nhn?isHttpsRedirect=true&blogId=tipsware&logNo=221065382244&proxyReferer=
	https://lunarcat-repo.tistory.com/6
	https://docs.microsoft.com/ko-kr/windows/console/
	https://dongwook8467.tistory.com/10
	https://blog.naver.com/PostView.nhn?blogId=tipsware&logNo=221242072724
*/