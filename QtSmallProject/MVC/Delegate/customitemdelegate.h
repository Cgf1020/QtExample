#ifndef CUSTOMITEMDELEGATE_H
#define CUSTOMITEMDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>
#include <QListView>




typedef struct CustomItemData{
    QString iconPath;       //图标路径
    QString title;          //
    QString subTitle;
    QString content;
    QString time;           //时间
} CustomItemData;

//将自定义的数据结构注册，否则不可设置为Item的数据。Qt提供了注册自定义数据的宏
Q_DECLARE_METATYPE(CustomItemData)    //自定义结构体WItemData




class CustomItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit CustomItemDelegate(QObject *parent = nullptr);


public:
    /*渲染
     * @painter: 数据项的绘制全部由它完成
     * @option: 数据项在视图小部件中绘制的各项参数,如坐标、状态、图标... 较为重要的（我们要用的）就是坐标和状态，其中坐标信息包含在rect中，状态信息包含在state中。
     * @index: 数据项的数据模型
    */
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;


    /*返回Item窗口大小，重写以单独设置Item大小
    */
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;


    /*双击Item时创建一个控件，返回控件的QWidget指针。该组件会被作为用户编辑数据时所使用的编辑器，从模型中接受数据，返回用户修改的数据。（//创建你编辑时候的控件）
    */
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    /*完成编辑后，将编辑内容同步给数据模型。 在编辑框显示时会调用它为编辑框设置大小和位置
     * @editor: createEditor所创建的控件
     * @option: 数据项在视图小部件中绘制的各项参数
     * @index: 数据的索引
    */
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    /*为编辑框设置内容, 编辑的时候设置数据到上面创建的editor中
     * @editor: createEditor所创建的控件
     * @index: 数据的索引
    */
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;


    /*完成编辑后，将编辑内容同步给数据模型
     * @editor: createEditor所创建的控件
     * @model: view中设置进去的 model
     * @index: 数据的索引
    */
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

signals:

};

#endif // CUSTOMITEMDELEGATE_H
