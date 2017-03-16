#include "gridsizedialog.h"
#include <QHBoxLayout>

//létrehozunk egy dialógus ablakot a tábla méretének megadásához
//konstruktorban megadjuk az ablakon lévő objektumokat
GridSizeDialog::GridSizeDialog(QWidget *parent) :QDialog(parent)
{
    setFixedSize(250,120); //tábla méret
    setWindowTitle(trUtf8("Beállítások")); //ablak címe
    setModal(true); // előugró ablak, rögtön megkapja a fókuszt

    _label = new QLabel(trUtf8("Tábla mérete: "));
    _spinBox = new QSpinBox();
    _spinBox->setRange(6, 10); // az értékek 6 és 10 közöttiek lehetnek
    _spinBox->setSingleStep(2); // a lépésköz 2

    _okButton = new QPushButton(trUtf8("OK"));
    _okButton->setFixedSize(75, 23); // a gombok mérete rögzített
    _cancelButton = new QPushButton(trUtf8("Mégse"));
    _cancelButton->setFixedSize(75, 23);

    connect(_okButton, SIGNAL(clicked()), this, SLOT(accept())); // elfogadás állapota
    connect(_cancelButton, SIGNAL(clicked()), this, SLOT(reject())); // elvetés állapota

    //Ablak elrendezés
    QHBoxLayout *upperLayout = new QHBoxLayout();
    upperLayout->addWidget(_label);
    upperLayout->addWidget(_spinBox);

    QHBoxLayout *lowerLayout = new QHBoxLayout();
    lowerLayout->addWidget(_okButton);
    lowerLayout->addWidget(_cancelButton);

    QVBoxLayout *mLayout = new QVBoxLayout();
    mLayout->addLayout(upperLayout);
    mLayout->addLayout(lowerLayout);

    setLayout(mLayout);
}
