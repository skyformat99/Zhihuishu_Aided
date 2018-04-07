#define QDBG qDebug()<<__FILE__<<__FUNCTION__<<__LINE__

#include <QtWidgets/QApplication>
#include <QtWidgets>

class GlobalApplication : public QApplication
{
public:
	GlobalApplication(int&argc, char **argv);
	~GlobalApplication();

	bool notify(QObject*, QEvent *);
	void setWindowInstance(QWidget*wnd);
private:
	QWidget *widget;
};