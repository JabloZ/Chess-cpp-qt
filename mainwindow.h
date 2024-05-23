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
    char who_now='w';
    std::vector<std::array<char,3>> changed_fields;
    std::string chessboard[8][8]={ {"br","bk","bb","bq","BK","bb","bk","br"},
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
    Ui::Chess *ui;
    void onAnyButtonClicked();
    std::vector<std::array<int,2>> possibleMoves(int x,int y,char f,char c);

};
#endif // MAINWINDOW_H
