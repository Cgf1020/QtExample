#ifndef MULTILEVELMENU_H
#define MULTILEVELMENU_H

#include <QWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QMenu>

namespace Ui {
class MultiLevelMenu;
}

class MultiLevelMenu : public QWidget
{
    Q_OBJECT

public:
    explicit MultiLevelMenu(QWidget *parent = nullptr);
    ~MultiLevelMenu();

    /*添加顶层节点
     *@name：顶层节点显示的名字
    */
    void addTopLevelItem(QString name);

    /*添加子节点
     *@name：子节点显示的名字
    */
    void addSubLevelItem(QString name);

private slots:
    //鼠标点击item
    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_pushButton_clicked();

private:
    //初始化
    void init();

private:
    Ui::MultiLevelMenu *ui;

    QMenu *m_menu = nullptr;
};

#endif // MULTILEVELMENU_H
