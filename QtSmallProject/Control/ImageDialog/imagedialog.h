#ifndef IMAGEDIALOG_H
#define IMAGEDIALOG_H

#include <QWidget>
#include <QDialog>

namespace Ui {
class ImageDialog;
}

class ImageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImageDialog(QWidget *parent = nullptr);
    ~ImageDialog();

    void Init(QString imagePath);

private:
    Ui::ImageDialog *ui;
};

#endif // IMAGEDIALOG_H
