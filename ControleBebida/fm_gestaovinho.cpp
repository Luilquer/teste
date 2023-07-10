#include "fm_gestaovinho.h"
#include "ui_fm_gestaovinho.h"
#include <QMessageBox>
#include <QtSql>
#include "funcoes_globais.h"

fm_gestaoVinho::fm_gestaoVinho(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fm_gestaoVinho)
{
    ui->setupUi(this);
    //abrir o banco de dados
    if(!con.aberto()){
        if(!con.abrir()){
            QMessageBox::warning(this, "ERROR", "Erro ao abrir banco de Dados");
        }
    }


    //definir o número de coluna que será exibido na tabela de consulta
    ui->tw_gv_listar->setColumnCount(2);

    //deixar sempre na primeira aba
    ui->tabWidget->setCurrentIndex(0);


    //definições larguras ...
    ui->tw_gv_listar->setColumnWidth(0, 50);
    ui->tw_gv_listar->setColumnWidth(1, 100);

    //cabeçalhos
    QStringList cab = {"ID", "Nome"};

    //inserir na tabela o cabeçalho
    ui->tw_gv_listar->setHorizontalHeaderLabels(cab);

    //restrições, cor da linha ao ser selecionada
    ui->tw_gv_listar->setStyleSheet("QTableView {selection-background-color:blue}");

    //desabilitando a edição
    ui->tw_gv_listar->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //selecionar a linha inteira ao clicar em uma cela
    ui->tw_gv_listar->setSelectionBehavior(QAbstractItemView::SelectRows);
    //desabilitar os números relacionados à linhas
    ui->tw_gv_listar->verticalHeader()->setVisible(false);



}

fm_gestaoVinho::~fm_gestaoVinho()
{
    delete ui;
}



void fm_gestaoVinho::on_btn_add_salvar_clicked()
{
    QString idEstilo=ui->txt_add_estilo->text();
    QString nome=ui->txt_add_nome->text();
    QString lote=ui->txt_add_lote->text();
    QString docura=ui->txt_add_docura->text();
    QString acidez=ui->txt_add_acidez->text();


    //INSERIR NA TABELA
    QSqlQuery query;

        query.prepare("insert into Vinho (id_estilo,nome_vinho,lote_vinho,doncura_vinho,acidez_vinho) values"
                    "("+QString::number(idEstilo.toInt())+",'"+nome+"','"+lote+"','"+docura+"','"+acidez+"')");


    if(!query.exec()){
         QMessageBox::critical(this, "ERRO", "Erro ao inserir na tabela Vinho");
    }else{
        QMessageBox::information(this, "GRAVADO", "Dados inseridos no Banco de Dados");
        //limpar todos os campos e posicipn
        ui->txt_add_estilo->clear();
        ui->txt_add_nome->clear();
        ui->txt_add_lote->clear();
        ui->txt_add_docura->clear();
        ui->txt_add_acidez->clear();
        ui->txt_add_nome->setFocus();

    }

}

void fm_gestaoVinho::on_pushButtonSalvar_2_clicked()
{
    //verifica se existe algum botão selecionado
    if(ui->tw_gv_listar->currentRow() == -1){
        QMessageBox::warning(this, "ERRO", "Erro selecione um item");
        return;
    }


    //buscar o id
    QString id = ui->tw_gv_listar->item(ui->tw_gv_listar->currentRow(), 0)->text();

    //armazena cada um em seus respectivos campos
    QString idEstilo=ui->txt_gv_estilo->text();
    QString nome=ui->txt_gv_nome->text();
    QString lote=ui->txt_gv_lote->text();
    QString docura=ui->txt_gv_docura->text();
    QString acidez=ui->txt_gv_acidez->text();


    //Atualização (update) Na tabela Clientes
    QSqlQuery query;
    //não pode ter espaços entre as ","


    query.prepare("update Vinho set id_estilo='"+QString::number(idEstilo.toInt())+"', nome_vinho='"+nome+"', lote_vinho='"+lote+"', doncura_vinho='"+docura+"', acidez_vinho='"+acidez+"' where id_vinho="+id);
    if(!query.exec()){
        QMessageBox::information(this, "ERRO", "ERRO NA ATUALIZAÇÃO");

    }


    if(query.exec()){
        //atualiza os dados
        int linha = ui->tw_gv_listar->currentRow();
        ui->tw_gv_listar->item(linha, 1)->setText(nome);

        QMessageBox::information(this, "UPDATE", "Tabela atualizado com sucesso");

    }else{

        QMessageBox::warning(this, "ERRO", "Erro ao atualizar Tabela");
    }
}

void fm_gestaoVinho::on_tabWidget_currentChanged(int index)
{
    //verifica se é a primeira(0) tab ou segunda(1)
    if(index == 1){
        funcoes_globais::removerLinhas(ui->tw_gv_listar);// chama a função para remover linhas

        int contLinhas=0;
        //Remover os produtos do tW, para não exibir duplicatas
        QSqlQuery query;
        //consulta
        query.prepare("select id_vinho, nome_vinho from Vinho order by id_vinho");

        if(query.exec()){

            while(query.next()){
                //faz a inserções de linhas
                ui->tw_gv_listar->insertRow(contLinhas);
                //inserir a primeira coluna primeiro produto
                ui->tw_gv_listar->setItem(contLinhas, 0, new QTableWidgetItem(query.value(0).toString()));
                //segunda coluna
                ui->tw_gv_listar->setItem(contLinhas, 1, new QTableWidgetItem(query.value(1).toString()));

                //tamanho da linhas
                ui->tw_gv_listar->setRowHeight(contLinhas, 20);
                contLinhas++;

            }

        }else{
            QMessageBox::warning(this, "ERRO", "Erro ao listar no Banco de Dados");
        }


    }
}

void fm_gestaoVinho::on_pushButtonExcluir_2_clicked()
{
    //verifica se existe algum botão selecionado
    if(ui->tw_gv_listar->currentRow() == -1){
        QMessageBox::warning(this, "ERRO", "Erro selecione um cliente");
        return;
    }

    //verificar se relamente deve excluir
        QMessageBox::StandardButton opcao;
        opcao = QMessageBox::question(this, "EXCLUSÃO","Confirma a exclusão do usuário ?",QMessageBox::Yes|QMessageBox::No);

        if(opcao == QMessageBox::Yes){
            int linha = ui->tw_gv_listar->currentRow();
            QString id = ui->tw_gv_listar->item(linha, 0)->text();

            QSqlQuery query;

            //Deletar
            query.prepare("delete from Vinho where id_vinho="+id);

            if(query.exec()){
                ui->tw_gv_listar->removeRow(linha);
                QMessageBox::information(this, "DELETADO", "Item excluido com sucesso");
            }else{
                QMessageBox::warning(this, "ERRO", "Erro ao excluir na tabela");
            }

        }
}

void fm_gestaoVinho::on_tw_gv_listar_itemSelectionChanged()
{
    //buscar o id do produto, para exibir na tela
    int id;
    //busca passando a linha atual, indice zero(onde está o codigo)
    id = ui->tw_gv_listar->item(ui->tw_gv_listar->currentRow(), 0)->text().toInt();

    QSqlQuery query;

    //consulta pelo id
    query.prepare("select * from Vinho where id_vinho="+QString::number(id));

    //verifica se rodou
    if(query.exec()){
         query.first();
        //de acordo com a posição na tabela no banco de dados
        ui->txt_gv_estilo->setText(query.value(1).toString());
        ui->txt_gv_nome->setText(query.value(2).toString());
        ui->txt_gv_lote->setText(query.value(3).toString());
        ui->txt_gv_docura->setText(query.value(4).toString());
        ui->txt_gv_acidez->setText(query.value(5).toString());


    }
}

void fm_gestaoVinho::on_btn_gv_filtrar_clicked()
{
    //remover linhas da tabela, verificar se exite um valor digitado
    funcoes_globais::removerLinhas(ui->tw_gv_listar);


    //se tiver vai verificar de acordo com a query

    QString busca;
    //verificar se tem alguma coisa digitada
    if(ui->txt_gv_filtrar->text() == ""){
        if(ui->rb_gv_idVinho->isChecked()){

                busca="select id_vinho,nome_vinho from Vinho order by id_vinho";
        }else{

                busca="select id_vinho,nome_vinho from Vinho order by nome_vinho";
             }
        }else{
                if(ui->rb_gv_idVinho->isChecked()){

                    busca="select id_vinho,nome_vinho from Vinho where id_vinho="+ui->txt_gv_filtrar->text()+" order by id_vinho";
              }else{

                    busca="select id_vinho,nome_vinho from Vinho where nome_vinho like '%"+ ui->txt_gv_filtrar->text()+"%' order by nome_vinho";

                    }
             }

    int contLinhas = 0;
    QSqlQuery query;
    query.prepare(busca);

    if(query.exec()){
        while(query.next()){
            //faz a inserções de linhas
            ui->tw_gv_listar->insertRow(contLinhas);
            //inserir a primeira coluna primeiro
            ui->tw_gv_listar->setItem(contLinhas, 0, new QTableWidgetItem(query.value(0).toString()));
            //segunda coluna
            ui->tw_gv_listar->setItem(contLinhas, 1, new QTableWidgetItem(query.value(1).toString()));

            //tamanho da linhas
            ui->tw_gv_listar->setRowHeight(contLinhas, 20);
            contLinhas++;

        }
    }else{

         QMessageBox::warning(this, "ERRO", "Erro ao exibir tabela");

    }

    ui->txt_gv_filtrar->clear();
    ui->txt_gv_filtrar->setFocus();
}

void fm_gestaoVinho::on_btn_add_limpar_clicked()
{
    ui->txt_add_estilo->clear();
    ui->txt_add_nome->clear();
    ui->txt_add_lote->clear();
    ui->txt_add_docura->clear();
    ui->txt_add_acidez->clear();
    ui->txt_add_nome->setFocus();
}
