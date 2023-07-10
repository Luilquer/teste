#ifndef FM_CONSULTARCOMIDA_H
#define FM_CONSULTARCOMIDA_H

#include <QDialog>
#include "Conexao.h"

namespace Ui {
class fm_consultarComida;
}

class fm_consultarComida : public QDialog
{
    Q_OBJECT

public:
    explicit fm_consultarComida(QWidget *parent = nullptr);
    ~fm_consultarComida();
    Conexao con;

private slots:
    void on_pushButton_clicked();

private:
    Ui::fm_consultarComida *ui;
};

#endif // FM_CONSULTARCOMIDA_H
