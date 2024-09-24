#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib")
#include "main.h"
#include "manager.h"
#include <thread>
#include <random>

const char* CLASS_NAME = "AppClass";
const char* WINDOW_NAME = "ダンジョン";
const char* GAME_VERSION = "0.9.0" ;

#include <d2d1.h>
#include <dwrite.h>
#include <wrl.h>
#include <iostream>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")



LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


HWND g_Window;

HWND GetWindow()
{
	return g_Window;
}

XMFLOAT2 GetWindowSize()
{
	RECT rect;
	GetWindowRect(GetWindow(), &rect);

	return XMFLOAT2(rect.right - rect.left, rect.bottom - rect.top);
}
//// 乱数のシードを設定 (システムの時計を使用)
//std::random_device rd;
//std::mt19937 generator(rd());  // メルセンヌ・ツイスターの乱数生成器

int GetRand(int min, int max)
{
	//// 0.0 から 1.0 までの浮動小数点の乱数を生成する
	//std::uniform_real_distribution<int> distribution(min, max);
	//// 乱数を生成
	//int randomValue = distribution(generator);
	return 0;
}

LRESULT CALLBACK FPSWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

// FPSウインドウ用
Microsoft::WRL::ComPtr<ID2D1HwndRenderTarget> pFPSRenderTarget;
Microsoft::WRL::ComPtr<ID2D1Factory> pD2DFactory;
Microsoft::WRL::ComPtr<IDWriteTextFormat> pTextFormat;
Microsoft::WRL::ComPtr<IDWriteFactory> pDWriteFactory;

void InitializeFPSDirectWrite(HWND hwnd)
{
	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, pD2DFactory.GetAddressOf());
	RECT rc;
	GetClientRect(hwnd, &rc);

	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, pD2DFactory.GetAddressOf());
	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(pDWriteFactory.GetAddressOf()));

	pDWriteFactory->CreateTextFormat(
		L"Arial",                // フォント
		nullptr,
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		24.0f,                   // サイズ
		L"en-us",
		pTextFormat.GetAddressOf()
	);

	hr = pD2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)),
		pFPSRenderTarget.GetAddressOf()
	);
}

void RenderFPSWindow(float fps)
{
	pFPSRenderTarget->BeginDraw();
	pFPSRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));

	wchar_t fpsText[256];
	swprintf_s(fpsText, 256, L"FPS: %.2f", fps);

	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> pBrush;
	pFPSRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), pBrush.GetAddressOf());

	pFPSRenderTarget->DrawText(
		fpsText,
		wcslen(fpsText),
		pTextFormat.Get(),
		D2D1::RectF(0, 0, 200, 50),  // 表示領域
		pBrush.Get()
	);

	pFPSRenderTarget->EndDraw();
}

// ボーダレスウインドウ
void SetBorderlessWindow(HWND hwnd)
{
	// 現在のモニターの解像度を取得
	HMONITOR hMonitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
	MONITORINFO mi = { sizeof(mi) };
	if (GetMonitorInfo(hMonitor, &mi))
	{
		// ボーダーを無くす
		SetWindowLong(hwnd, GWL_STYLE, WS_POPUP);
		SetWindowPos(hwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top,
			mi.rcMonitor.right - mi.rcMonitor.left,
			mi.rcMonitor.bottom - mi.rcMonitor.top,
			SWP_FRAMECHANGED | SWP_NOOWNERZORDER);
	}
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(288);

	// 乱数のシードを設定
	srand(static_cast<unsigned int>(time(0)));
	ShowCursor(FALSE);
	//// 乱数エンジンを初期化する (mt19937はよく使われる乱数生成器)
	//std::random_device rd;  // ノイズを使用したシード
	//std::mt19937 gen(rd()); // メルセンヌ・ツイスタ法を使用
	//std::uniform_int_distribution<> distrib(1, 100); // 1から100の間の整数を生成

	WNDCLASSEX wcex;
	{
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = 0;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		wcex.hIcon = nullptr;
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = nullptr;
		wcex.lpszMenuName = nullptr;
		wcex.lpszClassName = CLASS_NAME;
		wcex.hIconSm = nullptr;

		RegisterClassEx(&wcex);


		RECT rc = { 0, 0, (LONG)SCREEN_WIDTH, (LONG)SCREEN_HEIGHT };
		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

		g_Window = CreateWindowEx(0, CLASS_NAME, WINDOW_NAME, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
			rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance, nullptr);
	}

	#if _DEBUG
	
	#else // releseの時のみ
	// ボーダレスウインドウ
	SetBorderlessWindow(g_Window);
	#endif

	CoInitializeEx(nullptr, COINITBASE_MULTITHREADED);


	Manager::Init();


	ShowWindow(g_Window, nCmdShow);
	UpdateWindow(g_Window);


#if _DEBUG


	{
		const char* fpsClassName = "FPSClass";
		const char* fpsWindowName = "FPSWindow";

		// FPSウィンドウ用
		WNDCLASSEX fpsWcex;
		fpsWcex.cbSize = sizeof(WNDCLASSEX);
		fpsWcex.style = 0;
		fpsWcex.lpfnWndProc = FPSWndProc; 
		fpsWcex.cbClsExtra = 0;
		fpsWcex.cbWndExtra = 0;
		fpsWcex.hInstance = hInstance;
		fpsWcex.hIcon = nullptr;
		fpsWcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		fpsWcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		fpsWcex.lpszMenuName = nullptr;
		fpsWcex.lpszClassName = fpsClassName;
		fpsWcex.hIconSm = nullptr;

		RegisterClassEx(&fpsWcex);


		// FPS表示用のウィンドウを作成
		HWND hFPSWindow = CreateWindowEx(
			0,
			fpsClassName,
			fpsWindowName,
			WS_OVERLAPPEDWINDOW,
			0, 0,				// 位置
			300, 100,			// サイズ
			nullptr,
			nullptr,
			hInstance,
			nullptr
		);

		// FPSウィンドウを表示
		ShowWindow(hFPSWindow, nCmdShow);
		UpdateWindow(hFPSWindow);
		InitializeFPSDirectWrite(hFPSWindow);

		// フォント
		HRESULT hr = pDWriteFactory->CreateTextFormat(
			L"Arial",						// フォント
			nullptr,                 
			DWRITE_FONT_WEIGHT_REGULAR,		// 太さ
			DWRITE_FONT_STYLE_NORMAL,		// スタイル
			DWRITE_FONT_STRETCH_NORMAL,		// 幅
			24.0f,							// サイズ
			L"en-us",                   
			pTextFormat.GetAddressOf()
		);
	}
#endif

	DWORD dwExecLastTime;
	DWORD dwCurrentTime;
	timeBeginPeriod(1);
	dwExecLastTime = timeGetTime();
	dwCurrentTime = 0;
	int frameCount = 0;
	float frameTime = 0;
	float totalTime = 0;
	

	MSG msg;
	while(1)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
		else
		{
			dwCurrentTime = timeGetTime();
			frameTime = dwCurrentTime - dwExecLastTime;
			totalTime += frameTime;
			frameCount++;

			if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				// FPSを計算
				float fps = frameCount / (totalTime / 1000.0f);
				frameCount = 0;
				totalTime = 0.0f;

				Manager::Update();

				Manager::Draw();

				#if _DEBUG
				// FPSウィンドウの描画
				RenderFPSWindow(fps);
				#endif
			}
		}
	}

	timeEndPeriod(1);

	UnregisterClass(CLASS_NAME, wcex.hInstance);

	Manager::Uninit();

	CoUninitialize();

	return (int)msg.wParam;
}




LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{


	switch(uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


