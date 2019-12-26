#include <iostream>
#include <cstring>
#include <QKeyEvent>
#include <QDebug>
#include "GUI/GUI.hpp"
#include "ui_MainWindow.h"
#include "ui_EditWindow.h"

#define slash '/'

using namespace GUI_module;

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.stopButton->setEnabled(false);
	ui.addButton->setVisible(false);
	ui.deleteButton->setVisible(false);
	ui.label_0->setVisible(false);
	ui.label_1->setVisible(false);
	ui.label_2->setVisible(false);
	ui.label_3->setVisible(false);
	ui.movementBox->setCurrentIndex(-1);
	ui.keysLine->setReadOnly(true);
}

EditWindow::EditWindow(QDialog *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	//ui.keyboardLabel->setPixmap(QPixmap("Eng_keyboard.png"));
	/*ui.keyboardLabel->setVisible(false);
	ui.keyboardLabel_rus->setVisible(true);*/
	QPoint p;
	ui.addMouseMove->setEnabled(false);
	ui.setCords->setEnabled(false);
	p.setX(ui.keyboardLabel->x());
	p.setY(ui.keyboardLabel->y());
	ui.keyboardLabel_rus->move(p);
	this->setFocus();
	QPalette *palette = new QPalette();
	palette->setColor(QPalette::Base, Qt::gray);
	palette->setColor(QPalette::Text, Qt::black);
	ui.mouseDelayEdit->setPalette(*palette);
	ui.xEdit->setPalette(*palette);
	ui.yEdit->setPalette(*palette);
	ui.xEdit_2->setPalette(*palette);
	ui.yEdit_2->setPalette(*palette);
	/*if (ui.xEdit->text() != "0" || ui.yEdit->text() != "0")
	{
		ui.absolute->setChecked(true);
		ui.setCords->setEnabled(true);
		ui.addMouseMove->setEnabled(true);
		ui.xEdit->setReadOnly(false);
		ui.yEdit->setReadOnly(false);
		QPalette *palette = new QPalette();
		palette->setColor(QPalette::Base, Qt::white);
		palette->setColor(QPalette::Text, Qt::black);
		ui.xEdit->setPalette(*palette);
		ui.yEdit->setPalette(*palette);
	}
	else if (ui.xEdit_2->text() != "0" || ui.yEdit_2->text() != "0")
	{
		ui.relative->setChecked(true);
		ui.setCords->setEnabled(true);
		ui.addMouseMove->setEnabled(true);
		ui.xEdit_2->setReadOnly(false);
		ui.yEdit_2->setReadOnly(false);
		QPalette *palette = new QPalette();
		palette->setColor(QPalette::Base, Qt::white);
		palette->setColor(QPalette::Text, Qt::black);
		ui.xEdit->setPalette(*palette);
		ui.yEdit->setPalette(*palette);
	}
	else
	{
		ui.addMouseMove->setEnabled(false);
		ui.setCords->setEnabled(false);
	}*/
	connect(ui.no, SIGNAL(clicked()), this, SLOT(noSelected()));
	connect(ui.relative, SIGNAL(clicked()), this, SLOT(relativeSelected()));
	connect(ui.absolute, SIGNAL(clicked()), this, SLOT(absoluteSelected()));
	ui.setCords->setVisible(true); 
	ui.checker->setVisible(false);
	allPButtons = findChildren<QPushButton *>();
	for (int i = 0; i < allPButtons.size(); i++)
	{
		if (allPButtons.at(i) != ui.cancel && allPButtons.at(i) != ui.setCords && allPButtons.at(i) != ui.langButton && allPButtons.at(i) != ui.reset && allPButtons.at(i) != ui.ok &&
			allPButtons.at(i) != ui.addMouseMove && allPButtons.at(i) != ui.L_CLICK && allPButtons.at(i) != ui.R_CLICK)
		{
			QObject::connect(allPButtons.at(i), SIGNAL(clicked()), this, SLOT(pushButtonKeys()));
		}
	}
}

void MainWindow::on_movementBox_activated(int index)
{
	switch (index)
	{
	case 0: ui.keysLine->setText(ui.label_0->text()); break;
	case 1: ui.keysLine->setText(ui.label_1->text()); break;
	case 2: ui.keysLine->setText(ui.label_2->text()); break;
	case 3: ui.keysLine->setText(ui.label_3->text()); break;
	default: ui.keysLine->setText("");
	}
}

EditWindow::~EditWindow()
{
	emit restoreCursorSig();
}

void EditWindow::mousePressEvent(QMouseEvent *event)
{
	this->setFocus();
}

void EditWindow::noSelected()
{
	ui.setCords->setEnabled(false);
	ui.mouseDelayEdit->setReadOnly(true);
	ui.xEdit->setText("0");
	ui.yEdit->setText("0");
	ui.xEdit_2->setText("0");
	ui.yEdit_2->setText("0");
	QPalette *palette1 = new QPalette();
	palette1->setColor(QPalette::Base, Qt::gray);
	palette1->setColor(QPalette::Text, Qt::black);
	ui.xEdit->setPalette(*palette1);
	ui.yEdit->setPalette(*palette1);
	ui.mouseDelayEdit->setPalette(*palette1);
	ui.xEdit_2->setPalette(*palette1);
	ui.yEdit_2->setPalette(*palette1);
	ui.xEdit->setReadOnly(true);
	ui.yEdit->setReadOnly(true);
	ui.xEdit_2->setReadOnly(1);
	ui.yEdit_2->setReadOnly(1);
	ui.addMouseMove->setEnabled(false);
	ui.setCords->setEnabled(false);
}

void EditWindow::relativeSelected()
{
	ui.mouseDelayEdit->setReadOnly(false);
	ui.xEdit->setText("0");
	ui.yEdit->setText("0");
	ui.xEdit_2->setText("0");
	ui.yEdit_2->setText("0");
	ui.setCords->setEnabled(true);
	ui.xEdit_2->setReadOnly(false);
	ui.yEdit_2->setReadOnly(false);
	ui.xEdit->setReadOnly(true);
	ui.yEdit->setReadOnly(true);
	QPalette *palette = new QPalette();
	palette->setColor(QPalette::Base, Qt::white);
	palette->setColor(QPalette::Text, Qt::black);
	ui.xEdit_2->setPalette(*palette);
	ui.yEdit_2->setPalette(*palette);
	ui.mouseDelayEdit->setPalette(*palette);
	QPalette *palette1 = new QPalette();
	palette1->setColor(QPalette::Base, Qt::gray);
	palette1->setColor(QPalette::Text, Qt::black);
	ui.xEdit->setPalette(*palette1);
	ui.yEdit->setPalette(*palette1);
	ui.addMouseMove->setEnabled(true);
}

void EditWindow::absoluteSelected()
{
	ui.mouseDelayEdit->setReadOnly(false);
	ui.xEdit->setText("0");
	ui.yEdit->setText("0");
	ui.xEdit_2->setText("0");
	ui.yEdit_2->setText("0");
	ui.setCords->setEnabled(true);
	ui.xEdit->setReadOnly(false);
	ui.yEdit->setReadOnly(false);
	ui.xEdit_2->setReadOnly(true);
	ui.yEdit_2->setReadOnly(true);
	QPalette *palette = new QPalette();
	palette->setColor(QPalette::Base, Qt::white);
	palette->setColor(QPalette::Text, Qt::black);
	ui.xEdit->setPalette(*palette);
	ui.yEdit->setPalette(*palette);
	ui.mouseDelayEdit->setPalette(*palette);
	QPalette *palette1 = new QPalette();
	palette1->setColor(QPalette::Base, Qt::gray);
	palette1->setColor(QPalette::Text, Qt::black);
	ui.xEdit_2->setPalette(*palette1);
	ui.yEdit_2->setPalette(*palette1);
	ui.addMouseMove->setEnabled(true);
}

void EditWindow::keyPressEvent(QKeyEvent *event)
{
	QString ss = ui.checker->text();
	QString t;
	QString s;
	switch ((int)event->key())
	{
		case 16777248: s = "R_SHIFT"; break;
		case 16777249: s = "L_CTRL"; break;
		case 16777216: s = "ESC"; break;
		case 16777264: s = "F1"; break;
		case 16777265: s = "F2"; break;
		case 16777266: s = "F3"; break;
		case 16777267: s = "F4"; break;
		case 16777268: s = "F5"; break;
		case 16777269: s = "F6"; break;
		case 16777270: s = "F7"; break;
		case 16777271: s = "F8"; break;
		case 16777272: s = "F9"; break;
		case 16777273: s = "F10"; break;
		case 16777274: s = "F11"; break;
		case 16777275: s = "F12"; break;
		case 32:       s = "SPACE"; break;
		case 16777217: s = "TAB"; break;
		case 16777252: s = "CAPS_LOCK"; break;
		case 16777251: s = "ALT"; break;
		case 16777234: s = "LEFT"; break;
		case 16777236: s = "RIGHT"; break;
		case 16777235: s = "UP"; break;
		case 16777237: s = "DOWN"; break;
		case 16777224: s = "PAUSE"; break;
		case 16777223: s = "DELETE"; break;
		case 16777254: s = "SCROLL LOCK"; break;
		case 16777238: s = "PGUP"; break;
		case 16777239: s = "PGDN"; break;
		case 16777253: s = "NUMLOCK"; break;
		case 92:       s = slash; break;
		case 16777219: s = "BACKSPACE"; break;
		case 34:       s = '"'; break;
		case 16777220: s = "ENTER"; break; // left
		case 16777221: s = "ENTER"; break; // right
		case 16777250: s = "L_WIN"; break; //it's R_WIN. ━╤デ╦︻(▀̿̿Ĺ̯̿▀)
		case 43:       s = "ADD"; break;
		case 45:       s = "SUBTRACT"; break;
		default:       s = (QString)event->key();
	}
	
	if(event->modifiers() & Qt::KeypadModifier)
	{
		switch ((int)event->key()) 
		{
			case 48: s = "NUM0"; break;
			case 49: s = "NUM1"; break;
			case 50: s = "NUM2"; break;
			case 51: s = "NUM3"; break;
			case 52: s = "NUM4"; break;
			case 53: s = "NUM5"; break;
			case 54: s = "NUM6"; break;
			case 55: s = "NUM7"; break;
			case 56: s = "NUM8"; break;
			case 57: s = "NUM9"; break;
		}
	}
	
	qDebug() << "*** pressed" << s;
	//qDebug() << "*** pressed" << (int)event->key();

	t = ui.keyLabel->text();
 	if (s != ss && s != t)
	{
		if (t == "None" || t == "")
		{
			ui.keyLabel->setText(s);
		}
		else
		{
			t += " + ";
			t += s;
			ui.keyLabel->setText(t);
		}
		ui.checker->setText(s);
	}
	else
	{
		if (t == s)
		{
			t = "";
			ui.keyLabel->setText(t);
			ui.checker->setText("");
		}
		else
		{
			int pos = t.lastIndexOf(QChar('+'));
			t = t.left(pos - 1);
			ui.keyLabel->setText(t);
			pos = t.lastIndexOf(QChar('+'));
			ui.checker->setText(t.right(t.size() - pos - 2));
		}
	}
	if (ui.keyLabel->text() == "")
	{
		ui.keyLabel->setText("None");
	}
}

TCP_IPWindow::TCP_IPWindow(QDialog *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

AboutWindow::AboutWindow(QDialog* parent)
{
	ui.setupUi(this);
}

void EditWindow::pushButtonKeys()
{
	QString ss = ui.checker->text();
	QString t;
	QString s = sender()->objectName();
	if (s.size() == 2 && s[0] == 'n')
	{
		s = s[1];
	}
	if (s == "TILDA")
	{
		s = '~';
	}
	else if (s == "SUBTRACT2")
	{
		s = "SUBTRACT";
	}
	else if (s == "ADD2")
	{
		s = "ADD";
	}
	else if (s == "DELETE2")
	{
		s = "DELETE";
	}
	else if (s == "L_BRACKET")
	{
		s = "[";
	}
	else if (s == "R_BRACKET")
	{
		s = "]";
	}
	else if (s == "SEMICOLON")
	{
		s = ";";
	}
	else if (s == "QUOTATION_MARK")
	{
		s = "''";
	}
	else if (s == "COMMA")
	{
		s = ",";
	}
	else if (s == "POINT")
	{
		s = ".";
	}
	else if (s == "SLASH")
	{
		s = "/";
	}
	if (ui.langButton->text() == "RUS")
	{
		if (s == "Q")
		{
			s = u8"Й";
		}
		else if (s == "W")
		{
			s = u8"Ц";
		}
		else if (s == "E")
		{
			s = u8"У";
		}
		else if (s == "R")
		{
			s = u8"К";
		}
		else if (s == "T")
		{
			s = u8"Е";
		}
		else if (s == "Y")
		{
			s = u8"Н";
		}
		else if (s == "U")
		{
			s = u8"Г";
		}
		else if (s == "I")
		{
			s = u8"Ш";
		}
		else if (s == "O")
		{
			s = u8"Щ";
		}
		else if (s == "P")
		{
			s = u8"З";
		}
		else if (s == "[")
		{
			s = u8"Х";
		}
		else if (s == "]")
		{
			s = u8"Ъ";
		}
		else if (s == "A")
		{
			s = u8"Ф";
		}
		else if (s == "S")
		{
			s = u8"Ы";
		}
		else if (s == "D")
		{
			s = u8"В";
		}
		else if (s == "F")
		{
			s = u8"А";
		}
		else if (s == "G")
		{
			s = u8"П";
		}
		else if (s == "H")
		{
			s = u8"Р";
		}
		else if (s == "J")
		{
			s = u8"О";
		}
		else if (s == "K")
		{
			s = u8"Л";
		}
		else if (s == "L")
		{
			s = u8"Д";
		}
		else if (s == ";")
		{
			s = u8"Ж";
		}
		else if (s == "''")
		{
			s = u8"Э";
		}
		else if (s == "Z")
		{
			s = u8"Я";
		}
		else if (s == "X")
		{
			s = u8"Ч";
		}
		else if (s == "C")
		{
			s = u8"С";
		}
		else if (s == "V")
		{
			s = u8"М";
		}
		else if (s == "B")
		{
			s = u8"И";
		}
		else if (s == "N")
		{
			s = u8"Т";
		}
		else if (s == "M")
		{
			s = u8"Ь";
		}
		else if (s == ",")
		{
			s = u8"Б";
		}
		else if (s == ".")
		{
			s = u8"Ю";
		}
	}
	t = ui.keyLabel->text();
	if (s != ss && s != t)
	{
		if (t == "None" || t == "")
		{
			ui.keyLabel->setText(s);
		}
		else
		{
			t += " + ";
			t += s;
			ui.keyLabel->setText(t);
		}
		ui.checker->setText(s);
	}
	else
	{
		if (t == s)
		{
			t = "";
			ui.keyLabel->setText(t);
			ui.checker->setText("");
		}
		else
		{
			int pos = t.lastIndexOf(QChar('+'));
			t = t.left(pos - 1);
			ui.keyLabel->setText(t);
			pos = t.lastIndexOf(QChar('+'));
			ui.checker->setText(t.right(t.size() - pos - 2));
		}
	}
	if (ui.keyLabel->text() == "")
	{
		ui.keyLabel->setText("None");
	}
}

void EditWindow::on_reset_clicked() // Rename!!!
{
	ui.keyLabel->setText("None");
	ui.xEdit->setText("0");
	ui.yEdit->setText("0");
	ui.xEdit_2->setText("0");
	ui.yEdit_2->setText("0");
	ui.mouseDelayEdit->setText("0");
}

void EditWindow::on_ok_clicked() // And this too
{
	Settings_module::Setting setting;
	setting.id = ID;
	setting.movement = ui.movementEdit->text().toStdString();
	setting.keys = ui.keyLabel->text().toStdString();
	setting.x = ui.xEdit->text().toDouble();
	setting.dx = ui.xEdit_2->text().toDouble();
	setting.y = ui.yEdit->text().toDouble();
	setting.dy = ui.yEdit_2->text().toDouble();
	setting.mouseDelay = ui.mouseDelayEdit->text().toDouble();

	emit editSettingSig(setting);
	close();
}

void EditWindow::on_setCords_clicked() // ...
{
	ui.xEdit->setText("0");
	ui.yEdit->setText("0");
	ui.xEdit_2->setText("0");
	ui.yEdit_2->setText("0");
	qInfo() << QString::number(QCursor::pos().x());
	emit changeCursorSig();
	if (ui.relative->isChecked())
	{
		QCursor::setPos(geometry().center());
	}
	while (true)
	{
		if (GetAsyncKeyState(VK_RBUTTON))
		{
			if (ui.absolute->isChecked())
			{
				ui.xEdit->setText(QString::number(QCursor::pos().x()));
				ui.yEdit->setText(QString::number(QCursor::pos().y()));
			}
			else if (ui.relative->isChecked())
			{
				ui.xEdit_2->setText(QString::number(QCursor::pos().x() - geometry().center().x()));
				ui.yEdit_2->setText(QString::number(QCursor::pos().y() - geometry().center().y()));
			}
			break;
		}
	}
	emit restoreCursorSig();
}

void EditWindow::on_addMouseMove_clicked()
{
	QString t;
	if (ui.keyLabel->text() != "None") 
	{
		t = ui.keyLabel->text();
	}
	else
	{
		t = "";
	}
	if (ui.relative->isChecked())
	{
		if (t != "") t += " + ";
		//QString s = "RelMouseMoveTo(" + ui.xEdit_2->text() + "; " + ui.yEdit_2->text() + ")";
		t.remove("+ MOUSE_MOVE ");
		t.remove("MOUSE_MOVE + ");
		QString s = "MOUSE_MOVE";
		t += s;
	}
	else if (ui.absolute->isChecked())
	{
		if (t != "") t += " + ";
		//QString s = "AbsMouseMoveTo(" + ui.xEdit->text() + "; " + ui.yEdit->text() + ")";
		t.remove("+ MOUSE_MOVE ");
		t.remove("MOUSE_MOVE + ");
		QString s = "MOUSE_MOVE";
		t += s;
	}
	//t.remove("MOUSE_MOVE");
	ui.keyLabel->setText(t);
}

void EditWindow::on_L_CLICK_clicked()
{
	QString t;
	if (ui.keyLabel->text() != "None")
	{
		t = ui.keyLabel->text();
	}
	else
	{
		t = "";
	}
	if (t != "") t += " + ";
	QString s = "L_CLICK";
	t += s;
	ui.keyLabel->setText(t);
}

void EditWindow::on_R_CLICK_clicked()
{
	QString t;
	if (ui.keyLabel->text() != "None")
	{
		t = ui.keyLabel->text();
	}
	else
	{
		t = "";
	}
	if (t != "") t += " + ";
	QString s = "R_CLICK";
	t += s;
	ui.keyLabel->setText(t);
}

void MainWindow::on_changeButton_clicked() // ...
{
	Settings_module::Setting nullSetting;
	nullSetting.isNULL = true;
	switch (ui.movementBox->currentIndex())
	{
		case 0:
		{
			emit openEditWindow(1, nullSetting);
			break;
		}
		case 1:
		{
			emit openEditWindow(2, nullSetting);
			break;
		}
		case 2:
		{
			emit openEditWindow(3, nullSetting);
			break;
		}
		case 3:
		{
			emit openEditWindow(4, nullSetting);
			break;
		}
	}
}
/*void MainWindow::on_changeButton_2_clicked() // ...
{
	Settings_module::Setting nullSetting;
	nullSetting.isNULL = true;
	emit openEditWindow(2, nullSetting);
}

void MainWindow::on_changeButton_3_clicked() // ...
{
	Settings_module::Setting nullSetting;
	nullSetting.isNULL = true;
	emit openEditWindow(3, nullSetting);
}

void MainWindow::on_changeButton_4_clicked() // ...
{
	Settings_module::Setting nullSetting;
	nullSetting.isNULL = true;
	emit openEditWindow(4, nullSetting);
}*/

void MainWindow::on_startButton_clicked() // ...
{
	ui.label->setText(QString::fromUtf8(u8"Запущен"));
	ui.startButton->setEnabled(false);
	ui.stopButton->setEnabled(true);
	emit start_stopProgram(true);
}

void MainWindow::on_stopButton_clicked() // ...
{
	ui.label->setText(QString::fromUtf8(u8"Остановлен"));
	ui.startButton->setEnabled(true);
	ui.stopButton->setEnabled(false);
	emit start_stopProgram(false);
}

void GUI::on_changeIP_Port_triggered(QAction* action) // ...
{
	tcp_ipWindow->show();
}

void GUI::on_aboutProgram_triggered(QAction* action) // ...
{
	aWindow->show();
}

void GUI::start_stopProgramSlt(bool started) // ...
{
	emit start_stopProgramSig(started);
}

void GUI::changeCursorSlt()
{
	emit changeCursorSig();
}

void GUI::restoreCursorSlt()
{
	emit restoreCursorSig();
}

void TCP_IPWindow::on_okButton_clicked() // ...
{
	char* ip = ui.ipLine->text().toUtf8().data();
	int port = ui.portLine->text().toInt();
	emit updateIP_PortSig(ip, port);
}

void GUI::updateIP_PortSlt(char* ip, int port) // ...
{
	emit updateIP_PortSig(ip, port);
}

void EditWindow::openWindow(int ID, Settings_module::Setting setting)
{
	this->ID = ID;
	if (setting.isNULL)
	{
		emit getUpdatedSettingsSig();
		return; // At next stages we should change it. If setting does not exist it should be created
	}

	ui.movementEdit->setText(QString::fromStdString(setting.movement));
	ui.keyLabel->setText(QString::fromStdString(setting.keys));
	ui.xEdit->setText(QString::number(setting.x));
	ui.xEdit_2->setText(QString::number(setting.dx));
	ui.yEdit->setText(QString::number(setting.y));
	ui.yEdit_2->setText(QString::number(setting.dy));
	/*ui.xEdit->setText(QString::number(0));
	ui.xEdit_2->setText(QString::number(0));
	ui.yEdit->setText(QString::number(0));
	ui.yEdit_2->setText(QString::number(0));*/
	ui.mouseDelayEdit->setText(QString::number(setting.mouseDelay));
	ui.no->setChecked(true);
	ui.addMouseMove->setEnabled(false);
	ui.setCords->setEnabled(false);

	setModal(true);
	show();
}

void EditWindow::updatedSettingsSlt(std::vector<Settings_module::Setting> settings)
{
	for (unsigned int i = 0; i < settings.size(); i++)
	{
		if (ID == settings[i].id)
		{
			openWindow(ID, settings[i]);
		}
	}
}

void EditWindow::on_langButton_clicked()
{
	if (ui.langButton->text() == "ENG")
	{
		ui.langButton->setText("RUS");
		ui.keyboardLabel->setVisible(false);
		ui.keyboardLabel_rus->setVisible(true);
	}
	else
	{
		ui.langButton->setText("ENG");
		ui.keyboardLabel->setVisible(true);
		ui.keyboardLabel_rus->setVisible(false);
	}
}


GUI::GUI(int & argc, char ** argv) :
	app(argc, argv)
{
	//create windows and show main window
	window = new MainWindow();
	window->show();
	eWindow = new EditWindow();
	tcp_ipWindow = new TCP_IPWindow();
	aWindow = new AboutWindow();

	connect(window, SIGNAL(openEditWindow(int, Settings_module::Setting)), eWindow, SLOT(openWindow(int, Settings_module::Setting)));
	connect(tcp_ipWindow, SIGNAL(updateIP_PortSig(char*, int)), this, SLOT(updateIP_PortSlt(char*, int)));
	connect(window->ui.server, SIGNAL(triggered(QAction*)), this, SLOT(on_changeIP_Port_triggered(QAction*)));
	connect(window->ui.about, SIGNAL(triggered(QAction*)), this, SLOT(on_aboutProgram_triggered(QAction*)));
	connect(eWindow, SIGNAL(getUpdatedSettingsSig()), this, SLOT(getUpdatedSettingsSlt()));
	connect(this, SIGNAL(updatedSettingsSig(std::vector<Settings_module::Setting>)), eWindow, SLOT(updatedSettingsSlt(std::vector<Settings_module::Setting>)));
	connect(eWindow, SIGNAL(editSettingSig(Settings_module::Setting)), this, SLOT(editSettingSlt(Settings_module::Setting)));
	connect(window, SIGNAL(start_stopProgram(bool)), this, SLOT(start_stopProgramSlt(bool)));
	connect(eWindow, SIGNAL(changeCursorSig()), this, SLOT(changeCursorSlt()));
	connect(eWindow, SIGNAL(restoreCursorSig()), this, SLOT(restoreCursorSlt()));
}

void GUI::getUpdatedSettingsSlt()
{
	emit getUpdatedSettingsSig();
}

void GUI::updatedSettingsSlt(std::vector<Settings_module::Setting> settings)
{
	emit updatedSettingsSig(settings);
	Settings_module::Setting setting1;
	Settings_module::Setting setting2;
	Settings_module::Setting setting3;
	Settings_module::Setting setting4;
	for (unsigned int i = 0; i < settings.size(); i++)
	{
		if (settings[i].id == 1)
		{
			setting1 = settings[i];
		}
		if (settings[i].id == 2)
		{
			setting2 = settings[i];
		}
		if (settings[i].id == 3)
		{
			setting3 = settings[i];
		}
		if (settings[i].id == 4)
		{
			setting4 = settings[i];
		}
	}
	QString keyLineStr1 = QString::fromStdString(setting1.keys);
	QString keyLineStr2 = QString::fromStdString(setting2.keys);
	QString keyLineStr3 = QString::fromStdString(setting3.keys);
	QString keyLineStr4 = QString::fromStdString(setting4.keys);
	/*if (setting1.dx != 0 || setting1.dy != 0)
	{
		keyLineStr1 += " + MOUSE_MOVE";
	}
	if (setting2.dx != 0 || setting2.dy != 0)
	{
		keyLineStr2 += " MOUSE_MOVE";
	}
	if (setting3.dx != 0 || setting3.dy != 0)
	{
		keyLineStr3 += " MOUSE_MOVE";
	}
	if (setting4.dx != 0 || setting4.dy != 0)
	{
		keyLineStr4 += " MOUSE_MOVE";
	}*/
	window->ui.label_0->setText(keyLineStr1);
	window->ui.label_1->setText(keyLineStr2);
	window->ui.label_2->setText(keyLineStr3);
	window->ui.label_3->setText(keyLineStr4);
	/*window->ui.movementLine->setText(QString::fromStdString(setting1.movement));
	window->ui.movementLine_2->setText(QString::fromStdString(setting2.movement));
	window->ui.movementLine_3->setText(QString::fromStdString(setting3.movement));
	window->ui.movementLine_4->setText(QString::fromStdString(setting4.movement));*/
	window->ui.movementBox->setItemText(0, QString::fromStdString(setting1.movement));
	window->ui.movementBox->setItemText(1, QString::fromStdString(setting2.movement));
	window->ui.movementBox->setItemText(2, QString::fromStdString(setting3.movement));
	window->ui.movementBox->setItemText(3, QString::fromStdString(setting4.movement));
	window->ui.movementBox->setCurrentIndex(0);
	window->ui.keysLine->setText(window->ui.label_0->text());
}

void GUI::editSettingSlt(Settings_module::Setting setting)
{
	emit editSettingSig(setting);
}

int GUI::WaitingStopGUI()
{
	return app.exec();
}

GUI::~GUI()
{
	delete window;
	delete eWindow;
	delete tcp_ipWindow;
}
