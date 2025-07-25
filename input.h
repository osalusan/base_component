#pragma once


class Input
{
private:
	static BYTE m_OldKeyState[256];
	static BYTE m_KeyState[256];
public:
	static void Init();
	static void Uninit();
	static void Update();

	static bool GetKeyRelease(BYTE KeyCode);
	static bool GetKeyPress( BYTE KeyCode );
	static bool GetKeyTrigger( BYTE KeyCode );

};
