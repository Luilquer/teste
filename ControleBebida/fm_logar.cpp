#include "fm_logar.h"
#include "ui_fm_logar.h"
#include <QMessageBox>
#include "fm_principal.h"
#include "variaveis_globais.h"


fm_logar::fm_logar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fm_logar)
{
    ui->setupUi(this);
    logado=false;

}

fm_logar::~fm_logar()
{
    delete ui;
}

void fm_logar::on_btn_logar_clicked()
{
    if(!con.abrir()){
        QMessageBox::warning(this, "Erro", "Erro ao abrir o banco de dados");
    }else{
        QString username,senha;
        username=ui->txt_username->text();
        senha=ui->txt_senha->text();
        QSqlQuery query;
        query.prepare("select * from Cliente where username_cliente='"+username+"' and senha_cliente='"+senha+"'");
        if(query.exec()){
            query.first();
            if(query.value(1).toString()!=""){
                variaveis_globais::logado=true;
                variaveis_globais::nome_cliente=query.value(1).toString();
                variaveis_globais::id_cliente=query.value(0).toInt();
                variaveis_globais::acesso_cliente=query.value(5).toString();
                con.fechar();
                close();
            }else{
                QMessageBox::warning(this, "Erro", "Cliente não encontrado");
            }
        }else{
            QMessageBox::warning(this, "Erro", "Falha no login");
        }
    }
    //Login
    con.fechar();
}

void fm_logar::on_btn_cancelar_clicked()
{
    logado=false;
    close();
}


