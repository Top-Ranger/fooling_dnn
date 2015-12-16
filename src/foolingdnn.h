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
    void enableUiActions(bool enabled);

    Ui::FoolingDNN *ui;
    QStringListModel *_model;
};

#endif // FOOLINGDNN_H
