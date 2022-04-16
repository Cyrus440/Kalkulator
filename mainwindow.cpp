#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegularExpression>
#include <QtMath>

double calcVal = 0.0;
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;
bool sinTrigger = false;
bool cosTrigger = false;
bool tanTrigger = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcVal));
    QPushButton *numButtons[10];
    for(int i = 0; i<10; ++i){
        QString butName = "Button" + QString::number(i);
        numButtons[i] = MainWindow::findChild<QPushButton *>(butName);
        connect(numButtons[i], SIGNAL(released()), this,
                SLOT(NumPressed()));
    }

    connect(ui->Add, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));

    connect(ui->Equals, SIGNAL(released()), this,
            SLOT(EqualButtonPressed()));

    connect(ui->ChangeSign, SIGNAL(released()), this,
            SLOT(ChangeNumberSign()));

    connect(ui->sin, SIGNAL(released()), this,
            SLOT(TrygButtonPressed()));
    connect(ui->cos, SIGNAL(released()), this,
            SLOT(TrygButtonPressed()));
    connect(ui->tan, SIGNAL(released()), this,
            SLOT(TrygButtonPressed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::NumPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();
    if((displayVal.toDouble()== 0) || (displayVal.toDouble() == 0.0)){
        ui->Display->setText(butVal);
    } else{
        QString newVal = displayVal + butVal;
        double dblNewVal = newVal.toDouble();
        ui->Display->setText(QString::number(dblNewVal, 'g', 16));
    }
}

void MainWindow::MathButtonPressed(){
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
    QString displayVal= ui->Display->text();
    calcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    if(QString::compare(butVal, "/" , Qt::CaseInsensitive) == 0){
        divTrigger = true;
    } else if(QString::compare(butVal, "*", Qt::CaseInsensitive) == 0){
        multTrigger = true;
    } else if(QString::compare(butVal, "+", Qt::CaseInsensitive) == 0){
        addTrigger = true;
    } else{
        subTrigger = true;
    }
    ui->Display->setText("");
}

void MainWindow::EqualButtonPressed(){
    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dblDisplayValue = displayVal.toDouble();
    if(addTrigger || subTrigger || multTrigger || divTrigger || sinTrigger || cosTrigger || tanTrigger){
        if(addTrigger){
            solution = calcVal + dblDisplayValue;
        }else if(subTrigger){
            solution = calcVal - dblDisplayValue;
        }else if(multTrigger){
            solution = calcVal * dblDisplayValue;
        }else if(divTrigger){
            solution = calcVal / dblDisplayValue;
        }else if(sinTrigger){
            solution = qSin(dblDisplayValue);
        }else if(cosTrigger){
            solution = qCos(dblDisplayValue);
        }else{
            solution = qTan(dblDisplayValue);
        }
    }
    ui->Display->setText(QString::number(solution));
}

void MainWindow::ChangeNumberSign(){
    QString displayVal =  ui->Display->text();
    QRegularExpression reg("[-]?[0-9.]*");
    QRegularExpressionMatch match = reg.match(displayVal);
    if(match.hasMatch()){
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1*dblDisplayVal;
        ui->Display->setText(QString::number(dblDisplayValSign));
    }
}
void MainWindow::TrygButtonPressed(){
    sinTrigger = false;
    cosTrigger = false;
    tanTrigger = false;
    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    if(QString::compare(butVal, "sin" , Qt::CaseInsensitive) == 0){
        sinTrigger = true;
    }else if(QString::compare(butVal, "cos" , Qt::CaseInsensitive) == 0){
        cosTrigger = true;
    }else{
        tanTrigger = true;
    }
}
