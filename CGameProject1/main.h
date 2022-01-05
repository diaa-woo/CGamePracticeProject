#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>  
/*
	conio.h는 콘솔 입력 함수를 호출시켜 준다.
	옛날 MS-DOS시절부터 사용된 헤더 파일이며, 현재는 C언어 표준도 아니고 POSIX 함수도 아니기에, Visual Studio에서만 사용 가능(리눅스, OS X 사용 불가)
	
	POSIX(Portable Operating System Interface + X(UNIX의 X): 유닉스의 애플리케이션 프로그래밍 인터페이스(Application Programing Interface, API) 규격, 위 규격에 따르면 유닉스와 직접적인 연관이 없어도 유닉스 호환(Unix-like) 운영체제라고 부름
	예시로, 리눅스는 유닉스와는 별도로 개발되었지만 POSIX 표준을 거의 다 준수하기 때문에 리눅스는 유닉스 호환 운영체제로 봄(공식인증을 잘 안해줘서, 그냥 넓게 보면 호환 운영 체제라 침)
	macOS도 POSIX를 따름. macOS는 10.5 버젼부터 정식 인증을 받음

	C언어에는 POSIX를 따르는 헤더 파일과 함수들이 일부 존재하는데, 이 개수가 상당하다. 다만 이 POSIX를 따르지 않다고 해서 다른 헤더파일들은 POSIX 규격을 따르는 운영체제에서 따르지 못한다는 소리는 아니다.
*/

#define MAXENEMY 10
#define MAXBALL 20
#define ESC 27

struct tag_enemy{
	int Type;
	int health;
	int x;
	int y;
	int Delta;
	int nFrame;
	int nStay;
	boolean ifAlive;
}Enemy[MAXENEMY];

struct tag_player{
	int x;
	int y;
	boolean ifAlive;
}Player;

const char* arEnemy[] = { ";:^:; ", " zZWZz ", " o0@0o ", " <-=-> " };

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE; //Cursor type

int score;

const int refreshRate = 25;

struct tag_Ball {
	boolean ifExist;
	int x, y;
	int nFrame;
	int nStay;
}Ball[MAXBALL];

void gotoxy(int x, int y);  //콘솔 이동 함수

void End();  //게임 엔딩 함수

void setcursortype(CURSOR_TYPE c);  //커서 타입 변경 함수