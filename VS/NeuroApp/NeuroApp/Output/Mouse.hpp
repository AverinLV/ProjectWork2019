#pragma once
#define OEMRESOURCE
#include <Windows.h>
#include <QCursor>
#include <QObject>

namespace Output_module
{
	class Mouse : public QObject
	{
		Q_OBJECT;
	public:
		Mouse();
		~Mouse();

	public slots:
		void getCoordsSlt(); //Return QPoint structure with current coords of cursor. This coords depends on resolution of screen
		void setCoordsSlt(double x, double y); //Move cursor to x y coordinate
		void setCoordsSlt(QPoint point); //Move cursor to QPoint coordinate
		void setCoordsSlt(QPoint point, int time); //Move cursor to QPoint coordinate in time (ms)
		void setCoordsSlt(double x, double y, int time); //Move cursor to x y coordinate in time (ms)
		void shiftCoordsSlt(double x, double y); //Shift cursor by x y
		void shiftCoordsSlt(double x, double y, int time); // Shift cursor by x y in time (ms)
		void pressLeftClickSlt(); //Press left button of the mouse
		void releaseLeftClickSlt(); //Release left button of the mouse
		void pressRightClickSlt(); //Press right button of the mouse
		void releaseRightClickSlt(); //Release right button of the mouse
		void changeCursorSlt(); //Change system cursor
		void restoreCursorSlt(); //Restore system cursor

	private slots:
		void setCurrentCoordsSlt(QPoint);

	signals:
		void newCoordsSig(QPoint currentCoords);
		void leftClickedSig();
		void leftReleasedSig();
		void rightClickedSig();
		void rightReleasedSig();

	private:
		bool alreadyRunning;
		QPoint currentCoords;
		QCursor cursor;
		HANDLE LoadNoShareCursor(UINT ocr_id);
		HANDLE hHand;
		HANDLE hArrow;
		bool isCursorChanged;
	};
}
