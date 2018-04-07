#include "Window_VideoArea_Screen.h"

ScreenShot1::ScreenShot1(QWidget *parent) :QDialog(parent)//区域截屏特殊窗口
{
	fullScreenPix = QPixmap::grabWindow(QApplication::desktop()->winId());
	fullTempPix = fullScreenPix;
}

void ScreenShot1::showEvent(QShowEvent *event)//显示全屏窗口
{
	showFullScreen();
	setCursor(Qt::CrossCursor);
}

void ScreenShot1::paintEvent(QPaintEvent *event)//显示全屏截图图片
{
	QPainter painter(this);
	painter.drawPixmap(0, 0, fullTempPix);
	QDialog::paintEvent(event);
}

void ScreenShot1::mousePressEvent(QMouseEvent *event)//鼠标按下
{
	if (event->button() == Qt::LeftButton)
	{
		startPoint = event->pos();
	}
}

void ScreenShot1::mouseMoveEvent(QMouseEvent *event)//鼠标移动
{
		fullTempPix = fullScreenPix;
		endPonit = event->pos();
		paint(fullTempPix);
}

void ScreenShot1::mouseReleaseEvent(QMouseEvent *event)//鼠标放开
{
	if (event->button() == Qt::LeftButton)
	{
		endPonit = event->pos();
		NextWindow();
	}
}

void ScreenShot1::paint(QPixmap &pixmap)//截图矩形绘制
{
	QPoint startPoint_temp = startPoint;
	QPoint endPonit_temp = endPonit;
	QPainter painter(&pixmap);
	painter.setPen(Qt::white);
	for (int i = 0; i < 3; i++)
	{
		painter.drawRect(QRect(startPoint_temp, endPonit_temp));
		startPoint_temp.setX(startPoint_temp.x() + 1); endPonit_temp.setX(endPonit_temp.x() - 1);
		startPoint_temp.setY(startPoint_temp.y() + 1); endPonit_temp.setY(endPonit_temp.y() - 1);
	}
	update();
}

void ScreenShot1::NextWindow(void)
{
	this->close();
	NextWin = new Window_QuestionAreaScreen(startPoint, endPonit);
	NextWin->show();
}