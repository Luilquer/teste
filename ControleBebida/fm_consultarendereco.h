#ifndef FM_CONSULTARENDERECO_H
#define FM_CONSULTARENDERECO_H

#include <QDialog>
#include "Conexao.h"

namespace Ui {
class fm_consultarEndereco;
}

class fm_consultarEndereco : public QDialog
{
    Q_OBJECT

public:
    explicit fm_consultarEndereco(QWidget *parent = nullptr);
    ~fm_consultarEndereco();
    Conexao con;

private slots:
    void on_pushButton_clicked();

private:
    Ui::fm_consultarEndereco *ui;
};

#endif // FM_CONSULTARENDERECO_H
