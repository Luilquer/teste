#ifndef FM_GESTAOFORNECEDOR_H
#define FM_GESTAOFORNECEDOR_H

#include <QDialog>
#include <QObject>
#include "Conexao.h"

namespace Ui {
class fm_gestaofornecedor;
}

class fm_gestaofornecedor : public QDialog
{
    Q_OBJECT

public:
    explicit fm_gestaofornecedor(QWidget *parent = nullptr);
    ~fm_gestaofornecedor();
    Conexao con;

private slots:
    void on_btn_novo_novofor_clicked();

    void on_btn_gravar_novoforn_clicked();

    void on_bnt_filtrar_forn_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_bnt_gf_escluir_clicked();

    void on_bnt_gf_salvar_clicked();

    void on_tw_gf_listafor_itemSelectionChanged();

private:
    Ui::fm_gestaofornecedor *ui;
};

#endif // FM_GESTAOFORNECEDOR_H
