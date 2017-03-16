#include "breakthroughwidget.h"
#include <QMessageBox>

BreakThroughWidget::BreakThroughWidget(QWidget *parent): QWidget(parent)
{
    setMinimumSize(600, 600);
    setBaseSize(600,600);
    setWindowTitle(trUtf8("Áttörés"));

    newGameButton = new QPushButton(trUtf8("Új játék")); // új játék gomb
    //connect(newGameButton, SIGNAL(clicked()), this, SLOT(newGameButtonClicked()));

    mainLayout = new QVBoxLayout();
    mainLayout->addWidget(newGameButton);

    tableLayout = new QGridLayout(); // rácsos elhelyezkedés a játékmezőnek
    //generateTable();

    mainLayout->addLayout(tableLayout);
    setLayout(mainLayout);

    _gridSizeDialog = new GridSizeDialog();
    connect(newGameButton, SIGNAL(clicked()), _gridSizeDialog, SLOT(exec())); // méretező ablak megjelenítése gombnyomásra
    connect(_gridSizeDialog, SIGNAL(accepted()), this, SLOT(resizeGrid())); // átméretezés a dialógus elfogadására
    //newGame();
}

BreakThroughWidget::~BreakThroughWidget(){
    delete _gridSizeDialog;
}

/*void BreakThroughWidget::newGame()
{
    for (int i = 0; i < 6; ++i)
        for (int j = 0; j < 6; ++j)
        {
            buttonTable[i][j]->setText(""); // a szöveget töröljük
            buttonTable[0][j]->setText("2");
            buttonTable[1][j]->setText("2");
            buttonTable[buttonTable.size()-1][j]->setText("1");
            buttonTable[buttonTable.size()-2][j]->setText("1");
            buttonTable[i][j]->setEnabled(true); // bekapcsoljuk a gombot
        }

    stepCount = 0; // először az 1 lép
}*/

/*void BreakThroughWidget::newGameButtonClicked()
{
    newGame();
}
*/
/*void BreakThroughWidget::generateTable()
{
    buttonTable.resize(6);

    for (int i = 0; i < 6; ++i)
    {
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
}*/


void BreakThroughWidget::resizeGrid(){
    foreach(QVector<QPushButton*> rows, buttonTable){
       foreach(QPushButton* button, rows){
          tableLayout->removeWidget(button);
          delete button;
       }
    }
    buttonTable.clear();

    int meret = _gridSizeDialog->gridSize();
    buttonTable.resize(meret);
    for (int i = 0; i < meret; ++i)
    {
        buttonTable[i].resize(meret);
        for (int j = 0; j < meret; ++j)
        {
            buttonTable[i][j]= new QPushButton( this);
            buttonTable[i][j]->setFont(QFont("Times New Roman", 50, QFont::Bold));
            buttonTable[i][j]->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

            tableLayout->addWidget(buttonTable[i][j], i, j); // gombok felvétele az elhelyezésbe

            connect(buttonTable[i][j], SIGNAL(clicked()), this, SLOT(buttonClicked()));
        }
    }

    for (int i = 0; i < meret; ++i)
        for (int j = 0; j < meret; ++j)
        {
            buttonTable[i][j]->setText(""); // a szöveget töröljük
            buttonTable[0][j]->setText("2");
            buttonTable[1][j]->setText("2");
            buttonTable[buttonTable.size()-1][j]->setText("1");
            buttonTable[buttonTable.size()-2][j]->setText("1");
            buttonTable[i][j]->setEnabled(true); // bekapcsoljuk a gombot
        }

    stepCount = 0; // először az 1 lép
}



void BreakThroughWidget::buttonClicked()
{
    QPushButton* senderButton = dynamic_cast <QPushButton*> (QObject::sender());
    int location = tableLayout->indexOf(senderButton);
    //senderButton->setText(QString::number(location));
    stepGame(location / _gridSizeDialog->gridSize(), location % _gridSizeDialog->gridSize());
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
        _gridSizeDialog->exec();
        resizeGrid();
        //newGame();
    }
    else if(won==2){
        QMessageBox::information(this, trUtf8("Játék vége"), trUtf8("A kettes játékos nyert"));
        _gridSizeDialog->exec();
        resizeGrid();
        //newGame();
    }
}
