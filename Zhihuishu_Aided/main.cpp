#include "Window_Declear.h"
#include "GlobalApplication.h"

int main(int argc, char *argv[])
{
	GlobalApplication a(argc, argv);
	Window_Declear w;
	w.show();
	a.exec();
	return 0;
}