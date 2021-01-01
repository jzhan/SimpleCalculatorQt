#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLineEdit>
#include <QPushButton>
#include <QChar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->line_op_display->clear();

    init();

    connect(ui->btn_key_0, SIGNAL(clicked()), this, SLOT(on_digitButton_clicked()));
    connect(ui->btn_key_1, SIGNAL(clicked()), this, SLOT(on_digitButton_clicked()));
    connect(ui->btn_key_2, SIGNAL(clicked()), this, SLOT(on_digitButton_clicked()));
    connect(ui->btn_key_3, SIGNAL(clicked()), this, SLOT(on_digitButton_clicked()));
    connect(ui->btn_key_4, SIGNAL(clicked()), this, SLOT(on_digitButton_clicked()));
    connect(ui->btn_key_5, SIGNAL(clicked()), this, SLOT(on_digitButton_clicked()));
    connect(ui->btn_key_6, SIGNAL(clicked()), this, SLOT(on_digitButton_clicked()));
    connect(ui->btn_key_7, SIGNAL(clicked()), this, SLOT(on_digitButton_clicked()));
    connect(ui->btn_key_8, SIGNAL(clicked()), this, SLOT(on_digitButton_clicked()));
    connect(ui->btn_key_9, SIGNAL(clicked()), this, SLOT(on_digitButton_clicked()));

    connect(ui->btn_op_ce, SIGNAL(clicked()), this, SLOT(on_operatorButton_clicked()));
    connect(ui->btn_op_c, SIGNAL(clicked()), this, SLOT(on_operatorButton_clicked()));
    connect(ui->btn_op_dot, SIGNAL(clicked()), this, SLOT(on_operatorButton_clicked()));
    connect(ui->btn_op_del, SIGNAL(clicked()), this, SLOT(on_operatorButton_clicked()));
    connect(ui->btn_op_plus, SIGNAL(clicked()), this, SLOT(on_operatorButton_clicked()));
    connect(ui->btn_op_minus, SIGNAL(clicked()), this, SLOT(on_operatorButton_clicked()));
    connect(ui->btn_op_mul, SIGNAL(clicked()), this, SLOT(on_operatorButton_clicked()));
    connect(ui->btn_op_div, SIGNAL(clicked()), this, SLOT(on_operatorButton_clicked()));
    connect(ui->btn_op_as, SIGNAL(clicked()), this, SLOT(on_operatorButton_clicked()));
}

void MainWindow::init() {
    is_decimal = false;
    op_state = false;
    str_digit = "0";
    result = 0;
    last_operator = 0;
}

void MainWindow::on_digitButton_clicked(){
    if(last_operator == '=') {
        init();

        ui->line_op_display->setText("");
    }

    op_state = false;

    QPushButton *btn_sender = qobject_cast<QPushButton*>(sender());
    if(str_digit == "0") str_digit = btn_sender->text();
    else str_digit = str_digit.append(btn_sender->text());

    ui->line_main_display->clear();
    ui->line_main_display->setText(str_digit);
}

void MainWindow::on_operatorButton_clicked(){
    QPushButton *btn_sender = qobject_cast<QPushButton*>(sender());

    if(btn_sender->objectName() == "btn_op_ce") {
        init();

        ui->line_main_display->setText(str_digit);
        ui->line_op_display->setText("");

        enableButton();
    } else if(btn_sender->objectName() == "btn_op_c") {
        if(last_operator == '=') return;

        str_digit = "0";
        is_decimal = false;

        ui->line_main_display->setText(str_digit);
    } else if(btn_sender->objectName() == "btn_op_dot") {
        if(is_decimal) return;

        is_decimal = true;
        str_digit = str_digit.append(btn_sender->text());
    } else if(btn_sender->objectName() == "btn_op_del") {
        if(str_digit == "0" or last_operator == '=') return;

        int len = str_digit.length() - 1;
        QChar last_digit = str_digit[len];

        if(last_digit == '.') {
            str_digit = str_digit.left(len - 1);
            is_decimal = false;
        } else {
            str_digit = str_digit.left(len);

            if(len - 1 >= 0 and str_digit[len - 1] == '.') {
                str_digit = str_digit.left(len - 1);
                is_decimal = false;
            }
        }

        if(str_digit == "") str_digit.append("0");

        ui->line_main_display->clear();
        ui->line_main_display->setText(str_digit);
    } else {
        if(!op_state or btn_sender->objectName() == "btn_op_as")
            calculate();

        op_state = true;

        if(btn_sender->objectName() == "btn_op_plus")
            last_operator = '+';
        else if(btn_sender->objectName() == "btn_op_minus")
            last_operator = '-';
        else if(btn_sender->objectName() == "btn_op_mul")
            last_operator = '*';
        else if(btn_sender->objectName() == "btn_op_div")
             last_operator = '/';
        else if(btn_sender->objectName() == "btn_op_as") {
            last_operator = '=';
            op_state = false;
            str_digit = QString::number(result);
        }

        ui->line_op_display->setText(QString(last_operator));
    }
}

void MainWindow::calculate() {
    switch(last_operator) {
        case '+':
            result += str_digit.toFloat();

            break;
        case '-':
            result -= str_digit.toFloat();

            break;
        case '*':
            result *= str_digit.toFloat();

            break;
        case '/':
            if(str_digit.toFloat() != 0)
                result /= str_digit.toFloat();
            else {
                ui->line_main_display->setText("NaN");
                disableButton();

                return;
            }

            break;
        default:
            result = str_digit.toFloat();
    }

    ui->line_main_display->setText(QString::number(result));

    str_digit = "0";
    is_decimal = false;
}

void MainWindow::disableButton() {
    ui->btn_key_0->setEnabled(false);
    ui->btn_key_1->setEnabled(false);
    ui->btn_key_2->setEnabled(false);
    ui->btn_key_3->setEnabled(false);
    ui->btn_key_4->setEnabled(false);
    ui->btn_key_5->setEnabled(false);
    ui->btn_key_6->setEnabled(false);
    ui->btn_key_7->setEnabled(false);
    ui->btn_key_8->setEnabled(false);
    ui->btn_key_9->setEnabled(false);

    ui->btn_op_c->setEnabled(false);
    ui->btn_op_dot->setEnabled(false);
    ui->btn_op_plus->setEnabled(false);
    ui->btn_op_minus->setEnabled(false);
    ui->btn_op_mul->setEnabled(false);
    ui->btn_op_div->setEnabled(false);
    ui->btn_op_as->setEnabled(false);
    ui->btn_op_del->setEnabled(false);
}

void MainWindow::enableButton() {
    ui->btn_key_0->setEnabled(true);
    ui->btn_key_1->setEnabled(true);
    ui->btn_key_2->setEnabled(true);
    ui->btn_key_3->setEnabled(true);
    ui->btn_key_4->setEnabled(true);
    ui->btn_key_5->setEnabled(true);
    ui->btn_key_6->setEnabled(true);
    ui->btn_key_7->setEnabled(true);
    ui->btn_key_8->setEnabled(true);
    ui->btn_key_9->setEnabled(true);

    ui->btn_op_c->setEnabled(true);
    ui->btn_op_dot->setEnabled(true);
    ui->btn_op_plus->setEnabled(true);
    ui->btn_op_minus->setEnabled(true);
    ui->btn_op_mul->setEnabled(true);
    ui->btn_op_div->setEnabled(true);
    ui->btn_op_as->setEnabled(true);
    ui->btn_op_del->setEnabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}
