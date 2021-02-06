#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QMessageBox>
#include <QPalette>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->setRowCount(1);
    ui->tableWidget->setItem(0, 0, new QTableWidgetItem(""));
    //this->setBackgroundRole(QPalette::Dark);
}
QFile f("Сідлові точки.txt");

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_spinBox_valueChanged(int arg1)
{
    ui->tableWidget->setRowCount(arg1);
}

void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
    ui->tableWidget->setColumnCount(arg1);
}

void MainWindow::on_pushButton_clicked()
{
    int i = ui->tableWidget->rowCount();
    int j = ui->tableWidget->columnCount();
    int arr[i][j];
    for(int ii = 0; ii < i; ii++)
        for(int jj = 0; jj < j; jj++){
            arr[ii][jj] = rand()%10+1;
            ui->tableWidget->setItem(ii, jj, new QTableWidgetItem(QString::number(arr[ii][jj])));
        }
}

void MainWindow::on_pushButton_2_clicked()
{
    f.open((QFile::WriteOnly | QFile::Text | QFile::Append));
    int i = ui->tableWidget->rowCount();
    int j = ui->tableWidget->columnCount();
    int m[i][j];
    bool leo = false;
    for(int ii = 0; ii < i; ii++){
        for(int jj = 0; jj < j; jj++){
            if(ui->tableWidget->item(ii, jj) == NULL)
                leo = true;
            else
                if(ui->tableWidget->item(ii, jj)->text() != "")
                    m[ii][jj] = ui->tableWidget->item(ii, jj)->text().toInt();
                else leo = true;

        }
    }
    if(leo)
    {
        message("Помилка", "Ви повинні заповнити всі поля");
        return;
    }
    int max_i[i], max_j[j], min_i[i], min_j[j];

    for(int ii = 0; ii<i; ii++){
            max_i[ii] = m[ii][0];
            min_i[ii] = m[ii][0];
        }
        for(int jj = 0; jj<j; jj++){
            max_j[jj] = m[0][jj];
            min_j[jj] = m[0][jj];
        }

        for(int ii = 0; ii<i; ii++){
            for(int jj = 0; jj<j; jj++){

        QTextStream cout(&f);
        cout<<m[ii][jj]<<"\t";
        }
            QTextStream cout(&f);
            cout<<"\n";
        }

        for(int ii = 0; ii<i; ii++){
            for(int jj = 0; jj<j; jj++){
        if(m[ii][jj] > max_i[ii])
            max_i[ii] = m[ii][jj];
        if(m[ii][jj] < min_i[ii])
        min_i[ii] = m[ii][jj];
           }
       }
        for(int jj = 0; jj<j; jj++){
        for(int ii = 0; ii<i; ii++){
            if(m[ii][jj] > max_j[jj])
                max_j[jj] = m[ii][jj];
            if(m[ii][jj] < min_j[jj])
            min_j[jj] = m[ii][jj];
            }
        }
    bool h = false;
    for(int ii = 0; ii<i; ii++){
        for(int jj = 0; jj<j; jj++){
            if(max_i[ii] == min_j[jj]){
                h = true;
                QTextStream cout(&f);
                cout<<"Сідлова точка: "<<max_i[ii]<< "("<<ii+1<<", "<<jj+1<<")\n";
                ui->tableWidget->item(ii, jj)->setBackground(QColor::fromRgb(137, 250, 155));
            }
            if(min_i[ii] == max_j[jj]){
                h = true;
                QTextStream cout(&f);
                cout<<"Сідлова точка: "<<""<<max_j[jj]<< "("<<ii+1<<", "<<jj+1<<")\n";
                ui->tableWidget->item(ii, jj)->setBackground(QColor::fromRgb(137, 250, 155));
            }
        }
    }
        if(!h){
            QTextStream cout(&f);
            cout<<"Сідлові точки відсутні\n\n";
            message("Важливо", "Сідлові точки відсутні");
        }else{
            QTextStream cout(&f);
            cout<<"\n";
        }
        f.close();
}

void MainWindow::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    QString arg1 = item->text();
    foreach(QChar c, arg1)
        {
            if(!c.isNumber())
            {
                 message("Помилка", "Ви повинні ввести число");
                item->setText("");
                return;
            }
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    message("Важливо", "Файл очищено");
    f.remove();
}

void MainWindow::message(QString title, QString text){
    QMessageBox msgbox;
    msgbox.setWindowTitle(title);
    msgbox.setText(text);
    msgbox.exec();
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->tableWidget->clearContents();
    ui->spinBox->setValue(1);
    ui->spinBox_2->setValue(1);
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->tableWidget->setRowCount(1);
    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->clearContents();
    ui->spinBox->setValue(1);
    ui->spinBox_2->setValue(1);
}
