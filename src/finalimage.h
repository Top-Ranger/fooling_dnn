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

#ifndef FINALIMAGE_H
#define FINALIMAGE_H

#include <QDialog>
#include <QImage>

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
    QImage _image;
};

#endif // FINALIMAGE_H
