#ifndef PICTUREDISPLAYVIEW_H
#define PICTUREDISPLAYVIEW_H

#include <QWidget>

namespace Ui {
class PictureDisplayView;
}

class PictureDisplayView : public QWidget
{
    Q_OBJECT

public:
    explicit PictureDisplayView(QWidget *parent = nullptr);
    ~PictureDisplayView();

private:
    Ui::PictureDisplayView *ui;
};

#endif // PICTUREDISPLAYVIEW_H
