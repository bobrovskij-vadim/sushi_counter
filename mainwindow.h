#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QVector>
#include <QPushButton>
#include <QTextEdit>
#include <QWidget>
#include <QMessageBox>
#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QLabel>
#include <QLineEdit>
#include <QDate>
#include <QTime>
#include <QWidget>
#include <QAction>
#include <QCloseEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    //-------Поля ввода-------
    QLineEdit *add_line_number;
    QLineEdit *add_line_position;
    QLineEdit *del_line_number;
    QLineEdit *del_line_position;
    QTextEdit *input_sequence;
    //--------Кнопки----------
    QPushButton *add_button;
    QPushButton *del_button;
    QPushButton *save_button;
    QPushButton *continue_button;
    QPushButton *clean_all;
    QPushButton *save_to_file;
    QPushButton *display_result_button;
    //---------Слои-----------
    QHBoxLayout *add_layout;
    QHBoxLayout *del_layout;
    QVBoxLayout *text_edit_layout;
    QVBoxLayout *add_H1_layout;
    QVBoxLayout *add_H2_layout;
    QVBoxLayout *add_H3_layout;
    QVBoxLayout *del_H1_layout;
    QVBoxLayout *del_H2_layout;
    QVBoxLayout *del_H3_layout;
    QHBoxLayout *add_label_layout;
    QHBoxLayout *del_label_layout;
    QHBoxLayout *save_layout;
    QHBoxLayout *control_panel;
    QVBoxLayout *main_layout;
    //-----Текстовые лайбы----
    QLabel *add_label;
    QLabel *add_label_number;
    QLabel *add_label_position;
    QLabel *del_label;
    QLabel *del_label_number;
    QLabel *del_label_position;
    QLabel *input_label;
    QLabel *empty;

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_add_button_clicked();

    void on_del_button_clicked();

    void on_display_result_clicked();

    void on_clean_all_clicked();

    void on_save_to_file_clicked();

    void on_save_button();

    void on_continue_button();

};

class Position
{
private:
    QString m_number;
    QString m_name;
    int m_sum;

public:

    Position()
    {
        m_number = " ";
        m_name = "-----";
        m_sum = 0;
    };
    Position(QString number, QString name = "-----", int sum = 0) : m_number(number), m_name(name), m_sum(sum) {}

    QString Get_m_number()
    {
      return m_number;
    }

    QString Get_m_name();
    int Get_m_sum();

    QString Set_m_number(QString num) { this->m_number = num; }
    QString Set_m_name(QString name) { this->m_name = name; }
    int Set_m_sum(int sum) { this->m_sum = sum; }

    Position& operator+=(const int units)
    {
        m_sum += units;
        return *this;
    }
    Position& operator-=(const int units)
    {
        m_sum -= units;
        return *this;
    }

};

#endif // MAINWINDOW_H
