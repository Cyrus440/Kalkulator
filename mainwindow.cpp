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
bool powTrigger = false;
bool sqrtTrigger = false;
bool bmiTrigger = false;

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
    connect(ui->Power, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Sqrt, SIGNAL(released()), this,
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

    connect(ui->BMI, SIGNAL(released()), this,
            SLOT(BMIButtonPressed()));
    connect(ui->Clear, SIGNAL(released()), this,
            SLOT(ClearButtonPressed()));
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
    powTrigger = false;
    sqrtTrigger = false;
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
    } else if(QString::compare(butVal, "-", Qt::CaseInsensitive) == 0){
        subTrigger = true;
    } else if(QString::compare(butVal, "^x", Qt::CaseInsensitive) == 0){
        powTrigger = true;
    } else{
        sqrtTrigger = true;
    }
    ui->Display->setText("");
}

void MainWindow::EqualButtonPressed(){
    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dblDisplayValue = displayVal.toDouble();
    if(addTrigger || subTrigger || multTrigger || divTrigger || sinTrigger || cosTrigger || tanTrigger || powTrigger || sqrtTrigger || bmiTrigger){
        if(addTrigger){
            solution = calcVal + dblDisplayValue;
            ui->Display->setText(QString::number(solution));
        }else if(subTrigger){
            solution = calcVal - dblDisplayValue;
            ui->Display->setText(QString::number(solution));
        }else if(multTrigger){
            solution = calcVal * dblDisplayValue;
            ui->Display->setText(QString::number(solution));
        }else if(divTrigger){
            solution = calcVal / dblDisplayValue;
            ui->Display->setText(QString::number(solution));
        }else if(sinTrigger){
            solution = qSin(dblDisplayValue);
            ui->Display->setText(QString::number(solution));
        }else if(cosTrigger){
            solution = qCos(dblDisplayValue);
            ui->Display->setText(QString::number(solution));
        }else if(tanTrigger){
            solution = qTan(dblDisplayValue);
            ui->Display->setText(QString::number(solution));
        }else if(powTrigger){
            solution = qPow(calcVal, dblDisplayValue);
            ui->Display->setText(QString::number(solution));
        }else if(sqrtTrigger){
            solution = qSqrt(calcVal);
            ui->Display->setText(QString::number(solution));
        }else if(bmiTrigger){
            solution = calcVal / (qPow(dblDisplayValue/100 , 2));
            if (solution < 16){
                ui->Display->setText(QString::number(solution) + " - wyglodzenie");
            }else if((solution >= 16) && (solution <= 16.99) ){
                ui->Display->setText(QString::number(solution) + " - wychudzenie");
            }else if((solution >= 17) && (solution <= 18.49) ){
                ui->Display->setText(QString::number(solution) + " - niedowaga");
            }else if((solution >= 18.50) && (solution <= 24.99) ){
                ui->Display->setText(QString::number(solution) + " - poprana waga");
            }else if((solution >=25 ) && (solution <= 29.99) ){
                ui->Display->setText(QString::number(solution) + " - nadwaga");
            }else if((solution >= 30) && (solution <= 34.99) ){
                ui->Display->setText(QString::number(solution) + " - I st. otylosci");
            }else if((solution >= 35) && (solution <= 39.99) ){
                ui->Display->setText(QString::number(solution) + " - II st. otylosci");
            }else{
                ui->Display->setText(QString::number(solution) + " - otylosc skrajna");
            }
        }else{
            solution = dblDisplayValue;
        }
    }
    //ui->Display->setText(QString::number(solution));
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
    ui->Display->setText("");
}

void MainWindow::BMIButtonPressed(){
    bmiTrigger = false;
    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    if(QString::compare(butVal, "BMI", Qt::CaseInsensitive) == 0){
        bmiTrigger = true;
    }
    ui->Display->setText("");
}
void MainWindow::ClearButtonPressed(){
    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    if(QString::compare(butVal, "AC", Qt::CaseInsensitive) == 0){
        calcVal = 0.0;
        divTrigger = false;
        multTrigger = false;
        addTrigger = false;
        subTrigger = false;
        sinTrigger = false;
        cosTrigger = false;
        tanTrigger = false;
        powTrigger = false;
        sqrtTrigger = false;
        bmiTrigger = false;
    }
    ui->Display->setText(QString::number(calcVal));
}
