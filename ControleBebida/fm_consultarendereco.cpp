#include "fm_consultarendereco.h"
#include "ui_fm_consultarendereco.h"

#include <QMessageBox>
#include <QtSql>
#include "funcoes_globais.h"

fm_consultarEndereco::fm_consultarEndereco(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fm_consultarEndereco)
{
    ui->setupUi(this);

    //abrir o banco de dados
    if(!con.aberto()){
        if(!con.abrir()){
            QMessageBox::warning(this, "ERROR", "Erro ao abrir banco de Dados");
        }
    }




    //listas produtos
    //Organizando a exibição da tabela
    ui->tw_listarEnd->horizontalHeader()->setVisible(true);
    ui->tw_listarEnd->setColumnCount(7);
    QStringList cab1 = {"ID","ID. Cliente","ID. Fornecedor","Cidade","Rua", "UF", "Bairro"};
    ui->tw_listarEnd->setHorizontalHeaderLabels(cab1);
    //fazer um redimencionamento de acordo com o conteudo
    ui->tw_listarEnd->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tw_listarEnd->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //configurar
    ui->tw_listarEnd->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw_listarEnd->setEditTriggers(QAbstractItemView::NoEditTriggers);



    int contLinhas = 0;
    QSqlQuery query;

    //consulta
    query.prepare("select * from Endereco ");
    query.exec();
    query.first();
    //Inserir os elemntos no tw
    do{
        ui->tw_listarEnd->insertRow(contLinhas);
        //inserindo os intens
        ui->tw_listarEnd->setItem(contLinhas, 0, new QTableWidgetItem(query.value(0).toString()));
        ui->tw_listarEnd->setItem(contLinhas, 1, new QTableWidgetItem(query.value(1).toString()));
        ui->tw_listarEnd->setItem(contLinhas, 2, new QTableWidgetItem(query.value(2).toString()));
        ui->tw_listarEnd->setItem(contLinhas, 3, new QTableWidgetItem(query.value(3).toString()));
        ui->tw_listarEnd->setItem(contLinhas, 4, new QTableWidgetItem(query.value(4).toString()));
        ui->tw_listarEnd->setItem(contLinhas, 5, new QTableWidgetItem(query.value(5).toString()));
        ui->tw_listarEnd->setItem(contLinhas, 6, new QTableWidgetItem(query.value(6).toString()));
        contLinhas++;
    }while(query.next());





}

fm_consultarEndereco::~fm_consultarEndereco()
{
    delete ui;
}

void fm_consultarEndereco::on_pushButton_clicked()
{
    QString endereco = ui->lineEditSearchEndereco->text();

   //Selecionando NA TABELA
    QSqlQuery query;
    if(endereco == ""){
        query.prepare("SELECT COUNT(DISTINCT id_endereco) as total FROM Endereco");
    } else {

        query.prepare("SELECT COUNT(DISTINCT id_endereco) as total FROM Endereco, Cliente, Fornecedor where Endereco.bairro = '"+ endereco +"'");
    }

    if(!query.exec()){
         QMessageBox::critical(this, "ERRO", "Erro ao inserir novo Endereço");
    }else{
        query.first();
        ui->lineEditResultEndereco->setText(query.value(0).toString());
        //limpar todos os campos e posicipn
        ui->lineEditSearchEndereco->clear();
    }
}
