#ifndef BTNDELEGATE_H
#define BTNDELEGATE_H

#include <QObject>
#include <QPushButton>
#include <QStyledItemDelegate>
#include <QPoint>


class BtnDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit BtnDelegate(QObject *parent = nullptr);


    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;



    bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index);


signals:
    void open(const QModelIndex &index);


private:
    QPoint m_mousePoint;  // 鼠标位置
    int m_nType;  // 按钮状态：0-划过 1-按下
    QScopedPointer<QPushButton> playBackBtn;

    QStringList m_btnNames;

};

#endif // BTNDELEGATE_H
