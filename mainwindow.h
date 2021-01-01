#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //void on_pushButton_clicked(QPushButton *);

    void on_digitButton_clicked();
    void on_operatorButton_clicked();

private:
    Ui::MainWindow *ui;
    QString str_digit;
    float result;
    char last_operator;

    bool is_decimal;
    bool op_state;

    void calculate();
    void disableButton();
    void enableButton();
    void init();
};
#endif // MAINWINDOW_H
