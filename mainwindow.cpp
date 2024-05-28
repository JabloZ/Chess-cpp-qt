#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QGridLayout>
#include <QFrame>
#include <QString>
#include <QMainWindow>
#include <QDebug>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Chess)
{
    ui->setupUi(this);
    std::string chessboard[8][8]={ {"br","bk","bb","bq","bK","bb","bk","br"},
                                    {"bp","bp","bp","bp","bp","bp","bp","bp"},
                                    {"e","e","e","e","e","e","e","e"},
                                    {"e","e","e","e","e","e","e","e"},
                                    {"e","e","e","e","e","e","e","e"},
                                    {"e","e","e","e","e","e","e","e"},
                                    {"wp","wp","wp","wp","wp","wp","wp","wp"},
                                    {"wr","wk","wb","wq","wK","wb","wk","wr"}};
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){

            QString buttonName = QString("p%1%2").arg(j).arg(i);

            if (does_button_exist(buttonName)==true) {
                QPushButton *button = findChild<QPushButton*>(buttonName);
                if (chessboard[j][i]!="e"){

                    button->setText(QString::fromStdString(chessboard[j][i]));

                    }
                connect(button, &QPushButton::clicked, this, &MainWindow::onAnyButtonClicked);
                }

            }
    }
    QString framename="promotion_frame";
    QFrame *frame_to_edit=findChild<QFrame*>(framename);
    frame_to_edit->setVisible(false);
    QPushButton *button1 = findChild<QPushButton*>(QString::fromStdString("queenbutton"));
    connect(button1, &QPushButton::clicked, this, &MainWindow::promotion);
    QPushButton *button2 = findChild<QPushButton*>(QString::fromStdString("bishopbutton"));
    connect(button2, &QPushButton::clicked, this, &MainWindow::promotion);
    QPushButton *button3 = findChild<QPushButton*>(QString::fromStdString("knightbutton"));
    connect(button3, &QPushButton::clicked, this, &MainWindow::promotion);
    QPushButton *button4 = findChild<QPushButton*>(QString::fromStdString("rookbutton"));
    connect(button4, &QPushButton::clicked, this, &MainWindow::promotion);

}
bool MainWindow::does_button_exist(QString buttonName){
    QPushButton *button = findChild<QPushButton*>(buttonName);
    return button!=nullptr;
}


MainWindow::~MainWindow()
{
    delete ui;
}

