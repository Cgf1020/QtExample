#ifndef THERMOMETER_H
#define THERMOMETER_H

#include <QWidget>

#include <QPropertyAnimation>

namespace Ui {
class Thermometer;
}

class Thermometer : public QWidget
{
    Q_OBJECT

public:
    explicit Thermometer(QWidget *parent = nullptr);
    ~Thermometer();

    qreal getValue();
    void setValue(qreal value);

protected:
    void paintEvent(QPaintEvent *event) override;


public slots:
    void startAnimation();


private:
    Ui::Thermometer *ui;

    qreal m_value;
    qreal curValue;
    int m_width;
    QRectF m_rect;
    int maxValue, minValue;
    qreal m_radius;
    QPropertyAnimation *m_valueAnimation;
    void updateRect();
};

#endif // THERMOMETER_H
