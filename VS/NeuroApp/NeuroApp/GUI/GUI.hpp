#pragma once
#include <QtWidgets>
#include <QDialog>
#include <qobject.h>
#include <vector>

#include "ui_MainWindow.h"
#include "ui_EditWindow.h"
#include "ui_TCP_IPWindow.h"
#include "ui_AboutWindow.h"
#include "Settings/Setting.hpp"

namespace GUI_module 
{
	class EditWindow : public QDialog
	{
		Q_OBJECT

	public:
		EditWindow(QDialog *parent = Q_NULLPTR);
		~EditWindow();
		void mousePressEvent(QMouseEvent *event);
		QList<QPushButton *> allPButtons;
	signals:
		void getUpdatedSettingsSig();
		void editSettingSig(Settings_module::Setting);
		void changeCursorSig();
		void restoreCursorSig();
	private slots:
		void openWindow(int, Settings_module::Setting);
		void on_ok_clicked();
		void pushButtonKeys();
		void on_reset_clicked();
		void on_setCords_clicked();
		void updatedSettingsSlt(std::vector<Settings_module::Setting>);
		void keyPressEvent(QKeyEvent *event);
		void noSelected();
		void relativeSelected();
		void absoluteSelected();
		void on_addMouseMove_clicked();
		void on_L_CLICK_clicked();
		void on_R_CLICK_clicked();
		void on_langButton_clicked();
	private:
		Ui::EditWindow ui;
		int ID = 0;
	};

	class TCP_IPWindow : public QDialog
	{
		Q_OBJECT

	public:
		TCP_IPWindow(QDialog *parent = Q_NULLPTR);
	signals:
		void updateIP_PortSig(char* ip, int port);
	private slots:
		void on_okButton_clicked();
	private:
		Ui::TCP_IPWindow ui;
	};

	class AboutWindow : public QDialog
	{
		Q_OBJECT

	public:
		AboutWindow(QDialog *parent = Q_NULLPTR);

	private:
		Ui::AboutWindow ui;
	};
	
	class MainWindow : public QMainWindow
	{
		Q_OBJECT

	public:
		MainWindow(QWidget *parent = Q_NULLPTR);
		EditWindow* changeWindow;
		Ui::MainWindowClass ui;
	signals:
		void openEditWindow(int, Settings_module::Setting);
		void start_stopProgram(bool started);
	private slots:
		void on_changeButton_clicked();   
		/*void on_changeButton_2_clicked();   
		void on_changeButton_3_clicked(); 
		void on_changeButton_4_clicked(); */
		void on_startButton_clicked();
		void on_stopButton_clicked();
		void on_movementBox_activated(int index);
	};

	class GUI : public QObject
	{
		Q_OBJECT
	public:
		GUI(int& argc, char** argv);
		int WaitingStopGUI();
		~GUI();
		MainWindow* window;
		EditWindow* eWindow;
		TCP_IPWindow* tcp_ipWindow;
		AboutWindow* aWindow;
	signals:
		void getUpdatedSettingsSig();
		void updatedSettingsSig(std::vector<Settings_module::Setting>);
		void editSettingSig(Settings_module::Setting);
		void updateIP_PortSig(char*, int);
		void start_stopProgramSig(bool);
		void changeCursorSig();
		void restoreCursorSig();
	private:
		QApplication app;
	private slots:
		void getUpdatedSettingsSlt();
		void updatedSettingsSlt(std::vector<Settings_module::Setting>);
		void editSettingSlt(Settings_module::Setting);
		void on_changeIP_Port_triggered(QAction* action);
		void on_aboutProgram_triggered(QAction* action);
		void updateIP_PortSlt(char*,int);
		void start_stopProgramSlt(bool);
		void changeCursorSlt();
		void restoreCursorSlt();
	};
}
