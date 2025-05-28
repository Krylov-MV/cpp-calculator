#pragma once

#include "calculator.h"
#include "enums.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    void SetInputText(const std::string& text);
    void SetErrorText(const std::string& text);
    void SetFormulaText(const std::string& text);
    void SetMemText(const std::string& text);
    void SetExtraKey(const std::optional<std::string>& key);
    void SetDigitKeyCallback(std::function<void(int key)> cb) { digit_cb_ = cb; }
    void SetProcessOperationKeyCallback(std::function<void(Operation key)> cb) { operation_cb_ = cb; }
    void SetProcessControlKeyCallback(std::function<void(ControlKey key)> cb) { control_cb_ = cb; }
    void SetControllerCallback(std::function<void(ControllerType controller)> cb) { controller_cb_ = cb; }

private slots:
    void on_tb_zero_clicked();
    void on_tb_one_clicked();
    void on_tb_two_clicked();
    void on_tb_three_clicked();
    void on_tb_four_clicked();
    void on_tb_five_clicked();
    void on_tb_six_clicked();
    void on_tb_seven_clicked();
    void on_tb_eight_clicked();
    void on_tb_nine_clicked();
    void on_tb_add_clicked();
    void on_tb_substract_clicked();
    void on_tb_multiplicate_clicked();
    void on_tb_divide_clicked();
    void on_tb_power_clicked();
    void on_tb_comma_clicked();
    void on_tb_negate_clicked();
    void on_tb_reset_clicked();
    void on_tb_equal_clicked();
    void on_tb_clear_clicked();
    void on_tb_ms_clicked();
    void on_tb_ml_clicked();
    void on_tb_mc_clicked();
    void on_tb_plus_minus_clicked();
    void on_tb_backspace_clicked();
    void on_tb_extra_clicked();
    void on_cmb_controller_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;

    std::function<void(Operation key)> operation_cb_;
    std::function<void(int key)> digit_cb_;
    std::function<void(ControlKey key)> control_cb_;
    std::function<void(ControllerType controller)> controller_cb_;

    const std::pair<QString, ControllerType> controller_types_[7] = {
        {"double", ControllerType::DOUBLE},
        {"float", ControllerType::FLOAT},
        {"uint8_t", ControllerType::UINT8_T},
        {"int", ControllerType::INT},
        {"int64_t", ControllerType::INT64_T},
        {"size_t", ControllerType::SIZE_T},
        {"Rational", ControllerType::RATIONAL}
    };
};
