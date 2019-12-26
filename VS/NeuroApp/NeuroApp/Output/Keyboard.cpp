#include "Output/Keyboard.hpp"
#include <QDebug>

using namespace Output_module;

Keyboard::Keyboard()
{}

Keyboard::~Keyboard()
{}

void Keyboard::pressButtonSlt(std::string sKey)
{
	INPUT input;
	WORD vKey = getKeyCode(sKey);
	input.type = INPUT_KEYBOARD;
	input.ki.wScan = 0;
	input.ki.time = 0;
	input.ki.dwExtraInfo = 0;
	input.ki.wVk = vKey;
	input.ki.dwFlags = 0;
	SendInput(1, &input, sizeof(INPUT));

	std::string command = "echo TRY TO PRESS: " + sKey + " >> keyboard.log";
	//system(command.c_str());
	//keybd_event(vKey, 0x45, KEYEVENTF_EXTENDEDKEY | 0, 0);
	if (GetAsyncKeyState(vKey))
	{
		command = "echo SUCCESFULLY PRESSED: " + sKey + " >> keyboard.log";
		//system(command.c_str());
	}
}


void Keyboard::releaseButtonSlt(std::string sKey)
{
	INPUT input;
	WORD vKey = getKeyCode(sKey);

	input.type = INPUT_KEYBOARD;
	input.ki.wScan = 0;
	input.ki.time = 0;
	input.ki.dwExtraInfo = 0;
	input.ki.wVk = vKey;
	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));

	std::string command = "echo TRY TO RELEASE: " + sKey + " >> keyboard.log";
	//system(command.c_str());
	//keybd_event(vKey, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
	if (!GetAsyncKeyState(vKey))
	{
		command = "echo SUCCESFULLY RELEASED: " + sKey + " >> keyboard.log";
		//system(command.c_str());
	}
	command = "echo ================================== >> keyboard.log";
	//system(command.c_str());
}

byte Keyboard::getKeyCode(std::string sKey)
{
	if (sKey.size() == 1 && isalpha(sKey[0]))
	{
		return byte(sKey[0]);
	}
	if (sKey == u8"É")
	{
		return getKeyCode("Q");
	}
	if (sKey == u8"Ö")
	{
		return getKeyCode("W");
	}
	if (sKey == u8"Ó")
	{
		return getKeyCode("E");
	}
	if (sKey == u8"Ê")
	{
		return getKeyCode("R");
	}
	if (sKey == u8"Å")
	{
		return getKeyCode("T");
	}
	if (sKey == u8"Í")
	{
		return getKeyCode("Y");
	}
	if (sKey == u8"Ã")
	{
		return getKeyCode("U");
	}
	if (sKey == u8"Ø")
	{
		return getKeyCode("I");
	}
	if (sKey == u8"Ù")
	{
		return getKeyCode("O");
	}
	if (sKey == u8"Ç")
	{
		return getKeyCode("P");
	}
	if (sKey == u8"Õ")
	{
		return getKeyCode("[");
	}
	if (sKey == u8"Ú")
	{
		return getKeyCode("]");
	}
	if (sKey == u8"Ô")
	{
		return getKeyCode("A");
	}
	if (sKey == u8"Û")
	{
		return getKeyCode("S");
	}
	if (sKey == u8"Â")
	{
		return getKeyCode("D");
	}
	if (sKey == u8"À")
	{
		return getKeyCode("F");
	}
	if (sKey == u8"Ï")
	{
		return getKeyCode("G");
	}
	if (sKey == u8"Ð")
	{
		return getKeyCode("H");
	}
	if (sKey == u8"Î")
	{
		return getKeyCode("J");
	}
	if (sKey == u8"Ë")
	{
		return getKeyCode("K");
	}
	if (sKey == u8"Ä")
	{
		return getKeyCode("L");
	}
	if (sKey == u8"Æ")
	{
		return getKeyCode(";");
	}
	if (sKey == u8"Ý")
	{
		return getKeyCode("''");
	}
	if (sKey == u8"ß")
	{
		return getKeyCode("Z");
	}
	if (sKey == u8"×")
	{
		return getKeyCode("X");
	}
	if (sKey == u8"Ñ")
	{
		return getKeyCode("C");
	}
	if (sKey == u8"Ì")
	{
		return getKeyCode("V");
	}
	if (sKey == u8"È")
	{
		return getKeyCode("B");
	}
	if (sKey == u8"Ò")
	{
		return getKeyCode("N");
	}
	if (sKey == u8"Ü")
	{
		return getKeyCode("M");
	}
	if (sKey == u8"Á")
	{
		return getKeyCode(",");
	}
	if (sKey == u8"Þ")
	{
		return getKeyCode(".");
	}
	if (sKey == "BACKSLASH")
	{
		return 220;
	}
	if (sKey == ";")
	{
		return 186;
	}
	if (sKey == "''") 
	{
		return 222;
	}
	if (sKey == "L_CTRL")
	{
		return VK_LCONTROL;
	}
	if (sKey == "ALT")
	{
		return VK_MENU;
	}
	if (sKey == "L_WIN")
	{
		return VK_LWIN;
	}
	if (sKey == "SPACE")
	{
		return VK_SPACE;
	}
	if (sKey == "R_CTRL")
	{
		return VK_RCONTROL;
	}
	if (sKey == "L_SHIFT")
	{
		return VK_LSHIFT;
	}
	if (sKey == "CAPS_LOCK")
	{
		return VK_CAPITAL;
	}
	if (sKey == "TAB")
	{
		return VK_TAB;
	}
	if (sKey == "LEFT")
	{
		return VK_LEFT;
	}
	if (sKey == "RIGHT")
	{
		return VK_RIGHT;
	}
	if (sKey == "UP")
	{
		return VK_UP;
	}
	if (sKey == "DOWN")
	{
		return VK_DOWN;
	}
	if (sKey == "R_SHIFT")
	{
		return VK_RSHIFT;
	}
	if (sKey == "ENTER")
	{
		return VK_RETURN;
	}
	if (sKey == "NUMLOCK")
	{
		return VK_NUMLOCK;
	}
	if (sKey == "BACKSPACE")
	{
		return VK_BACK;
	}
	if (sKey == "SCROLL_LOCK")
	{
		return VK_SCROLL;
	}
	if (sKey == "PAUSE")
	{
		return VK_PAUSE;
	}
	if (sKey == "DELETE")
	{
		return VK_DELETE;
	}
	if (sKey == "PGUP")
	{
		return VK_PRIOR;
	}
	if (sKey == "PGDN")
	{
		return VK_NEXT;
	}
	if (sKey == "F1")
	{
		return VK_F1;
	}
	if (sKey == "F2")
	{
		return VK_F2;
	}
	if (sKey == "F3")
	{
		return VK_F3;
	}
	if (sKey == "F4")
	{
		return VK_F4;
	}
	if (sKey == "F5")
	{
		return VK_F5;
	}
	if (sKey == "F6")
	{
		return VK_F6;
	}
	if (sKey == "F7")
	{
		return VK_F7;
	}
	if (sKey == "F8")
	{
		return VK_F8;
	}
	if (sKey == "F9")
	{
		return VK_F9;
	}
	if (sKey == "F10")
	{
		return VK_F10;
	}
	if (sKey == "F11")
	{
		return VK_F11;
	}
	if (sKey == "F12")
	{
		return VK_F12;
	}
	if (sKey == "NUM0")
	{
		return VK_NUMPAD0;
	}
	if (sKey == "NUM1")
	{
		return VK_NUMPAD1;
	}
	if (sKey == "NUM2")
	{
		return VK_NUMPAD2;
	}
	if (sKey == "NUM3")
	{
		return VK_NUMPAD3;
	}
	if (sKey == "NUM4")
	{
		return VK_NUMPAD4;
	}
	if (sKey == "NUM5")
	{
		return VK_NUMPAD5;
	}
	if (sKey == "NUM6")
	{
		return VK_NUMPAD6;
	}
	if (sKey == "NUM7")
	{
		return VK_NUMPAD7;
	}
	if (sKey == "NUM8")
	{
		return VK_NUMPAD8;
	}
	if (sKey == "NUM9")
	{
		return VK_NUMPAD9;
	}
	if (sKey == "DECIMAL")
	{
		return VK_DECIMAL;
	}
	if (sKey == "ADD")
	{
		return VK_ADD;
	}
	if (sKey == "SUBTRACT")
	{
		return VK_SUBTRACT;
	}
	if (sKey == "DIVIDE")
	{
		return VK_DIVIDE;
	}
	if (sKey == "MULTIPLY")
	{
		return VK_MULTIPLY;
	}
	if (sKey == "ESC")
	{
		return VK_ESCAPE;
	}
	if (sKey == "~")
	{
		return 192;
	}
	if (sKey == "=")
	{
		return 187;
	}
	if (sKey == "-")
	{
		return 189;
	}
	if (sKey == "0")
	{
		return 48;
	}
	if (sKey == "1")
	{
		return 49;
	}
	if (sKey == "2")
	{
		return 50;
	}
	if (sKey == "3")
	{
		return 51;
	}
	if (sKey == "4")
	{
		return 52;
	}
	if (sKey == "5")
	{
		return 53;
	}
	if (sKey == "6")
	{
		return 54;
	}
	if (sKey == "7")
	{
		return 55;
	}
	if (sKey == "8")
	{
		return 56;
	}
	if (sKey == "9")
	{
		return 57;
	}
	if (sKey == ",")
	{
		return 188;
	}
	if (sKey == ".")
	{
		return 190;
	}
	if (sKey == "/")
	{
		return 191;
	}
	if (sKey == ";")
	{
		return 196;
	}
	if (sKey == "'")
	{
		return 222;
	}
	if (sKey == "[")
	{
		return 219;
	}
	if (sKey == "]")
	{
		return 221;
	}
	if (sKey == "|")
	{
		return 220;
	}
	return 0;
}
