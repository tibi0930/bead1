#include "breakthroughwidget.h"
#include <QMessageBox>

BreakThroughWidget::BreakThroughWidget(QWidget *parent): QWidget(parent)
{
    setMinimumSize(600, 600);
    setBaseSize(600,600);
    setWindowTitle(trUtf8("Áttörés"));

    tableLayout = new QGridLayout(); // rácsos elhelyezkedés a játékmezőnek
    generateTable();

    setLayout(tableLayout);

    newGame();
}

void BreakThroughWidget::newGame()
{
    for (int i = 0; i < 6; ++i)
        for (int j = 0; j < 6; ++j)
        {
            gameTable[i][j] = 0; // a játékosok pozícióit töröljük
            buttonTable[i][j]->setText(""); // a szöveget töröljük
            buttonTable[0][j]->setText("2");
            buttonTable[1][j]->setText("2");
            buttonTable[buttonTable.size()-1][j]->setText("1");
            buttonTable[buttonTable.size()-2][j]->setText("1");
            buttonTable[i][j]->setEnabled(true); // bekapcsoljuk a gombot
        }

    stepCount = 0; // először az 1 lép
}

void BreakThroughWidget::generateTable()
{
    gameTable = new int*[6];
    buttonTable.resize(6);

    for (int i = 0; i < 6; ++i)
    {
        gameTable[i] = new int[6];
        buttonTable[i].resize(6);
        for (int j = 0; j < 6; ++j)
        {
            buttonTable[i][j]= new QPushButton( this);
            buttonTable[i][j]->setFont(QFont("Times New Roman", 50, QFont::Bold));
            buttonTable[i][j]->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

            tableLayout->addWidget(buttonTable[i][j], i, j); // gombok felvétele az elhelyezésbe

            connect(buttonTable[i][j], SIGNAL(clicked()), this, SLOT(buttonClicked()));
        }
    }
}

void BreakThroughWidget::buttonClicked()
{
    QPushButton* senderButton = dynamic_cast <QPushButton*> (QObject::sender());
    int location = tableLayout->indexOf(senderButton);
    //senderButton->setText(QString::number(location));
    stepGame(location / 6, location % 6);
}

void BreakThroughWidget::stepGame(int x, int y)
{
    if ((stepCount % 2 == 0) && buttonTable[x][y]->text() == "1"){
        if(x > 0){
            if(buttonTable[x-1][y]->text()==""){
                if(y>0 && buttonTable[x-1][y-1]->text()=="2"){
                    buttonTable[x-1][y-1]->setText("1");
                    buttonTable[x][y]->setText("");
                    stepCount++;
                    checkGame();
                }
                else if((y< buttonTable[x].size()-1) && buttonTable[x-1][y+1]->text()=="2"){
                    buttonTable[x-1][y+1]->setText("1");
                    buttonTable[x][y]->setText("");
                    stepCount++;
                    checkGame();
                }
                else{
                    buttonTable[x-1][y]->setText("1");
                    buttonTable[x][y]->setText("");
                    stepCount++;
                    checkGame();
                }
             }

             if(buttonTable[x-1][y]->text()=="1" || buttonTable[x-1][y]->text()=="2"){
                if(y>0 && buttonTable[x-1][y-1]->text()=="2"){
                    buttonTable[x-1][y-1]->setText("1");
                    buttonTable[x][y]->setText("");
                    stepCount++;
                    checkGame();
                }
                else if((y< buttonTable[x].size()-1) && buttonTable[x-1][y+1]->text()=="2"){
                    buttonTable[x-1][y+1]->setText("1");
                    buttonTable[x][y]->setText("");
                    stepCount++;
                    checkGame();
                }
             }
          }
       }


     else if((stepCount % 2 != 0) &&buttonTable[x][y]->text() == "2"){
        if(x < buttonTable.size()-1){
            if(buttonTable[x+1][y]->text()==""){
                if(y>0 && buttonTable[x+1][y-1]->text()=="1"){
                    buttonTable[x+1][y-1]->setText("2");
                    buttonTable[x][y]->setText("");
                    stepCount++;
                    checkGame();
                }
                else if((y< buttonTable[x].size()-1) && buttonTable[x+1][y+1]->text()=="1"){
                    buttonTable[x+1][y+1]->setText("2");
                    buttonTable[x][y]->setText("");
                    stepCount++;
                    checkGame();
                }
                else{
                    buttonTable[x+1][y]->setText("2");
                    buttonTable[x][y]->setText("");
                    stepCount++;
                    checkGame();
                }
            }

            if(buttonTable[x+1][y]->text()=="1" || buttonTable[x+1][y]->text()=="2"){
                if(y>0 && buttonTable[x+1][y-1]->text()=="1"){
                    buttonTable[x+1][y-1]->setText("2");
                    buttonTable[x][y]->setText("");
                    stepCount++;
                    checkGame();
                }
                else if((y< buttonTable[x].size()-1) && buttonTable[x+1][y+1]->text()=="1"){
                    buttonTable[x+1][y+1]->setText("2");
                    buttonTable[x][y]->setText("");
                    stepCount++;
                    checkGame();
                }
            }
        }
     }
    checkGame();
}

void BreakThroughWidget::checkGame(){
    int won=0;
    if(stepCount % 2 != 0){
        for(int j=0; j<buttonTable.size()-1; ++j){
            if(buttonTable[0][j]->text() == "1")
                won = 1;
        }
    }
    if(stepCount % 2 == 0){
        for(int j=0; j<buttonTable.size()-1; ++j){
            if(buttonTable[buttonTable.size()-1][j]->text() == "2")
                won = 2;
        }
    }
    if (won==1){
        QMessageBox::information(this, trUtf8("Játék vége"), trUtf8("Az egyes játékos nyert"));
        newGame();
    }
    else if(won==2){
        QMessageBox::information(this, trUtf8("Játék vége"), trUtf8("A kettes játékos nyert"));
        newGame();
    }
}
