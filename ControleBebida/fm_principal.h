#ifndef FM_PRINCIPAL_H
#define FM_PRINCIPAL_H

#include <QMainWindow>
#include <QtSql>

QT_BEGIN_NAMESPACE
namespace Ui { class fm_principal; }
QT_END_NAMESPACE

class fm_principal : public QMainWindow
{
    Q_OBJECT

public:
    fm_principal(QWidget *parent = nullptr);
    ~fm_principal();
    QIcon cadFechado;
    QIcon *cadAberto=new QIcon();



private slots:
    void on_btn_bloquear_clicked();    

    void on_actionColaboradores_triggered();

    void on_actionSair_triggered();

    void on_actionFornecedor_triggered();

    void on_actionCerveja_triggered();

    void on_actionVinho_triggered();

    void on_actionEstilo_triggered();

    void on_actionHarmonizacao_triggered();

    void on_actionComida_triggered();

    void on_actionEndereco_triggered();

    void on_actionConsultarEndereco_triggered();

    void on_actionConsultarAlcool_triggered();

    void on_actionConsultarComida_triggered();

private:
    Ui::fm_principal *ui;
};
#endif // FM_PRINCIPAL_H
