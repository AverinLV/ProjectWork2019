#include "Logic.hpp"
#include <QDebug>
#include <string>
#include <sstream>
#include <Windows.h>

using namespace Logic_module;

Logic::Logic()
{
}

Logic::~Logic()
{
}

void Logic::newInputDataSlt(unsigned int IDSignal)
{
	switch (IDSignal) 
	{
	case 44:
		IDSignal = 1; // left hand
		break;
	case 3:
		IDSignal = 2; //thumb of right hand
		break;
	case 10:
		IDSignal = 3; // middle finger of right hand
		break;
	case 12:
		IDSignal = 4; // pinkie of right hand
		break;
	default:
		return;
		break;
	}

	qDebug() << "Input data: " << IDSignal;

	Settings_module::Setting setting;
	for (unsigned int i = 0; i < settings.size(); i++)
	{
		if (IDSignal == settings[i].id)
		{
			setting = settings[i];
		}
	}

	if (setting.keys != "None")
	{
		std::string str = setting.keys;
		int rep = 0;
		for (unsigned int i = 0; i < str.size(); i++)
		{
			if (str[i] == '+')
			{
				rep++;
				str[i] = ' ';
			}
		}
		std::vector<std::string> keys;
		std::string key;
		std::stringstream ss;
		ss << str;
		for (int i = 0; i < rep + 1; i++)
		{
			ss >> key;
			keys.push_back(key);
		}
		for (unsigned int i = 0; i < keys.size(); i++) // Pressing keys 
		{
			qInfo() << "KEY " << i << " " << QString::fromUtf8(keys[i].c_str());
			if (keys[i] == "L_CLICK" )
			{
				emit pressLeftClickSig();
				Sleep(5);
			}
			else if (keys[i] == "R_CLICK")
			{
				emit pressRightClickSig();
				Sleep(5);
			}
			else if (keys[i] == "L_DOUBLECLICK")
			{
				emit pressLeftClickSig();
				Sleep(5);
				emit releaseLeftClickSig();
				emit pressLeftClickSig();
				Sleep(5);
				emit releaseLeftClickSig();

			}
			else if (keys[i] == "MOUSE_MOVE")
			{
				if (setting.x > 0 || setting.y > 0)
				{
					if (setting.mouseDelay == 0)
					{
						emit setCoordsSig(setting.x, setting.y);
					}
					else
					{
						emit setCoordsSig(setting.x, setting.y, (int)(setting.mouseDelay * 1000));
					}
				}
				else if (setting.dx != 0 || setting.dy != 0)
				{
					if (setting.mouseDelay == 0)
					{
						emit shiftCoordsSig(setting.dx, setting.dy);
					}
					else
					{
						emit shiftCoordsSig(setting.dx, setting.dy, (int)(setting.mouseDelay * 1000));
					}
				}
			}
			else
			{
				emit pressKeySig(keys[i]);
				Sleep(5);
			}
		}
		for (unsigned int i = 0; i < keys.size(); i++) // Releasing
		{
			if (keys[i] == "L_CLICK")
			{
				emit releaseLeftClickSig();
			}
			else if (keys[i] == "R_CLICK")
			{
				emit releaseRightClickSig();
			}
			else if (keys[i] != "L_DOUBLECLICK")
			{
				emit releaseKeySig(keys[i]);
			}
		}
	}
	/*if (setting.dx != 0 || setting.dy != 0)
	{
		if (setting.x >= 0 && setting.y >= 0)
		{
			emit setCoordsSig(setting.x, setting.y);
		}
		emit setCoordsSig(setting.dx, setting.dy, (int)(setting.mouseDelay * 1000)); // it's long time running!!! create thread! //it's ok boy stfu
	}*/


	/*if (setting.x > 0 || setting.y > 0)
	{
		if (setting.mouseDelay == 0)
		{
			emit setCoordsSig(setting.x, setting.y);
		}
		else
		{
			emit setCoordsSig(setting.x, setting.y, (int)(setting.mouseDelay * 1000));
		}
	}
	else if (setting.dx != 0 || setting.dy != 0)
	{
		qInfo() << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
		if (setting.mouseDelay == 0)
		{
			emit shiftCoordsSig(setting.dx, setting.dy);
		}
		else
		{
			emit shiftCoordsSig(setting.dx, setting.dy, (int)(setting.mouseDelay * 1000));
		}
	}*/


	/*else if (setting.dx > 0 || setting.dy > 0)
	{
		emit setCoordsSig(setting.dx, setting.dy, (int)(setting.mouseDelay * 1000));
	}*/
}

void Logic::updateSettings(std::vector<Settings_module::Setting> settings)
{
	this->settings = settings;
}
