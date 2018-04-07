#ifndef WINDOW_VIDEOAREA_SCREEN_H
#define WINDOW_VIDEOAREA_SCREEN_H

//#include <QtWidgets>
#include "Window_QuestionAreaScreen.h"

class ScreenShot1 : public QDialog
{
	Q_OBJECT
public:
	explicit ScreenShot1(QWidget *parent = 0);

protected:
	void showEvent(QShowEvent *event);
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void paint(QPixmap &pixmap);

private:
	QPixmap fullScreenPix;
	QPixmap fullTempPix;
	QPoint startPoint;
	QPoint endPonit;
	Window_QuestionAreaScreen* NextWin;

signals:

	public slots :
		void NextWindow(void);

};

#endif // WINDOW_VIDEOAREA_SCREEN_H