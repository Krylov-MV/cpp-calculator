#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->l_result->setText("0");
    ui->l_memory->setText("");
    ui->l_formula->setText("");

    SetText("0");
}

MainWindow::~MainWindow() {
    delete ui;
}

QString MainWindow::RemoveTrailingZeroes(const QString &text) const {
    for (qsizetype i = 0; i < text.size(); ++i) {
        if (text[i] != '0') {
            return text.mid(i);
        }
    }
    return "";
}

QString MainWindow::NormalizeNumber(const QString &text) const {
    if (text.isEmpty()) {
        return "0";
    }
    if (text.startsWith('.')) {
        // Рекурсивный вызов.
        return NormalizeNumber("0" + text);
    }
    if (text.startsWith('-')) {
        // Рекурсивный вызов.
        return "-" + NormalizeNumber(text.mid(1));
    }
    if (text.startsWith('0') && !text.startsWith("0.")) {
        return NormalizeNumber(RemoveTrailingZeroes(text));
    }
    return text;
}

QString MainWindow::OpToString(Operation op) const {
    switch(op) {
    case Operation::NO_OPERATION: return "";
    case Operation::ADDITION: return "+";
    case Operation::DIVISION: return "÷";
    case Operation::MULTIPLICATION: return "×";
    case Operation::SUBTRACTION: return "−";
    case Operation::POWER: return "^";
    }
}

void MainWindow::SetText(const QString& text) {
    input_number_ = NormalizeNumber(RemoveTrailingZeroes(text));;
    ui->l_result->setText(input_number_);

    active_number_ = input_number_.toDouble();
}

void MainWindow::AddText(const QString& suffix){
    input_number_ += suffix;
    SetText(input_number_);
}

void MainWindow::SetOperation(Operation op) {
    if (current_operation_ == Operation::NO_OPERATION) {
        calculator_.Set(active_number_);
    }

    current_operation_ = op;

    ui->l_formula->setText(QString ("%1 %2").arg(calculator_.GetNumber()).arg(OpToString(current_operation_)));

    input_number_.clear();
}

void MainWindow::on_tb_one_clicked()
{
    AddText("1");
}


void MainWindow::on_tb_two_clicked()
{
    AddText("2");
}


void MainWindow::on_tb_three_clicked()
{
    AddText("3");
}


void MainWindow::on_tb_four_clicked()
{
    AddText("4");
}


void MainWindow::on_tb_five_clicked()
{
    AddText("5");
}


void MainWindow::on_tb_six_clicked()
{
    AddText("6");
}


void MainWindow::on_tb_seven_clicked()
{
    AddText("7");
}


void MainWindow::on_tb_eight_clicked()
{
    AddText("8");
}


void MainWindow::on_tb_nine_clicked()
{
    AddText("9");
}


void MainWindow::on_tb_zero_clicked()
{
    AddText("0");
}


void MainWindow::on_tb_comma_clicked()
{
    if (input_number_.indexOf(".") == -1) {
        AddText(".");
    }
}


void MainWindow::on_tb_negate_clicked()
{
    if (input_number_.startsWith("-")) {
        input_number_ = input_number_.mid(1);
    } else {
        input_number_ = "-" + input_number_;
    }
    SetText(input_number_);
}


void MainWindow::on_tb_backspace_clicked()
{
    input_number_.chop(1);
    SetText(input_number_);
}


void MainWindow::on_tb_power_clicked()
{
    SetOperation(Operation::POWER);
}


void MainWindow::on_tb_divide_clicked()
{
    SetOperation(Operation::DIVISION);
}


void MainWindow::on_tb_multiplicate_clicked()
{
    SetOperation(Operation::MULTIPLICATION);
}


void MainWindow::on_tb_substract_clicked()
{
    SetOperation(Operation::SUBTRACTION);
}


void MainWindow::on_tb_add_clicked()
{
    SetOperation(Operation::ADDITION);
}


void MainWindow::on_tb_equal_clicked()
{
    if (current_operation_ != Operation::NO_OPERATION) {
        ui->l_formula->setText(QString ("%1 %2 %3 =").arg(calculator_.GetNumber()).arg(OpToString(current_operation_)).arg(active_number_));

        switch(current_operation_) {
        case Operation::ADDITION:
            calculator_.Add(active_number_);
            break;
        case Operation::SUBTRACTION:
            calculator_.Sub(active_number_);
            break;
        case Operation::MULTIPLICATION:
            calculator_.Mul(active_number_);
            break;
        case Operation::DIVISION:
            calculator_.Div(active_number_);
            break;
        case Operation::POWER:
            calculator_.Pow(active_number_);
            break;
        }

        active_number_ = calculator_.GetNumber();
        ui->l_result->setText(QString::number(active_number_));
        input_number_.clear();

        current_operation_ = Operation::NO_OPERATION;
    }
}


void MainWindow::on_tb_reset_clicked()
{
    current_operation_ = Operation::NO_OPERATION;
    ui->l_formula->setText("");
    SetText("0");
}


void MainWindow::on_tb_mc_clicked()
{
    memory_is_saved_ = false;
    ui->l_memory->setText("");
}


void MainWindow::on_tn_mr_clicked()
{
    if (memory_is_saved_) {
        active_number_ = saved_number_;
        ui->l_result->setText(QString::number(active_number_));
        input_number_ = 0;
    }
}


void MainWindow::on_tb_ms_clicked()
{
    saved_number_ = active_number_;
    memory_is_saved_ = true;
    ui->l_memory->setText("M");
}

