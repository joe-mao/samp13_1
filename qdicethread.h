#ifndef QDICETHREAD_H
#define QDICETHREAD_H

#include <QThread>


class QDiceThread : public QThread
{
    Q_OBJECT

private:
    int m_seq = 0;//掷骰子的线程类
    int m_diceValue;//骰子点数
    bool m_Paused = true;//暂停
    bool m_stop = false;//停止

protected:
    void run() Q_DECL_OVERRIDE;//线程任务

public:
    QDiceThread();
    void diceBegin();//掷一次骰子
    void dicePause();//暂停
    void stopThread();//结束线程

signals:
    void newValue(int seq, int diceVaule);//产生新点数的信号



};

#endif // QDICETHREAD_H
