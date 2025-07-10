#include <QApplication>
#include "menuinicio.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MenuInicio menu;
    if (menu.exec() == QDialog::Accepted) {
        MainWindow w;
        w.show();
        return a.exec();
    } else {
        return 0;
    }
}
