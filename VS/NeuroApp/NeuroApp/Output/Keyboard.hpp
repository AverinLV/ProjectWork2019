#pragma once
#include <Windows.h>
#include <string>
#include <ctype.h>
#include <QObject>

namespace Output_module
{
	class Keyboard : public QObject
	{
		Q_OBJECT
	public:
		Keyboard();
		~Keyboard();

	public slots:
		void pressButtonSlt(std::string sKey); //Input is upper english letter like "A" or button name like "CTRL"
		void releaseButtonSlt(std::string sKey); //Same 

	private:
		byte getKeyCode(std::string sKey);
	};
}
