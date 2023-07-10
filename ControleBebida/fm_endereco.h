#ifndef FM_ENDERECO_H
#define FM_ENDERECO_H

#include <QDialog>
#include "Conexao.h"

namespace Ui {
class fm_endereco;
}

class fm_endereco : public QDialog
{
    Q_OBJECT

public:
    explicit fm_endereco(QWidget *parent = nullptr);
    ~fm_endereco();
    Conexao con;

private slots:

    void on_btn_salvar_clicked();

    void on_btn_excluir_clicked();

    void on_btn_filtrar_clicked();

    void on_tw_listaEnd_itemSelectionChanged();

    void on_btn_add_clicked();

private:
    Ui::fm_endereco *ui;
};

#endif // FM_ENDERECO_H
