#include "Window_QuestionAreaScreen.h"

Window_QuestionAreaScreen::Window_QuestionAreaScreen(QPoint Start1_isd, QPoint End1_isd, QWidget *parent) : QWidget(parent)
{
	Start1 = Start1_isd, End1 = End1_isd;
	ui.setupUi(this);
	setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);//禁止最大化
	setFixedSize(this->width(), this->height());//禁止改变窗口大小
	setWindowIcon(QIcon(":/Zhihuishu_Aided/main_ico.ico"));//标题栏图标
	setWindowTitle(QStringLiteral("智慧树辅助软件"));//标题栏文字
	Img = QImage(":/Zhihuishu_Aided/example2.png");

	connect(ui.pushButton_1, SIGNAL(clicked()), this, SLOT(begin()));//关联
}

Window_QuestionAreaScreen::~Window_QuestionAreaScreen()
{

}

void Window_QuestionAreaScreen::paintEvent(QPaintEvent *event)//主界面左上角控件
{
	QPainter painter(this);
	painter.drawImage(QRect(30, 30, 384, 191), Img);
}

void Window_QuestionAreaScreen::begin(void)
{
	this->close();
	Sleep(1000);
	ShotWin = new ScreenShot2(Start1,End1);
	ShotWin->show();
}