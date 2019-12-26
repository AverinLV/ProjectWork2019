#pragma once

#include "Setting.hpp"
#include "LibXML.h"
#include <vector>
#include <fstream>
#include <QObject>
#include <QDebug>
/*
USAGE:
Run constructor with name of file in argument
If file does not exist it will be created
Run loadXML function
To add new setting in XML run addSetting(Setting &s)
To get vector of settings run getSettings()
To change setting run changeSetting(Setting s)
Each settings in XML file should have unique ID
*/


namespace Settings_module
{
	class XMLParser : public QObject
	{
		Q_OBJECT
	public:
		XMLParser(const char *aName);
		~XMLParser();

	public slots:

		void createXMLFileSlt(const char *aName); // Creates new XML File
		void getSettingsSlt(); // Get vector of settings
		void addSettingSlt(Settings_module::Setting &s); // Add new setting
		void deleteSettingSlt(unsigned long aId); // Delete setting by ID
		void changeSettingSlt(Settings_module::Setting s); // Change setting, ID should be initialized
		void clearXMLFileSlt(); // Reset XML file
		void loadXMLSlt(); // Load XML file

	signals:
		void updatedSettingsSig(std::vector<Settings_module::Setting> v);

	private:
		bool saveXMLFile();
		const char* name;
		std::vector<Setting> settings;
	};
}
