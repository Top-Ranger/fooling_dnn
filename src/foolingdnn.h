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

#ifndef FOOLINGDNN_H
#define FOOLINGDNN_H

#include <QMainWindow>
#include <QStringListModel>

namespace Ui {
class FoolingDNN;
}

class FoolingDNN : public QMainWindow
{
    Q_OBJECT

public:
    explicit FoolingDNN(QWidget *parent = 0);
    ~FoolingDNN();

private slots:
    void on_actionQuit_triggered();
    void on_actionAbout_triggered();
    void on_actionAbout_Qt_triggered();
    void on_pushButton_clicked();

private:
    Ui::FoolingDNN *ui;
    QStringListModel *_model;
};

#endif // FOOLINGDNN_H
