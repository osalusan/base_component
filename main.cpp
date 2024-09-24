#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib")
#include "main.h"
#include "manager.h"
#include <thread>
#include <random>

const char* CLASS_NAME = "AppClass";
const char* WINDOW_NAME = "�_���W����";
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
//// �����̃V�[�h��ݒ� (�V�X�e���̎��v���g�p)
//std::random_device rd;
//std::mt19937 generator(rd());  // �����Z���k�E�c�C�X�^�[�̗���������

int GetRand(int min, int max)
{
	//// 0.0 ���� 1.0 �܂ł̕��������_�̗����𐶐�����
	//std::uniform_real_distribution<int> distribution(min, max);
	//// �����𐶐�
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

// FPS�E�C���h�E�p
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
		L"Arial",                // �t�H���g
		nullptr,
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		24.0f,                   // �T�C�Y
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
		D2D1::RectF(0, 0, 200, 50),  // �\���̈�
		pBrush.Get()
	);

	pFPSRenderTarget->EndDraw();
}

// �{�[�_���X�E�C���h�E
void SetBorderlessWindow(HWND hwnd)
{
	// ���݂̃��j�^�[�̉𑜓x���擾
	HMONITOR hMonitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
	MONITORINFO mi = { sizeof(mi) };
	if (GetMonitorInfo(hMonitor, &mi))
	{
		// �{�[�_�[�𖳂���
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

	// �����̃V�[�h��ݒ�
	srand(static_cast<unsigned int>(time(0)));
	ShowCursor(FALSE);
	//// �����G���W�������������� (mt19937�͂悭�g���闐��������)
	//std::random_device rd;  // �m�C�Y���g�p�����V�[�h
	//std::mt19937 gen(rd()); // �����Z���k�E�c�C�X�^�@���g�p
	//std::uniform_int_distribution<> distrib(1, 100); // 1����100�̊Ԃ̐����𐶐�

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
	
	#else // relese�̎��̂�
	// �{�[�_���X�E�C���h�E
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

		// FPS�E�B���h�E�p
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


		// FPS�\���p�̃E�B���h�E���쐬
		HWND hFPSWindow = CreateWindowEx(
			0,
			fpsClassName,
			fpsWindowName,
			WS_OVERLAPPEDWINDOW,
			0, 0,				// �ʒu
			300, 100,			// �T�C�Y
			nullptr,
			nullptr,
			hInstance,
			nullptr
		);

		// FPS�E�B���h�E��\��
		ShowWindow(hFPSWindow, nCmdShow);
		UpdateWindow(hFPSWindow);
		InitializeFPSDirectWrite(hFPSWindow);

		// �t�H���g
		HRESULT hr = pDWriteFactory->CreateTextFormat(
			L"Arial",						// �t�H���g
			nullptr,                 
			DWRITE_FONT_WEIGHT_REGULAR,		// ����
			DWRITE_FONT_STYLE_NORMAL,		// �X�^�C��
			DWRITE_FONT_STRETCH_NORMAL,		// ��
			24.0f,							// �T�C�Y
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

				// FPS���v�Z
				float fps = frameCount / (totalTime / 1000.0f);
				frameCount = 0;
				totalTime = 0.0f;

				Manager::Update();

				Manager::Draw();

				#if _DEBUG
				// FPS�E�B���h�E�̕`��
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


