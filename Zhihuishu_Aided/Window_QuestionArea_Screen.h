#ifndef WINDOW_QUESTIONAREA_SCREEN_H
#define WINDOW_QUESTIONAREA_SCREEN_H

#include <QtWidgets>
#include "Window_BrowserWindowAreaScreen.h"

class ScreenShot2 : public QDialog
{
	Q_OBJECT
public:
	explicit ScreenShot2(QPoint Start1_isd, QPoint End1_isd, QWidget *parent = 0);

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
	Window_BrowserWindowAreaScreen* NextWin;
	QPoint Start1;
	QPoint End1;


signals:

	public slots :
		void NextWindow(void);

};

#endif // WINDOW_QUESTIONAREA_SCREEN_H