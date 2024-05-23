#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QGridLayout>
#include <QFrame>
#include <QMainWindow>
#include <QDebug>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Chess)
{
    ui->setupUi(this);
    std::string chessboard[8][8]={ {"br","bk","bb","bq","BK","bb","bk","br"},
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
            QPushButton *button = findChild<QPushButton*>(buttonName);
            if (chessboard[j][i]!="e"){
                button->setText(QString::fromStdString(chessboard[j][i]));}
            connect(button, &QPushButton::clicked, this, &MainWindow::onAnyButtonClicked);
        }
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}

