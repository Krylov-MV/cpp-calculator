#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->cmb_controller->addItems({"double", "float", "uint8_t", "int",
                                  "int64_t", "size_t", "Rational"});

    SetInputText("0");
    SetFormulaText("");
    SetMemText("");
    SetExtraKey(std::nullopt);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetInputText(const std::string& text) {
    ui->l_result->setStyleSheet("");
    ui->l_result->setText(QString::fromStdString(text));
}

void MainWindow::SetErrorText(const std::string& text) {
    ui->l_result->setStyleSheet("color: red;");
    ui->l_result->setText(QString::fromStdString(text));
}

void MainWindow::SetFormulaText(const std::string& text) {
    ui->l_formula->setText(QString::fromStdString(text));
}

void MainWindow::SetMemText(const std::string& text) {
    ui->l_memory->setText(QString::fromStdString(text));
}

void MainWindow::SetExtraKey(const std::optional<std::string>& key) {
    if (key) {
        ui->tb_extra->setText(QString::fromStdString(*key));
        ui->tb_extra->show();
    } else {
        ui->tb_extra->hide();
    }
}

void MainWindow::on_cmb_controller_currentIndexChanged(int index) {
    Q_UNUSED(index);
    if (controller_cb_) {
        QString type_str = ui->cmb_controller->currentText();

        for (const auto& [name, type] : controller_types_) {
            if (name == type_str) {
                controller_cb_(type);
                return;
            }
        }
    }
}

void MainWindow::on_tb_add_clicked() {
    if (operation_cb_) {
        operation_cb_(Operation::ADDITION);
    }
}

void MainWindow::on_tb_substract_clicked() {
    if (operation_cb_) {
        operation_cb_(Operation::SUBTRACTION);
    }
}

void MainWindow::on_tb_multiplicate_clicked() {
    if (operation_cb_) {
        operation_cb_(Operation::MULTIPLICATION);
    }
}

void MainWindow::on_tb_divide_clicked() {
    if (operation_cb_) {
        operation_cb_(Operation::DIVISION);
    }
}

void MainWindow::on_tb_power_clicked() {
    if (operation_cb_) {
        operation_cb_(Operation::POWER);
    }
}

void MainWindow::on_tb_comma_clicked() {
    if (control_cb_) {
        control_cb_(ControlKey::EXTRA_KEY);
    }
}

void MainWindow::on_tb_negate_clicked() {
    if (control_cb_) {
        control_cb_(ControlKey::PLUS_MINUS);
    }
}

void MainWindow::on_tb_reset_clicked() {
    if (control_cb_) {
        control_cb_(ControlKey::CLEAR);
    }
}

void MainWindow::on_tb_zero_clicked() {
    if (digit_cb_) {
        digit_cb_(0);
    }
}

void MainWindow::on_tb_one_clicked() {
    if (digit_cb_) {
        digit_cb_(1);
    }
}

void MainWindow::on_tb_two_clicked() {
    if (digit_cb_) {
        digit_cb_(2);
    }
}

void MainWindow::on_tb_three_clicked() {
    if (digit_cb_) {
        digit_cb_(3);
    }
}

void MainWindow::on_tb_four_clicked() {
    if (digit_cb_) {
        digit_cb_(4);
    }
}

void MainWindow::on_tb_five_clicked() {
    if (digit_cb_) {
        digit_cb_(5);
    }
}

void MainWindow::on_tb_six_clicked() {
    if (digit_cb_) {
        digit_cb_(6);
    }
}

void MainWindow::on_tb_seven_clicked() {
    if (digit_cb_) {
        digit_cb_(7);
    }
}

void MainWindow::on_tb_eight_clicked() {
    if (digit_cb_) {
        digit_cb_(8);
    }
}

void MainWindow::on_tb_nine_clicked() {
    if (digit_cb_) {
        digit_cb_(9);
    }
}

void MainWindow::on_tb_equal_clicked() {
    if (control_cb_) {
        control_cb_(ControlKey::EQUALS);
    }
}

void MainWindow::on_tb_clear_clicked() {
    if (control_cb_) {
        control_cb_(ControlKey::CLEAR);
    }
}

void MainWindow::on_tb_ms_clicked() {
    if (control_cb_) {
        control_cb_(ControlKey::MEM_SAVE);
    }
}

void MainWindow::on_tb_ml_clicked() {
    if (control_cb_) {
        control_cb_(ControlKey::MEM_LOAD);
    }
}

void MainWindow::on_tb_mc_clicked() {
    if (control_cb_) {
        control_cb_(ControlKey::MEM_CLEAR);
    }
}

void MainWindow::on_tb_plus_minus_clicked() {
    if (control_cb_) {
        control_cb_(ControlKey::PLUS_MINUS);
    }
}

void MainWindow::on_tb_backspace_clicked() {
    if (control_cb_) {
        control_cb_(ControlKey::BACKSPACE);
    }
}

void MainWindow::on_tb_extra_clicked() {
    if (control_cb_) {
        control_cb_(ControlKey::EXTRA_KEY);
    }
}
