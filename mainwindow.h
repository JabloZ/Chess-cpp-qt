#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <vector>
#include <QMainWindow>
#include <string.h>
QT_BEGIN_NAMESPACE
namespace Ui { class Chess; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    bool game_ended=false;
    char who_now='w';
    char figure_choosen[4];
    std::vector<std::array<char,3>> changed_fields;
    std::vector<std::array<int,2>> possible_moves;
    int b_king_at[2]={0,4};
    int w_king_at[2]={7,4};
    int moves_without_mate=0;
    std::string chessboard[8][8]={ {"br","bk","bb","bq","bK","bb","bk","br"},
                                    {"bp","bp","bp","bp","bp","bp","bp","bp"},
                                    {"e","e","e","e","e","e","e","e"},
                                    {"e","e","e","e","e","e","e","e"},
                                    {"e","e","e","e","e","e","e","e"},
                                    {"e","e","e","e","e","e","e","e"},
                                    {"wp","wp","wp","wp","wp","wp","wp","wp"},
                                    {"wr","wk","wb","wq","wK","wb","wk","wr"}};
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    bool is_checked();
    bool is_mate();
    std::vector<std::array<int,2>> erase_wrong_movements(std::vector<std::array<int,2>> pos_mov, int x, int y);
    Ui::Chess *ui;
    void onAnyButtonClicked();
    void clearColors();
    std::vector<std::array<int,2>> possibleMoves(int x,int y,char f,char c,char who_is_my_color, std::string checked_chessboard[8][8]);
    bool cancels_check(std::string chessboard_after_move[8][8]);

};
#endif // MAINWINDOW_H
