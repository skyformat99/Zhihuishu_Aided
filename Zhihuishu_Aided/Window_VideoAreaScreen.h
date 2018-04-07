#ifndef WINDOW_VIDEOAREASCREEN_H
#define WINDOW_VIDEOAREASCREEN_H

#include "ui_Window_VideoAreaScreen.h"
#//include <QtGui>
#include "Window_VideoArea_Screen.h"
//#include <Windows.h>

class Window_VideoAreaScreen : public QWidget
{
	Q_OBJECT

public:
	Window_VideoAreaScreen(QWidget *parent = 0);
	~Window_VideoAreaScreen();

private:
	Ui::Window_VideoAreaScreen ui;
	QImage Img;
	ScreenShot1* ShotWin;

	private slots:
	void begin(void);

protected:
	void paintEvent(QPaintEvent *event);

};

#endif // WINDOW_VIDEOAREASCREEN_H