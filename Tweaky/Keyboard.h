#pragma once
#include "Windows.h"

//Creates an INPUT for a key down event, given the @keyCode.
INPUT* ToDownKey(INPUT *down, byte keyCode)
{
	down->type = INPUT_KEYBOARD;
	down->ki.wVk = LOBYTE(keyCode);
	down->ki.wScan = 0;
	down->ki.dwFlags = 0;
	down->ki.time = 0;
	down->ki.dwExtraInfo = NULL;
	return down;
}

//Creates an INPUT for a key up event, given the @keyCode.
INPUT* ToUpKey(INPUT *up, byte keyCode)
{
	up->type = INPUT_KEYBOARD;
	up->ki.wVk = LOBYTE(keyCode);
	up->ki.wScan = 0;
	up->ki.dwFlags = KEYEVENTF_KEYUP;
	up->ki.time = 0;
	up->ki.dwExtraInfo = NULL;
	return up;
}

//Builds string. aka keyCode[0] down/up -> keyCode[1] down/up
int BuildStringInput(INPUT *input, byte *keyCode, int length)
{
	if (input == NULL || keyCode == NULL || length <= 0)
		return -1;

	int i = 0, j = 0;
	while (i < 2 * length)
	{
		ToDownKey(&input[i++], keyCode[j]);
		ToUpKey(&input[i++], keyCode[j++]);
	}
	return 0;
}

//Builds shortcut input: keyCode[0] down -> keyCode[1] down -> keyCode[1] up -> keyCode[0] up. 
//Length should be  length of keyCode array. AKA half the size of the input array. 
int BuildShortcutInput(INPUT *input, byte *keyCode, int length)
{
	if (input == NULL || keyCode == NULL || length <= 0)
		return -1;

	int j = 0;

	for (int i = 0; i < length; i++)
		ToDownKey(&input[j++], keyCode[i]);

	for (int i = length - 1; i > -1; i--)
		ToUpKey(&input[j++], keyCode[i]);

	return 0;
}

//Converts between Virtual Key name to its corresponding byte. 
byte BracketToVirtualKeyCode(const wchar_t *tmp)
{
	if (0 == wcscmp(tmp, L"VK_LBUTTON"))
		return 0x01;

	if (0 == wcscmp(tmp, L"VK_RBUTTON"))
		return 0x02;

	if (0 == wcscmp(tmp, L"VK_CANCEL"))
		return 0x03;

	if (0 == wcscmp(tmp, L"VK_MBUTTON"))
		return 0x04;

	if (0 == wcscmp(tmp, L"VK_XBUTTON1"))
		return 0x05;

	if (0 == wcscmp(tmp, L"VK_XBUTTON2"))
		return 0x06;

	if (0 == wcscmp(tmp, L"VK_BACK"))
		return 0x08;

	if (0 == wcscmp(tmp, L"VK_TAB"))
		return 0x09;

	if (0 == wcscmp(tmp, L"VK_CLEAR"))
		return 0x0C;

	if (0 == wcscmp(tmp, L"VK_RETURN"))
		return 0x0D;

	if (0 == wcscmp(tmp, L"VK_SHIFT"))
		return 0x10;

	if (0 == wcscmp(tmp, L"VK_CONTROL"))
		return 0x11;

	if (0 == wcscmp(tmp, L"VK_MENU"))
		return 0x12;

	if (0 == wcscmp(tmp, L"VK_PAUSE"))
		return 0x13;

	if (0 == wcscmp(tmp, L"VK_CAPITAL"))
		return 0x14;

	if (0 == wcscmp(tmp, L"VK_KANA"))
		return 0x15;

	if (0 == wcscmp(tmp, L"VK_HANGUEL"))
		return 0x15;

	if (0 == wcscmp(tmp, L"VK_HANGUL"))
		return 0x15;

	if (0 == wcscmp(tmp, L"VK_JUNJA"))
		return 0x17;

	if (0 == wcscmp(tmp, L"VK_FINAL"))
		return 0x18;

	if (0 == wcscmp(tmp, L"VK_HANJA"))
		return 0x19;

	if (0 == wcscmp(tmp, L"VK_KANJI"))
		return 0x19;

	if (0 == wcscmp(tmp, L"VK_ESCAPE"))
		return 0x1B;

	if (0 == wcscmp(tmp, L"VK_CONVERT"))
		return 0x1C;

	if (0 == wcscmp(tmp, L"VK_NONCONVERT"))
		return 0x1D;

	if (0 == wcscmp(tmp, L"VK_ACCEPT"))
		return 0x1E;

	if (0 == wcscmp(tmp, L"VK_MODECHANGE"))
		return 0x1F;

	if (0 == wcscmp(tmp, L"VK_SPACE"))
		return 0x20;

	if (0 == wcscmp(tmp, L"VK_PRIOR"))
		return 0x21;

	if (0 == wcscmp(tmp, L"VK_NEXT"))
		return 0x22;

	if (0 == wcscmp(tmp, L"VK_END"))
		return 0x23;

	if (0 == wcscmp(tmp, L"VK_HOME"))
		return 0x24;

	if (0 == wcscmp(tmp, L"VK_LEFT"))
		return 0x25;

	if (0 == wcscmp(tmp, L"VK_UP"))
		return 0x26;

	if (0 == wcscmp(tmp, L"VK_RIGHT"))
		return 0x27;

	if (0 == wcscmp(tmp, L"VK_DOWN"))
		return 0x28;

	if (0 == wcscmp(tmp, L"VK_SELECT"))
		return 0x29;

	if (0 == wcscmp(tmp, L"VK_PRINT"))
		return 0x2A;

	if (0 == wcscmp(tmp, L"VK_EXECUTE"))
		return 0x2B;

	if (0 == wcscmp(tmp, L"VK_SNAPSHOT"))
		return 0x2C;

	if (0 == wcscmp(tmp, L"VK_INSERT"))
		return 0x2D;

	if (0 == wcscmp(tmp, L"VK_DELETE"))
		return 0x2E;

	if (0 == wcscmp(tmp, L"VK_HELP"))
		return 0x2F;

	if (0 == wcscmp(tmp, L"VK_LWIN"))
		return 0x5B;

	if (0 == wcscmp(tmp, L"VK_RWIN"))
		return 0x5C;

	if (0 == wcscmp(tmp, L"VK_APPS"))
		return 0x5D;

	if (0 == wcscmp(tmp, L"VK_SLEEP"))
		return 0x5F;

	if (0 == wcscmp(tmp, L"VK_NUMPAD0"))
		return 0x60;

	if (0 == wcscmp(tmp, L"VK_NUMPAD1"))
		return 0x61;

	if (0 == wcscmp(tmp, L"VK_NUMPAD2"))
		return 0x62;

	if (0 == wcscmp(tmp, L"VK_NUMPAD3"))
		return 0x63;

	if (0 == wcscmp(tmp, L"VK_NUMPAD4"))
		return 0x64;

	if (0 == wcscmp(tmp, L"VK_NUMPAD5"))
		return 0x65;

	if (0 == wcscmp(tmp, L"VK_NUMPAD6"))
		return 0x66;

	if (0 == wcscmp(tmp, L"VK_NUMPAD7"))
		return 0x67;

	if (0 == wcscmp(tmp, L"VK_NUMPAD8"))
		return 0x68;

	if (0 == wcscmp(tmp, L"VK_NUMPAD9"))
		return 0x69;

	if (0 == wcscmp(tmp, L"VK_MULTIPLY"))
		return 0x6A;

	if (0 == wcscmp(tmp, L"VK_ADD"))
		return 0x6B;

	if (0 == wcscmp(tmp, L"VK_SEPARATOR"))
		return 0x6C;

	if (0 == wcscmp(tmp, L"VK_SUBTRACT"))
		return 0x6D;

	if (0 == wcscmp(tmp, L"VK_DECIMAL"))
		return 0x6E;

	if (0 == wcscmp(tmp, L"VK_DIVIDE"))
		return 0x6F;

	if (0 == wcscmp(tmp, L"VK_F1"))
		return 0x70;

	if (0 == wcscmp(tmp, L"VK_F2"))
		return 0x71;

	if (0 == wcscmp(tmp, L"VK_F3"))
		return 0x72;

	if (0 == wcscmp(tmp, L"VK_F4"))
		return 0x73;

	if (0 == wcscmp(tmp, L"VK_F5"))
		return 0x74;

	if (0 == wcscmp(tmp, L"VK_F6"))
		return 0x75;

	if (0 == wcscmp(tmp, L"VK_F7"))
		return 0x76;

	if (0 == wcscmp(tmp, L"VK_F8"))
		return 0x77;

	if (0 == wcscmp(tmp, L"VK_F9"))
		return 0x78;

	if (0 == wcscmp(tmp, L"VK_F10"))
		return 0x79;

	if (0 == wcscmp(tmp, L"VK_F11"))
		return 0x7A;

	if (0 == wcscmp(tmp, L"VK_F12"))
		return 0x7B;

	if (0 == wcscmp(tmp, L"VK_F13"))
		return 0x7C;

	if (0 == wcscmp(tmp, L"VK_F14"))
		return 0x7D;

	if (0 == wcscmp(tmp, L"VK_F15"))
		return 0x7E;

	if (0 == wcscmp(tmp, L"VK_F16"))
		return 0x7F;

	if (0 == wcscmp(tmp, L"VK_F17"))
		return 0x80;

	if (0 == wcscmp(tmp, L"VK_F18"))
		return 0x81;

	if (0 == wcscmp(tmp, L"VK_F19"))
		return 0x82;

	if (0 == wcscmp(tmp, L"VK_F20"))
		return 0x83;

	if (0 == wcscmp(tmp, L"VK_F21"))
		return 0x84;

	if (0 == wcscmp(tmp, L"VK_F22"))
		return 0x85;

	if (0 == wcscmp(tmp, L"VK_F23"))
		return 0x86;

	if (0 == wcscmp(tmp, L"VK_F24"))
		return 0x87;

	if (0 == wcscmp(tmp, L"VK_NUMLOCK"))
		return 0x90;

	if (0 == wcscmp(tmp, L"VK_SCROLL"))
		return 0x91;

	if (0 == wcscmp(tmp, L"VK_LSHIFT"))
		return 0xA0;

	if (0 == wcscmp(tmp, L"VK_RSHIFT"))
		return 0xA1;

	if (0 == wcscmp(tmp, L"VK_LCONTROL"))
		return 0xA2;

	if (0 == wcscmp(tmp, L"VK_RCONTROL"))
		return 0xA3;

	if (0 == wcscmp(tmp, L"VK_LMENU"))
		return 0xA4;

	if (0 == wcscmp(tmp, L"VK_RMENU"))
		return 0xA5;

	if (0 == wcscmp(tmp, L"VK_BROWSER_BACK"))
		return 0xA6;

	if (0 == wcscmp(tmp, L"VK_BROWSER_FORWARD"))
		return 0xA7;

	if (0 == wcscmp(tmp, L"VK_BROWSER_REFRESH"))
		return 0xA8;

	if (0 == wcscmp(tmp, L"VK_BROWSER_STOP"))
		return 0xA9;

	if (0 == wcscmp(tmp, L"VK_BROWSER_SEARCH"))
		return 0xAA;

	if (0 == wcscmp(tmp, L"VK_BROWSER_FAVORITES"))
		return 0xAB;

	if (0 == wcscmp(tmp, L"VK_BROWSER_HOME"))
		return 0xAC;

	if (0 == wcscmp(tmp, L"VK_VOLUME_MUTE"))
		return 0xAD;

	if (0 == wcscmp(tmp, L"VK_VOLUME_DOWN"))
		return 0xAE;

	if (0 == wcscmp(tmp, L"VK_VOLUME_UP"))
		return 0xAF;

	if (0 == wcscmp(tmp, L"VK_MEDIA_NEXT_TRACK"))
		return 0xB0;

	if (0 == wcscmp(tmp, L"VK_MEDIA_PREV_TRACK"))
		return 0xB1;

	if (0 == wcscmp(tmp, L"VK_MEDIA_STOP"))
		return 0xB2;

	if (0 == wcscmp(tmp, L"VK_MEDIA_PLAY_PAUSE"))
		return 0xB3;

	if (0 == wcscmp(tmp, L"VK_LAUNCH_MAIL"))
		return 0xB4;

	if (0 == wcscmp(tmp, L"VK_LAUNCH_MEDIA_SELECT"))
		return 0xB5;

	if (0 == wcscmp(tmp, L"VK_LAUNCH_APP1"))
		return 0xB6;

	if (0 == wcscmp(tmp, L"VK_LAUNCH_APP2"))
		return 0xB7;

	if (0 == wcscmp(tmp, L"VK_OEM_1"))
		return 0xBA;

	if (0 == wcscmp(tmp, L"VK_OEM_PLUS"))
		return 0xBB;

	if (0 == wcscmp(tmp, L"VK_OEM_COMMA"))
		return 0xBC;

	if (0 == wcscmp(tmp, L"VK_OEM_MINUS"))
		return 0xBD;

	if (0 == wcscmp(tmp, L"VK_OEM_PERIOD"))
		return 0xBE;

	if (0 == wcscmp(tmp, L"VK_OEM_2"))
		return 0xBF;

	if (0 == wcscmp(tmp, L"VK_OEM_3"))
		return 0xC0;

	if (0 == wcscmp(tmp, L"VK_OEM_4"))
		return 0xDB;

	if (0 == wcscmp(tmp, L"VK_OEM_5"))
		return 0xDC;

	if (0 == wcscmp(tmp, L"VK_OEM_6"))
		return 0xDD;

	if (0 == wcscmp(tmp, L"VK_OEM_7"))
		return 0xDE;

	if (0 == wcscmp(tmp, L"VK_OEM_8"))
		return 0xDF;

	if (0 == wcscmp(tmp, L"VK_OEM_102"))
		return 0xE2;

	if (0 == wcscmp(tmp, L"VK_PROCESSKEY"))
		return 0xE5;

	if (0 == wcscmp(tmp, L"VK_PACKET"))
		return 0xE7;

	if (0 == wcscmp(tmp, L"VK_ATTN"))
		return 0xF6;

	if (0 == wcscmp(tmp, L"VK_CRSEL"))
		return 0xF7;

	if (0 == wcscmp(tmp, L"VK_EXSEL"))
		return 0xF8;

	if (0 == wcscmp(tmp, L"VK_EREOF"))
		return 0xF9;

	if (0 == wcscmp(tmp, L"VK_PLAY"))
		return 0xFA;

	if (0 == wcscmp(tmp, L"VK_ZOOM"))
		return 0xFB;

	if (0 == wcscmp(tmp, L"VK_NONAME"))
		return 0xFC;

	if (0 == wcscmp(tmp, L"VK_PA1"))
		return 0xFD;

	if (0 == wcscmp(tmp, L"VK_OEM_CLEAR"))
		return 0xFE;

	return 0x00;
}

//keyCode should be preallocated!
int StringToVirtualKeyArray(const wchar_t *text, byte *keyCode)
{
	int len = wcslen(text);
	int keyCodeLen = 0;
	wchar_t *tmp = (wchar_t*)calloc(wcslen(text) + 1, sizeof(wchar_t));
	int j = 0, k = 0;

	for (int i = 0; i < len; i++)
	{
		if (text[i] == '{')
		{
			i++;
			j = 0;
			while (text[i] != '}')
			{
				tmp[j++] = text[i++];
			}
			tmp[j++] = '\0';
			keyCode[k++] = BracketToVirtualKeyCode(tmp);
		}
		else
		{
			keyCode[k++] = toupper(text[i]);
		}

	}
	keyCode[k] = '\0';
	free(tmp);
	return k;
}

//Finds all virtual keys that are currently pressed and sends the corresponding keyUp msg. 
int UnpressAllKeys()
{
	INPUT input[256];
	int index = 0;

	//If a non-toggle button is pressed...
	for (int i = 0; i < 256; i++)
		if (GetAsyncKeyState(i))
			ToUpKey(&input[index++], i);

	SendInput(index, input, sizeof(INPUT));
	return 0;
}

//Unpresses modifier keys (Ctrl, Alt, Win, and Shift).
bool UnpressModifierKeys(bool onlyIfPressed = false)
{
	INPUT input[256];
	int index = 0;
	int key = 0;

	key = VK_MENU;
	if ((onlyIfPressed == false) || GetAsyncKeyState(key))
		ToUpKey(&input[index++], key);

	key = VK_CONTROL;
	if ((onlyIfPressed == false) || GetAsyncKeyState(key))
		ToUpKey(&input[index++], key);

	key = VK_LWIN;
	if ((onlyIfPressed == false) || GetAsyncKeyState(key))
		ToUpKey(&input[index++], key);

	key = VK_RWIN;
	if ((onlyIfPressed == false) || GetAsyncKeyState(key))
		ToUpKey(&input[index++], key);

	key = VK_SHIFT;
	if ((onlyIfPressed == false) || GetAsyncKeyState(key))
		ToUpKey(&input[index++], key);

	SendInput(index, input, sizeof(INPUT));
	return true;
}

//Convenience method. This isn't efficient at all! 
int SendShortcut(const wchar_t *str)
{
	UnpressAllKeys();

	byte *keyCode = (byte*)calloc(wcslen(str), sizeof(byte) + 1);
	int length = StringToVirtualKeyArray(str, keyCode);
	INPUT *input = (INPUT*)calloc(length * 2, sizeof(INPUT));

	if (BuildShortcutInput(input, keyCode, length))
		return -1;

	int ret = SendInput(2 * length, input, sizeof(INPUT));

	free(input);
	free(keyCode);
	return ret;
}

//Convenience method to send key up messages
int SendUpKeys(const wchar_t *str)
{
	byte *keyCode = (byte*)calloc(wcslen(str), sizeof(byte) + 1);
	int length = StringToVirtualKeyArray(str, keyCode);
	INPUT *input = (INPUT*)calloc(length, sizeof(INPUT));

	for (int i = 0; i < length; i++)
		ToUpKey(&input[i], keyCode[i]);

	int ret = SendInput(length, input, sizeof(INPUT));

	free(input);
	free(keyCode);
	return ret;
}

//Convenience method to send key up messages
int SendDownKeys(const wchar_t *str)
{
	byte *keyCode = (byte*)calloc(wcslen(str), sizeof(byte) + 1);
	int length = StringToVirtualKeyArray(str, keyCode);
	INPUT *input = (INPUT*)calloc(length, sizeof(INPUT));

	for (int i = 0; i < length; i++)
		ToDownKey(&input[i], keyCode[i]);

	int ret = SendInput(length, input, sizeof(INPUT));

	free(input);
	free(keyCode);
	return ret;
}
