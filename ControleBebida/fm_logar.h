#ifndef FM_LOGAR_H
#define FM_LOGAR_H

#include <QDialog>
#include "Conexao.h"

namespace Ui {
class fm_logar;
}

class fm_logar : public QDialog
{
    Q_OBJECT

public:
    explicit fm_logar(QWidget *parent = nullptr);
    ~fm_logar();
    bool logado;
    Conexao con;
    QString nome,acesso;
   int id;

private slots:
    void on_btn_logar_clicked();

    void on_btn_cancelar_clicked();

private:
    Ui::fm_logar *ui;
};

#endif // FM_LOGAR_H
