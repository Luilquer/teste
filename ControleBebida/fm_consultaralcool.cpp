#include "fm_consultaralcool.h"
#include "ui_fm_consultaralcool.h"

#include <QMessageBox>
#include <QtSql>
#include "funcoes_globais.h"

fm_consultarAlcool::fm_consultarAlcool(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fm_consultarAlcool)
{
    ui->setupUi(this);

    //abrir o banco de dados
    if(!con.aberto()){
        if(!con.abrir()){
            QMessageBox::warning(this, "ERROR", "Erro ao abrir banco de Dados");
        }
    }
}

fm_consultarAlcool::~fm_consultarAlcool()
{
    delete ui;
}

void fm_consultarAlcool::on_pushButton_clicked()
{
    QString alcool = ui->lineEditSearchAlcool->text();

   //Selecionando NA TABELA
    QSqlQuery query;
    if(alcool == ""){
        query.prepare("select count(DISTINCT Estilo.id_estilo) as total from Estilo, Vinho, Cerveja;");
    } else {
        query.prepare("select count(DISTINCT Estilo.id_estilo) as total from Estilo, Vinho, Cerveja where Estilo.alcool_estilo = '"+alcool+"' and vinho.lote_vinho = '1999-02-03' and Cerveja.validade_cerveja = '2022-04-01';");
    }

    if(!query.exec()){
         QMessageBox::critical(this, "ERRO", "Erro ao inserir novo Endereço");
    }else{
        query.first();
        ui->lineEditResultAlcool->setText(query.value(0).toString());
        //limpar todos os campos e posicipn
        ui->lineEditSearchAlcool->clear();
    }
}
