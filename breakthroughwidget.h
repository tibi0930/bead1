#ifndef BREAKTHROUGHWIDGET_H
#define BREAKTHROUGHWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include "gridsizedialog.h"

class BreakThroughWidget : public QWidget
{
    Q_OBJECT  //makró

public:
    BreakThroughWidget(QWidget *parent = 0);
    ~BreakThroughWidget();
private slots:
    void buttonClicked();  //táblagombra kattintás eseménykezelője
    void resizeGrid(); // tábla méretezése

private:
    void stepGame(int x, int y);  //játék léptetése
    void checkGame();  //vége van-e a játéknak
    void generateTable(); //tábla létrehozása

    GridSizeDialog* _gridSizeDialog; // méretbeállító ablak

    int stepCount; //lépés számolás a játékos számának megállapításához
    QGridLayout* tableLayout;  //gombrács
    QVBoxLayout* mainLayout;
    QPushButton* newGameButton; //tábla gombjai
    QVector< QVector <QPushButton* > > buttonTable; //gombtábla
};

#endif // BREAKTHROUGHWIDGET_H
