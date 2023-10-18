#include "widget.h"

#include <QApplication>

#include "QQFriendList/qqfriendlist.h"

#include <vector>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Widget w;
//    w.show();

    QQFriendList q;

//    for(int i = 0; i < 5; i++)
//    {
//        q.addGroup("分组");
//    }

    q.show();
    return a.exec();
}
