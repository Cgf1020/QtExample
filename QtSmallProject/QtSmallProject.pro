QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    widget.cpp

HEADERS += \
    widget.h

FORMS += \
    widget.ui



#一些不知道怎么分类的控件
include ($$PWD/Control/Control.pri)

#使用QChart 绘制的图表
include ($$PWD/QCharts/QCharts.pri)

#包含 QCustomplot 图表
include ($$PWD/QCustomplot/QCustomplot.pri)

#包含 MVC的例子
include ($$PWD/MVC/MVC.pri)



#设置使用utf8
QMAKE_CFLAGS += /utf-8
QMAKE_CXXFLAGS += /utf-8

RESOURCES += \
    res/res.qrc
