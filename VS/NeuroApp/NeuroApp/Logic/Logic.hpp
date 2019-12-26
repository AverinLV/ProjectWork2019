#pragma once
#include <qobject.h>
#include "../Settings/Setting.hpp"
#include <vector>

namespace Logic_module
{
	class Logic : public QObject
	{
		Q_OBJECT
	public:
		Logic();
		~Logic();

	public slots:
		void newInputDataSlt(unsigned int);
		void updateSettings(std::vector<Settings_module::Setting>);

	signals:
		void pressKeySig(std::string key);
		void releaseKeySig(std::string Key);
		void pressLeftClickSig();
		void releaseLeftClickSig();
		void pressRightClickSig();
		void releaseRightClickSig();
		void setCoordsSig(double, double);
		void setCoordsSig(double, double, int);
		void shiftCoordsSig(double, double);
		void shiftCoordsSig(double, double, int);
	private:
		std::vector<Settings_module::Setting> settings;
	};
}
