#include "imagedialog.h"
#include "ui_imagedialog.h"

#include <QDebug>
#include <QImage>
#include <QPixmap>
#include <QString>

ImageDialog::ImageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageDialog)
{
    ui->setupUi(this);

}

ImageDialog::~ImageDialog()
{
    delete ui;
}

void ImageDialog::Init(QString imagePath)
{
    QImage image(imagePath);

    QPixmap pixmap = QPixmap::fromImage(image.scaled(QSize(ui->label->width(), ui->label->height()),Qt::KeepAspectRatio, Qt::SmoothTransformation));

    ui->label->setPixmap(pixmap);
    ui->label->setAlignment(Qt::AlignCenter);
}
