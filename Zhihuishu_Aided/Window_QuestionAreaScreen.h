#ifndef WINDOW_QUESTIONAREASCREEN_H
#define WINDOW_QUESTIONAREASCREEN_H

#include "ui_Window_QuestionAreaScreen.h"
#//include <QtGui>
#include "Window_QuestionArea_Screen.h"
//#include <Windows.h>

class Window_QuestionAreaScreen : public QWidget
{
	Q_OBJECT

public:
	Window_QuestionAreaScreen(QPoint Start1_isd, QPoint End1_isd, QWidget *parent = 0);
	~Window_QuestionAreaScreen();

private:
	Ui::Window_QuestionAreaScreen ui;
	QImage Img;
	ScreenShot2* ShotWin;
	QPoint Start1;
	QPoint End1;

	private slots:
	void begin(void);

protected:
	void paintEvent(QPaintEvent *event);

};

#endif // WINDOW_QUESTIONAREASCREEN_H