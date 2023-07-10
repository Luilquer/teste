#ifndef FM_GESTAOESTILO_H
#define FM_GESTAOESTILO_H

#include <QDialog>
#include "Conexao.h"

namespace Ui {
class fm_gestaoEstilo;
}

class fm_gestaoEstilo : public QDialog
{
    Q_OBJECT

public:
    explicit fm_gestaoEstilo(QWidget *parent = nullptr);
    ~fm_gestaoEstilo();
    Conexao con;

private slots:


    void on_btn_add_clicked();

    void on_btn_filtrar_clicked();

    void on_tw_estilo_itemSelectionChanged();

    void on_btn_salvar_clicked();

    void on_btn_excluir_clicked();

private:
    Ui::fm_gestaoEstilo *ui;
};

#endif // FM_GESTAOESTILO_H
