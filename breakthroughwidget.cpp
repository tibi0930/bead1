#include "breakthroughwidget.h"
#include <QMessageBox>

//konstruktor
BreakThroughWidget::BreakThroughWidget(QWidget *parent): QWidget(parent)
{
    setMinimumSize(600, 600); //Ablak minimum méret
    setBaseSize(600,600); //Ablak optimális
    setWindowTitle(trUtf8("Áttörés")); //Ablak címe

    newGameButton = new QPushButton(trUtf8("Új játék")); // új játék gomb

    mainLayout = new QVBoxLayout(); //Fő megjelenés, vizszintes elrendezéssel
    mainLayout->addWidget(newGameButton); //felülre hozzá adunk egy gombot

    tableLayout = new QGridLayout(); // rácsos elhelyezkedés a játékmezőnek
    mainLayout->addLayout(tableLayout); //mainLayouthoz hozzáadjuk a gombrács megjelenítőt
    setLayout(mainLayout); //mainLayout lesz a fő megjelenítő

    _gridSizeDialog = new GridSizeDialog();
    connect(newGameButton, SIGNAL(clicked()), _gridSizeDialog, SLOT(exec())); // méretező ablak megjelenítése gombnyomásra
    connect(_gridSizeDialog, SIGNAL(accepted()), this, SLOT(resizeGrid())); // átméretezés a dialógus elfogadására
}

BreakThroughWidget::~BreakThroughWidget(){
    delete _gridSizeDialog;
}

//tábla átméretezése
void BreakThroughWidget::resizeGrid(){

    //előző tábla törlése
    foreach(QVector<QPushButton*> rows, buttonTable){
       foreach(QPushButton* button, rows){
          tableLayout->removeWidget(button);
          delete button;
       }
    }
    buttonTable.clear();

    //új tábla létrehozása
    int meret = _gridSizeDialog->gridSize(); //méret segédváltozó
    buttonTable.resize(meret);  //tábla méret beállítás
    for (int i = 0; i < meret; ++i)
    {
        buttonTable[i].resize(meret);
        for (int j = 0; j < meret; ++j)
        {
            buttonTable[i][j]= new QPushButton( this);
            buttonTable[i][j]->setFont(QFont("Times New Roman", 50, QFont::Bold));
            buttonTable[i][j]->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
            // gombok felvétele az elhelyezésbe
            tableLayout->addWidget(buttonTable[i][j], i, j);
            //esemény hozzárendelése a gombokhoz
            connect(buttonTable[i][j], SIGNAL(clicked()), this, SLOT(buttonClicked()));
        }
    }

    //gombok beállítása
    for (int i = 0; i < meret; ++i)
        for (int j = 0; j < meret; ++j)
        {
            buttonTable[i][j]->setText(""); // a szöveget töröljük
            buttonTable[0][j]->setText("2"); //utolsó 2 sorba felvesszük a bábukat
            buttonTable[1][j]->setText("2");
            buttonTable[buttonTable.size()-1][j]->setText("1"); //első két sorba felvesszük a bábukat
            buttonTable[buttonTable.size()-2][j]->setText("1");
            buttonTable[i][j]->setEnabled(true); // bekapcsoljuk a gombot
        }

    stepCount = 0; //lépés számláló, először az 1 lép
}


void BreakThroughWidget::buttonClicked()
{
    QPushButton* senderButton = dynamic_cast <QPushButton*> (QObject::sender()); //konvertálás
    int location = tableLayout->indexOf(senderButton); //gomb pozíció
    //senderButton->setText(QString::number(location));
    stepGame(location / _gridSizeDialog->gridSize(), location % _gridSizeDialog->gridSize()); //gomb pozíciót i,j koordinátaként adjuk át,
                                                                                              //majd léptetjük a játékot
}

//gombra kattintás esetén lefutó metódus
void BreakThroughWidget::stepGame(int x, int y)
{
    //ha páros a lépés, mivel az 1-es játékos kezdett, így az egyes játékossal vagyunk.
    //és egyes gombot nyomunk
    if ((stepCount % 2 == 0) && buttonTable[x][y]->text() == "1"){
        if(x > 0){ //van még sor, ahova léphetünk
            if(buttonTable[x-1][y]->text()==""){  //ha előtte nincs senki
                if(y>0 && buttonTable[x-1][y-1]->text()=="2"){ //és nem szélső bábú, de balra átlósan van egy kettes, akkor leüti
                    buttonTable[x-1][y-1]->setText("1");  //ide lépett, 1-esre állítjuk
                    buttonTable[x][y]->setText("");  //innen ellépett, üresre állítjuk
                    stepCount++;  //következő bábu jön
                    checkGame();  //ellenőrizzük, hogy nyert-e ezzel a lépéssel
                }
                else if((y< buttonTable[x].size()-1) && buttonTable[x-1][y+1]->text()=="2"){  //jobb átlót vizsgálja
                    buttonTable[x-1][y+1]->setText("1");
                    buttonTable[x][y]->setText("");
                    stepCount++;
                    checkGame();
                }
                else{ //nincs ütés, előre lép
                    buttonTable[x-1][y]->setText("1");
                    buttonTable[x][y]->setText("");
                    stepCount++;
                    checkGame();
                }
             }
             //ha előtte áll egy bábu, oda nem tud lépni, ezért megvizsgálja az átlokat. Ha ott kettes van, leüti és odalép
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

    //ugyan úgy, mint az egyes játékosnál
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
}

//lépések után megvizsgáljuk, hogy vége van-e a játéknak
void BreakThroughWidget::checkGame(){
    int won=0;  //kezdetben nincs nyertes
    //egyes nyer, ha eléri a tábla tuloldalara (0. sor)
    if(stepCount % 2 != 0){
        for(int j=0; j<buttonTable.size()-1; ++j){
            if(buttonTable[0][j]->text() == "1")
                won = 1;
        }
    }
    //kettes nyer, ha eléri ugyan úgy a tábla tuloldalat
    if(stepCount % 2 == 0){
        for(int j=0; j<buttonTable.size()-1; ++j){
            if(buttonTable[buttonTable.size()-1][j]->text() == "2")
                won = 2;
        }
    }
    //kiírjuk a nyertest egy üzenetként a felhasználó számára
    if (won==1){
        QMessageBox::information(this, trUtf8("Játék vége"), trUtf8("Az egyes játékos nyert"));
        _gridSizeDialog->exec();
        resizeGrid();
    }
    else if(won==2){
        QMessageBox::information(this, trUtf8("Játék vége"), trUtf8("A kettes játékos nyert"));
        _gridSizeDialog->exec();
        resizeGrid();
    }
}
