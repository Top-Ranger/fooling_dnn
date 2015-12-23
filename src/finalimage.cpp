/*
 * Copyright (C) 2015 Marcus Soll
 * This file is part of fooling_dnn.
 *
 * fooling_dnn is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * fooling_dnn is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with fooling_dnn. If not, see <http://www.gnu.org/licenses/>.
 */

#include "finalimage.h"
#include "ui_finalimage.h"

#include <QFileDialog>

FinalImage::FinalImage(QImage image, double confidence, QString class_string, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FinalImage),
    _image(image)
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
        _image.save(saveTo);
    }
}
