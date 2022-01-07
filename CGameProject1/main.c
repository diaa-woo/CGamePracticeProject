#include "main.h"

player Player;

void setcursortype(CURSOR_TYPE c) {
	CONSOLE_CURSOR_INFO CurInfo;
	/*
		콘솔 커서에 대한 정보 표시

		코드:
		typedef struct _CONSOLE_CURSOR_INFO {
			DWORD dwSize;
			BOOL ?bVisible;
		} CONSOLE_CURSOR_INFO, *PCONSOLE_CURSOR_INFO;	

		dwSize: 커서로 채워진 문자 셀의 백분율(범위: 1~100)(예외로, 레지스트리에 CursorSize가 0으로 설정된 경우 dwSize는 0 반환) 커서 모양은 다양함 
		bVisible: 커서의 표시 유형, 커서 표시시 TRUE;
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
		지정된 콘솔 화면 버퍼에 대한 커서의 크기와 표시 유형을 설정

		코드:
		BOOL WINAPI SetConsoleCursorInfo(
			 _In_	HANDLE		hConsoleOutput,  // (콘솔 화면 버퍼에 대한 핸들)
			_In_ const CONSOLE_CURSOR_INFO *lpConsoleCursorInfo  // (콘솔 화면 버퍼의 커서에 대한 새 사양 제공)
		);

		이 함수에서 핸들과 콘솔 커서에 구조체의 주소값을 받음

	*/
}

void gotoxy(int x, int y) {
	COORD CursorPosition = { x,y };
	/*
		COORD는 윈도우 환경, 콘솔 화면 버퍼에서 문자 셀의 좌표 지정해주는 구조체
		구조체로 지정할 필요 없이 CursorPosition으로 한번에 x,y 값을 지정해줄 수 있음.
	*/
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
	/*
		응용프로그램이 직접 커널 부분의 메모리를 참조할 시 리스크 발생 가능, 이에 주소를 사용하는 포인터 대신 핸들을 사용

		핸들(Handle): 운영체제 내부에 있는 어떤 리소스의 주소를 정수로 치환한 값

		운영체제는 리소스의 주소와 핸들 값을 한 쌍으로 묶어 관리하는 '핸들 테이블' 보유
		응용프로그램에서 이 테이블에 핸들 값을 전송해 주고, 이 테이블에서 해시한 다음, 해당 테이블 주소에 들어있는 리소스의 주소로 이동해 줌.

		Win32 프로그램에서는 핸들 값을 저장할 경우 HANDLE라는 자료형을 기본적으로 사용, 이 자료형의 크기는 32비트 운영체제일 경우 'unsigned int' 자료형과 동일

		'GetStdHandle'는 핸들 값을 반환해주는 함수이며, 'STD_OUTPUT_HANDLE'는 표준콘솔출력의 핸들을 의미

		결론으로, 저 코드는 위치값과 콘솔 핸들을 해당 함수에 전달해주어 콘솔의 위치를 이동시켜줌.
	*/
}

void End() {
	system("cls");
	gotoxy(30, 10);
	printf("==========================GAME OVER============================\n\n");
	gotoxy(58, 15);
	printf("점수=%d\n\n\n\n\n\n\n\n\n\n\n", score);
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
			* _kbhit() 함수는 키보드의 키가 눌려 있으면 0이 아닌 값을, 눌려 있지 않으면 0을 반환
			이를 이용해 키보드의 키가 눌려져 있을 때만 입력을 받을 수 있음

			* _getch()는 사용자에게 키보드로 하나의 키를 입력받는 함수 중 하나
			차이점은, 다른 입력 함수들은 보통 '표준 입력' 방식으로 표준 입력 버퍼에 저장되는데, 이 함수는 '콘솔 입력'으로 버퍼에 저장되지 않고 해당 입력값을 즉시 반환 뒤 종료 된다.
			값은 받지만 그 입력값을 콘솔에 출력해주지는 않음
			즉각적인 반응을 해야할 때 필요함
		*/
		switch (ch)  //키 입력 처리
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

		//적군 생성
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


		//총알 발사
		if (checkShoot == 1) {
			gotoxy(bx, by);
			_putch(' ');
			/*
				한 글자만 출력하여 준다.
				얘를 뭣하러 쓰나 싶겠지만 우선 버퍼를 거치지 않고 바로 출력하기에 출력 속도가 상당히 빠르고, 많은 기능을 포함하고 있는 printf에 비해 더 빠른 속도를 나타내어 준다
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


		// 적군 총알 이동
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

		//적군과 아군 총알의 충돌 판정
		for (i = 0; i < MAXENEMY; i++) {
			if (!Enemy[i].ifAlive) continue;
			if (Enemy[i].y == by && abs(Enemy[i].x - bx) <= 2) {
				/*
					abs() 함수
					헤더파일: <stdlib.h>
					함수원형: int abs(int num)
					함수설명: 인자로 들어온 int 타입의 num의 절대값을 반환하는 함수
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

		// 적군 총알과 아군의 충돌 판정
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

		//적군 이동 및 출력
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
				//총알 발사
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

		// 파이터 및 점수 출력
		gotoxy(Player.x - 3, 23);
		puts(" <<A>> ");
		gotoxy(0, 24);
		printf("점수=%d", score);

		Sleep(1000 / refreshRate);
	}
	return 0;
}








/*
	인용:
	https://cosmosscoding.tistory.com/12
	https://m.blog.naver.com/PostView.nhn?isHttpsRedirect=true&blogId=tipsware&logNo=221065382244&proxyReferer=
	https://lunarcat-repo.tistory.com/6
	https://docs.microsoft.com/ko-kr/windows/console/
	https://dongwook8467.tistory.com/10
	https://blog.naver.com/PostView.nhn?blogId=tipsware&logNo=221242072724
*/