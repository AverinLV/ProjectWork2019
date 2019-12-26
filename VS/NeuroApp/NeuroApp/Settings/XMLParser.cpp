#include "XMLParser.hpp"

using namespace tinyxml2;
using namespace Settings_module;

XMLParser::XMLParser(const char *aName):
name{aName},
settings{}
{
	std::fstream fs;
	fs.open(aName);
	if (fs.fail()) 
	{
		createXMLFileSlt(aName);
	}
}

XMLParser::~XMLParser()
{}

void XMLParser::createXMLFileSlt(const char *aName)
{
	XMLDocument file;
	if (file.SaveFile(aName))
	{
		qCritical() << "Unable to create XML file. Further work of the program may be incorrect. Abort recommended";
	}
}

void XMLParser::loadXMLSlt()
{
	XMLDocument file;
	file.LoadFile(name);
	XMLElement* root = file.RootElement();
	XMLElement* setting;
	if (root != nullptr)
	{
		setting = root->FirstChildElement();
	}
	else
	{
		Settings_module::Setting s;
		s.dx = 0;
		s.dy = 0;
		s.keys = "None";
		s.mouseDelay = 0;
		s.movement = "Undefined movement";
		s.x = 0;
		s.y = 0;
		for (int i = 0; i < 4; i++)
		{
			addSettingSlt(s);
		}
		return;
	}

	settings = {};

	while (setting != nullptr)
	{
		Setting s;
		s.id = std::stoi(setting->Attribute("id"));
		s.movement = setting->FirstChildElement("movement")->GetText();
		s.x = std::stod(setting->FirstChildElement("x")->GetText());
		s.y = std::stod(setting->FirstChildElement("y")->GetText());
		s.keys = setting->FirstChildElement("keys")->GetText();
		s.dx = std::stod(setting->FirstChildElement("dx")->GetText());
		s.dy = std::stod(setting->FirstChildElement("dy")->GetText());
		s.mouseDelay = std::stod(setting->FirstChildElement("mouseDelay")->GetText());
		settings.push_back(s);
		setting = setting->NextSiblingElement();
	}
	getSettingsSlt();
}

bool XMLParser::saveXMLFile()
{
	XMLDocument file;
	XMLElement *root = file.NewElement("root");

	for (const Setting &s: settings) 
	{
		XMLElement *setting = file.NewElement("setting");
		setting->SetAttribute("id", static_cast<int>(s.id));

		XMLElement *movement = file.NewElement("movement");
		setting->LinkEndChild(movement);
		movement->LinkEndChild(file.NewText(s.movement.c_str()));

		XMLElement *x = file.NewElement("x");
		setting->LinkEndChild(x);
		x->LinkEndChild(file.NewText(std::to_string(s.x).c_str()));

		XMLElement *y = file.NewElement("y");
		setting->LinkEndChild(y);
		y->LinkEndChild(file.NewText(std::to_string(s.y).c_str()));

		XMLElement *keys = file.NewElement("keys");
		setting->LinkEndChild(keys);
		keys->LinkEndChild(file.NewText(s.keys.c_str()));

		XMLElement *dx = file.NewElement("dx");
		setting->LinkEndChild(dx);
		dx->LinkEndChild(file.NewText(std::to_string(s.dx).c_str()));

		XMLElement *dy = file.NewElement("dy");
		setting->LinkEndChild(dy);
		dy->LinkEndChild(file.NewText(std::to_string(s.dy).c_str()));

		XMLElement *mouseDelay = file.NewElement("mouseDelay");
		setting->LinkEndChild(mouseDelay);
		mouseDelay->LinkEndChild(file.NewText(std::to_string(s.mouseDelay).c_str()));
		root->LinkEndChild(setting);
  }
	file.LinkEndChild(root);
	return file.SaveFile(name) == 0;
}

void XMLParser::getSettingsSlt()
{
	emit updatedSettingsSig(settings);
}

void XMLParser::addSettingSlt(Setting &s)
{
	if (settings.size() != 0)
	{
		int i = 1;
		bool flag = true;
		while (true)
		{
			for (unsigned int k = 0; k < settings.size(); k++)
			{
				if (i == settings[k].id)
				{
					flag = false;
					continue;
				}
			}
			if (flag)
			{
				s.id = i;
				break;
			}
			i++;
			flag = true;
		}
	}
	else
	{
		s.id = settings.size() + 1;
	}
	settings.push_back(s);
	saveXMLFile();
	getSettingsSlt();
}

void XMLParser::deleteSettingSlt(unsigned long aId)
{
	for (auto it = settings.begin(); it != settings.end(); ++it)
	{
		if ((*it).id == aId)
		{
			it = settings.erase(it);
			if (!saveXMLFile())
			{
				qCritical() << "Unable to save XML file. Further work of the program may be incorrect. Abort recommended";
			}
		}
	}
	if (settings.size() == 0)
	{
		clearXMLFileSlt();
	}
	getSettingsSlt();
}

void XMLParser::changeSettingSlt(Setting s)
{
	for (unsigned int i = 0; i < settings.size(); i++)
	{
		if (settings[i].id == s.id)
		{
			settings[i] = s;

			saveXMLFile();
		}
	}
	getSettingsSlt();
}

void XMLParser::clearXMLFileSlt()
{
	XMLDocument file;
	settings.clear();
	getSettingsSlt();
	if (!file.SaveFile(name))
	{
		qCritical() << "Unable to clear XML file. Further work of the program may be incorrect. Abort recommended"; 
	}
}

