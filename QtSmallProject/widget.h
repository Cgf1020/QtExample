#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "Map/map.h"
#include "WaveProgressBar/waveprogressbar.h"
#include "Thermometer/thermometer.h"
#include "Curve/curve.h"
#include "Battery/battery.h"
#include "Dashboard/dashboard.h"

#include "QCustomplot/qcustomplotcurve.h"



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
    void on_map_btn_clicked();

    void on_WaveProgressBar_btn_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();


    void on_Battery_btn_clicked();

    void on_wendu_dashboard_btn_clicked();

    void on_QCustomPlot_btn_clicked();

private:
    void Init();

    void CreateCurve();
    void CreateMap();
    void CreateWaveProgressBar();
    void CreateThermometer();
    void CreateBattery();
    void CreateDashboard();

    void CreateQCustomPlotCurve();



private:
    Ui::Widget *ui;

    Curve*              _curve{NULL};
    Map*                _Map{NULL};
    WaveProgressBar*    _WaveProgressBar{NULL};
    Thermometer*        _Thermometer{NULL};
    Battery*            _Battery{NULL};             //电池
    Dashboard*          _Dashboard{NULL};           //温度仪表盘


    QCustomPlotCurve*   _QCustomPlotCurve{NULL};
};





















#endif // WIDGET_H
