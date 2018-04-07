#include "Window_BrowserWindowAreaScreen.h"

Window_BrowserWindowAreaScreen::Window_BrowserWindowAreaScreen(QPoint Start1_isd, QPoint End1_isd, QPoint Start2_isd, QPoint End2_isd, QWidget *parent) : QWidget(parent)
{
	Start1 = Start1_isd, End1 = End1_isd, Start2 = Start2_isd, End2 = End2_isd;
	ui.setupUi(this);
	setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);//禁止最大化
	setFixedSize(this->width(), this->height());//禁止改变窗口大小
	setWindowIcon(QIcon(":/Zhihuishu_Aided/main_ico.ico"));//标题栏图标
	setWindowTitle(QStringLiteral("智慧树辅助软件"));//标题栏文字
	Img = QImage(":/Zhihuishu_Aided/example3.png");

	connect(ui.pushButton_1, SIGNAL(clicked()), this, SLOT(begin()));//关联
}

Window_BrowserWindowAreaScreen::~Window_BrowserWindowAreaScreen()
{

}

void Window_BrowserWindowAreaScreen::paintEvent(QPaintEvent *event)//主界面左上角控件
{
	QPainter painter(this);
	painter.drawImage(QRect(30, 30, 384, 191), Img);
}

void Window_BrowserWindowAreaScreen::begin(void)
{
	this->close();
	Sleep(1000);
	ShotWin = new ScreenShot3(Start1, End1, Start2, End2);
	ShotWin->show();
}