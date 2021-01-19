#include "mainwindow.h"

QVector <Position> position_list;
QFile temp_save("temp_file.csv");

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

    setWindowTitle("СУШИ");

    //--------------Текстовые лайбы------------------
    {
    add_label = new QLabel("ДОБАВИТЬ");
    add_label_number = new QLabel("Количество:");
    add_label_position = new QLabel("Номер позиции:");
    empty = new QLabel("  ");

    del_label = new QLabel("УДАЛИТЬ");
    del_label_number = new QLabel("Количество:");
    del_label_position = new QLabel("Номер позиции:");
    input_label = new QLabel("ПОСЛЕДОВАТЕЛЬНОСТЬ ВВОДА");
    }
    //-------------------Кнопки----------------------
    {
    add_button = new QPushButton("&Добавить", this);
    add_button->setShortcut(Qt::Key_Return);
    del_button = new QPushButton("&Удалить", this);
    del_button->setToolTip("Если просто нажать 'Удалить' - удалится последнмй ввод.\nЕсли заполнить поля, отнимется заданное кол-во от заданной позиции");
    clean_all = new QPushButton("&Очистить все", this);
    clean_all->setToolTip("Обнуляет все ввeденные данные");
    save_button = new QPushButton("&Сохранить", this);
    save_button->setToolTip("Сохранение");
    continue_button = new QPushButton("&Продолжить", this);
    continue_button->setToolTip("Заполнит данные из последнего сохранения");
    save_to_file = new QPushButton("&Сохранить в файл", this);
    save_to_file->setToolTip("Файл сохраняется в ту же папку где лежит программа");
    display_result_button = new QPushButton("&Вывести результат", this);
    }
    //-----------------Поля ввода--------------------
    {
    add_line_number = new QLineEdit;
    add_line_position = new QLineEdit;

    del_line_number = new QLineEdit;
    del_line_position = new QLineEdit;

    input_sequence = new QTextEdit;
    }
    //--------------------Слои-----------------------
    {
    add_layout = new QHBoxLayout;
    add_label_layout = new QHBoxLayout;
    del_layout = new QHBoxLayout;
    text_edit_layout = new QVBoxLayout;
    add_H1_layout = new QVBoxLayout;
    add_H2_layout = new QVBoxLayout;
    add_H3_layout = new QVBoxLayout;
    del_label_layout = new QHBoxLayout;
    del_H1_layout = new QVBoxLayout;
    del_H2_layout = new QVBoxLayout;
    del_H3_layout = new QVBoxLayout;
    save_layout = new QHBoxLayout;
    control_panel = new QHBoxLayout;
    main_layout = new QVBoxLayout;
    }
    //-----------Наложение объектов на слои----------
{
    add_layout->addWidget(add_line_number);
    add_layout->addWidget(add_line_position);
    add_layout->addWidget(add_button);

    add_H1_layout->addWidget(add_label_number);
    add_H1_layout->addWidget(add_line_number);

    add_H2_layout->addWidget(add_label_position);
    add_H2_layout->addWidget(add_line_position);

    add_H3_layout->addWidget(empty);
    add_H3_layout->addWidget(add_button);

    add_label_layout->addLayout(add_H1_layout);
    add_label_layout->addLayout(add_H2_layout);
    add_label_layout->addLayout(add_H3_layout);

    del_H1_layout->addWidget(del_label_number);
    del_H1_layout->addWidget(del_line_number);

    del_H2_layout->addWidget(del_label_position);
    del_H2_layout->addWidget(del_line_position);

    del_H3_layout->addWidget(empty);
    del_H3_layout->addWidget(del_button);

    del_label_layout->addLayout(del_H1_layout);
    del_label_layout->addLayout(del_H2_layout);
    del_label_layout->addLayout(del_H3_layout);

    save_layout->addWidget(save_button);
    save_layout->addWidget(continue_button);

    control_panel->addWidget(clean_all);
    control_panel->addWidget(save_to_file);
    control_panel->addWidget(display_result_button);

    main_layout->addWidget(add_label);
    main_layout->addLayout(add_label_layout);
    main_layout->addWidget(del_label);
    main_layout->addLayout(del_label_layout);
    main_layout->addWidget(input_label);
    main_layout->addWidget(input_sequence);
    main_layout->addLayout(save_layout);
    main_layout->addLayout(control_panel);

    QWidget *wgt = new QWidget(this);
    wgt->setLayout(main_layout);
    setCentralWidget(wgt);

 //   setLayout(main_layout);
    }
    //-----------Считывание файла с данными----------
    {
    QFile data_file("database.csv");
    if(!data_file.open(QFile::ReadOnly))
    {
        QMessageBox::information(this,"Oшибка", "Не открылся файл с ассортиментом!");
    }

    QTextStream stream(&data_file);

    QString position;

    while(!stream.atEnd())
    {
        position = stream.readLine();
        QString left_part = position.left(position.indexOf(','));
        QString right_part = position.section(',',1);
        Position a(left_part, right_part, 0);
        position_list.push_back(a);
    }

    data_file.flush(); // Сбрасывание
    data_file.close();

    /*{---------Цикл вывода данных из файла-----------
    {
    for (int i = 0; i < position_list.size(); i++)
    {
       input_sequence->append(QString("%1. %2").arg(position_list[i].Get_m_number()).arg(position_list[i].Get_m_name()));

    }*/
    }
    //---------------Сигналы и слоты-----------------
    {
    connect(add_button, SIGNAL(clicked()),this,SLOT(on_add_button_clicked()));
    connect(del_button, SIGNAL(clicked()),this,SLOT(on_del_button_clicked()));
    connect(clean_all,SIGNAL(clicked()),this,SLOT(on_clean_all_clicked()));
    connect(display_result_button, SIGNAL(clicked()),this,SLOT(on_display_result_clicked()));
    connect(save_button, SIGNAL(clicked()),this,SLOT(on_save_button()));
    connect(continue_button, SIGNAL(clicked()),this,SLOT(on_continue_button()));
    connect(save_to_file,SIGNAL(clicked()),this,SLOT(on_save_to_file_clicked()));
    }

}

MainWindow::~MainWindow()
{
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox message;
    message.setText("Ты точно хочешь закрыть программу?");
    message.addButton("Да", QMessageBox::YesRole);
    message.addButton("Нет", QMessageBox::NoRole);
    message.addButton("Отмена", QMessageBox::RejectRole);
    int result = message.exec();
    if (result == 0)
    {
        event->accept();
    } else if (result == 1)
    {
        event->ignore();
    } else
    {
        event->ignore();
    }

}


QString Position::Get_m_name()
{
    return m_name;
}

int Position::Get_m_sum()
{
     return m_sum;
}

int counter = 0;       // для вывода количества вводов
QString add_Position;  // номер позици для ввода
int add_Units;         // вводимое количество

void MainWindow::on_add_button_clicked()
{
    add_Position = add_line_position->text();
    add_Units = add_line_number->text().toInt();

    for (int i = 1; i < position_list.size(); i++)
    {
        if (add_Position == position_list[i].Get_m_number())
        {
            position_list[i] += add_Units;
            counter++;
            input_sequence->append(QString("%1. %2 %3: %4").arg(counter).arg(position_list[i].Get_m_number()).arg(position_list[i].Get_m_name()).arg(add_Units));
        }


        add_line_position->clear();
    }

}

void MainWindow::on_del_button_clicked()
{
    QString del_Position = del_line_position->text();
    int del_Units = del_line_number->text().toInt();

    if (del_Position.isEmpty())
    {
           int del_number = add_Position.toInt(); // переменная для удаления предидущего ввода б
           position_list[del_number] -= add_Units;
           input_sequence->append(QString("Previous input was deleted"));
    }
    else
    {
        for (int i = 1; i < position_list.size(); i++)
        {
            if (del_Position == position_list[i].Get_m_number())
            {
                position_list[i] -= del_Units;
                counter++;
                input_sequence->append(QString("%1. %2 %3 - deleted %4").arg(counter).arg(position_list[i].Get_m_number()).arg(position_list[i].Get_m_name()).arg(del_Units));
            }
        }
    }


}

void MainWindow::on_clean_all_clicked()
{

    QMessageBox* pmbx =
                        new QMessageBox("MessageBox",
                        "Ты точно хочешь все удалить?",
                        QMessageBox::Information,
                        QMessageBox::Yes,
                        QMessageBox::No,
                        QMessageBox::Cancel | QMessageBox::Escape);
    int n = pmbx->exec();
    delete pmbx;
    if (n == QMessageBox::Yes)
    {

        for (int i = 1; i < position_list.size(); i++)
        {
            position_list[i].Set_m_sum(0);
        }

        input_sequence->clear();
        add_line_number->clear();
        add_line_position->clear();
    }

}

void MainWindow::on_save_to_file_clicked()
{

    QString file_name = QDate::currentDate().toString("'report_'yyyy_MM_dd'.ods'");

    QFile save_file(file_name);

    if (!save_file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::information(this, "Ошибка", "Файл не открылся!");
    }

    QTextStream stream(&save_file);

    for (int i = 0; i < position_list.size(); i++)
    {
        //if(position_list[i].Get_m_sum() > 0) если решит что вывод нужен только заполненных позиций
        stream << position_list[i].Get_m_number() << ", " << position_list[i].Get_m_name() << ", " << position_list[i].Get_m_sum() << "\n";
    }

    save_file.close();


}

void MainWindow::on_save_button()
{
    if (!temp_save.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::information(this, "Ошибка", "Файл для сохранения не существует!");
    }

    QTextStream stream(&temp_save);

    for (int i = 0; i < position_list.size(); i++)
    {
        stream << position_list[i].Get_m_number() << ", " << position_list[i].Get_m_name() << ", " << position_list[i].Get_m_sum() << "\n";
    }

    temp_save.close();

}

void MainWindow::on_continue_button()
{


    position_list.clear();

    if(!temp_save.open(QFile::ReadOnly))
        {
            QMessageBox::information(this,"Oшибка", "Не открылся файл с ассортиментом!");
        }

        QTextStream stream(&temp_save);

        QString position;

        while(!stream.atEnd())
        {
            position = stream.readLine();
            QString first_part = position.left(position.indexOf(','));
            QString second_part = position.section(',',1, 1);
            QString third_part = position.section(',', 2);
            int num = third_part.toInt();

            //arr.push_back(num);
            Position a(first_part, second_part, num);
            position_list.push_back(a);
        }

        input_sequence->append("Was downloaded the last preservation!");

    temp_save.close();

}

void MainWindow::on_display_result_clicked()
{
    QWidget *result = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout;
    QTextEdit *display_arr = new QTextEdit;

    for (int i = 0; i < position_list.size(); i++)
    {
       if(position_list[i].Get_m_sum() > 0)
       {
       display_arr->append(QString("%1. %2 - %3").arg(position_list[i].Get_m_number()).arg(position_list[i].Get_m_name()).arg(position_list[i].Get_m_sum()));
       }
    }

    layout->addWidget(display_arr);
    result->setLayout(layout);

    result->show();

}

