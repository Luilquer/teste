#include "fm_gestaofornecedor.h"
#include "ui_fm_gestaofornecedor.h"
#include <QMessageBox>
#include <QtSql>
#include "funcoes_globais.h"

fm_gestaofornecedor::fm_gestaofornecedor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fm_gestaofornecedor)
{
    ui->setupUi(this);
    //abrir o banco de dados
    if(!con.aberto()){
        if(!con.abrir()){
            QMessageBox::warning(this, "EROO", "Erro ao abrir banco de Dados");
        }
    }



    //posicionar no nome
    ui->txt_gf_nome->setFocus();

    //definir o número de coluna que será exibido na tabela de consulta
    ui->tw_gf_listafor->setColumnCount(2);

    //deixar sempre na primeira aba
    ui->tabWidget->setCurrentIndex(0);

    //definições larguras ...
    ui->tw_gf_listafor->setColumnWidth(0, 50);
    ui->tw_gf_listafor->setColumnWidth(1, 100);

    //cabeçalhos
    QStringList cab = {"ID", "Nome"};

    //inserir na tabela o cabeçalho
    ui->tw_gf_listafor->setHorizontalHeaderLabels(cab);

    //restrições, cor da linha ao ser selecionada
    ui->tw_gf_listafor->setStyleSheet("QTableView {selection-background-color:blue}");

    //desabilitando a edição
    ui->tw_gf_listafor->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //selecionar a linha inteira ao clicar em uma cela
    ui->tw_gf_listafor->setSelectionBehavior(QAbstractItemView::SelectRows);
    //desabilitar os números relacionados à linhas
    ui->tw_gf_listafor->verticalHeader()->setVisible(false);

}

fm_gestaofornecedor::~fm_gestaofornecedor()
{
    delete ui;
}

void fm_gestaofornecedor::on_btn_novo_novofor_clicked()
{
    //limpar todos os campos e focar
    ui->txt_nome_novofor->clear();
    ui->txt_descricao_novofor->clear();


    //centraliza em nome
    ui->txt_nome_novofor->setFocus();
}

void fm_gestaofornecedor::on_btn_gravar_novoforn_clicked()
{
    QString nome=ui->txt_nome_novofor->text();
    QString descricao=ui->txt_descricao_novofor->text();



    //INSERIR NA TABELA
    QSqlQuery query;
    query.prepare("insert into Fornecedor (nome_forn,descricao_forn) values"
                  "('"+nome+"','"+descricao+"')");


    if(!query.exec()){
         QMessageBox::critical(this, "ERRO", "Erro ao inserir novo fornecedor");
    }else{
        QMessageBox::information(this, "GRAVADO", "Fornecedor inserido no Banco de Dados");
        //limpar todos os campos e posicipn
        ui->txt_nome_novofor->clear();
        ui->txt_descricao_novofor->clear();
        //centraliza em nome
        ui->txt_nome_novofor->setFocus();

    }

}

void fm_gestaofornecedor::on_bnt_filtrar_forn_clicked()
{



    //remover linhas da tabela, verificar se exite um valor digitado
    funcoes_globais::removerLinhas(ui->tw_gf_listafor);


    //se tiver vai verificar de acordo com a query

    QString busca;
    //verificar se tem alguma coisa digitada
    if(ui->txt_gf_filtro->text() == ""){
        if(ui->rb_gf_idfor->isChecked()){

                busca="select id_fornecedor,nome_forn from Fornecedor order by id_fornecedor";
        }else{

                busca="select id_fornecedor,nome_forn from Fornecedor order by nome_forn";
        }

        }else{
                if(ui->rb_gf_idfor->isChecked()){

                    busca="select id_fornecedor,nome_forn from Fornecedor where id_fornecedor="+ui->txt_gf_filtro->text()+" order by id_fornecedor";
              }else{

                    busca="select id_fornecedor,nome_forn from Fornecedor where nome_forn like '%"+ ui->txt_gf_filtro->text()+"%' order by nome_forn";

                    }
             }

    int contLinhas = 0;
    QSqlQuery query;
    query.prepare(busca);

    if(query.exec()){
        while(query.next()){
            //faz a inserções de linhas
            ui->tw_gf_listafor->insertRow(contLinhas);
            //inserir a primeira coluna primeiro
            ui->tw_gf_listafor->setItem(contLinhas, 0, new QTableWidgetItem(query.value(0).toString()));
            //segunda coluna
            ui->tw_gf_listafor->setItem(contLinhas, 1, new QTableWidgetItem(query.value(1).toString()));

            //tamanho da linhas
            ui->tw_gf_listafor->setRowHeight(contLinhas, 20);
            contLinhas++;

        }
    }else{

         QMessageBox::warning(this, "ERRO", "Erro ao exibir fornecedor");

    }

    ui->txt_gf_filtro->clear();
    ui->txt_gf_filtro->setFocus();
}



void fm_gestaofornecedor::on_tabWidget_currentChanged(int index)
{
    //verifica se é a primeira(0) tab ou segunda(1)
    if(index == 1){
        funcoes_globais::removerLinhas(ui->tw_gf_listafor);// chama a função para remover linhas

        int contLinhas=0;
        //Remover os produtos do tW, para não exibir duplicatas
        QSqlQuery query;
        //consulta
        query.prepare("select id_fornecedor, nome_forn from Fornecedor order by id_fornecedor");

        if(query.exec()){

            while(query.next()){
                //faz a inserções de linhas
                ui->tw_gf_listafor->insertRow(contLinhas);
                //inserir a primeira coluna primeiro produto
                ui->tw_gf_listafor->setItem(contLinhas, 0, new QTableWidgetItem(query.value(0).toString()));
                //segunda coluna
                ui->tw_gf_listafor->setItem(contLinhas, 1, new QTableWidgetItem(query.value(1).toString()));

                //tamanho da linhas
                ui->tw_gf_listafor->setRowHeight(contLinhas, 20);
                contLinhas++;

            }

        }else{
            QMessageBox::warning(this, "ERRO", "Erro ao listar no Banco de Dados");
        }


    }
}

void fm_gestaofornecedor::on_bnt_gf_escluir_clicked()
{
    //verifica se existe algum botão selecionado
    if(ui->tw_gf_listafor->currentRow() == -1){
        QMessageBox::warning(this, "ERRO", "Erro selecione um fornecedor");
        return;
    }

    //verificar se relamente deve excluir
        QMessageBox::StandardButton opcao;
        opcao = QMessageBox::question(this, "EXCLUSÃO","Confirma a exclusão do usuário ?",QMessageBox::Yes|QMessageBox::No);

        if(opcao == QMessageBox::Yes){
            int linha = ui->tw_gf_listafor->currentRow();
            QString id = ui->tw_gf_listafor->item(linha, 0)->text();

            QSqlQuery query;

            //Deletar
            query.prepare("delete from Fornecedor where id_fornecedor="+id);

            if(query.exec()){
                ui->tw_gf_listafor->removeRow(linha);
                QMessageBox::information(this, "DELETADO", "Fornecedor excluido com sucesso");
            }else{
                QMessageBox::warning(this, "ERRO", "Erro ao excluir na tabela fornecedor");
            }

        }
}

void fm_gestaofornecedor::on_bnt_gf_salvar_clicked()
{
    //verifica se existe algum botão selecionado
    if(ui->tw_gf_listafor->currentRow() == -1){
        QMessageBox::warning(this, "ERRO", "Erro selecione um cliente");
        return;
    }

    //buscar o id
    QString id = ui->tw_gf_listafor->item(ui->tw_gf_listafor->currentRow(), 0)->text();

    //armazena cada um em seus respectivos campos
    QString nome=ui->txt_gf_nome->text();
    QString descricao=ui->txt_gf_descricao->text();


    //Atualização (update) Na tabela
    QSqlQuery query;

    query.prepare("update Fornecedor set nome_forn='"+nome+"', descricao_forn='"+descricao+"' where id_fornecedor="+id);

    if(query.exec()){
        //atualiza os dados
        int linha = ui->tw_gf_listafor->currentRow();
        ui->tw_gf_listafor->item(linha, 1)->setText(nome);

        QMessageBox::information(this, "UPDATE", "Tabela atualizado com sucesso");

    }else{

        QMessageBox::warning(this, "ERRO", "Erro ao atualizar Tabela");
    }
}

void fm_gestaofornecedor::on_tw_gf_listafor_itemSelectionChanged()
{
    //buscar o id do produto, para exibir na tela
    int id;
    //busca passando a linha atual, indice zero(onde está o codigo)
    id = ui->tw_gf_listafor->item(ui->tw_gf_listafor->currentRow(), 0)->text().toInt();

    QSqlQuery query;

    //consulta pelo id
    query.prepare("select * from Fornecedor where id_fornecedor="+QString::number(id));

    //verifica se rodou
    if(query.exec()){
        //toda vez que um produto for selecionado as informações serão
        //exibidas nos campos de texto(respectivamente)
        //preenche com o retorno da query
        query.first();
        //de acordo com a posição na tabela no banco de dados
        ui->txt_gf_nome->setText(query.value(1).toString());
        ui->txt_gf_descricao->setText(query.value(2).toString());


    }
}
