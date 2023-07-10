#ifndef FM_CONSULTARALCOOL_H
#define FM_CONSULTARALCOOL_H

#include <QDialog>
#include "Conexao.h"

namespace Ui {
class fm_consultarAlcool;
}

class fm_consultarAlcool : public QDialog
{
    Q_OBJECT

public:
    explicit fm_consultarAlcool(QWidget *parent = nullptr);
    ~fm_consultarAlcool();
    Conexao con;

private slots:
    void on_pushButton_clicked();

private:
    Ui::fm_consultarAlcool *ui;
};

#endif // FM_CONSULTARALCOOL_H
