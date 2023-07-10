#ifndef FM_GESTAOCOMIDA_H
#define FM_GESTAOCOMIDA_H

#include <QDialog>
#include "Conexao.h"


namespace Ui {
class fm_gestaoComida;
}

class fm_gestaoComida : public QDialog
{
    Q_OBJECT

public:
    explicit fm_gestaoComida(QWidget *parent = nullptr);
    ~fm_gestaoComida();
    Conexao con;

private slots:
    void on_pushButtonSalvarComida_1_clicked();

    void on_pushButtonExcluirComida_1_clicked();

    void on_pushButtonSalvarComida_2_clicked();

    void on_pushButtonExcluirComida_2_clicked();

    void on_pushButtonFiltrar_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_tableWidget_itemSelectionChanged();

private:
    Ui::fm_gestaoComida *ui;
};

#endif // FM_GESTAOCOMIDA_H
