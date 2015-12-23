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

#include "runner.h"
#include "ui_runner.h"

#include <QtConcurrent>

namespace {
void runGa(GenericGeneticAlgorithm *ga)
{
    return ga->runGa();
}
}

GARunner::GARunner(GenericGeneticAlgorithm *ga, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Runner)
{
    ui->setupUi(this);
    this->setWindowFlags(((windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowCloseButtonHint));
    ui->progressBar->setValue(0);

    QObject::connect(ga, SIGNAL(ga_current_round(qint32,qint32,double,double)), this, SLOT(getProgress(qint32,qint32,double,double)));
    QObject::connect(ga, SIGNAL(ga_finished(double,double,qint32)), this, SLOT(getFinished(double,double,qint32)));
   _future = QtConcurrent::run(runGa, ga);
}

GARunner::~GARunner()
{
    delete ui;
}

void GARunner::getProgress(qint32 progress, qint32 max, double best, double average)
{
    ui->progressBar->setMaximum(max);
    ui->progressBar->setValue(progress);
    ui->fitness->setText(QString("%1").arg(best, 8));
    ui->a_fitness->setText(QString("%1").arg(average, 8));
}

void GARunner::getFinished(double, double, qint32)
{
    close();
}
