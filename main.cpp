#include "mainwindow.h"
#include <iostream>
#include <string.h>
#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QGridLayout>
#include <QFrame>
#include <QDebug>
#include <vector>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
std::vector<std::array<int,2>> MainWindow::possibleMoves(int x,int y,char f,char c){
    std::vector<std::array<int,2>> moves;
    if (f=='p'){
        if (c=='w' && x==6){
            moves.push_back({x-1,y});
            moves.push_back({x-2,y});
            return moves;
        }
        if (c=='b' && x==1){

            moves.push_back({x,y+1});
            moves.push_back({x,y+2});
            return moves;
        }
    }
}
void MainWindow::onAnyButtonClicked() {
    //std::cout<<who_now; //background-color: rgb(108, 82, 70);
    for (auto& fld : changed_fields){
        int x=fld[0]-'0';
        int y=fld[1]-'0';
        char c=fld[2];
        QString frameName = QString("f%1%2").arg(fld[0]).arg(fld[1]);
        QFrame *frame = findChild<QFrame*>(frameName);
        if ((x+y)%2==0){
            frame->setStyleSheet("background-color: rgb(255, 255, 255);");
        }
        else{
               frame->setStyleSheet("background-color: rgb(108, 82, 70);");
        }
    }
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    if (clickedButton) {
        QString buttonName = clickedButton->objectName();
        std::string pname=buttonName.toStdString();
        int x=pname.at(1)-'0';
        int y=pname.at(2)-'0';

        if (chessboard[x][y].at(0)==who_now){

            QString frameName = QString("f%1%2").arg(x).arg(y);
            QFrame *frame = findChild<QFrame*>(frameName);
            frame->setStyleSheet("");
            frame->setStyleSheet("background-color: rgb(144,238,144);");
            changed_fields.push_back({x+'0',y+'0','w'});
            std::vector<std::array<int,2>> where=possibleMoves(x,y,chessboard[x][y].at(1),chessboard[x][y].at(0));
            for (auto& it : where) {
                std::cout <<"|"<< it[0] <<" "<<it[1];
                QString frameName = QString("f%1%2").arg(it[0]).arg(it[1]);
                QFrame *frame = findChild<QFrame*>(frameName);
                frame->setStyleSheet("");
                frame->setStyleSheet("background-color: rgb(143,188,143);");
                changed_fields.push_back({it[0]+'0',it[1]+'0','w'});
            }
        }
    }
}
