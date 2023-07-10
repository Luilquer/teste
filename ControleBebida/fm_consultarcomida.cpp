#include "fm_consultarcomida.h"
#include "ui_fm_consultarcomida.h"

#include <QMessageBox>
#include <QtSql>
#include "funcoes_globais.h"

fm_consultarComida::fm_consultarComida(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fm_consultarComida)
{
    ui->setupUi(this);

    //abrir o banco de dados
    if(!con.aberto()){
        if(!con.abrir()){
            QMessageBox::warning(this, "ERROR", "Erro ao abrir banco de Dados");
        }
    }
}

fm_consultarComida::~fm_consultarComida()
{
    delete ui;
}

void fm_consultarComida::on_pushButton_clicked()
{
    QString comida = ui->lineEditSearchComida->text();

   //Selecionando NA TABELA
    QSqlQuery query;
    if(comida == ""){
        query.prepare("select count(DISTINCT Comida.id_comida) from Comida, Harmonizacao, Vinho, Comida_harmonizacao, Vinho_harmonizacao;");
    } else {
        query.prepare("select count(DISTINCT Comida.id_comida) as Total from Comida, Harmonizacao, Vinho, Comida_harmonizacao, Vinho_harmonizacao where Comida.nome_comida = '"+comida+"' and Comida.id_comida = Comida_harmonizacao.id_comida  and Comida_harmonizacao.id_harmonizacao = Harmonizacao.id_harmonizacao  and Harmonizacao.id_harmonizacao = Vinho_harmonizacao.id_harmonizacao  and Vinho_harmonizacao.id_vinho = Vinho.id_vinho;");
    }

    if(!query.exec()){
         QMessageBox::critical(this, "ERRO", "Erro ao inserir novo Endereço");
    }else{
        query.first();
        ui->lineEditResultComida->setText(query.value(0).toString());
        //limpar todos os campos e posicipn
        ui->lineEditSearchComida->clear();
    }
}
