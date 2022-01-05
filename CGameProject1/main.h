#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>  
/*
	conio.h�� �ܼ� �Է� �Լ��� ȣ����� �ش�.
	���� MS-DOS�������� ���� ��� �����̸�, ����� C��� ǥ�ص� �ƴϰ� POSIX �Լ��� �ƴϱ⿡, Visual Studio������ ��� ����(������, OS X ��� �Ұ�)
	
	POSIX(Portable Operating System Interface + X(UNIX�� X): ���н��� ���ø����̼� ���α׷��� �������̽�(Application Programing Interface, API) �԰�, �� �԰ݿ� ������ ���н��� �������� ������ ��� ���н� ȣȯ(Unix-like) �ü����� �θ�
	���÷�, �������� ���н��ʹ� ������ ���ߵǾ����� POSIX ǥ���� ���� �� �ؼ��ϱ� ������ �������� ���н� ȣȯ �ü���� ��(���������� �� �����༭, �׳� �а� ���� ȣȯ � ü���� ħ)
	macOS�� POSIX�� ����. macOS�� 10.5 �������� ���� ������ ����

	C���� POSIX�� ������ ��� ���ϰ� �Լ����� �Ϻ� �����ϴµ�, �� ������ ����ϴ�. �ٸ� �� POSIX�� ������ �ʴٰ� �ؼ� �ٸ� ������ϵ��� POSIX �԰��� ������ �ü������ ������ ���Ѵٴ� �Ҹ��� �ƴϴ�.
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

void gotoxy(int x, int y);  //�ܼ� �̵� �Լ�

void End();  //���� ���� �Լ�

void setcursortype(CURSOR_TYPE c);  //Ŀ�� Ÿ�� ���� �Լ�