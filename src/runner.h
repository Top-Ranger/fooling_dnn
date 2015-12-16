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

    void waitFinished();

private slots:
    void getProgress(qint32 progress, qint32 max, double, double);

private:
    Ui::Runner *ui;
    QFuture<void> _future;
};

#endif // RUNNER_H
