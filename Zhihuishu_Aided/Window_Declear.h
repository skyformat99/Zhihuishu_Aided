#ifndef WINDOW_DECLEAR_H
#define WINDOW_DECLEAR_H

#include "ui_Window_Declear.h"
//#include <QtWidgets>
//#include <QtGui>
#include "Window_VideoAreaScreen.h"

class Window_Declear : public QWidget
{
	Q_OBJECT

public:
	Window_Declear(QWidget *parent = 0);
	~Window_Declear();

private:
	Ui::Window_Declear ui;
	QImage iconImg;
	Window_VideoAreaScreen* NextWin;

	private slots:
	void EnabledNext(void);
	void NextWindow(void);


protected:
	void paintEvent(QPaintEvent *event);

};

#endif // WINDOW_DECLEAR_H
