#ifndef _CREATE_GAME_H_
#define _CREATE_GAME_H_

#include<windows.h>
#include"tank.h"


void OnTimer(HWND hwnd);
void OnTimer1(HWND hwnd);
void OnTimer2(HWND hwnd);
void OnKeyDown(DWORD vk);
void CreateGame(HWND hwnd, // Ö÷´°¿Ú¾ä±ú
	DWORD dwInitTimerElapse, //
	direction init_dir);
void GamePaint(HWND hwnd);
#endif