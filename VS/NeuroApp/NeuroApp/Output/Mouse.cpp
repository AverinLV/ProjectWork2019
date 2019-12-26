#include "Output/Mouse.hpp"
#include <cmath>
#include <QEventLoop>
#include <QTimer>
#include <qdebug.h>

using namespace Output_module;

Mouse::Mouse() :
	isCursorChanged(false),
	alreadyRunning(false)
{
	QObject::connect(this, SIGNAL(newCoordsSig(QPoint)), this, SLOT(setCurrentCoordsSlt(QPoint)));
}


Mouse::~Mouse()
{
	QObject::disconnect(this, SIGNAL(newCoordsSig(QPoint)), this, SLOT(setCurrentCoordsSlt(QPoint)));
}

void Mouse::getCoordsSlt()
{
	emit newCoordsSig(QCursor::pos());
}

void Mouse::setCoordsSlt(double x, double y)
{
	cursor.setPos(x, y);
}

void Mouse::setCoordsSlt(QPoint point)
{
	cursor.setPos(point);
}

void Mouse::setCoordsSlt(QPoint point, int time)
{
	if (alreadyRunning)
	{
		return;
	}
	setCoordsSlt(point.x(), point.y(), time);
}

void Mouse::setCoordsSlt(double x, double y, int time)
{
	if (alreadyRunning)
	{
		return;
	}
	else
	{
		alreadyRunning = true;
	}
	if (time <= 0)
	{
		setCoordsSlt(x, y);
		return;
	}
	getCoordsSlt();
	double dx = abs(x - currentCoords.x());
	double dy = abs(y - currentCoords.y());
	double curX = currentCoords.x();
	double curY = currentCoords.y();
	short int xMult = 1;
	short int yMult = 1;
	if (curX > x)
	{
		xMult = -1;
	}
	if (curY > y)
	{
		yMult = -1;
	}
	QEventLoop loop;
	double sleepTime = time / 100;
	for (int i = 0; i < 100; i++)
	{
		curX += dx / 100 * xMult;
		curY += dy / 100 * yMult;
		cursor.setPos(curX, curY);
		QTimer::singleShot(sleepTime, &loop, SLOT(quit()));
		loop.exec();
	}
	setCoordsSlt(x, y);
	alreadyRunning = false;
}

void Mouse::shiftCoordsSlt(double x, double y)
{
	getCoordsSlt();
	cursor.setPos(currentCoords.x() + x, currentCoords.y() + y);
}

void Mouse::shiftCoordsSlt(double x, double y, int time)
{
	if (alreadyRunning)
	{
		return;
	}
	getCoordsSlt();
	double xNew = currentCoords.x() + x;
	double yNew = currentCoords.y() + y;
	setCoordsSlt(xNew, yNew, time);
}

void Mouse::pressLeftClickSlt()
{
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	emit leftClickedSig();
}

void Mouse::releaseLeftClickSlt()
{
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	emit leftReleasedSig();
}

void Mouse::pressRightClickSlt()
{
	mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
	emit rightClickedSig();
}

void Mouse::releaseRightClickSlt()
{
	mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
	emit rightReleasedSig();
}

void Mouse::changeCursorSlt()
{
	if (isCursorChanged)
	{
		return;
	}
	isCursorChanged = true;
	hHand = LoadCursorFromFile(TEXT("GUI/Images/Cross.cur"));
	hArrow = LoadNoShareCursor(OCR_NORMAL);
	SetSystemCursor((HCURSOR)hHand, OCR_NORMAL);
}

void Mouse::restoreCursorSlt()
{
	if (!isCursorChanged)
	{
		return;
	}
	isCursorChanged = false;
	SetSystemCursor((HCURSOR)hArrow, OCR_NORMAL);
}

void Mouse::setCurrentCoordsSlt(QPoint coords)
{
	this->currentCoords = coords;
}

HANDLE Mouse::LoadNoShareCursor(UINT ocr_id)
{
	HANDLE tmp = LoadImage(0, MAKEINTRESOURCE(ocr_id), IMAGE_CURSOR, 0, 0, LR_SHARED);
	if (!tmp)
	{
		return 0;
	}
	return CopyImage(tmp, IMAGE_CURSOR, 0, 0, 0);
}
