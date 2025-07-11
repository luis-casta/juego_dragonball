#ifndef MENUINICIO_H
#define MENUINICIO_H

#include <QDialog>
#include <QMediaPlayer>
#include <QAudioOutput>

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
    QMediaPlayer* player;
    QAudioOutput* audioOutput;
};

#endif // MENUINICIO_H
