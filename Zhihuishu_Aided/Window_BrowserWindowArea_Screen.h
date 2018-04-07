#ifndef WINDOW_BROWSERWINDOWAREA_SCREEN_H
#define WINDOW_BROWSERWINDOWAREA_SCREEN_H

//#include <QtWidgets>
#include "Window_Main.h"

class ScreenShot3 : public QDialog
{
	Q_OBJECT
public:
	explicit ScreenShot3(QPoint Start1_isd, QPoint End1_isd, QPoint Start2_isd, QPoint End2_isd, QWidget *parent = 0);

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
	Window_Main* NextWin;
	QPoint Start1;
	QPoint End1;
	QPoint Start2;
	QPoint End2;


signals:

	public slots :
		void NextWindow(void);

};

#endif // WINDOW_BROWSERWINDOWAREA_SCREEN_H