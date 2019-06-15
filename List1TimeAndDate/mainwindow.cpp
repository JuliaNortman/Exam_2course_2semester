#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tmr = new QTimer;
    tmr->setInterval(1000);
    connect(tmr, SIGNAL(timeout()), this, SLOT(updateTime()));
    tmr->start();

    setDate();
}

MainWindow::~MainWindow()
{
    tmr->stop();
    if(tmr) delete tmr;
    delete ui;
}

void MainWindow::updateTime()
{
    ui->timeLabel->setText(QTime::currentTime().toString());

    if(QTime::currentTime().minute() == 0 && QTime::currentTime().second() == 0)
    {
        setDate();
    }
}

void MainWindow::setDate()
{
    ui->dateLabel->setText(QString::number(QDate::currentDate().day())+"."+
                           QString::number(QDate::currentDate().month())+"."+
                           QString::number(QDate::currentDate().year()));
}
