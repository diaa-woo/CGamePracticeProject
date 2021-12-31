#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;

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



int main() {
	setcursortype(NOCURSOR);
	gotoxy(0, 0); 
	printf("(0, 0) 좌표에 출력했습니다."); 
	gotoxy(40, 12); 
	printf("(40, 12) 좌표에 출력했습니다."); 
	gotoxy(0, 24); 
	printf("가장 밑줄에 출력했습니다.");
	return 0;
}








/*
	인용:
	https://m.blog.naver.com/PostView.nhn?isHttpsRedirect=true&blogId=tipsware&logNo=221065382244&proxyReferer=
	https://lunarcat-repo.tistory.com/6
	https://docs.microsoft.com/ko-kr/windows/console/
*/