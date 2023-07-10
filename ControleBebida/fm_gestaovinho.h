#ifndef FM_GESTAOVINHO_H
#define FM_GESTAOVINHO_H

#include <QDialog>
#include "Conexao.h"

namespace Ui {
class fm_gestaoVinho;
}

class fm_gestaoVinho : public QDialog
{
    Q_OBJECT

public:
    explicit fm_gestaoVinho(QWidget *parent = nullptr);
    ~fm_gestaoVinho();
    Conexao con;

private slots:


    void on_btn_add_salvar_clicked();

    void on_pushButtonSalvar_2_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_pushButtonExcluir_2_clicked();

    void on_tw_gv_listar_itemSelectionChanged();

    void on_btn_gv_filtrar_clicked();

    void on_btn_add_limpar_clicked();

private:
    Ui::fm_gestaoVinho *ui;
};

#endif // FM_GESTAOVINHO_H
