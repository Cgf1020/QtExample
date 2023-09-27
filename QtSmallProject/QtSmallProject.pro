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


#包含 地图控件
include ($$PWD/Map/Map.pri)
#包含 水波图控件
include ($$PWD/WaveProgressBar/WaveProgressBar.pri)
#包含 温度计控件
include ($$PWD/Thermometer/Thermometer.pri)






#设置使用utf8
QMAKE_CFLAGS += /utf-8
QMAKE_CXXFLAGS += /utf-8
