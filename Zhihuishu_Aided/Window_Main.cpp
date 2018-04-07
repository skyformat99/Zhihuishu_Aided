#include "Window_Main.h"

Window_Main::Window_Main(QPoint Start1_isd, QPoint End1_isd, QPoint Start2_isd, QPoint End2_isd, QPoint Start3_isd, QPoint End3_isd, QWidget *parent) : QWidget(parent)
{
	T2 = new Thread_Timer();
	ui.setupUi(this);
	setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);//禁止最大化
	setFixedSize(this->width(), this->height());//禁止改变窗口大小
	setWindowIcon(QIcon(":/Zhihuishu_Aided/main_ico.ico"));//标题栏图标
	setWindowTitle(QStringLiteral("智慧树辅助"));//标题栏文字
	Start1 = Start1_isd, End1 = End1_isd, Start2 = Start2_isd, End2 = End2_isd, Start3 = Start3_isd, End3 = End3_isd;//各坐标点更名加入本类的成员
	//计算Start End 1 2各点窗口内相对坐标
	Start1 -= Start3, End1 = Start1 + (End1_isd - Start1_isd);
	Start2 -= Start3, End2 = Start2 + (End2_isd - Start2_isd);
	//==================================

	//准备SendMessage
	GoalWindowName_Str = "课程学习_智慧树 - Google Chrome";
	WCHAR LPCWSTR[256];
	memset(LPCWSTR, 0, sizeof(LPCWSTR));
	MultiByteToWideChar(CP_ACP, 0, GoalWindowName_Str, strlen(GoalWindowName_Str) + 1, LPCWSTR, sizeof(LPCWSTR) / sizeof(LPCWSTR[0]));
	GoalWindow_HD = FindWindow(NULL, LPCWSTR);

	//给移动光标线程计算与传入坐标和
	MiddlePoint.setX((Start1.x() + End1.x()) / 2), MiddlePoint.setY((Start1.y() + End1.y()) / 2);
	T1.MiddlePoint = this->MiddlePoint;
	T1.GoalWindow_HD = GoalWindow_HD;

	T3.Start1 = Start1, T3.End1 = End1, T3.Start2 = Start2, T3.End2 = End2;//给屏幕检测线程传入坐标和
	T3.GoalWindow_HD = GoalWindow_HD;

	handle = (HWND)(winId());// 获取当前窗口句柄 
	strcpy(name_str, "Zhihuishu_Aided_STOP");
	MultiByteToWideChar(CP_ACP, 0, name_str, -1, name_tchar, 100);
	HotKeyId = GlobalAddAtom(name_tchar);//得到热键的唯一标识
	RegisterHotKey(handle, HotKeyId, 0, VK_F8);//注册全局热键F8
	qApp->installNativeEventFilter(this);//与当前窗口关联

	//初始线程运行标识置零
	T1.flag_Thread_MoveArrow = 0;
	T2->flag_Thread_Timer = 0;
	T3.flag_Thread_ScreenAnalyze = 0;

	connect(ui.pushButton_1, SIGNAL(clicked()), this, SLOT(Start(void)));//关联开始按钮
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(close(void)));//关联退出按钮
	connect(T2, SIGNAL(Touch(void)), this, SLOT(Judge(void)));//WTF???你妈啊！为什么连不上啊！更新：=_=原来是槽函数声明没放到正确位置。。。
}

Window_Main::~Window_Main()
{

}

void Window_Main::paintEvent(QPaintEvent *event)
{

}

void Window_Main::ToClick(int mode)
{
	int tmp = T1.flag_Thread_MoveArrow;
	if (tmp == 1)
	{
		T1.flag_Thread_MoveArrow = 0;
	}
	switch (mode)
	{
		//视频结束自动下一节
	case 1:
	{
		//SetCursorPos(Start1.x() + 165, End1.y() + 30);
		SendMessage(GoalWindow_HD, WM_MOUSEMOVE, 0, (((End1.y() + 30) << 16) + (Start1.x() + 165)));

		//mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		SendMessage(GoalWindow_HD, WM_LBUTTONDOWN, 0, (((End1.y() + 30) << 16) + (Start1.x() + 165)));
		SendMessage(GoalWindow_HD, WM_LBUTTONUP, 0, (((End1.y() + 30) << 16) + (Start1.x() + 165)));
	}break;
	//弹题自动关闭
	case 2:
	{
		//SetCursorPos(Start2.x() + 750, Start2.y() + 20);
		SendMessage(GoalWindow_HD, WM_MOUSEMOVE, 0, (((Start2.y() + 20) << 16) + (Start2.x() + 750)));

		//mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		SendMessage(GoalWindow_HD, WM_LBUTTONDOWN, 0, (((Start2.y() + 20) << 16) + (Start2.x() + 750)));
		SendMessage(GoalWindow_HD, WM_LBUTTONUP, 0, (((Start2.y() + 20) << 16) + (Start2.x() + 750)));
	}break;
	default:break;
	}
	if (tmp == 1)
	{
		T1.flag_Thread_MoveArrow = 1;
	}
}

void Window_Main::Start(void)
{
	T3.IfVideoEnd = 0;//视频结束标识置零
	T3.IfQuestionShow = 0;//弹题标识置零
	hide();
	MoveArrow();
	TimeBegin();
	ScreenAnalyze();
}

void Window_Main::Judge(void)
{
	if (T3.IfVideoEnd == 1)
	{
		ToClick(1);
		T3.IfVideoEnd = 0;
	}
	if (T3.IfQuestionShow == 1)
	{
		ToClick(2);
		T3.IfQuestionShow = 0;
	}
}

//子线程部分
void Window_Main::ScreenAnalyze(void)
{
	T3.flag_Thread_ScreenAnalyze = 1;//运行标识置为1
	T3.start();
}

void Window_Main::MoveArrow(void)
{
	T1.flag_Thread_MoveArrow = 1;
	T1.start();
}

void Window_Main::TimeBegin(void)
{
	T2->flag_Thread_Timer = 1;
	T2->start();
}

void Thread_Timer::run(void)
{
	while (flag_Thread_Timer)
	{
		emit Touch();
		sleep(1);
	}
}

void Thread_ScreenAnalyze::run(void)
{
	while (flag_Thread_ScreenAnalyze)
	{
		//截图
		QScreen *VideoArea_Screen = QGuiApplication::primaryScreen();//播放按钮区域截图
		VideoArea_Pix = VideoArea_Screen->grabWindow((WId)GoalWindow_HD, Start1.x() + 20, End1.y() - 235, 100, 100);
		QScreen *QuestionArea_Screen = QGuiApplication::primaryScreen();//弹题区域截图
		QuestionArea_Pix = QuestionArea_Screen->grabWindow((WId)GoalWindow_HD, Start2.x(), Start2.y(), 770, 450);
		VideoArea_Img = VideoArea_Pix.toImage(), QuestionArea_Img = QuestionArea_Pix.toImage();

		//弹题区域截图判断RGB均>=200的像素点占总区域的百分比>=0.9
		int PixelSub = 0;
		uchar* imagebits = QuestionArea_Img.bits();
		int RightPixel = 0;
		int TotalPixel = QuestionArea_Img.width()*QuestionArea_Img.height();
		for (int i = 0; i < QuestionArea_Img.height(); i++)
		{
			PixelSub = i*QuestionArea_Img.width() * 4;
			for (int j = 0; j < QuestionArea_Img.width(); j++)
			{
				int R = imagebits[PixelSub + j * 4 + 2];
				int G = imagebits[PixelSub + j * 4 + 1];
				int B = imagebits[PixelSub + j * 4 + 0];
				if ((R >= 200) && (G >= 200) && (B >= 200))
				{
					RightPixel++;
				}
			}
		}
		double QuestionAreaRatio = (double)RightPixel / (double)TotalPixel;
		if (QuestionAreaRatio >= 0.90)
		{
			IfQuestionShow = 1;
		}

		if (!IfQuestionShow)//如果弹题了，忽略检测到的视频结束标识
		{
			//播放按钮区域截图判断与预置图片的相似度

			//VideoEndFlag
			//VideoEndFlag = QImage(":/Zhihuishu_Aided/VideoEndFlag-100_100.png");
			//int Pixelsub_VideoEndFlag = 0;
			//uchar* imagebits_VideoEndFlag = VideoEndFlag.bits();
			//int TwoValue_VideoEndFlag[100][100];
			//int RGB_VideoEndFlag = 0;
			//for (int i = 0; i < 100; i++)
			//{
			//	Pixelsub_VideoEndFlag = i * 100 * 4;
			//	for (int j = 0; j < 100; j++)
			//	{
			//		int R = imagebits_VideoEndFlag[Pixelsub_VideoEndFlag + j * 4 + 2];
			//		int G = imagebits_VideoEndFlag[Pixelsub_VideoEndFlag + j * 4 + 1];
			//		int B = imagebits_VideoEndFlag[Pixelsub_VideoEndFlag + j * 4 + 0];
			//		RGB_VideoEndFlag = 0.299*R + 0.587*G + 0.114*B;
			//		if (RGB_VideoEndFlag >= 127.5)
			//		{
			//			TwoValue_VideoEndFlag[i][j] = 1;
			//		}
			//		else
			//		{
			//			TwoValue_VideoEndFlag[i][j] = 0;
			//		}
			//	}
			//}
			//int VideoEndFlag_PixelValue_1 = 0;
			//for (int i = 0; i < 100; i++)
			//{
			//	for (int j = 0; j < 100; j++)
			//	{
			//		if (TwoValue_VideoEndFlag[i][j] == 1)
			//		{
			//			VideoEndFlag_PixelValue_1++;
			//		}
			//	}
			//}
			//double VideoEndFlagRatio = (double)VideoEndFlag_PixelValue_1 / 10000;
			//================================================================================
			//VideoArea_Img
			int Pixelsub_VideoArea_Img = 0;
			uchar* imagebits_VideoArea_Img = VideoArea_Img.bits();
			int TwoValue_VideoArea_Img[100][100];
			int RGB_VideoArea_Img = 0;
			for (int i = 0; i < 100; i++)
			{
				Pixelsub_VideoArea_Img = i * 100 * 4;
				for (int j = 0; j < 100; j++)
				{
					int R = imagebits_VideoArea_Img[Pixelsub_VideoArea_Img + j * 4 + 2];
					int G = imagebits_VideoArea_Img[Pixelsub_VideoArea_Img + j * 4 + 1];
					int B = imagebits_VideoArea_Img[Pixelsub_VideoArea_Img + j * 4 + 0];
					RGB_VideoArea_Img = 0.299*R + 0.587*G + 0.114*B;
					if (RGB_VideoArea_Img >= 127.5)
					{
						TwoValue_VideoArea_Img[i][j] = 1;
					}
					else
					{
						TwoValue_VideoArea_Img[i][j] = 0;
					}
				}
			}
			int VideoArea_Img_PixelValue_1 = 0;
			for (int i = 0; i < 100; i++)
			{
				for (int j = 0; j < 100; j++)
				{
					if (TwoValue_VideoArea_Img[i][j] == 1)
					{
						VideoArea_Img_PixelValue_1++;
					}
				}
			}
			double VideoArea_ImgRatio = (double)VideoArea_Img_PixelValue_1 / 10000;
			if ((VideoArea_ImgRatio < 0.69640 + 0.03) && (VideoArea_ImgRatio > 0.69640 - 0.03))
			{
				IfVideoEnd = 1;
			}
		}

		sleep(5);
	}
}

void Thread_MoveArrow::run(void)
{
	while (flag_Thread_MoveArrow)
	{
		SendMessage(GoalWindow_HD, WM_MOUSEMOVE, 0, (((MiddlePoint.y()) << 16) + (MiddlePoint.x())));
		//SetCursorPos(MiddlePoint.x(), MiddlePoint.y());
		sleep(1);
		//SetCursorPos(MiddlePoint.x() + 10, MiddlePoint.y());
		SendMessage(GoalWindow_HD, WM_MOUSEMOVE, 0, (((MiddlePoint.y()) << 16) + (MiddlePoint.x() + 10)));
		sleep(1);
	}
}

void Window_Main::keyPressEvent(QKeyEvent *event)//内部按键检测-已置空
{

}

bool Window_Main::nativeEventFilter(const QByteArray &eventType, void *message, long *result)//重写消息处理函数-WIN_HOTKEY
{
	if (eventType == "windows_generic_MSG")
	{
		MSG *msg = (MSG*)message;
		if (msg->message == WM_HOTKEY)
		{
			//各线程运行标识置零
			T1.flag_Thread_MoveArrow = 0;
			T2->flag_Thread_Timer = 0;
			T3.flag_Thread_ScreenAnalyze = 0;
			show();

			return true;
		}
	}
	return false;
}