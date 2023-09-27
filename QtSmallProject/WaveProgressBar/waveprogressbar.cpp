#include "waveprogressbar.h"
#include "ui_waveprogressbar.h"

#include <QPainterPath>

WaveProgressBar::WaveProgressBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WaveProgressBar)
{
    ui->setupUi(this);

    m_font.setFamily("Microsoft YaHei");
    this->startTimer(m_updateTime);
}

WaveProgressBar::~WaveProgressBar()
{
    delete ui;
}


void WaveProgressBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    int height = this->height();
    int width = this->width();
    int side = qMin(width, height);

    //计算当前值所占百分比
    double percent = 1 - (double)(m_value - m_minValue) / (m_maxValue - m_minValue);

    //正弦曲线公式 y = A * sin(ωx + φ) + k
    double w = m_waterDensity * M_PI / width;   //w表示周期,可以理解为水波的密度,值越大密度越大(浪越密集 ^_^),取值 密度*M_PI/宽度
    double A = height * m_waterHeight;  //A表示振幅,可以理解为水波的高度,值越大高度越高(越浪 ^_^),取值高度的百分比
    double k = height * percent;    //k表示y轴偏移,可以理解为进度,取值高度的进度百分比

    QPainterPath waterPath1;    //第一条波浪路径集合
    QPainterPath waterPath2;    //第二条波浪路径集合

    //移动到左上角起始点
    waterPath1.moveTo(0, height);
    waterPath2.moveTo(0, height);

    m_offset += m_speed;
    if (m_offset > (width / 2))
        m_offset = 0;

    //计算路劲
    for(int x = 0; x <= width; x++)
    {
        double waterY1 = (double)(A * sin(w * x + m_offset)) + k; //第一条波浪Y轴
        double waterY2 = (double)(A * sin(w * x + m_offset + (width / 2 * w))) + k; //第二条波浪Y轴
        if (m_value == m_minValue)   //如果当前值为最小值则Y轴为高度
        {
            waterY1 = height;
            waterY2 = height;
        }
        if (m_value == m_maxValue)  //如果当前值为最大值则Y轴为0
        {
            waterY1 = 0;
            waterY2 = 0;
        }
        waterPath1.lineTo(x, waterY1);
        waterPath2.lineTo(x, waterY2);
    }
    //移动到右下角结束点,整体形成一个闭合路径
    waterPath1.lineTo(width, height);
    waterPath2.lineTo(width, height);

    //大路径
    QPainterPath bigPath;
    if(m_borderWidth <= 0)
        painter.setPen(Qt::NoPen);
    else
        painter.setPen(m_boderColor);
    painter.setBrush(m_bgColor);
    if (m_percentStyle == eStyle_Rect)
    {
        painter.setBrush(m_bgColor);
        painter.drawRoundRect(m_borderWidth, m_borderWidth, width, height,5,5);
        bigPath.addRoundRect(m_borderWidth, m_borderWidth, width, height,5,5);
    }
    else if (m_percentStyle == eStyle_Circle)
    {
        side = side - m_borderWidth * 2;
        painter.drawEllipse((width - side) / 2, m_borderWidth, side, side);
        bigPath.addEllipse((width - side) / 2, m_borderWidth, side, side);
    }

    //新路径,用大路径减去波浪区域的路径,形成遮罩效果
    QPainterPath path;

    //第一条波浪挖去后的路径
    m_usedColor.setAlpha(100);
    path = bigPath.intersected(waterPath1);
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_usedColor);
    painter.drawPath(path);

    //第二条波浪挖去后的路径
    m_usedColor.setAlpha(180);
    path = bigPath.intersected(waterPath2);
    painter.setBrush(m_usedColor);
    painter.drawPath(path);

    //绘制文字
    m_font.setPixelSize(side/4);
    painter.setPen(m_textColor);
    painter.setFont(m_font);
    painter.drawText(this->rect(), Qt::AlignCenter, QString("%1%").arg(m_value));
}

void WaveProgressBar::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    this->update();
}
