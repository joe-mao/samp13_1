#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(&threadA, SIGNAL(started()), this, SLOT(onthreadA_started()));
    connect(&threadA, SIGNAL(finished()), this, SLOT(onthreadA_finished()));
    connect(&threadA, SIGNAL(newValue(int, int)), this, SLOT(onthreadA_newValue(int, int)));

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::closeEvent(QCloseEvent *event)
{
    //窗口关闭事件，必须结束线程
    if(threadA.isRunning()){
        threadA.stopThread();
        threadA.wait();
    }
    event->accept();
}

void Dialog::onthreadA_started()
{
    //线程的started()信号的响应槽函数
    this->ui->LabA->setText("Thread状态: thread started");
}

void Dialog::onthreadA_finished()
{
    //线程的finished()信号的响应槽函数
    this->ui->LabA->setText("Thread状态: thread finished");

}

void Dialog::onthreadA_newValue(int seq, int diceValue)
{
    //QDiceThread的newValue()信号的响应槽函数，显示骰子次数和点数
    QString str = QString::asprintf("第 %d 次掷骰子， 点数为: %d", seq, diceValue);
    this->ui->plainTextEdit->appendPlainText(str);
    QPixmap pic;//图片显示
    QString filename = QString::asprintf(":/image/dice/%d.PNG", diceValue);
    pic.load(filename);
    this->ui->LabPic->setPixmap(pic);
}

void Dialog::on_btnStartThread_clicked()
{
    //启动线程 按钮
    threadA.start();
    this->ui->btnStartThread->setEnabled(false);
    this->ui->btnStopThread->setEnabled(true);
    this->ui->btnDiceBegin->setEnabled(true);
    this->ui->btnDiceEnd->setEnabled(false);

}

void Dialog::on_btnStopThread_clicked()
{
    //结束线程 按钮
    threadA.stopThread();//结束线程的run（）函数的运行
    threadA.wait();
    this->ui->btnStartThread->setEnabled(true);
    this->ui->btnStopThread->setEnabled(false);
    this->ui->btnDiceBegin->setEnabled(false);
    this->ui->btnDiceEnd->setEnabled(false);
}



void Dialog::on_btnDiceBegin_clicked()
{
    //开始 掷骰子按钮
    threadA.diceBegin();
    this->ui->btnDiceBegin->setEnabled(false);
    this->ui->btnDiceEnd->setEnabled(true);
}



void Dialog::on_btnDiceEnd_clicked()
{
    //暂停 掷骰子按钮
    threadA.dicePause();
    this->ui->btnDiceBegin->setEnabled(true);
    this->ui->btnDiceEnd->setEnabled(false);
}



void Dialog::on_btnClear_clicked()
{
    //清空文本按钮
    this->ui->plainTextEdit->clear();
}
