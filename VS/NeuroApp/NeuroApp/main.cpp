#include <QDebug>

#include "Input/Input.hpp"
#include "Output/Mouse.hpp"
#include "Output/Keyboard.hpp"
#include "GUI/GUI.hpp"
#include "Settings/XMLParser.hpp"
#include "Settings/Setting.hpp"
#include "Connector/Connector.hpp"
#include "Logic/Logic.hpp"
#include "Audio/Audio.hpp"

#include "API/GameAPIdll.h"

#include <vector>
#include <map>

struct Statistics
{
	unsigned int n_got = 0;
	unsigned int n_tries = 0;
	unsigned int n_right = 0;
};


int main(int argc, char *argv[])
{
	GUI_module::GUI* gui = new GUI_module::GUI(argc, argv);
	Output_module::Mouse* mouse	= new Output_module::Mouse();
	Output_module::Keyboard* keyboard = new Output_module::Keyboard();
	Input_module::NetworkClient* networkClient = new Input_module::NetworkClient("Client connection");
	Settings_module::XMLParser* xmlParser = new Settings_module::XMLParser("Settings.xml");
	Logic_module::Logic* logic = new Logic_module::Logic();
	Audio_module::Audio* audio = new Audio_module::Audio("Audio/knock_sound.wav");
	Connect_module::Connector* connector = new Connect_module::Connector(gui, mouse, keyboard, networkClient, xmlParser, logic, audio);
	xmlParser->loadXMLSlt();
	QString lang = QApplication::inputMethod()->locale().name();
	qInfo() << lang;
	
	int returnInt = gui->WaitingStopGUI();
	delete (connector);
	delete (gui);
	delete (mouse);
	delete (keyboard);
	delete (networkClient);
	delete (xmlParser);
	return returnInt;
}
