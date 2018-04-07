#ifndef WINDOW_BROWSERWINDOWAREASCREEN_H
#define WINDOW_BROWSERWINDOWAREASCREEN_H

#include "ui_Window_BrowserWindowAreaScreen.h"
#//include <QtGui>
#include "Window_BrowserWindowArea_Screen.h"
//#include <Windows.h>

class Window_BrowserWindowAreaScreen : public QWidget
{
	Q_OBJECT

public:
	Window_BrowserWindowAreaScreen(QPoint Start1_isd, QPoint End1_isd, QPoint Start2_isd, QPoint End2_isd, QWidget *parent = 0);
	~Window_BrowserWindowAreaScreen();

private:
	Ui::Window_BrowserWindowAreaScreen ui;
	QImage Img;
	ScreenShot3* ShotWin;
	QPoint Start1;
	QPoint End1;
	QPoint Start2;
	QPoint End2;

	private slots:
	void begin(void);

protected:
	void paintEvent(QPaintEvent *event);

};

#endif // WINDOW_BROWSERWINDOWAREASCREEN_H