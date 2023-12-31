#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <QtWebChannel/QtWebChannel>

namespace Ui {
class Map;
}

class Map : public QWidget
{
    Q_OBJECT

public:
    explicit Map(QWidget *parent = nullptr);
    ~Map();


private:
    void InitMap();


private:
    Ui::Map *ui;

    QWebChannel*        _channel;
};

#endif // MAP_H
