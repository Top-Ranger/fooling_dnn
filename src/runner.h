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

#ifndef RUNNER_H
#define RUNNER_H

#include <QDialog>
#include <ga/genericgeneticalgorithm.h>

#include <QFuture>

namespace Ui {
class Runner;
}

class GARunner : public QDialog
{
    Q_OBJECT

public:
    explicit GARunner(GenericGeneticAlgorithm *ga, QWidget *parent = 0);
    ~GARunner();

private slots:
    void getProgress(qint32 progress, qint32 max, double  best, double average);
    void getFinished(double, double, qint32);

private:
    Ui::Runner *ui;
    QFuture<void> _future;
};

#endif // RUNNER_H
