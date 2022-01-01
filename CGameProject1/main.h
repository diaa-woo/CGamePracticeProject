#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>  
/*
	conio.h는 콘솔 입력 함수를 호출시켜 준다.
*/

#define MAXBALL 20
#define ESC 27

typedef struct {
	int Type;
	int health;
	int x;
	int y;
	int Delta;
	int nStay;
	boolean ifAlive;
}Player;

const char* arEnemy[] = { ";:^:; ", " zZWZz ", " o0@0o ", " <-=-> " };

struct tag_Ball {
	boolean ifExist;
	int x, y;
	int nFrame;
	int nStay;
}Ball[MAXBALL];

