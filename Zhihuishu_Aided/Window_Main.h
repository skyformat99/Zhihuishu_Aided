#ifndef WINDOW_MAIN_H
#define WINDOW_MAIN_H

#include "ui_Window_Main.h"
#include <Windows.h>
#include <QtWidgets>
#include <QtGui>
#include <Qthread>
#include <cstring>
#include <qabstractnativeeventfilter.h>

class Thread_MoveArrow : public QThread//移动光标线程
{
	Q_OBJECT
public:
	HWND GoalWindow_HD;
	QPoint MiddlePoint;
	int flag_Thread_MoveArrow;
	void run();
};

class Thread_Timer : public QThread//计时线程
{
	Q_OBJECT
public:
	int flag_Thread_Timer;
	void run();
signals:
	void Touch(void);
};

class Thread_ScreenAnalyze : public QThread//屏幕检测线程
{
	Q_OBJECT
public:
	int flag_Thread_ScreenAnalyze;
	QPoint Start1;//视频播放界面矩形
	QPoint End1;//
	QPoint Start2;//网页弹题矩形
	QPoint End2;//
	int IfVideoEnd;//是否视频结束
	int IfQuestionShow;//是否弹题
	QPixmap VideoArea_Pix;
	QPixmap QuestionArea_Pix;
	QImage VideoArea_Img;
	QImage QuestionArea_Img;
	QImage VideoEndFlag;
	HWND GoalWindow_HD;

	void run();
};

class Window_Main : public QWidget,QAbstractNativeEventFilter
{
	Q_OBJECT

public:
	Window_Main(QPoint Start1_isd, QPoint End1_isd, QPoint Start2_isd, QPoint End2_isd, QPoint Start3_isd, QPoint End3_isd, QWidget *parent = 0);
	~Window_Main();
	QPoint MiddlePoint;
	bool nativeEventFilter(const QByteArray &eventType, void *message, long *result);

private:
	Ui::Window_Main ui;
	Thread_MoveArrow T1;
	Thread_Timer* T2;
	Thread_ScreenAnalyze T3;
	void MoveArrow(void);
	void ScreenAnalyze(void);
	void ToClick(int mode);
	void TimeBegin(void);
	int HotKeyId;
	TCHAR name_tchar[100];
	char name_str[100];
	HWND handle;
	QPoint Start1;//视频播放界面矩形
	QPoint End1;//
	QPoint Start2;//网页弹题矩形
	QPoint End2;//
	QPoint Start3;//浏览器窗口界面矩形
	QPoint End3;//
	char* GoalWindowName_Str;
	HWND GoalWindow_HD;


	private slots:
	void Start(void);
	void Judge(void);

protected:
	void paintEvent(QPaintEvent *event);
	void keyPressEvent(QKeyEvent *event);

};

#endif // WINDOW_MAIN_H