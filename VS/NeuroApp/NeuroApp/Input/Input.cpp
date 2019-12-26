#pragma once
#pragma comment (lib,"Ws2_32.lib")

#include "Input.hpp"
#include "API/GameAPIdll.h"
#include <iostream>
using namespace Input_module;

NetworkClient::NetworkClient(QString threadName) :
	name(threadName) 
{}

NetworkClient::~NetworkClient()
{
	Disconnect();
	terminate();
}

void NetworkClient::stopClient()
{
	isSendRequest = false;
	for (auto &stat : stats)
	{
		Stat(stat.first, stat.second.n_got, stat.second.n_tries, stat.second.n_right);
	}
	Stop();
}

void NetworkClient::request()
{
	stats[0].n_tries++;
	unsigned int answer = Request(0);
	
	stats[answer].n_right++;
	stats[answer].n_got++;
	emit InputDataSig(answer);
	qDebug() << answer << "  \n";
}

void NetworkClient::updateIP_PortSlt(char* ipAddress, int port)
{
	this->ipAddress = ipAddress;
	this->port = port;
};

void NetworkClient::start_stopProgramSlt(bool isStart)
{
	if (isStart)
	{
		qDebug() << ">>Client started";
		startClient();
	}
	else
	{
		stopClient();
		qDebug() << ">>Client stopped";
	}
};

void NetworkClient::startClient()
{
	Connect(ipAddress, port);
	qDebug() << "Connected";
	if (!(Start()))
	{
		qDebug() << "Error!";
	}
	else
	{
		isSendRequest = true;
		start();
	}
}

void NetworkClient::run()
{
	while (isSendRequest)
	{
		emit AudioSig();
		request();
	}
}
