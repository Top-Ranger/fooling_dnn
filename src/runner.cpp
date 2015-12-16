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
   _future = QtConcurrent::run(runGa, ga);
}

GARunner::~GARunner()
{
    delete ui;
}

void GARunner::waitFinished()
{
    while(!_future.isFinished())
    {
        QCoreApplication::processEvents();
    }
}

void GARunner::getProgress(qint32 progress, qint32 max, double, double)
{
    ui->progressBar->setMaximum(max);
    ui->progressBar->setValue(progress);
}
