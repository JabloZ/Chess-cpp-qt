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
#include <algorithm>
#include <array>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
std::vector<std::array<int,2>> MainWindow::possibleMoves(int x,int y,char f,char c){
    std::vector<std::array<int,2>> moves;
    switch(f){
        case 'p':
            switch(c){
                case 'w':
                    if (x==0){
                        break;
                    }
                    if (x==6 && chessboard[x-2][y].at(0)=='e'){
                        moves.push_back({x-2,y});
                    }
                    if (chessboard[x-1][y].at(0)=='e'){
                        moves.push_back({x-1,y});
                    }
                    if ((y-1)>=0 && chessboard[x-1][y-1].at(0)!=who_now && chessboard[x-1][y-1].at(0)!='e' && chessboard[x-1][y-1].at(1)!='K'){ //w lewy gorny
                        moves.push_back({x-1,y-1});
                    }
                    if ((y+1)<8 &&chessboard[x-1][y+1].at(0)!=who_now && chessboard[x-1][y+1].at(0)!='e' && chessboard[x-1][y+1].at(1)!='K'){ //w prawy gorny
                        moves.push_back({x-1,y+1});
                    }
                    return moves;

                case 'b':
                    if (x==7){
                        break;
                    }
                    if (x==1 && chessboard[x+2][y].at(0)=='e'){
                        moves.push_back({x+2,y});
                    }
                    if (chessboard[x+1][y].at(0)=='e'){
                        moves.push_back({x+1,y});
                    }
                    if ((y-1)>=0 && chessboard[x+1][y-1].at(0)!=who_now && chessboard[x+1][y-1].at(0)!='e'  && chessboard[x+1][y-1].at(1)!='K'){ //w lewy gorny
                        moves.push_back({x+1,y-1});
                    }
                    if ((y+1)<8 && chessboard[x+1][y+1].at(0)!=who_now && chessboard[x+1][y+1].at(0)!='e'  && chessboard[x+1][y+1].at(1)!='K'){ //w prawy gorny
                        moves.push_back({x+1,y+1});
                    }
                    return moves;


                }
        case 'r':
                std::cout<<"here";
            for (int x2=x-1;x2>=0;x2--){ //w gore
                        if (chessboard[x2][y].at(0)!='e' && chessboard[x2][y].at(0)!=who_now){
                            moves.push_back({x2,y});
                            break;
                        }
                        if (chessboard[x2][y].at(0)=='e'){
                                moves.push_back({x2,y});
                            }
                            else{break;}
            }
            for (int x2=x+1;x2<=7;x2++){ //w dol
                        if (chessboard[x2][y].at(0)!='e' && chessboard[x2][y].at(0)!=who_now){
                            moves.push_back({x2,y});
                            break;
                        }
                        if (chessboard[x2][y].at(0)=='e'){
                            moves.push_back({x2,y});
                        }
                        else{break;}
            }
            for (int y2=y-1;y2>=0;y2--){ //w lewo
                        if (chessboard[x][y2].at(0)!='e' && chessboard[x][y2].at(0)!=who_now){
                            moves.push_back({x,y2});
                            break;
                        }
                        if (chessboard[x][y2].at(0)=='e'){
                            moves.push_back({x,y2});
                        }
                        else{break;}
            }
            for (int y2=y+1;y2<=7;y2++){ //w lewo
                        if (chessboard[x][y2].at(0)!='e' && chessboard[x][y2].at(0)!=who_now){
                            moves.push_back({x,y2});
                            break;
                        }
                        if (chessboard[x][y2].at(0)=='e'){
                            moves.push_back({x,y2});
                        }
                        else{break;}
            }
            return moves;
        default:
            std::cout<<"different figure";
            break;
    }
}
void MainWindow::clearColors(){
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
}
void MainWindow::onAnyButtonClicked() {

    //std::cout<<who_now; //background-color: rgb(108, 82, 70);
    clearColors();
    bool change_frame_color=true;
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    if (clickedButton) {
        QString buttonName = clickedButton->objectName();
        std::string pname=buttonName.toStdString();
        int x=pname.at(1)-'0';
        int y=pname.at(2)-'0';
        std::array<int,2> cur={x,y};
        if (figure_choosen[3]==who_now){

                if (std::find(possible_moves.begin(), possible_moves.end(), cur) != possible_moves.end()) {

                    std::cout<<"possible move";
                    std::string fname;
                    fname+=figure_choosen[3];
                    fname+=figure_choosen[2];

                    chessboard[x][y]=fname;
                    chessboard[figure_choosen[0]-'0'][figure_choosen[1]-'0']="e";

                    QString buttonName12 = QString("p%1%2").arg(x).arg(y);
                    QPushButton *buttonc = findChild<QPushButton*>(buttonName12);
                    buttonc->setText(QString::fromStdString(fname));

                    QString buttonName22 = QString("p%1%2").arg(figure_choosen[0]-'0').arg(figure_choosen[1]-'0');
                    QPushButton *buttonc2 = findChild<QPushButton*>(buttonName22);
                    buttonc2->setText(QString::fromStdString(""));
                    change_frame_color=false;
                    for (int i=0; i<4; i++){
                        figure_choosen[i]='0';
                    }
                    possible_moves.clear();
                    if (who_now=='w'){
                        who_now='b';
                    }
                    else{who_now='w';}
                   }
        }
        if (chessboard[x][y].at(0)==who_now){

            QString frameName = QString("f%1%2").arg(x).arg(y);
            QFrame *frame = findChild<QFrame*>(frameName);
            if (change_frame_color==true){
                    frame->setStyleSheet("background-color: rgb(144,238,144);");
                    changed_fields.push_back({x+'0',y+'0','w'});
                    std::vector<std::array<int,2>> where=possibleMoves(x,y,chessboard[x][y].at(1),chessboard[x][y].at(0));
                    possible_moves=where;
                    figure_choosen[0]=x+'0';
                    figure_choosen[1]=y+'0';
                    figure_choosen[2]=chessboard[x][y].at(1);
                    figure_choosen[3]=chessboard[x][y].at(0);

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
}
