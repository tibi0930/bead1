#ifndef BREAKTHROUGHWIDGET_H
#define BREAKTHROUGHWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include "gridsizedialog.h"

class BreakThroughWidget : public QWidget
{
    Q_OBJECT

public:
    BreakThroughWidget(QWidget *parent = 0);
    ~BreakThroughWidget();
private slots:
    void buttonClicked();  //táblagombra kattintás eseménykezelője
    //void newGameButtonClicked(); // új játék gombra kattintás eseménykezelője
    void resizeGrid(); // rács méretezése

private:
    void stepGame(int x, int y);  //játék léptetése
    void checkGame();  //vége van-e a játéknak
    void generateTable(); //tábla létrehozása
    void newGame();  //új játék kezdése

    GridSizeDialog* _gridSizeDialog; // méretbeállító ablak

    int stepCount; //játékos száma
    QGridLayout * tableLayout;  //gombrács
    QVBoxLayout * mainLayout;
    QPushButton* newGameButton;
    QVector< QVector <QPushButton* > > buttonTable; //gombtábla
};

#endif // BREAKTHROUGHWIDGET_H
