#include "picturescroll.h"
#include "ui_picturescroll.h"


#include <QDebug>
#include <QScrollBar>
#include <QFile>
#include <QFileInfo>

PictureScroll::PictureScroll(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PictureScroll)
{
    ui->setupUi(this);

    this->Init();
}

PictureScroll::~PictureScroll()
{
    delete ui;
}

int PictureScroll::AddLabelImage(QString picUrl)
{
    //构建文件类
    QFileInfo fileInfo(picUrl);
//    qDebug() << "fileInfo: " << fileInfo.filePath() << ",  name: " << fileInfo.fileName();


    // 从文件加载 QImage
    //1.加载图片
    QImage image(fileInfo.filePath());

    //2.将 QImage 转换为 QPixmap
    QPixmap pixmap = QPixmap::fromImage(image.scaled(QSize(thumbnailWidth_, thumbnailHeight_),Qt::KeepAspectRatio, Qt::SmoothTransformation));

//    qDebug() << "pixmap: " << pixmap.width() << ", " << pixmap.height();


    // 添加到  ListWidget
    QListWidgetItem *imageItem = new QListWidgetItem;
    imageItem->setIcon(QIcon(pixmap));
    imageItem->setText(fileInfo.fileName());
//    imageItem->setSizeHint(QSize(220, 200));  设置固定的大小
    imageItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignTop);
    // 连接item的clicked信号到槽函数，实现item的点击事件
    ui->listWidget->addItem(imageItem);

    //保存图片
    picPathMap_.insert(fileInfo.fileName(), fileInfo);


    return true;
}

void PictureScroll::onScrollLabelClick()
{

}

bool PictureScroll::eventFilter(QObject *obj, QEvent *ev)
{
//    if (ev->type() == QEvent::MouseButtonPress)
//    {
//        qDebug() << "1";

//        //主界面的显示选中的图片
//        //const QPixmap *pixmap() const;
//        QLabel* label = static_cast<QLabel*>(obj);
//        const QPixmap* pixmap = label->pixmap();

//        qDebug() << "ui->PicDisplay_label->size(): " << ui->PicDisplay_label->size().width() << ", " << ui->PicDisplay_label->size().height();

//        QPixmap p = pixmap->scaled(ui->PicDisplay_label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

//        qDebug() << "pixmap size: " << p.size().width() << ", " << p.size().height();

//        ui->PicDisplay_label->setPixmap(p);

//        //设置点击选中的样式

//        return true;
//    }


    //按钮的事件
//    if(ui->pre_btn == obj || ui->next_btn == obj)
//    {
//        if(QEvent::Enter == ev->type())//鼠标进入
//        {
//            qDebug() << "鼠标进入";
//            ui->pre_btn->show();
//            ui->next_btn->show();
//        }
//        else if (QEvent::Leave == ev->type())//鼠标离开
//        {
//            qDebug() << "鼠标离开";
//            ui->pre_btn->hide();
//            ui->next_btn->hide();
//        }
//    }


    return QWidget::eventFilter(obj, ev);
}

void PictureScroll::onListWidgetCurrentRowChange(int currentRow)
{
    qDebug() << " onListWidgetCurrentRowChange ";

    QListWidgetItem *current = ui->listWidget->currentItem();

    // 将Item摆在视图中间
//    ui->listWidget->scrollToItem(current, QAbstractItemView::PositionAtCenter);
//    current->setSelected(true);

    // 查找map
    QString text = current->text();

    auto it = picPathMap_.find(text);

    if(it != picPathMap_.end())
    {
        QFileInfo fileInfo = it.value();

        QImage image(fileInfo.filePath());

        QPixmap pixmap = QPixmap::fromImage(image.scaled(QSize(ui->PicDisplay_label->width(), ui->PicDisplay_label->height()),Qt::KeepAspectRatio, Qt::SmoothTransformation));

        ui->PicDisplay_label->setPixmap(pixmap);
    }
}

void PictureScroll::Init()
{
    thumbnailWidth_ = 300;
    thumbnailHeight_ = 170;

    // 禁止item移动
    ui->listWidget->setMovement(QListView::Static);
    // 设置列表的显示模式为图标模式
    ui->listWidget->setViewMode(QListView::IconMode);
    // 设置图片大小
    ui->listWidget->setIconSize(QSize(300, 200));
    // 设置item布局方向
    ui->listWidget->setFlow(QListView::LeftToRight);
    // 设置item之间的间距为10
    //ui->listWidget->setSpacing(50);
    // 自动排序
//    ui->listWidget->setSortingEnabled(true);
    // 设置环换行
    ui->listWidget->setWrapping(false);

    connect(ui->listWidget, &QListWidget::currentRowChanged, this, &PictureScroll::onListWidgetCurrentRowChange);


    AddLabelImage("D://MyCode/QtExample/QtSmallProject/res/pic/1.jpg");
    AddLabelImage("D://MyCode/QtExample/QtSmallProject/res/pic/2.jpg");
    AddLabelImage("D://MyCode/QtExample/QtSmallProject/res/pic/3.png");
    AddLabelImage("D://MyCode/QtExample/QtSmallProject/res/pic/4.jpg");
    AddLabelImage("D://MyCode/QtExample/QtSmallProject/res/pic/5.png");
    AddLabelImage("D://MyCode/QtExample/QtSmallProject/res/pic/6.jpeg");
    AddLabelImage("D://MyCode/QtExample/QtSmallProject/res/pic/7.png");
    AddLabelImage("D://MyCode/QtExample/QtSmallProject/res/pic/8.png");
    AddLabelImage("D://MyCode/QtExample/QtSmallProject/res/pic/9.png");
    AddLabelImage("D://MyCode/QtExample/QtSmallProject/res/pic/10.png");
    AddLabelImage("D://MyCode/QtExample/QtSmallProject/res/pic/11.png");

//    设置样式，直接在函数中设置
//    this->setStyleSheet("QListWidget::item{padding-top:4px; padding-bottom:4px; margin-left:30px; margin-right:30px}"
//                        "QListWidget::item:selected{background:lightgray; color:red; }");
    //加载样式表
    QFile file(":/qss/PivtureScroll.css");
    if (file.open(QFile::ReadOnly)) {

        qDebug() << " 成功加载qss";

        QString qss = QLatin1String(file.readAll());
        this->setStyleSheet(qss);
        file.close();
    }
}

void PictureScroll::on_pre_btn_clicked()
{
    //设置 listWidget 点击前一个
    int currentRow = ui->listWidget->currentRow();
    if(currentRow == 0)
        return;
    int preRow = currentRow - 1;
    ui->listWidget->setCurrentRow(preRow);
}


void PictureScroll::on_next_btn_clicked()
{
    //设置 listWidget 点击前一个
    int currentRow = ui->listWidget->currentRow();

    if(currentRow == ui->listWidget->count() - 1)
        return;

    int nextRow = currentRow + 1;

    ui->listWidget->setCurrentRow(nextRow);
}

