#ifndef WAVEPROGRESSBAR_H
#define WAVEPROGRESSBAR_H

#include <QWidget>
#include <QPainter>
#include <QtMath>



/* 模仿一个水波动态展现的控件
 *
*/

namespace Ui {
class WaveProgressBar;
}

class WaveProgressBar : public QWidget
{
    Q_OBJECT

public:
    explicit WaveProgressBar(QWidget *parent = nullptr);
    ~WaveProgressBar();

    //绘制的水波的样式
    enum Style_Type{
        eStyle_Rect = 0,    //矩形
        eStyle_Circle,      //圆
    };

    //进度值
    void setValue(int value) {m_value = value;}
    int value() {return m_value;}

    //最大值
    void setMaxValue(int value) {m_maxValue = value;}
    int maxValue() {return m_maxValue;}

    //最小值
    void setMinValue(int value) {m_minValue = value;}
    int minValue() {return m_minValue;}

    //设置外框形状
    void setPercentStyle(WaveProgressBar::Style_Type type) {m_percentStyle = type;}
    Style_Type percentStyle() {return m_percentStyle;}

    //设置水波密度（周期）
    void setWaterDensity(int val) {m_waterDensity = val;}
    int waterDensity() {return m_waterDensity;}

    //设置水体颜色
    void setColor(QColor col) {m_usedColor = col;}
    QColor color() {return m_usedColor;}

    //设置水波高度（幅值）
    void setWaterHeight(double val) {m_waterHeight = val;}
    double waterHeight() {return m_waterHeight;}

    //设置边界宽度
    void setBorderWidth(int val) {m_borderWidth = val;}
    int borderWidth() {return m_borderWidth;}

    //设置边框圆角
    void setRound(int round){m_round = round;}

    //设置字体颜色
    void setTextColor(QColor col) {m_textColor = col;}
    QColor textColor() {return m_textColor;}

    //设置字体边框颜色
    void setBoderColor(QColor col) {m_boderColor = col;}
    QColor boderColor() {return m_boderColor;}

    //设置背景颜色
    void setBgColor(QColor col) {m_bgColor = col;}
    QColor bgColor() {return m_bgColor;}

    //设置刷新间隔，越小刷新速度越快，cpu消耗越大
    void setUpdateTime(int time){m_updateTime = time;   this->startTimer(m_updateTime);}

    //设置波浪移动速度
    void setSpeed(int speed){m_speed = speed;}

protected:
    void paintEvent(QPaintEvent *event) override;
    void timerEvent(QTimerEvent *event) override;







private:
    Ui::WaveProgressBar *ui;


    Style_Type m_percentStyle = eStyle_Circle;   //边框类型

    int m_borderWidth = 0;                                  //边框宽度
    QColor m_boderColor = QColor(0,0,0,80);                 //边框颜色
    int m_round = 5;                                        //边框圆角

    QColor m_usedColor = QColor(180,255,255);               //水体颜色
    QColor m_textColor = Qt::white;                         //字体颜色
    QColor m_bgColor = Qt::gray;                            //背景颜色

    int m_updateTime = 100;         //水波波动速度，越大越慢
    int m_waterDensity = 5;         // 水波的密度
    double m_waterHeight = 0.02;    //水波高度
    double m_offset = 50;           //水波相位差
    double m_speed = 0.4;           //一次刷新的位移，可代表波浪移动速度

    QFont m_font;       //字体，默认大小为控件大小的1/4

    int m_value = 66;               //当前的水波值
    int m_minValue = 0;
    int m_maxValue = 100;

};

#endif // WAVEPROGRESSBAR_H
