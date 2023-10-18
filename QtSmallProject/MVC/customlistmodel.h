#ifndef CUSTOMLISTMODEL_H
#define CUSTOMLISTMODEL_H


/*自定义模型需要实现Qt中的抽象模型类（QAbstractItemModel）中的纯虚函数。
 * 其中，最基本的函数包括rowCount()、columnCount()、data()和index()函数。rowCount()和columnCount()函数返回模型中行和列的数量，data()函数用于获取模型中某个单元格的数据，而index()函数返回模型中指定行和列的QModelIndex对象。
 * 开发者还可以实现其他函数，如headerData()函数用于返回模型的列标题和行标题，以及setData()函数用于设置模型中某个单元格的数据。在自定义模型中还可以使用信号和槽机制，以便在数据发生变化时通知视图部件进行更新。
 *
*/


/*******!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*********
 * 1. QAbstractListModel中的
*/



#include <QObject>
#include <QStringList>
#include <QAbstractListModel>
#include <QModelIndex>

class CustomListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit CustomListModel(QObject *parent = nullptr);

    /* 设置数据
     * @strings：数据
     * @DisplayRole：数据项的角色（目前我还不知道干什么用的）
    */
    void setStringList(const QStringList &strings);
    QStringList stringList() const;


    /* 获取Model 数据的行数
    */
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /* 获取对象 index的数据
     * @index：Model中数据项的 索引
     * @DisplayRole：数据项的角色（目前我还不知道干什么用的）
    */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /* 设置index对应项的数据
     * @index：Model中数据项的 索引
     * @value：需要设置的值
     * @DisplayRole：数据项的角色（目前我还不知道干什么用的）
    */
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    /* 插入/移除 行
     * @row：行号
     * @count：列号，ListModel中 这个就是为0
     * @QModelIndex：插入移除 行的索引
    */
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;


    /* 获取数据的标志：我不太懂
     * 用来设置单元格的标志（可用、可选中、可复选状态等）。
     * @index：索引
     * return:
    */
    Qt::ItemFlags flags(const QModelIndex &index) const override;
signals:



private:
    QStringList strList;

};

#endif // CUSTOMLISTMODEL_H
