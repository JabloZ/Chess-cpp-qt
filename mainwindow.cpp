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
    QPushButton *button5 = findChild<QPushButton*>(QString::fromStdString("buttonrestart"));
    connect(button5, &QPushButton::clicked, this, &MainWindow::initializeGame);
}
bool MainWindow::does_button_exist(QString buttonName){
    QPushButton *button = findChild<QPushButton*>(buttonName);
    return button!=nullptr;
}
void MainWindow::initializeGame(){
    game_ended=false;
    waiting_for_promotion=false;
    who_now='w';
    figure_choosen[4]={};
    changed_fields={};
    possible_moves={};
    promoted_pawn_at[0]=8;
    promoted_pawn_at[1]=8;

    b_king_at[0]=0;
    b_king_at[1]=4;
    w_king_at[0]=7;
    w_king_at[1]=4;
    moves_without_mate=0;
    std::string initial_chessboard[8][8]={ {"br","bk","bb","bq","bK","bb","bk","br"},
                                    {"bp","bp","bp","bp","bp","bp","bp","bp"},
                                    {"e","e","e","e","e","e","e","e"},
                                    {"e","e","e","e","e","e","e","e"},
                                    {"e","e","e","e","e","e","e","e"},
                                    {"e","e","e","e","e","e","e","e"},
                                    {"wp","wp","wp","wp","wp","wp","wp","wp"},
                                    {"wr","wk","wb","wq","wK","wb","wk","wr"}};

    for (int i=0;i<8;i++){
            for (int j=0;j<8;j++){
                chessboard[j][i]=initial_chessboard[j][i];
                QString buttonName = QString("p%1%2").arg(j).arg(i);

                if (does_button_exist(buttonName)==true) {
                QPushButton *button = findChild<QPushButton*>(buttonName);
                if (chessboard[j][i]!="e"){

                    button->setText(QString::fromStdString(chessboard[j][i]));

                }
                else{
                    button->setText(QString::fromStdString(""));
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
    QPushButton *button5 = findChild<QPushButton*>(QString::fromStdString("buttonrestart"));
    connect(button5, &QPushButton::clicked, this, &MainWindow::initializeGame);
}

MainWindow::~MainWindow()
{
    delete ui;
}

