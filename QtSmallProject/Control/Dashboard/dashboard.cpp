#include "dashboard.h"
#include "ui_dashboard.h"

#include <QPainter>
#include <QTimer>
#include <QtMath>
#include <QDebug>

Dashboard::Dashboard(QString title, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Dashboard)
{
    ui->setupUi(this);


    this->InitForm();
    this->InitStyleSheet();
}

Dashboard::~Dashboard()
{
    delete ui;
}

void Dashboard::setRange(double minValue, double maxValue)
{
    //如果最小值大于或者等于最大值则不设置
    if (minValue >= maxValue) {
        return;
    }

    this->_minValue = minValue;
    this->_maxValue = maxValue;

    //如果目标值不在范围值内,则重新设置目标值
    //值小于最小值则取最小值,大于最大值则取最大值
    if (this->_value < minValue) {
        setValue(minValue);
    } else if (this->_value > maxValue) {
        setValue(maxValue);
    }

    this->update();
}

void Dashboard::setRange(int minValue, int maxValue)
{
    setRange((double)minValue, (double)maxValue);
}

void Dashboard::setValue(double value)
{
    //值和当前值一致则无需处理
    if (value == this->_value) {
        return;
    }

    //值小于最小值则取最小值, 大于最大值则取最大值=========>>>>>更新 this->_value 值
    if (value < this->_minValue) {
        this->_value = this->_minValue;
    } else if (value > this->_maxValue) {
        this->_value = this->_maxValue;
    }
    else{
        this->_value = value;
    }

    emit valueChanged(this->_value);

    if (this->_animation) {
        this->_timer->stop();
        this->_timer->start();
    } else {
        this->_currentValue = value;
        this->update();
    }
}

void Dashboard::setValue(int value)
{
    setValue(double(value));
}

void Dashboard::setScaleMajor(int scaleMajor)
{
    this->_scaleMajor = scaleMajor;
}

void Dashboard::setScaleMinor(int scaleMinor)
{
    //    this->_scaleMinor = scaleMinor;
}

void Dashboard::setPaintAngle(int startAngle, int endAngle) noexcept
{
    this->_startAngle = startAngle;
    this->_endAngle = endAngle;
}

void Dashboard::setAnimation(bool animation) noexcept
{
    this->_animation = animation;
}

void Dashboard::setAnimationStep(double animationStep) noexcept
{
    this->_animationStep = animationStep;
}

void Dashboard::setRingWidth(int ringWidth) noexcept
{
    this->_ringWidth = ringWidth;
}

void Dashboard::setRingStartPercent(int ringStartPercent) noexcept
{
    this->_ringStartPercent = ringStartPercent;
}

void Dashboard::setRingMidPercent(int ringMidPercent) noexcept
{
    this->_ringMidPercent = ringMidPercent;
}

void Dashboard::setRingEndPercent(int ringEndPercent) noexcept
{
    this->_ringEndPercent = ringEndPercent;
}

void Dashboard::setRingColorStart(const QColor &ringColorStart) noexcept
{
    this->_ringColorStart = ringColorStart;
}

void Dashboard::setRingColorMid(const QColor &ringColorMid) noexcept
{
    this->_ringColorMid = ringColorMid;
}

void Dashboard::setRingColorEnd(const QColor &ringColorEnd) noexcept
{
    this->_ringColorEnd = ringColorEnd;
}

void Dashboard::setPointerColor(const QColor &pointerColor) noexcept
{
    this->_pointerColor = pointerColor;
}

void Dashboard::setTextColor(const QColor &textColor) noexcept
{
    this->_textColor = textColor;
}

void Dashboard::setTextSuffix(QString suffix) noexcept
{
    this->_suffix = suffix;
}







void Dashboard::paintEvent(QPaintEvent *event)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //获取当前的宽高
    int width = this->width();
    int height = this->height() - ui->label->height();
    int side = qMin(width, height);

    //计算出仪表盘的半径大小
    _radius = side / 2;

    //painter.fillRect(rect(), QColor("#242b3b"))

    painter.translate(width / 2, height / 2);




    //绘制表盘圆环
    drawRing(&painter);
    //绘制表盘刻度
    drawScale(&painter);
    //绘制表盘刻度值
    drawScaleNum(&painter);
    //绘制表盘指针
    drawPointer(&painter);
    //绘制表盘显示值
    drawValue(&painter);
}

void Dashboard::drawRing(QPainter *painter)
{
    painter->save();

    QPen pen;
    pen.setCapStyle(Qt::FlatCap);
    pen.setWidthF(this->_ringWidth);

    //计算出 绘制刻度盘所在的矩形的位置和大小
    int radius = _radius;
    QRectF rect = QRectF(-radius, -radius, radius * 2, radius * 2);

    //计算总范围角度,根据占比例自动计算三色圆环范围角度
    double angleAll = this->_endAngle - this->_startAngle;
    double angleStart = angleAll * (double)this->_ringStartPercent / 100;
    double angleMid = angleAll * (double)this->_ringMidPercent / 100;
    double angleEnd = angleAll * (double)this->_ringEndPercent / 100;

    //绘制第一圆环
    pen.setColor(this->_ringColorStart);
    painter->setPen(pen);
//    painter->drawArc(rect, (270 - this->_startAngle - angleStart) * 16, angleStart * 16);
    painter->drawArc(rect, this->_startAngle * 16, angleStart * 16);
    painter->drawArc(rect, 210 * 16, -90 * 16);

    //绘制第二圆环
    pen.setColor(this->_ringColorMid);
    painter->setPen(pen);
//    painter->drawArc(rect, (360 - this->_startAngle - angleStart - angleMid) * 16, angleMid * 16);
    painter->drawArc(rect, (this->_startAngle + angleStart) * 16, angleMid * 16);
//    painter->drawArc(rect, 150 * 16, -120 * 16);

    //绘制第三圆环
    pen.setColor(this->_ringColorEnd);
    painter->setPen(pen);
//    painter->drawArc(rect, (360 - this->_startAngle - angleStart - angleMid - angleEnd) * 16, angleEnd * 16);
    painter->drawArc(rect, (this->_startAngle + angleStart + angleMid) * 16, angleEnd * 16);
//    painter->drawArc(rect, 30 * 16, -60 * 16);

    painter->restore();

}

void Dashboard::drawScale(QPainter *painter)
{
    painter->save();

    //绘制客户端值的半径
    int radius = this->_radius - this->_ringWidth;

    QPen pen;
    pen.setColor(this->_textColor);
    pen.setWidthF(1.5);
    pen.setCapStyle(Qt::RoundCap);

    painter->rotate(360 - this->_startAngle);

    //刻度的角度    总的角度 / (刻度的数量 - 1) = 每个刻度的角度
    double angleStep = (-this->_endAngle + this->_startAngle) / (this->_scaleMajor - 1);

    //计算圆环对应大刻度范围索引
//    int indexStart = this->_scaleMajor * (double)this->_ringStartPercent / 100 + 1;
//    int indexMid = this->_scaleMajor * (double)this->_ringMidPercent / 100 - 1;
//    int indexEnd = this->_scaleMajor * (double)this->_ringEndPercent / 100 + 1;
//    int index = 0;

    for(int i = 0; i < this->_scaleMajor; i++)
    {
        painter->drawLine(radius - 10, 0, radius, 0);
        painter->rotate(angleStep);
    }

    painter->restore();
}
void Dashboard::drawScaleNum(QPainter *painter)
{
    painter->save();

    //刻度值的半径大小
    int radius = this->_radius - this->_ringWidth - 20;

    QPen pen;
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidthF(1.5);
    pen.setColor(this->_textColor);
    painter->setPen(pen);

    double deltaRad = (-this->_endAngle + this->_startAngle) / (this->_scaleMajor - 1);   // 240 / 8
    double startRad = this->_startAngle;

    for (int i = 0; i < this->_scaleMajor; i++) {
        double sina = qSin((startRad - i * deltaRad) * ((M_PI / 180)));
        double cosa = qCos((startRad - i * deltaRad) * ((M_PI / 180)));
        double value = 1.0 * i * ((this->_maxValue - this->_minValue) / (this->_scaleMajor - 1)) + this->_minValue;

        QString strValue = QString("%1").arg((double)value, 0, 'f', 0);
        double textWidth = fontMetrics().width(strValue);
        double textHeight = fontMetrics().height();
        int x = radius * cosa - textWidth / 2;
        int y = -radius * sina + textHeight / 4;

        painter->drawText(x, y, strValue);
    }

    painter->restore();
}

void Dashboard::drawPointer(QPainter *painter)
{
    painter->save();


    int radius = this->_radius - this->_ringWidth - 20 - 30;
    int offset = 20;

    painter->setPen(Qt::NoPen);
    painter->setBrush(this->_pointerColor);

    QPolygon pts;
    pts << QPoint(0,0) << QPoint(0 + offset, 8) << QPoint(0 + radius, 0) << QPoint(0 + offset, -8);

    painter->rotate(360 - this->_startAngle);

    double degRotate = (-this->_endAngle + this->_startAngle) / (this->_maxValue - this->_minValue) * (this->_currentValue - this->_minValue);

    painter->rotate(degRotate);

    painter->drawConvexPolygon(pts);

    painter->restore();
}

void Dashboard::drawValue(QPainter *painter)
{
    painter->save();
    QPen pen;
    pen.setColor(Qt::white);
    painter->setPen(pen);

    QFont font;
    font.setFamily("Microsoft YaHei");
    font.setBold(true);
    font.setPointSize(30);
    painter->setFont(font);

    int textWidth = fontMetrics().width(QString::number(this->_currentValue));
    painter->drawText(-(textWidth/2+15),_radius*2/5,QString::number(this->_currentValue));
    painter->restore();
}

void Dashboard::InitForm()
{
    this->_ringWidth = 10;                  //可以通过widget的大小计算

    this->_maxValue = 40;
    this->_minValue = -40;
    this->_value = 30;

    this->_currentValue = 10;


    this->_startAngle = 210;                //仪表盘的开始角度
    this->_endAngle = -30;                  //仪表盘的结束角度   ：  按顺时针算的

    this->_scaleMajor = 9;

    this->_ringStartPercent = 20;
    this->_ringMidPercent = 60;
    this->_ringEndPercent = 20;

    this->_ringColorStart = Qt::green;            //第一圆环颜色
    this->_ringColorMid = Qt::blue;               //第二圆环颜色
    this->_ringColorEnd = Qt::red;                //第三圆环颜色

    this->_pointerColor = Qt::gray;
    this->_textColor = Qt::blue;                 //文字颜色

    this->_animationStep = 1;

    _timer = new QTimer(this);
    _timer->setInterval(10);
    connect(_timer, SIGNAL(timeout()), this, SLOT(updateValue()));
    this->_timer->start();
}


void Dashboard::InitStyleSheet()
{
    //设置ChartView 的背景颜色 为 暗黑色
    //    this->setStyleSheet("background-color:#242b3b;");

//    this->setStyleSheet("QLabel{color:black;}");

    ui->label->setText("_title");
}

void Dashboard::updateValue()
{
    if(this->_currentValue < this->_value)
    {
        _currentValue += _animationStep;
        if (_currentValue >= _value) {
            _currentValue = _value;
            _timer->stop();
        }

        this->update();
    }
    else if(this->_currentValue > this->_value)
    {
        _currentValue -= _animationStep;
        if (_currentValue <= _value) {
            _currentValue = _value;
            _timer->stop();
        }
        this->update();
    }
    else
    {
        _timer->stop();
    }
}

void Dashboard::on_horizontalSlider_valueChanged(int value)
{
    setValue(value);
}

