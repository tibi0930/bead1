#ifndef GRIDSIZEDIALOG_H
#define GRIDSIZEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>

class GridSizeDialog : public QDialog // rács méretét beállító dialógus
{
    Q_OBJECT
public:
    explicit GridSizeDialog(QWidget *parent = 0);
    int gridSize() { return _spinBox->value(); } // gombok számának lekérdezése

private:
    QLabel *_label; // címke
    QSpinBox *_spinBox; // számbeállító
    QPushButton *_okButton;
    QPushButton *_cancelButton;
};

#endif // GRIDSIZEDIALOG_H
