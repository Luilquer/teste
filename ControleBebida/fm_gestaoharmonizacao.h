#ifndef FM_GESTAOHARMONIZACAO_H
#define FM_GESTAOHARMONIZACAO_H

#include <QDialog>
#include <QObject>
#include "Conexao.h"

namespace Ui {
class fm_gestaoHarmonizacao;
}

class fm_gestaoHarmonizacao : public QDialog
{
    Q_OBJECT

public:
    explicit fm_gestaoHarmonizacao(QWidget *parent = nullptr);
    ~fm_gestaoHarmonizacao();
    Conexao con;

private slots:
    void on_pushButtonSalvar_1_clicked();

    void on_pushButtonCancelar_clicked();

    void on_pushButtonFiltrar_clicked();

    void on_pushButtonSalvar_2_clicked();

    void on_pushButtonExcluir_clicked();

    void on_tableWidget_itemSelectionChanged();

    void on_tabWidget_currentChanged(int index);

private:
    Ui::fm_gestaoHarmonizacao *ui;
};

#endif // FM_GESTAOHARMONIZACAO_H
