TEMPLATE = subdirs

SUBDIRS += \
    datetime \
    listwidget \
    treewidget \
    ipconfig \
    maskwidget \
    combobox \
    passwdcheck \
    matrix \
    mainwindow \
    messagecenter \
    autologin \
    tablewidget \
    datetimerange \
    datetime2 \
    searchline \
    pagenavigation \
    chart \
    painter \
    colordialog


#设置使用utf8
QMAKE_CFLAGS += /utf-8
QMAKE_CXXFLAGS += /utf-8
