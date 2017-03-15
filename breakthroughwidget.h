#ifndef BREAKTHROUGHWIDGET_H
#define BREAKTHROUGHWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>

class BreakThroughWidget : public QWidget
{
    Q_OBJECT

public:
    BreakThroughWidget(QWidget *parent = 0);

private slots:
    void buttonClicked();  //táblagombra kattintás eseménykezelője

private:
    void stepGame(int x, int y);  //játék léptetése
    //void checkGame();  //vége van-e a játéknak
    void generateTable(); //tábla létrehozása
    void newGame();  //új játék kezdése

    int stepCount; //játékos száma
    QGridLayout * tableLayout;  //gombrács
    QVector< QVector <QPushButton* > > buttonTable; //gombtábla
    int** gameTable;  //játéktábla
};

#endif // BREAKTHROUGHWIDGET_H
