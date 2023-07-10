#include "fm_gestaocerveja.h"
#include "ui_fm_gestaocerveja.h"
#include <QMessageBox>
#include <QtSql>
#include "funcoes_globais.h"

fm_gestaocerveja::fm_gestaocerveja(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fm_gestaocerveja)
{
    ui->setupUi(this);

    if(!con.aberto()){
        if(!con.abrir()){
            QMessageBox::warning(this, "ERROR", "Erro ao abrir banco de Dados");
        }
    }



    //definir o número de coluna que será exibido na tabela de consulta
    ui->tw_gc_listar->setColumnCount(2);

    //deixar sempre na primeira aba
    ui->tabWidget->setCurrentIndex(0);


    //definições larguras ...
    ui->tw_gc_listar->setColumnWidth(0, 50);
    ui->tw_gc_listar->setColumnWidth(1, 100);

    //cabeçalhos
    QStringList cab = {"ID", "Nome"};

    //inserir na tabela o cabeçalho
    ui->tw_gc_listar->setHorizontalHeaderLabels(cab);

    //restrições, cor da linha ao ser selecionada
    ui->tw_gc_listar->setStyleSheet("QTableView {selection-background-color:blue}");

    //desabilitando a edição
    ui->tw_gc_listar->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //selecionar a linha inteira ao clicar em uma cela
    ui->tw_gc_listar->setSelectionBehavior(QAbstractItemView::SelectRows);
    //desabilitar os números relacionados à linhas
    ui->tw_gc_listar->verticalHeader()->setVisible(false);

}

fm_gestaocerveja::~fm_gestaocerveja()
{
    delete ui;
}

void fm_gestaocerveja::on_btn_add_salvar_clicked()
{
    QString idEstilo=ui->txt_add_estilo->text();
    QString nome=ui->txt_add_nome->text();
    QString validade=ui->txt_add_lote->text();



   //INSERIR NA TABELA
    QSqlQuery query;



        query.prepare("insert into Cerveja (id_estilo,nome_cerveja,validade_cerveja) values"
                   "("+QString::number(idEstilo.toInt())+",'"+nome+"','"+validade+"')");


    if(!query.exec()){
         QMessageBox::critical(this, "ERRO", "Erro ao inserir na tabela");
    }else{
        QMessageBox::information(this, "GRAVADO", "Item inserido no Banco de Dados");
        //limpar todos os campos e posicipn
        ui->txt_add_estilo->clear();
        ui->txt_add_nome->clear();
        ui->txt_add_lote->clear();
        ui->txt_add_nome->setFocus();

    }
}

void fm_gestaocerveja::on_btn_add_limpar_clicked()
{
    //limpar todos os campos e posicipn
    ui->txt_add_estilo->clear();
    ui->txt_add_nome->clear();
    ui->txt_add_lote->clear();
    ui->txt_add_nome->setFocus();
}

void fm_gestaocerveja::on_btn_gv_filtrar_clicked()
{
    //remover linhas da tabela, verificar se exite um valor digitado
    funcoes_globais::removerLinhas(ui->tw_gc_listar);


    //se tiver vai verificar de acordo com a query

    QString busca;
    //verificar se tem alguma coisa digitada
    if(ui->txt_gc_filtrar->text() == ""){
        if(ui->rb_gc_idCerveja->isChecked()){

                busca="select id_cerveja,nome_cerveja from Cerveja order by id_cerveja";
        }else{

                busca="select id_cerveja,nome_cerveja from Cerveja order by nome_cerveja";
             }
        }else{
                if(ui->rb_gc_idCerveja->isChecked()){

                    busca="select id_cerveja,nome_cerveja from Cerveja where id_cerveja="+ui->txt_gc_filtrar->text()+" order by id_cerveja";
              }else{

                    busca="select id_cerveja,nome_cerveja from Cerveja where nome_cerveja like '%"+ ui->txt_gc_filtrar->text()+"%' order by nome_cerveja";

                    }
             }

    int contLinhas = 0;
    QSqlQuery query;
    query.prepare(busca);

    if(query.exec()){
        while(query.next()){
            //faz a inserções de linhas
            ui->tw_gc_listar->insertRow(contLinhas);
            //inserir a primeira coluna primeiro
            ui->tw_gc_listar->setItem(contLinhas, 0, new QTableWidgetItem(query.value(0).toString()));
            //segunda coluna
            ui->tw_gc_listar->setItem(contLinhas, 1, new QTableWidgetItem(query.value(1).toString()));

            //tamanho da linhas
            ui->tw_gc_listar->setRowHeight(contLinhas, 20);
            contLinhas++;

        }
    }else{

         QMessageBox::warning(this, "ERRO", "Erro ao exibir tabela");

    }

    ui->txt_gc_filtrar->clear();
    ui->txt_gc_filtrar->setFocus();
}

void fm_gestaocerveja::on_tw_gc_listar_itemSelectionChanged()
{
    //buscar o id do produto, para exibir na tela
    int id;
    //busca passando a linha atual, indice zero(onde está o codigo)
    id = ui->tw_gc_listar->item(ui->tw_gc_listar->currentRow(), 0)->text().toInt();

    QSqlQuery query;

    //consulta pelo id
    query.prepare("select * from Cerveja where id_cerveja="+QString::number(id));

    //verifica se rodou
    if(query.exec()){
         query.first();
        //de acordo com a posição na tabela no banco de dados
        ui->txt_gc_estilo->setText(query.value(1).toString());
        ui->txt_gc_nome->setText(query.value(2).toString());
        ui->txt_gc_lote->setText(query.value(3).toString());

    }
}

void fm_gestaocerveja::on_pushButtonSalvar_2_clicked()
{
    //verifica se existe algum botão selecionado
    if(ui->tw_gc_listar->currentRow() == -1){
        QMessageBox::warning(this, "ERRO", "Erro selecione um item");
        return;
    }


    //buscar o id
    QString id = ui->tw_gc_listar->item(ui->tw_gc_listar->currentRow(), 0)->text();

    //armazena cada um em seus respectivos campos
    QString idEstilo=ui->txt_gc_estilo->text();
    QString nome=ui->txt_gc_nome->text();
    QString lote=ui->txt_gc_lote->text();



    //Atualização (update) Na tabela
    QSqlQuery query;

    query.prepare("update Cerveja set id_estilo='"+QString::number(idEstilo.toInt())+"', nome_cerveja='"+nome+"', validade_cerveja='"+lote+"' where id_cerveja="+id);

    if(!query.exec()){
        QMessageBox::information(this, "ERRO", "ERRO NA ATUALIZAÇÃO");

    }


    if(query.exec()){
        //atualiza os dados
        int linha = ui->tw_gc_listar->currentRow();
        ui->tw_gc_listar->item(linha, 1)->setText(nome);

        QMessageBox::information(this, "UPDATE", "Tabela atualizado com sucesso");

    }else{

        QMessageBox::warning(this, "ERRO", "Erro ao atualizar Tabela");
    }
}

void fm_gestaocerveja::on_pushButtonExcluir_2_clicked()
{
    //verifica se existe algum botão selecionado
    if(ui->tw_gc_listar->currentRow() == -1){
        QMessageBox::warning(this, "ERRO", "Erro selecione um item");
        return;
    }

    //verificar se relamente deve excluir
        QMessageBox::StandardButton opcao;
        opcao = QMessageBox::question(this, "EXCLUSÃO","Confirma a exclusão do item ?",QMessageBox::Yes|QMessageBox::No);

        if(opcao == QMessageBox::Yes){
            int linha = ui->tw_gc_listar->currentRow();
            QString id = ui->tw_gc_listar->item(linha, 0)->text();

            QSqlQuery query;

            //Deletar
            query.prepare("delete from Cerveja where id_cerveja="+id);

            if(query.exec()){
                ui->tw_gc_listar->removeRow(linha);
                QMessageBox::information(this, "DELETADO", "Item excluido com sucesso");
            }else{
                QMessageBox::warning(this, "ERRO", "Erro ao excluir na tabela");
            }

        }

}
