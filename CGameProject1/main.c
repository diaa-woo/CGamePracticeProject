#include "main.h"

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;
const int refreshRate = 50;  
/*
	1�ʿ� ��� �ܼ��Է��� ���� ������ ��ƾ�� ���ϴ� ����
*/

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

void End() {
	system("cls");
	gotoxy(30, 10);
	printf("===============================GAME OVER===============================\n\n");
	gotoxy(58, 15);
	printf("����=%d\n\n\n\n\n\n\n\n\n\n\n", Score);
	setcursortype(NORMALCURSOR);
	getchar();
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



int main() {
	setcursortype(NOCURSOR);
	int x = 0, y = 0;
	int cnt = 1;
	/*
		�� ������ ī���͸� �ǹ���

		1�ʿ� refreshRate ������ŭ ������ ��, ���� ����� ī���͸� ������Ŵ
		�׸��� Ư�� �Լ��� �� ȣ�� �����ִ� ����

		���� �����ϰԵǸ� ���� �۾��� ���� Ÿ�̹� �Ǵ� ��ȣ�� �ֱ� ���� ������ �� ����
	*/
	char ch;

	Player myPlayer = { 100, 0, 0, TRUE };
	Player enemyPlayer = { 100, 79, 24, TRUE };

	gotoxy(x, y);
	printf("@");
	while (TRUE) {
		gotoxy(myPlayer.x, myPlayer.y);
		printf(" ");
		gotoxy(enemyPlayer.x, enemyPlayer.y);
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
		switch (ch)
		{
		case 'w':
			if (myPlayer.y > 0) myPlayer.y--;
			break;
		case 's':
			if (myPlayer.y < 24) myPlayer.y++;
			break;
		case 'a':
			if (myPlayer.x > 0) myPlayer.x--;
			break;
		case 'd':
			if (myPlayer.x < 79) myPlayer.x++;
			break;
		case ESC:
			End();
			return 0;
		}
		gotoxy(myPlayer.x, myPlayer.y);
		printf("@");
		gotoxy(enemyPlayer.x, enemyPlayer.y);
		printf("$");

		/*
			gotoxy(0, 0);
			printf("%d", cnt);  //���� �� ���
			if (cnt % 50 == 0) printf("\n%d", cnt / refreshRate);  //ī���� ���
		*/

		Sleep(1000 / refreshRate);
		cnt++;
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