#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>
#include "qdicethread.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

protected:
    void closeEvent(QCloseEvent * event);

private slots:
    //自定义槽函数
    void onthreadA_started();
    void onthreadA_finished();
    void onthreadA_newValue(int seq, int diceValue);

    void on_btnStartThread_clicked();

    void on_btnStopThread_clicked();

    void on_btnDiceBegin_clicked();

    void on_btnDiceEnd_clicked();

    void on_btnClear_clicked();

private:
    Ui::Dialog *ui;
    QDiceThread threadA;
};

#endif // DIALOG_H
