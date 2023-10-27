#include "listtemplate.h"
#include "ui_listtemplate.h"
#include "ui_msgitem.h"


MsgItem::MsgItem(QWidget *parent) : QWidget(parent), ui(new Ui::MsgItem)
{
    ui->setupUi(this);
    setWindowFlags( Qt::FramelessWindowHint/* | Qt::WindowStaysOnTopHint| Qt::WindowSystemMenuHint*/  | Qt::SubWindow );
    setAttribute( Qt::WA_TranslucentBackground, true );
    ui->btnClose->hide();
    ui->widgetCount->hide();
}

MsgItem::~MsgItem()
{
    delete ui;
}

QString MsgItem::msg() const
{
    return ui->lbMsg->text();
}

void MsgItem::setMsg(const QString& msg)
{
    ui->lbMsg->setText(msg);
}

QString MsgItem::header() const
{
    return m_header;
}

void MsgItem::setHeader(const QString& header)
{
    m_header = header;
    ui->widgetHead->setStyleSheet(QString("border-image: url(%1);").arg(header));
}

QString MsgItem::name() const
{
    return ui->lbName->text();
}

void MsgItem::setName(const QString& name)
{
    ui->lbName->setText(name);
}

QString MsgItem::datetime() const
{
    return ui->lbTime->text();
}

void MsgItem::setDatetime(const QString& datetime)
{
    ui->lbTime->setText(datetime);
}

int MsgItem::count() const
{
    return ui->lbCount->text().toInt();
}

void MsgItem::setCount(const int count)
{
    ui->lbCount->setText(QString::number(count));

     ui->widgetCount->setVisible(count != 0);
}

void MsgItem::setData(const QString &msg, const QString& nick, const QString& header, const QString& name, const QString& time )
{
    setMsg(msg);
    setUuid(nick);
    setHeader(header);
    setName(name);
    setDatetime(time);
}

void MsgItem::mousePressEvent(QMouseEvent* /*event*/)
{
    emit signal_selected(this);
}

void MsgItem::selected(bool selected)
{
    ui->widgetMain->setStyleSheet(selected ? QString("QWidget#widgetMain{ background-color: #F2F2F2; border-bottom: 1px solid #F2F2F2;}")
                                       : QString("QWidget#widgetMain{ background-color: #FFFFFF; border-bottom: 1px solid #F2F2F2;}" ));
    ui->btnClose->setVisible(selected);
    setCount(0);
}

void MsgItem::on_btnDeleteClicked()
{
    emit signal_delete(this);
}


ListTemplate::ListTemplate(QWidget *parent) : QWidget(parent), ui(new Ui::ListTemplate)
{
    ui->setupUi(this);

}

ListTemplate::~ListTemplate()
{
    delete ui;
}

void ListTemplate::AddWidgetMsgItem()
{
    auto pMsgItem = new MsgItem();
    QListWidgetItem *item = new QListWidgetItem;
    item->setSizeHint( QSize(360, 70));
    pMsgItem->setCount(99);
    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item, pMsgItem);

    connect(pMsgItem, &MsgItem::signal_selected, this, &ListTemplate::slot_selected);
    connect(pMsgItem, &MsgItem::signal_delete, this, &ListTemplate::slot_delete);
}

//第一种选中的实现方式
void ListTemplate::slot_selected(MsgItem *pWidget)
{
    if(Q_NULLPTR == pWidget)
    {
        return;
    }
    if(Q_NULLPTR != m_pCurrentItem)
    {
         m_pCurrentItem->selected(false);
    }

    pWidget->selected(true);
    m_pCurrentItem = pWidget;
}

//第二种选中的实现方式
void ListTemplate::on_listWidgetClicked(QListWidgetItem *pItem)
{
    if (Q_NULLPTR == pItem)
    {
        return;
    }
    if (Q_NULLPTR == m_pCurrent)
    {
        m_pCurrent = pItem;
        auto item = dynamic_cast<MsgItem*>(ui->listWidget->itemWidget(pItem));
        if (Q_NULLPTR == item)
        {
            return;
        }
        item->selected(true);
        return;
    }
    auto item = dynamic_cast<MsgItem*>(ui->listWidget->itemWidget(m_pCurrent));
    if (Q_NULLPTR == item)
    {
        return;
    }
    item->selected(false);
    m_pCurrent = pItem;
    item = dynamic_cast<MsgItem*>(ui->listWidget->itemWidget(pItem));
    if (item == Q_NULLPTR)
    {
        return;
    }
    item->selected(true);
}

void ListTemplate::slot_delete(QWidget* pWidget)
{
    delete pWidget;
    pWidget = Q_NULLPTR;
    QListWidgetItem *pItem = ui->listWidget->takeItem(ui->listWidget->currentRow());
    m_pCurrentItem = Q_NULLPTR;
    m_pCurrent = Q_NULLPTR;
}

void ListTemplate::on_btnAddClicked()
{
    AddWidgetMsgItem();
}
