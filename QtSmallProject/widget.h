#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "WaveProgressBar/waveprogressbar.h"




QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


private slots:
    void on_WaveProgressBar_btn_clicked();

private:
    void Init();

    void CreateWaveProgressBar();




private:
    Ui::Widget *ui;



    WaveProgressBar* _WaveProgressBar;
};
#endif // WIDGET_H
