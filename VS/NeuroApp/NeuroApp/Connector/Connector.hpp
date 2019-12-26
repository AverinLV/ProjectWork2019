#pragma once

#include "../Input/Input.hpp"
#include "../GUI/GUI.hpp"
#include "../Output/Mouse.hpp"
#include "../Output/Keyboard.hpp"
#include "../Settings/XMLParser.hpp"
#include "../Logic/Logic.hpp"
#include "../Audio/Audio.hpp"
#include <qobject.h>

namespace Connect_module
{
	class Connector : public QObject
	{
		Q_OBJECT

	public:
		Connector(GUI_module::GUI*, Output_module::Mouse*, Output_module::Keyboard*, Input_module::NetworkClient*, Settings_module::XMLParser*, Logic_module::Logic*, Audio_module::Audio*);
		~Connector();

		void connectAll();

	private:
		GUI_module::GUI* gui;
		Output_module::Mouse* mouse;
		Output_module::Keyboard* keyboard;
		Input_module::NetworkClient* networkClient;
		Settings_module::XMLParser* xmlParser;
		Logic_module::Logic* logic;
		Audio_module::Audio* audio;
	};
}
