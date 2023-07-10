#include "fm_principal.h"
#include "ui_fm_principal.h"
#include <QMessageBox>
#include "fm_logar.h"
#include "fm_gestaocolaboradores.h"
#include "variaveis_globais.h"
#include "fm_gestaofornecedor.h"

#include "fm_endereco.h"
#include "fm_gestaocerveja.h"
#include "fm_gestaovinho.h"
#include "fm_gestaoestilo.h"
#include "fm_gestaoharmonizacao.h"
#include "fm_gestaocomida.h"
#include "fm_consultarendereco.h"
#include "fm_consultaralcool.h"
#include "fm_consultarcomida.h"

//declarações globais
int variaveis_globais::id_cliente;
QString variaveis_globais::nome_cliente;
QString variaveis_globais::acesso_cliente;
QString variaveis_globais::username_cliente;
bool variaveis_globais::logado;

fm_principal::fm_principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::fm_principal)
{
    ui->setupUi(this);



    variaveis_globais::logado=false;
    cadFechado.addFile(":/imagens/Cadeado Fechado.png");
    cadAberto->addFile(":/imagens/Cadeado Aberto.png");

    //tirar o texto
    ui->btn_bloquear->setText("");
    ui->btn_bloquear->setIcon(cadFechado);
    ui->statusbar->addWidget(ui->btn_bloquear);
    ui->statusbar->addWidget(ui->lb_nome);


}

fm_principal::~fm_principal()
{
    delete ui;
}


void fm_principal::on_btn_bloquear_clicked()
{
    if(!variaveis_globais::logado){
        //chamar tela tela desbloqueio
        fm_logar f_logar;
        f_logar.exec();

        if(variaveis_globais::logado){
            ui->btn_bloquear->setIcon(*cadAberto);
            ui->lb_nome->setText(variaveis_globais::nome_cliente);
        }

    }else{
        variaveis_globais::logado=false;
         ui->btn_bloquear->setIcon(cadFechado);
         ui->lb_nome->setText("Sem Cliente");
    }
}




//Verifica qual o tipo de acesso
void fm_principal::on_actionColaboradores_triggered()
{
    if(variaveis_globais::logado){
        if(variaveis_globais::acesso_cliente=="A"){
            fm_gestaoColaboradores f_gestaoColaboradores;
            f_gestaoColaboradores.exec();
        }else{
            QMessageBox::information(this, "ACESSO", "ACESSO NÃO PERMITIDO");
        }
    }else{
         QMessageBox::information(this, "Login", "Não existe cliente logado");
    }
}




void fm_principal::on_actionSair_triggered()
{
    close();
}

//!-----------------------Fornecedor--------------------------
void fm_principal::on_actionFornecedor_triggered()
{
    //verifica se existe cliente logado
    if(variaveis_globais::logado){
        if(variaveis_globais::acesso_cliente=="A"){
            //cria um objeto do tipo fornecedor
            fm_gestaofornecedor f_gestaofornecedor;
            //executa a janela fornecedor
            f_gestaofornecedor.exec();

        }else{
            QMessageBox::information(this, "ACESSO", "ACESSO NÃO PERMITIDO");
        }
        //se for inserirdo um cliente que não consta no banco de dados
    }else{
         QMessageBox::information(this, "Login", "Não existe cliente logado");
    }
}


//!-----------------------Endereco--------------------------
void fm_principal::on_actionEndereco_triggered()
{
    if(variaveis_globais::logado){
        if(variaveis_globais::acesso_cliente=="A"){
            fm_endereco f_endereco;
            f_endereco.exec();
        }else{
            QMessageBox::information(this, "ACESSO", "ACESSO NÃO PERMITIDO");
        }
    }else{
         QMessageBox::information(this, "Login", "Não existe cliente logado");
    }
}


//!-----------------------Vinho--------------------------
void fm_principal::on_actionVinho_triggered()
{
    if(variaveis_globais::logado){
        if(variaveis_globais::acesso_cliente=="A"){
            fm_gestaoVinho f_gestaoVinho;
            f_gestaoVinho.exec();
        }else{
            QMessageBox::information(this, "ACESSO", "ACESSO NÃO PERMITIDO");
        }
    }else{
         QMessageBox::information(this, "Login", "Não existe cliente logado");
    }
}


//!-----------------------Estilo--------------------------
void fm_principal::on_actionEstilo_triggered()
{
    if(variaveis_globais::logado){
        if(variaveis_globais::acesso_cliente=="A"){
            fm_gestaoEstilo f_gestaoEstilo;
            f_gestaoEstilo.exec();
        }else{
            QMessageBox::information(this, "ACESSO", "ACESSO NÃO PERMITIDO");
        }
    }else{
         QMessageBox::information(this, "Login", "Não existe cliente logado");
    }
}


//!-----------------------Hamonizacao--------------------------
void fm_principal::on_actionHarmonizacao_triggered()
{
    if(variaveis_globais::logado){
        if(variaveis_globais::acesso_cliente=="A"){
            fm_gestaoHarmonizacao f_gestaoHarmonizacao;
            f_gestaoHarmonizacao.exec();
        }else{
            QMessageBox::information(this, "ACESSO", "ACESSO NÃO PERMITIDO");
        }
    }else{
         QMessageBox::information(this, "Login", "Não existe cliente logado");
    }
}


//!-----------------------Comida--------------------------
void fm_principal::on_actionComida_triggered()
{
    if(variaveis_globais::logado){
        if(variaveis_globais::acesso_cliente=="A"){
            fm_gestaoComida f_gestaoComida;
            f_gestaoComida.exec();
        }else{
            QMessageBox::information(this, "ACESSO", "ACESSO NÃO PERMITIDO");
        }
    }else{
         QMessageBox::information(this, "Login", "Não existe cliente logado");
    }
}



//!-----------------------Cerveja--------------------------
void fm_principal::on_actionCerveja_triggered()
{
    if(variaveis_globais::logado){
        if(variaveis_globais::acesso_cliente=="A"){
            fm_gestaocerveja f_gestaocerveja;
            f_gestaocerveja.exec();
        }else{
            QMessageBox::information(this, "ACESSO", "ACESSO NÃO PERMITIDO");
        }
    }else{
         QMessageBox::information(this, "Login", "Não existe cliente logado");
    }
}

//!-----------------------ConsultarEndereco--------------------------
void fm_principal::on_actionConsultarEndereco_triggered()
{
    if(variaveis_globais::logado){
        if(variaveis_globais::acesso_cliente=="A"){
            fm_consultarEndereco f_consultarEndereco;
            f_consultarEndereco.exec();
        }else{
            QMessageBox::information(this, "ACESSO", "ACESSO NÃO PERMITIDO");
        }
    }else{
         QMessageBox::information(this, "Login", "Não existe cliente logado");
    }
}

//!-----------------------ConsultarAlcool--------------------------
void fm_principal::on_actionConsultarAlcool_triggered()
{
    if(variaveis_globais::logado){
        if(variaveis_globais::acesso_cliente=="A"){
            fm_consultarAlcool f_consultarAlcool;
            f_consultarAlcool.exec();
        }else{
            QMessageBox::information(this, "ACESSO", "ACESSO NÃO PERMITIDO");
        }
    }else{
         QMessageBox::information(this, "Login", "Não existe cliente logado");
    }
}

//!-----------------------ConsultarComida--------------------------
void fm_principal::on_actionConsultarComida_triggered()
{
    if(variaveis_globais::logado){
        if(variaveis_globais::acesso_cliente=="A"){
            fm_consultarComida f_consultarComida;
            f_consultarComida.exec();
        }else{
            QMessageBox::information(this, "ACESSO", "ACESSO NÃO PERMITIDO");
        }
    }else{
         QMessageBox::information(this, "Login", "Não existe cliente logado");
    }
}
