#ifndef DASHBOARD_H
#define DASHBOARD_H


/**
 * 速度仪表盘控件
 * 1:可设置范围值,支持负数值
 * 2:可设置精确度,最大支持小数点后3位
 * 3:可设置大刻度数量/小刻度数量
 * 4:可设置开始旋转角度/结束旋转角度
 * 5:可设置是否启用动画效果以及动画效果每次移动的步长
 * 6:可设置三色圆环占比例
 * 7:自适应窗体拉伸,刻度尺和文字自动缩放
 */

#include <QWidget>

namespace Ui {
class Dashboard;
}

class Dashboard : public QWidget
{
    Q_OBJECT

public:
    explicit Dashboard(QString title, QWidget *parent = nullptr);
    ~Dashboard();

public:
    //设置范围值
    void setRange(double minValue, double maxValue);
    void setRange(int minValue, int maxValue);

    //设置目标值
    void setValue(double value);
    void setValue(int value);

    //设置精确度  没有用到  目前不知道哪里用的
    //void setPrecision(int precision);

    //设置主刻度数量
    void setScaleMajor(int scaleMajor);

    //设置小刻度数量
    void setScaleMinor(int scaleMinor);

    /* 设置绘制的角度
     * @startAngle: 开始旋转角度
     * @endAngle:   结束旋转角度
    */
    void setPaintAngle(int startAngle, int endAngle) noexcept;

    //设置是否启用动画显示
    void setAnimation(bool animation) noexcept;

    //设置动画显示的步长
    void setAnimationStep(double animationStep) noexcept;

    //设置饼圆宽度
    void setRingWidth(int ringWidth) noexcept;

    //设置三个圆环所占比例
    void setRingStartPercent(int ringStartPercent) noexcept;
    void setRingMidPercent(int ringMidPercent) noexcept;
    void setRingEndPercent(int ringEndPercent) noexcept;

    //设置三个圆环颜色
    void setRingColorStart(const QColor &ringColorStart) noexcept;
    void setRingColorMid(const QColor &ringColorMid) noexcept;
    void setRingColorEnd(const QColor &ringColorEnd) noexcept;

    //设置指针颜色
    void setPointerColor(const QColor &pointerColor) noexcept;
    //设置文本颜色
    void setTextColor(const QColor &textColor) noexcept;

    //设置文本后缀
    void setTextSuffix(QString suffix) noexcept;

protected:
    void paintEvent(QPaintEvent *event) override;

    void drawRing(QPainter *painter);       //绘制表盘圆环
    void drawScale(QPainter *painter);      //绘制表盘刻度
    void drawScaleNum(QPainter *painter);   //绘制表盘刻度值
    void drawPointer(QPainter *painter);    //绘制表盘指针
    void drawValue(QPainter *painter);      //绘制表盘显示值


private:
    void InitForm();

    void InitStyleSheet();

private slots:
    void updateValue();

    void on_horizontalSlider_valueChanged(int value);

signals:
    void valueChanged(int value);




private:
    double  _minValue;                  //最小值
    double  _maxValue;                  //最大值
    double  _value;                     //目标值
    double  _currentValue;              //当前值

    int     _precision;                 //精确度,小数点后几位   !!!!!!这个没用到

    int     _scaleMajor;                //大刻度数量
//    int     _scaleMinor;                //小刻度数量
    int     _startAngle;                //开始旋转角度
    int     _endAngle;                  //结束旋转角度

    bool    _animation;                 //是否启用动画显示
    double  _animationStep;             //动画显示时步长

    int     _ringWidth;                  //圆环宽度
    int     _ringStartPercent;           //第一圆环比例
    int     _ringMidPercent;             //第二圆环比例
    int     _ringEndPercent;             //第三圆环比例

    QColor  _ringColorStart;          //第一圆环颜色
    QColor  _ringColorMid;            //第二圆环颜色
    QColor  _ringColorEnd;            //第三圆环颜色

    QColor  _pointerColor;            //指针颜色
    QColor  _textColor;               //文字颜色

    QTimer* _timer;                  //定时器绘制动画
    //QLCDNumber *lcd;                //数码管


    int     _radius;                    //仪表盘半径

    QString _suffix;                    //文本后缀 str
private:
    Ui::Dashboard *ui;

    QString _title;                     //标题设置


};

#endif // DASHBOARD_H
