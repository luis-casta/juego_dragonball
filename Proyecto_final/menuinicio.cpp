#include "menuinicio.h"
#include "ui_dialog.h"  // Aquí usas el nombre del archivo .ui sin extensión

MenuInicio::MenuInicio(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MenuInicioDialog)
{
    ui->setupUi(this);

    connect(ui->btnJugar, &QPushButton::clicked, this, &MenuInicio::accept);
    connect(ui->btnSalir, &QPushButton::clicked, this, &MenuInicio::reject);
}

MenuInicio::~MenuInicio()
{
    delete ui;
}
