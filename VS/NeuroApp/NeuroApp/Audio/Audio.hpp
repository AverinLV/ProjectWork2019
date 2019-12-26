#pragma once
#include <QObject>
#include <string>
#include <QMediaPlayer>

namespace Audio_module
{
	class Audio : public QObject
	{
		Q_OBJECT
	public:
		Audio();
		Audio(std::string name);
		~Audio();
	public slots:
		void setMusicSlt(std::string name);//slot
		void playSlt();//slot
	private:
		QMediaPlayer player;
	};
}
