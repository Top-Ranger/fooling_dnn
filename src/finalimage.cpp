#include "finalimage.h"
#include "ui_finalimage.h"

#include <QFileDialog>

FinalImage::FinalImage(QImage image, double confidence, QString class_string, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FinalImage)
{
    ui->setupUi(this);
    ui->confidence->setText(QString("%1").arg(confidence));
    ui->classlabel->setText(class_string);
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addPixmap(QPixmap::fromImage(image));
    scene->setSceneRect(image.rect());
    ui->graphicsView->setScene(scene);
}

FinalImage::~FinalImage()
{
    delete ui;
}

void FinalImage::on_pushButton_clicked()
{
    QString saveTo = QFileDialog::getSaveFileName(this);
    if(saveTo != "")
    {

        QImage image;
        QPainter painter(&image);
        painter.setRenderHint(QPainter::SmoothPixmapTransform);
        ui->graphicsView->scene()->render(&painter);
        image.save(saveTo);
    }
}
