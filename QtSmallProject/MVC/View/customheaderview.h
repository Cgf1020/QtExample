#ifndef CUSTOMHEADERVIEW_H
#define CUSTOMHEADERVIEW_H

#include <QObject>
#include <QHeaderView>

class CustomHeaderView : public QHeaderView
{
    Q_OBJECT
public:
    /**
     * @brief CHeaderView 构造函数
     * @param orientation 方向
     * @param parent 父类对象
     */
    explicit CustomHeaderView(Qt::Orientation orientation, QWidget *parent = nullptr);

    /**
     * @brief setColumnCheckable 设置指定列是否可选
     * @param column 指定列
     * @param checkable 可选值
     */
    void setColumnCheckable(int column, bool checkable);

    /**
     * @param param: 设置列的复选框选择状态
     */
    void setColumnCheckState(bool state);


signals:
    /**
     * @brief columnSectionClicked Section点击信号
     * @param logicalIndex 点击位置
     * @param checked 选中值
     */
    void columnSectionClicked(int logicalIndex, bool checked);


protected:       // QHeaderView interface
    /**
     * @brief paintSection 绘制复选框
     * @param painter 绘制对象
     * @param rect 绘制区域
     * @param logicalIndex 当前索引位置
     */
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const;

private:
    //checkbox的开启或关闭状态
    bool isOn{false};
};

#endif // CUSTOMHEADERVIEW_H
