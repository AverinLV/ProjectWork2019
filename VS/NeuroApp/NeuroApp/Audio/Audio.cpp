#include "Audio.hpp"

using namespace Audio_module;

Audio::Audio()
{

}

Audio::Audio(std::string name)
{
	setMusicSlt(name);
}

Audio::~Audio()
{

}

void Audio::setMusicSlt(std::string name)
{
	player.setMedia(QUrl::fromLocalFile(QString::fromStdString(name)));
	player.setVolume(100);
}

void Audio::playSlt()
{
	player.play();
}
