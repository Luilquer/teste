#include "fm_endereco.h"
#include "ui_fm_endereco.h"
#include <QMessageBox>
#include <QtSql>
#include "funcoes_globais.h"


fm_endereco::fm_endereco(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fm_endereco)
{
    ui->setupUi(this);
    //abrir o banco de dados
    if(!con.aberto()){
        if(!con.abrir()){
            QMessageBox::warning(this, "ERROR", "Erro ao abrir banco de Dados");
        }
    }

    //definir o número de coluna que será exibido na tabela de consulta
    ui->tw_listaEnd->setColumnCount(2);


    //definições larguras ...
    ui->tw_listaEnd->setColumnWidth(0, 50);
    ui->tw_listaEnd->setColumnWidth(1, 100);

    //cabeçalhos
    QStringList cab = {"ID", "Cidade"};

    //inserir na tabela o cabeçalho
    ui->tw_listaEnd->setHorizontalHeaderLabels(cab);

    //restrições, cor da linha ao ser selecionada
    ui->tw_listaEnd->setStyleSheet("QTableView {selection-background-color:blue}");

    //desabilitando a edição
    ui->tw_listaEnd->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //selecionar a linha inteira ao clicar em uma cela
    ui->tw_listaEnd->setSelectionBehavior(QAbstractItemView::SelectRows);
    //desabilitar os números relacionados à linhas
    ui->tw_listaEnd->verticalHeader()->setVisible(false);

}

fm_endereco::~fm_endereco()
{
    delete ui;
}


// ESSE BOTAO É PARA CRIAR UM NOVO ENDERECO
void fm_endereco::on_btn_salvar_clicked()
{
    QString bairro=ui->txt_bairro->text();
    QString cidade=ui->txt_cidade->text();
    QString rua=ui->txt_rua->text();
    QString idCliente=ui->txt_idCliente->text();
    QString idForne=ui->txt_idFornecedor->text();
    QString uf=ui->txt_uf->text();


   //INSERIR NA TABELA
    QSqlQuery query;
    if(idCliente == ""){
        query.prepare("insert into Endereco (id_fornecedor,cidade,rua,uf,bairro) values"
                    "("+QString::number(idForne.toInt())+",'"+cidade+"','"+rua+"','"+uf+"','"+bairro+"')");
    }

    if(idForne == ""){
        query.prepare("insert into Endereco (id_cliente,cidade,rua,uf,bairro) values"
                   "("+QString::number(idCliente.toInt())+",'"+cidade+"','"+rua+"','"+uf+"','"+bairro+"')");
    }

    if(!query.exec()){
         QMessageBox::critical(this, "ERRO", "Erro ao inserir novo Endereço");
    }else{
        QMessageBox::information(this, "GRAVADO", "Endereço inserido no Banco de Dados");
        //limpar todos os campos e posicipn
        ui->txt_bairro->clear();
        ui->txt_cidade->clear();
        ui->txt_rua->clear();
        ui->txt_idCliente->clear();
        ui->txt_uf->clear();
        ui->txt_idFornecedor->clear();
        ui->txt_bairro->setFocus();

    }

//amrmazenar as infromações me variaveis e criar uma variavel
//query para armazenar no banco de dados
//verificar se os valores são do tipo real(com ponto) para salvar no BD

}

void fm_endereco::on_btn_excluir_clicked()
{
    //verifica se existe algum botão selecionado
    if(ui->tw_listaEnd->currentRow() == -1){
        QMessageBox::warning(this, "ERRO", "Erro selecione um Endereço");
        return;
    }

    //verificar se relamente deve excluir
        QMessageBox::StandardButton opcao;
        opcao = QMessageBox::question(this, "EXCLUSÃO","Confirma a exclusão do usuário ?",QMessageBox::Yes|QMessageBox::No);

        if(opcao == QMessageBox::Yes){
            int linha = ui->tw_listaEnd->currentRow();
            QString id = ui->tw_listaEnd->item(linha, 0)->text();

            QSqlQuery query;

            //Deletar
            query.prepare("delete from Endereco where id_endereco="+id);

            if(query.exec()){
                ui->tw_listaEnd->removeRow(linha);
                QMessageBox::information(this, "DELETADO", "Endereço excluido com sucesso");
            }else{
                QMessageBox::warning(this, "ERRO", "Erro ao excluir na tabela Endereço");
            }

        }
}

void fm_endereco::on_btn_filtrar_clicked()
{
    //remover linhas da tabela, verificar se exite um valor digitado
    funcoes_globais::removerLinhas(ui->tw_listaEnd);


    //se tiver vai verificar de acordo com a query

    QString busca;
    //verificar se tem alguma coisa digitada
    if(ui->txt_filtrar->text() == ""){
        if(ui->rb_idEnd->isChecked()){

                busca="select id_endereco,cidade from Endereco order by id_endereco";
        }else{

                busca="select id_endereco,cidade from Endereco order by cidade";
             }
        }else{
                if(ui->rb_idEnd->isChecked()){

                    busca="select id_endereco,cidade from Endereco where id_endereco="+ui->txt_filtrar->text()+" order by id_endereco";
              }else{

                    busca="select id_endereco,cidade from Endereco where cidade like '%"+ ui->txt_filtrar->text()+"%' order by cidade";

                    }
             }

    int contLinhas = 0;
    QSqlQuery query;
    query.prepare(busca);

    if(query.exec()){
        while(query.next()){
            //faz a inserções de linhas
            ui->tw_listaEnd->insertRow(contLinhas);
            //inserir a primeira coluna primeiro
            ui->tw_listaEnd->setItem(contLinhas, 0, new QTableWidgetItem(query.value(0).toString()));
            //segunda coluna
            ui->tw_listaEnd->setItem(contLinhas, 1, new QTableWidgetItem(query.value(1).toString()));

            //tamanho da linhas
            ui->tw_listaEnd->setRowHeight(contLinhas, 20);
            contLinhas++;

        }
    }else{

         QMessageBox::warning(this, "ERRO", "Erro ao exibir Endereço");

    }

    ui->txt_filtrar->clear();
    ui->txt_filtrar->setFocus();
}

void fm_endereco::on_tw_listaEnd_itemSelectionChanged()
{
    //buscar o id do produto, para exibir na tela
    int id;
    //busca passando a linha atual, indice zero(onde está o codigo)
    id = ui->tw_listaEnd->item(ui->tw_listaEnd->currentRow(), 0)->text().toInt();

    QSqlQuery query;

    //consulta pelo id
    query.prepare("select * from Endereco where id_endereco="+QString::number(id));

    //verifica se rodou
    if(query.exec()){
        //toda vez que um produto for selecionado as informações serão
        //exibidas nos campos de texto(respectivamente)
        //preenche com o retorno da query
        query.first();
        //de acordo com a posição na tabela no banco de dados

        ui->txt_idCliente->setText(query.value(1).toString());
        ui->txt_idFornecedor->setText(query.value(2).toString());
        ui->txt_cidade->setText(query.value(3).toString());//...
        ui->txt_rua->setText(query.value(4).toString());
        ui->txt_uf->setText(query.value(5).toString());//...
        ui->txt_bairro->setText(query.value(6).toString());//id

    }
}


//ATUALIZAR O ENDERECO
void fm_endereco::on_btn_add_clicked()
{
    //verifica se existe algum botão selecionado
    if(ui->tw_listaEnd->currentRow() == -1){
        QMessageBox::warning(this, "ERRO", "Erro selecione um item");
        return;
    }


    //buscar o id
    QString id = ui->tw_listaEnd->item(ui->tw_listaEnd->currentRow(), 0)->text();

    //armazena cada um em seus respectivos campos
    QString bairro=ui->txt_bairro->text();
    QString cidade=ui->txt_cidade->text();
    QString rua=ui->txt_rua->text();
    QString idCliente=ui->txt_idCliente->text();
    QString idForne=ui->txt_idFornecedor->text();
    QString uf=ui->txt_uf->text();


    //Atualização (update) Na tabela Clientes
    QSqlQuery query;
    //query.prepare("insert into Estilo (nome_estilo,cor_estilo,ingrediente_estilo,alcool_estilo) values"
    //"('"+nome+"','"+cor+"','"+ingrediente+"','"+alcool+"')");
    query.prepare("update Endereco set bairro='"+bairro+"', cidade='"+cidade+"', rua='"+rua+"', uf='"+uf+"', id_cliente='"+idCliente+"', id_fornecedor='"+idForne+"' where id_endereco="+id);

    if(query.exec()){
        //atualiza os dados
        int linha = ui->tw_listaEnd->currentRow();
        ui->tw_listaEnd->item(linha, 1)->setText(cidade);

        QMessageBox::information(this, "UPDATE", "Tabela atualizado com sucesso");

    }else{

        QMessageBox::warning(this, "ERRO", "Erro ao atualizar Tabela");
    }
}
