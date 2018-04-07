#include "Window_Declear.h"

Window_Declear::Window_Declear(QWidget *parent) : QWidget(parent)
{
	ui.setupUi(this);
	setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);//禁止最大化
	setFixedSize(this->width(), this->height());//禁止改变窗口大小
	setWindowIcon(QIcon(":/Zhihuishu_Aided/main_ico.ico"));//标题栏图标
	setWindowTitle(QStringLiteral("智慧树辅助软件"));//标题栏文字
	iconImg = QImage(":/Zhihuishu_Aided/main_ico.png");
	ui.pushButton_1->setDisabled(1);

	connect(ui.checkBox, SIGNAL(clicked()), this, SLOT(EnabledNext()));//关联
	connect(ui.pushButton_1, SIGNAL(clicked()), this, SLOT(NextWindow()));//关联
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(close()));//关联
}

Window_Declear::~Window_Declear()
{

}

void Window_Declear::paintEvent(QPaintEvent *event)//主界面左上角控件
{
	QPainter painter(this);
	painter.drawImage(QRect(10, 30, 100, 100), iconImg);
}

void Window_Declear::EnabledNext(void)
{
	if (ui.checkBox->isChecked())
	{
		ui.pushButton_1->setEnabled(1);
	}
	else
	{
		ui.pushButton_1->setDisabled(1);
	}
}

void Window_Declear::NextWindow(void)
{
	this->close();
	NextWin = new Window_VideoAreaScreen;
	NextWin->show();
}