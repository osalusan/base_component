#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define NOMINMAX
#include <windows.h>
#include <assert.h>
#include <functional>

#include <d3d11.h>
#pragma comment (lib, "d3d11.lib")


#include <DirectXMath.h>
using namespace DirectX;


#include "DirectXTex.h"


#if _DEBUG
#pragma comment(lib,"DirectXTex_Debug.lib")
#else
#pragma comment(lib,"DirectXTex_Release.lib")
#endif

#pragma comment (lib, "winmm.lib")

#if _DEBUG
#define SCREEN_WIDTH	(1280)
#define SCREEN_HEIGHT	(720)
#else
#define SCREEN_WIDTH	(1920)
#define SCREEN_HEIGHT	(1080)
#endif

#define MAX_PLAYERS (8)

HWND GetWindow();
XMFLOAT2 GetWindowSize();
int GetRand(int min,int max);
int GetMouseWheelValue();
//void Invoke(std::function<void()> Function, int Time);



