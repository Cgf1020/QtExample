#ifndef PICTURESCROLL_H
#define PICTURESCROLL_H

#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QMap>
#include <QListWidgetItem>
#include <QFileInfo>



namespace Ui {
class PictureScroll;
}

class PictureScroll : public QWidget
{
    Q_OBJECT

public:
    explicit PictureScroll(QWidget *parent = nullptr);
    ~PictureScroll();

    /* 添加缩略图位置
     * @picUrl: 图片的位置
    */
    int AddLabelImage(QString picUrl);


    /* 滚动区域的label点击事件
    */
    void onScrollLabelClick();


protected:
    bool eventFilter(QObject *obj, QEvent *ev) override;



private slots:
    void onListWidgetCurrentRowChange(int currentRow);

    void on_pre_btn_clicked();

    void on_next_btn_clicked();

private:
    void Init();



private:
    Ui::PictureScroll *ui;

    //当前显示的 QImage
    QImage currentImage_;


    //滚动区域的大小
    int scrollWidth_{0};
    int scrollHeight_{0};

    //缩略图片的大小
    int thumbnailWidth_{300};
    int thumbnailHeight_{0};


    QMap<QString, QFileInfo> picPathMap_;
};

#endif // PICTURESCROLL_H
