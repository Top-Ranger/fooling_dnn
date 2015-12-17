#ifndef FINALIMAGE_H
#define FINALIMAGE_H

#include <QDialog>

namespace Ui {
class FinalImage;
}

class FinalImage : public QDialog
{
    Q_OBJECT

public:
    explicit FinalImage(QImage image, double confidence, QString class_string, QWidget *parent = 0);
    ~FinalImage();

private slots:
    void on_pushButton_clicked();

private:
    Ui::FinalImage *ui;
};

#endif // FINALIMAGE_H
