#include "Window_VideoAreaScreen.h"

Window_VideoAreaScreen::Window_VideoAreaScreen(QWidget *parent) : QWidget(parent)
{
	ui.setupUi(this);
	setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);//禁止最大化
	setFixedSize(this->width(), this->height());//禁止改变窗口大小
	setWindowIcon(QIcon(":/Zhihuishu_Aided/main_ico.ico"));//标题栏图标
	setWindowTitle(QStringLiteral("智慧树辅助软件"));//标题栏文字
	Img = QImage(":/Zhihuishu_Aided/example.png");

	connect(ui.pushButton_1, SIGNAL(clicked()), this, SLOT(begin()));//关联
}

Window_VideoAreaScreen::~Window_VideoAreaScreen()
{

}

void Window_VideoAreaScreen::paintEvent(QPaintEvent *event)//主界面左上角控件
{
	QPainter painter(this);
	painter.drawImage(QRect(30, 30, 384,191), Img);
}

void Window_VideoAreaScreen::begin(void)
{
	this->close();
	Sleep(1000);
	ShotWin = new ScreenShot1;
	ShotWin->show();
}