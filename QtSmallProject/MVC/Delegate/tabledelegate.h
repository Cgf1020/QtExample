#ifndef TABLEDELEGATE_H
#define TABLEDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>
#include <QStandardItemModel>


class TableDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit TableDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;


    void setModel(QStandardItemModel* model)
    {
        model_ = model;
    }

protected:
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;



private slots:
    void deleteButtonClickEvent();



signals:
    //删除按钮点击事件
    void deleteButtonClickSignal();


private:
    void painterSnapshot(QPainter *painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

    void painterPlaybackBtn(QPainter *painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;





private:
//    const QRect PlayBackBtnRect{ 10,12,11,11 };   // 群组下拉图标  x,y,w,h
    QSize PlayBackBtnSize{32, 32};      //回放图像的大小

    QStandardItemModel* model_{nullptr};
};

#endif // TABLEDELEGATE_H
