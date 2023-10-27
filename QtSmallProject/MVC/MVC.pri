FORMS += \
    $$PWD/View/tableview.ui \
    $$PWD/mvc.ui \
    $$PWD/mvc_1_listmodel.ui

HEADERS += \
    $$PWD/Delegate/btndelegate.h \
    $$PWD/Delegate/customitemdelegate.h \
    $$PWD/Delegate/listdelegate.h \
    $$PWD/Delegate/tabledelegate.h \
    $$PWD/Model/customlistmodel.h \
    $$PWD/Model/customsortfilterproxymodel.h \
    $$PWD/View/customheaderview.h \
    $$PWD/View/listview.h \
    $$PWD/View/mvc_1_listmodel.h \
    $$PWD/View/tableview.h \
    $$PWD/mvc.h \
    $$PWD/mvcGlobalDefine.h


SOURCES += \
    $$PWD/Delegate/btndelegate.cpp \
    $$PWD/Delegate/customitemdelegate.cpp \
    $$PWD/Delegate/listdelegate.cpp \
    $$PWD/Delegate/tabledelegate.cpp \
    $$PWD/Model/customlistmodel.cpp \
    $$PWD/Model/customsortfilterproxymodel.cpp \
    $$PWD/View/customheaderview.cpp \
    $$PWD/View/listview.cpp \
    $$PWD/View/mvc_1_listmodel.cpp \
    $$PWD/View/tableview.cpp \
    $$PWD/mvc.cpp \
    $$PWD/mvcGlobalDefine.cpp


#包含 MVC的例子
include ($$PWD/MultiLevelMenu/MultiLevelMenu.pri)

#包含 图片滚动 缩略图
include ($$PWD/PictureScroll/PictureScroll.pri)

#包含 多张图片展示页面
include ($$PWD/PictureDisplayView/PictureDisplayView.pri)

#包含 QQ列表
include ($$PWD/QQFriendList/QQFriendList.pri)



