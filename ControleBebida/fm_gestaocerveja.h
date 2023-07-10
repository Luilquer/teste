#ifndef FM_GESTAOCERVEJA_H
#define FM_GESTAOCERVEJA_H

#include <QDialog>
#include "Conexao.h"

namespace Ui {
class fm_gestaocerveja;
}

class fm_gestaocerveja : public QDialog
{
    Q_OBJECT

public:
    explicit fm_gestaocerveja(QWidget *parent = nullptr);
    ~fm_gestaocerveja();
    Conexao con;

private slots:
    void on_btn_add_salvar_clicked();

    void on_btn_add_limpar_clicked();

    void on_btn_gv_filtrar_clicked();

    void on_tw_gc_listar_itemSelectionChanged();

    void on_pushButtonSalvar_2_clicked();

    void on_pushButtonExcluir_2_clicked();

private:
    Ui::fm_gestaocerveja *ui;
};

#endif // FM_GESTAOCERVEJA_H
