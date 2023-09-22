#include "widget.h"

#include <QApplication>
#include "utils_base/fonthepler.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //初始化字体类
    FontHepler::instance()->initFont();



    Widget w;
    w.show();
    return a.exec();
}
