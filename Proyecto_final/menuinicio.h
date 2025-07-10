#ifndef MENUINICIO_H
#define MENUINICIO_H

#include <QDialog>

namespace Ui {
class MenuInicioDialog;
}

class MenuInicio : public QDialog
{
    Q_OBJECT

public:
    MenuInicio(QWidget *parent = nullptr);
    ~MenuInicio();

private:
    Ui::MenuInicioDialog *ui;
};

#endif // MENUINICIO_H
