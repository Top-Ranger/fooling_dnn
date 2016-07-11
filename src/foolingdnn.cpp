/*
 * Copyright (C) 2015,2016 Marcus Soll
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

#include "foolingdnn.h"
#include "ui_foolingdnn.h"

#include "finalimage.h"
#include "runner.h"

#include <QMessageBox>
#include <QStringList>

#include <ga/cuckoosearch.h>
#include "simulation/alexnetsimulation.h"
#include <network/abstractneuralnetwork.h>
#include <network/imagedirectencodinggeneratornetwork.h>
#include <network/imagecppngeneratornetwork.h>

FoolingDNN::FoolingDNN(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FoolingDNN),
    _model(new QStringListModel(this))
{
    ui->setupUi(this);

    QStringList list;
    list << "Direct encoding";
    list << "CPPN";

    _model->setStringList(list);

    ui->listView->setModel(_model);
}

FoolingDNN::~FoolingDNN()
{
    delete ui;
}

void FoolingDNN::on_actionQuit_triggered()
{
    QApplication::quit();
}

void FoolingDNN::on_actionAbout_triggered()
{
    QMessageBox::about(this,
                       tr("About"),
                       tr( "Fooling DNN\n\n"
                        "A small application to generate fooling images for the AlexNet DNN.\n\n"
                           "This application uses qnn and qnn-image-generators which are licensed under the terms of the GNU Lesser General Public License version 3 or (at your opinion) any later version. \n\n"
                           "This application uses the caffe framework which is licensed under the 2-clause BSD license."));
}

void FoolingDNN::on_actionAbout_Qt_triggered()
{
    QApplication::aboutQt();
}

void FoolingDNN::on_pushButton_clicked()
{
    QString selection = ui->listView->currentIndex().data().toString();

    AbstractNeuralNetwork *network = NULL;

    if(selection == "")
    {
        QMessageBox::warning(this,
                             tr("Select generation mode"),
                             tr("Please select an image generation mode"));
        return;
    }
    else if(selection == "Direct encoding")
    {
        ImageDirectEncodingGeneratorNetwork::config config;
        config.image_path = "./image.png";
        config.width = 227;
        config.height = 227;
        network = new ImageDirectEncodingGeneratorNetwork(0, 0, config);
    }
    else if(selection == "CPPN")
    {
        ImageCPPNGeneratorNetwork::config config;
        config.image_path = "./image.png";
        config.width = 227;
        config.height = 227;
        config.max_size = 50;
        network = new ImageCPPNGeneratorNetwork(0, 0, config);
    }
    else
    {
        QMessageBox::critical(this,
                              tr("Unknown selection"),
                              QString(tr("Unknown selection: '%1'.")).arg(selection));
        return;
    }

    AlexNetSimulation *simulation = new AlexNetSimulation();
    GenericGeneticAlgorithm *ga = new CuckooSearch(network, simulation, 300, 0.99, 500);

    GARunner runner(ga, this);
    runner.exec();

    GenericGene *gene = ga->bestGene();
    simulation->initialise(network, gene);
    simulation->getScore();

    QImage image("./image.png");

    FinalImage window(image, ga->bestFitness(), QString("%1").arg(simulation->getClass()), this);
    window.exec();

    // Cleanup
    delete gene;
    delete network;
}
