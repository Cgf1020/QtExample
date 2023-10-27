#include "picturedisplayview.h"
#include "ui_picturedisplayview.h"

PictureDisplayView::PictureDisplayView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PictureDisplayView)
{
    ui->setupUi(this);
}

PictureDisplayView::~PictureDisplayView()
{
    delete ui;
}
