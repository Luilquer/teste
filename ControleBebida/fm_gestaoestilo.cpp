#include "fm_gestaoestilo.h"
#include "ui_fm_gestaoestilo.h"
#include <QMessageBox>
#include <QtSql>
#include "funcoes_globais.h"

fm_gestaoEstilo::fm_gestaoEstilo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fm_gestaoEstilo)
{
    ui->setupUi(this);
    //abrir o banco de dados
    if(!con.aberto()){
        if(!con.abrir()){
            QMessageBox::warning(this, "ERRO", "Erro ao abrir banco de Dados");
        }
    }


    //definir o número de coluna que será exibido na tabela de consulta
    ui->tw_estilo->setColumnCount(2);

    //definições larguras ...
    ui->tw_estilo->setColumnWidth(0, 50);
    ui->tw_estilo->setColumnWidth(1, 100);

    //cabeçalhos
    QStringList cab = {"ID", "Nome"};

    //inserir na tabela o cabeçalho
    ui->tw_estilo->setHorizontalHeaderLabels(cab);

    //restrições, cor da linha ao ser selecionada
    ui->tw_estilo->setStyleSheet("QTableView {selection-background-color:blue}");

    //desabilitando a edição
    ui->tw_estilo->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //selecionar a linha inteira ao clicar em uma cela
    ui->tw_estilo->setSelectionBehavior(QAbstractItemView::SelectRows);
    //desabilitar os números relacionados à linhas
    ui->tw_estilo->verticalHeader()->setVisible(false);




}

fm_gestaoEstilo::~fm_gestaoEstilo()
{
    delete ui;
}



void fm_gestaoEstilo::on_btn_add_clicked()
{
    QString nome=ui->txt_nomeEstilo->text();
    QString cor=ui->txt_corEstilo->text();
    QString ingrediente=ui->txt_ingrediente_estilo->text();
    QString alcool=ui->txt_alcoolEstilo->text();

   //INSERIR NA TABELA
    QSqlQuery query;

        query.prepare("insert into Estilo (nome_estilo,cor_estilo,ingrediente_estilo,alcool_estilo) values"
                    "('"+nome+"','"+cor+"','"+ingrediente+"','"+alcool+"')");


    if(!query.exec()){
         QMessageBox::critical(this, "ERRO", "Erro ao inserir novo Endereço");
    }else{
        QMessageBox::information(this, "GRAVADO", "Endereço inserido no Banco de Dados");
        //limpar todos os campos e posicipn
        ui->txt_nomeEstilo->clear();
        ui->txt_corEstilo->clear();
        ui->txt_ingrediente_estilo->clear();
        ui->txt_alcoolEstilo->clear();
        ui->txt_nomeEstilo->setFocus();

    }
}

void fm_gestaoEstilo::on_btn_filtrar_clicked()
{
    //remover linhas da tabela, verificar se exite um valor digitado
    funcoes_globais::removerLinhas(ui->tw_estilo);


    //se tiver vai verificar de acordo com a query

    QString busca;
    //verificar se tem alguma coisa digitada
    if(ui->txt_filtro->text() == ""){
        if(ui->rb_idEstilo->isChecked()){
                QStringList cab = {"ID", "Nome"};
                ui->tw_estilo->setHorizontalHeaderLabels(cab);
                busca="select id_estilo,nome_estilo from Estilo order by id_estilo";

        }else if(ui->rb_nome->isChecked()){

                QStringList cab = {"ID", "Nome"};
                ui->tw_estilo->setHorizontalHeaderLabels(cab);
                busca="select id_estilo,nome_estilo from Estilo order by nome_estilo";

        }else if(ui->rb_cor->isChecked()){

            //cabeçalhos
            QStringList cab = {"ID", "Cor"};

            //inserir na tabela o cabeçalho
            ui->tw_estilo->setHorizontalHeaderLabels(cab);
            busca="select id_estilo,cor_estilo from Estilo order by cor_estilo";

        }else if(ui->rb_alcool->isChecked()){

                QStringList cab = {"ID", "Alcool"};

                busca="select id_estilo,alcool_estilo from Estilo order by alcool_estilo";
                //inserir na tabela o cabeçalho
                ui->tw_estilo->setHorizontalHeaderLabels(cab);

        }else if(ui->rb_ingrediente->isChecked()) {

                QStringList cab = {"ID", "Ingrediente"};
                busca="select id_estilo,ingrediente_estilo from Estilo order by ingrediente_estilo";
                ui->tw_estilo->setHorizontalHeaderLabels(cab);
        }




        }else{
                if(ui->rb_idEstilo->isChecked()){

                    QStringList cab = {"ID", "Nome"};
                    ui->tw_estilo->setHorizontalHeaderLabels(cab);
                    busca="select id_estilo,nome_estilo from Estilo where id_estilo="+ui->txt_filtro->text()+" order by id_estilo";

                }else if(ui->rb_nome->isChecked()){

                    QStringList cab = {"ID", "Nome"};
                    ui->tw_estilo->setHorizontalHeaderLabels(cab);
                    busca="select id_estilo,nome_estilo from Estilo where nome_estilo like '%"+ ui->txt_filtro->text()+"%' order by nome_estilo";

                }else if(ui->rb_cor->isChecked()){

                    QStringList cab = {"ID", "Cor"};
                    ui->tw_estilo->setHorizontalHeaderLabels(cab);
                    busca="select id_estilo,cor_estilo from Estilo where cor_estilo like '%"+ ui->txt_filtro->text()+"%' order by cor_estilo";

                }else if(ui->rb_alcool->isChecked()){

                    QStringList cab = {"ID", "Alcool"};
                    ui->tw_estilo->setHorizontalHeaderLabels(cab);
                    busca="select id_estilo,alcool_estilo from Estilo where alcool_estilo like '%"+ ui->txt_filtro->text()+"%' order by alcool_estilo";

                }else if(ui->rb_ingrediente->isChecked()){

                    QStringList cab = {"ID", "Ingrediente"};
                    ui->tw_estilo->setHorizontalHeaderLabels(cab);
                    busca="select id_estilo,ingrediente_estilo from Estilo where ingrediente_estilo like '%"+ ui->txt_filtro->text()+"%' order by ingrediente_estilo";

                }
             }

    int contLinhas = 0;
    QSqlQuery query;
    query.prepare(busca);

    if(query.exec()){
        while(query.next()){
            //faz a inserções de linhas
            ui->tw_estilo->insertRow(contLinhas);
            //inserir a primeira coluna primeiro
            ui->tw_estilo->setItem(contLinhas, 0, new QTableWidgetItem(query.value(0).toString()));
            //segunda coluna
            ui->tw_estilo->setItem(contLinhas, 1, new QTableWidgetItem(query.value(1).toString()));

            //tamanho da linhas
            ui->tw_estilo->setRowHeight(contLinhas, 20);
            contLinhas++;

        }
    }else{

         QMessageBox::warning(this, "ERRO", "Erro ao exibir itens");

    }

    ui->txt_filtro->clear();
    ui->txt_filtro->setFocus();
}

void fm_gestaoEstilo::on_tw_estilo_itemSelectionChanged()
{
    //buscar o id do produto, para exibir na tela
    int id;
    //busca passando a linha atual, indice zero(onde está o codigo)
    id = ui->tw_estilo->item(ui->tw_estilo->currentRow(), 0)->text().toInt();

    QSqlQuery query;

    //consulta pelo id
    query.prepare("select * from Estilo where id_estilo="+QString::number(id));

    //verifica se rodou
    if(query.exec()){
        query.first();
        //de acordo com a posição na tabela no banco de dados
        ui->txt_nomeEstilo->setText(query.value(1).toString());//id
        ui->txt_corEstilo->setText(query.value(2).toString());//...
        ui->txt_ingrediente_estilo->setText(query.value(3).toString());
        ui->txt_alcoolEstilo->setText(query.value(4).toString());

    }
}

void fm_gestaoEstilo::on_btn_salvar_clicked()
{

    //verifica se existe algum botão selecionado
    if(ui->tw_estilo->currentRow() == -1){
        QMessageBox::warning(this, "ERRO", "Erro selecione um item");
        return;
    }


    //buscar o id
    QString id = ui->tw_estilo->item(ui->tw_estilo->currentRow(), 0)->text();

    //armazena cada um em seus respectivos campos
    QString nome=ui->txt_nomeEstilo->text();
    QString cor=ui->txt_corEstilo->text();
    QString ingrediente=ui->txt_ingrediente_estilo->text();
    QString alcool=ui->txt_alcoolEstilo->text();


    //Atualização (update) Na tabela Clientes
    QSqlQuery query;
    //query.prepare("insert into Estilo (nome_estilo,cor_estilo,ingrediente_estilo,alcool_estilo) values"
    //"('"+nome+"','"+cor+"','"+ingrediente+"','"+alcool+"')");
    query.prepare("update Estilo set nome_estilo='"+nome+"', cor_estilo='"+cor+"', ingrediente_estilo='"+ingrediente+"', alcool_estilo='"+alcool+"' where id_estilo="+id);

    if(query.exec()){
        //atualiza os dados
        int linha = ui->tw_estilo->currentRow();
        ui->tw_estilo->item(linha, 1)->setText(nome);

        QMessageBox::information(this, "UPDATE", "Tabela atualizado com sucesso");

    }else{

        QMessageBox::warning(this, "ERRO", "Erro ao atualizar Tabela");
    }

}

void fm_gestaoEstilo::on_btn_excluir_clicked()
{
    //verifica se existe algum botão selecionado
    if(ui->tw_estilo->currentRow() == -1){
        QMessageBox::warning(this, "ERRO", "Erro selecione um item");
        return;
    }

    //verificar se relamente deve excluir
        QMessageBox::StandardButton opcao;
        opcao = QMessageBox::question(this, "EXCLUSÃO","Confirma a exclusão do item ?",QMessageBox::Yes|QMessageBox::No);

        if(opcao == QMessageBox::Yes){
            int linha = ui->tw_estilo->currentRow();
            QString id = ui->tw_estilo->item(linha, 0)->text();

            QSqlQuery query;

            //Deletar
            query.prepare("delete from Estilo where id_estilo="+id);

            if(query.exec()){
                ui->tw_estilo->removeRow(linha);
                QMessageBox::information(this, "DELETADO", "Item excluido com sucesso");
            }else{
                QMessageBox::warning(this, "ERRO", "Erro ao excluir Item");
            }

        }
}
