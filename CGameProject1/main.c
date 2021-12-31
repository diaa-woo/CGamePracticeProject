#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;

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



int main() {
	setcursortype(NOCURSOR);
	gotoxy(0, 0); 
	printf("(0, 0) ��ǥ�� ����߽��ϴ�."); 
	gotoxy(40, 12); 
	printf("(40, 12) ��ǥ�� ����߽��ϴ�."); 
	gotoxy(0, 24); 
	printf("���� ���ٿ� ����߽��ϴ�.");
	return 0;
}








/*
	�ο�:
	https://m.blog.naver.com/PostView.nhn?isHttpsRedirect=true&blogId=tipsware&logNo=221065382244&proxyReferer=
	https://lunarcat-repo.tistory.com/6
	https://docs.microsoft.com/ko-kr/windows/console/
*/