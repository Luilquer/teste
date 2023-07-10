#include "fm_gestaocolaboradores.h"
#include "ui_fm_gestaocolaboradores.h"
#include <QMessageBox>
#include <QtSql>
#include "funcoes_globais.h"

fm_gestaoColaboradores::fm_gestaoColaboradores(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fm_gestaoColaboradores)
{
    ui->setupUi(this);
    //abrir o banco de dados
    if(!con.aberto()){
        if(!con.abrir()){
            QMessageBox::warning(this, "ERROR", "Erro ao abrir banco de Dados");
        }
    }


    ui->cb_acesso_novocolab->addItem("A");
    ui->cb_acesso_novocolab->addItem("B");
    ui->cb_ge_acessocolab->addItem("A");
    ui->cb_ge_acessocolab->addItem("B");
    //posicionar no nome
    ui->txt_nome_novocolab->setFocus();

    //definir o número de coluna que será exibido na tabela de consulta
    ui->tw_ge_listacolab->setColumnCount(2);

    //deixar sempre na primeira aba
    ui->tabWidget->setCurrentIndex(0);

    //definições larguras ...
    ui->tw_ge_listacolab->setColumnWidth(0, 50);
    ui->tw_ge_listacolab->setColumnWidth(1, 100);

    //cabeçalhos
    QStringList cab = {"ID", "Nome"};

    //inserir na tabela o cabeçalho
    ui->tw_ge_listacolab->setHorizontalHeaderLabels(cab);

    //restrições, cor da linha ao ser selecionada
    ui->tw_ge_listacolab->setStyleSheet("QTableView {selection-background-color:blue}");

    //desabilitando a edição
    ui->tw_ge_listacolab->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //selecionar a linha inteira ao clicar em uma cela
    ui->tw_ge_listacolab->setSelectionBehavior(QAbstractItemView::SelectRows);
    //desabilitar os números relacionados à linhas
    ui->tw_ge_listacolab->verticalHeader()->setVisible(false);

}

fm_gestaoColaboradores::~fm_gestaoColaboradores()
{
    delete ui;
}


void fm_gestaoColaboradores::on_btn_novo_novocolab_clicked()
{
    //limpar todos os campos e focar
    ui->txt_nome_novocolab->clear();
    ui->txt_senha_novocolb->clear();
    ui->txt_fone_novocolab->clear();
    ui->txt_username_novocolab->clear();

    //volta para o indice 0
    ui->cb_acesso_novocolab->setCurrentIndex(0);
    //centraliza em nome
    ui->txt_nome_novocolab->setFocus();

}

void fm_gestaoColaboradores::on_btn_gravar_novocolab_clicked()
{

    QString nome=ui->txt_nome_novocolab->text();
    QString username=ui->txt_username_novocolab->text();
    QString senha=ui->txt_senha_novocolb->text();
    QString telefone=ui->txt_fone_novocolab->text();
    QString acesso=ui->cb_acesso_novocolab->currentText();

    //VERIFICA O TIPO DE ACESSO SE FOR A: ADMINISTRADOR
    // B:  USUARIO/ CLIENTE

    //INSERIR NA TABELA
    QSqlQuery query;
    query.prepare("insert into Cliente (nome_cliente,username_cliente,senha_cliente,telefone_cliente,acesso_cliente) values"
                  "('"+nome+"','"+username+"','"+senha+"','"+telefone+"','"+acesso+"')");

    if(!query.exec()){
         QMessageBox::critical(this, "ERRO", "Erro ao inserir novo cliente");
    }else{
        QMessageBox::information(this, "GRAVADO", "Cliente inserido no Banco de Dados");
        //limpar todos os campos e posicipn
        ui->txt_nome_novocolab->clear();
        ui->txt_username_novocolab->clear();
        ui->txt_senha_novocolb->clear();
        ui->txt_fone_novocolab->clear();
        ui->cb_acesso_novocolab->setCurrentIndex(0);
        ui->txt_nome_novocolab->setFocus();

    }

//amrmazenar as infromações me variaveis e criar uma variavel
//query para armazenar no banco de dados
//verificar se os valores são do tipo real(com ponto) para salvar no BD

}



void fm_gestaoColaboradores::on_tabWidget_currentChanged(int index)
{
    //verifica se é a primeira(0) tab ou segunda(1)
    if(index == 1){
        funcoes_globais::removerLinhas(ui->tw_ge_listacolab);// chama a função para remover linhas

        int contLinhas=0;
        //Remover os produtos do tW, para não exibir duplicatas
        QSqlQuery query;
        //consulta
        query.prepare("select id_cliente, nome_cliente from Cliente order by id_cliente");

        if(query.exec()){

            while(query.next()){
                //faz a inserções de linhas
                ui->tw_ge_listacolab->insertRow(contLinhas);
                //inserir a primeira coluna primeiro produto
                ui->tw_ge_listacolab->setItem(contLinhas, 0, new QTableWidgetItem(query.value(0).toString()));
                //segunda coluna
                ui->tw_ge_listacolab->setItem(contLinhas, 1, new QTableWidgetItem(query.value(1).toString()));

                //tamanho da linhas
                ui->tw_ge_listacolab->setRowHeight(contLinhas, 20);
                contLinhas++;

            }

        }else{
            QMessageBox::warning(this, "ERRO", "Erro ao listar no Banco de Dados");
        }


    }
}


void fm_gestaoColaboradores::on_tw_ge_listacolab_itemSelectionChanged()
{
    //buscar o id do produto, para exibir na tela
    int id;
    //busca passando a linha atual, indice zero(onde está o codigo)
    id = ui->tw_ge_listacolab->item(ui->tw_ge_listacolab->currentRow(), 0)->text().toInt();

    QSqlQuery query;

    //consulta pelo id
    query.prepare("select * from Cliente where id_cliente="+QString::number(id));

    //verifica se rodou
    if(query.exec()){
        //toda vez que um produto for selecionado as informações serão
        //exibidas nos campos de texto(respectivamente)
        //preenche com o retorno da query
        query.first();
        //de acordo com a posição na tabela no banco de dados
        ui->txt_ge_nome->setText(query.value(1).toString());//id
        ui->txt_ge_username->setText(query.value(2).toString());//...
        ui->txt_ge_senha->setText(query.value(3).toString());
        ui->txt_ge_fone->setText(query.value(4).toString());
        ui->cb_ge_acessocolab->setCurrentText(query.value(5).toString());


    }
}


void fm_gestaoColaboradores::on_pushButton_clicked()
{
    //remover linhas da tabela, verificar se exite um valor digitado
    funcoes_globais::removerLinhas(ui->tw_ge_listacolab);


    //se tiver vai verificar de acordo com a query

    QString busca;
    //verificar se tem alguma coisa digitada
    if(ui->txt_ge_filtro->text() == ""){
        if(ui->rb_ge_idcolab->isChecked()){

                busca="select id_cliente,nome_cliente from Cliente order by id_cliente";
        }else{

                busca="select id_cliente,nome_cliente from Cliente order by nome_cliente";
             }
        }else{
                if(ui->rb_ge_idcolab->isChecked()){

                    busca="select id_cliente,nome_cliente from Cliente where id_cliente="+ui->txt_ge_filtro->text()+" order by id_cliente";
              }else{

                    busca="select id_cliente,nome_cliente from Cliente where nome_cliente like '%"+ ui->txt_ge_filtro->text()+"%' order by nome_cliente";

                    }
             }

    int contLinhas = 0;
    QSqlQuery query;
    query.prepare(busca);

    if(query.exec()){
        while(query.next()){
            //faz a inserções de linhas
            ui->tw_ge_listacolab->insertRow(contLinhas);
            //inserir a primeira coluna primeiro
            ui->tw_ge_listacolab->setItem(contLinhas, 0, new QTableWidgetItem(query.value(0).toString()));
            //segunda coluna
            ui->tw_ge_listacolab->setItem(contLinhas, 1, new QTableWidgetItem(query.value(1).toString()));

            //tamanho da linhas
            ui->tw_ge_listacolab->setRowHeight(contLinhas, 20);
            contLinhas++;

        }
    }else{

         QMessageBox::warning(this, "ERRO", "Erro ao exibir clientes");

    }

    ui->txt_ge_filtro->clear();
    ui->txt_ge_filtro->setFocus();
}

void fm_gestaoColaboradores::on_bnt_ge_salvar_clicked()
{
    //verifica se existe algum botão selecionado
    if(ui->tw_ge_listacolab->currentRow() == -1){
        QMessageBox::warning(this, "ERRO", "Erro selecione um cliente");
        return;
    }


    //buscar o id
    QString id = ui->tw_ge_listacolab->item(ui->tw_ge_listacolab->currentRow(), 0)->text();

    //armazena cada um em seus respectivos campos
    QString nome = ui->txt_ge_nome->text();
    QString username = ui->txt_ge_username->text();
    QString senha = ui->txt_ge_senha->text();
    QString fone = ui->txt_ge_fone->text();
    QString acesso = ui->cb_ge_acessocolab->currentText();


    //Atualização (update) Na tabela Clientes
    QSqlQuery query;
    //não pode ter espaços entre as ","
    query.prepare("update Cliente set nome_cliente='"+nome+"', username_cliente='"+username+"', senha_cliente='"+senha+"', telefone_cliente='"+fone+"', acesso_cliente='"+acesso+"' where id_cliente="+id);

    if(query.exec()){
        //atualiza os dados
        int linha = ui->tw_ge_listacolab->currentRow();
        ui->tw_ge_listacolab->item(linha, 1)->setText(nome);

        QMessageBox::information(this, "UPDATE", "Cliente atualizado com sucesso");

    }else{

        QMessageBox::warning(this, "ERRO", "Erro ao atualizar Tabela cliente");
    }
}

void fm_gestaoColaboradores::on_bnt_ge_escluir_clicked()
{
    //verifica se existe algum botão selecionado
    if(ui->tw_ge_listacolab->currentRow() == -1){
        QMessageBox::warning(this, "ERRO", "Erro selecione um cliente");
        return;
    }

    //verificar se relamente deve excluir
        QMessageBox::StandardButton opcao;
        opcao = QMessageBox::question(this, "EXCLUSÃO","Confirma a exclusão do usuário ?",QMessageBox::Yes|QMessageBox::No);

        if(opcao == QMessageBox::Yes){
            int linha = ui->tw_ge_listacolab->currentRow();
            QString id = ui->tw_ge_listacolab->item(linha, 0)->text();

            QSqlQuery query;

            //Deletar
            query.prepare("delete from Cliente where id_cliente="+id);

            if(query.exec()){
                ui->tw_ge_listacolab->removeRow(linha);
                QMessageBox::information(this, "DELETADO", "Cliente excluido com sucesso");
            }else{
                QMessageBox::warning(this, "ERRO", "Erro ao excluir na tabela cliente");
            }

        }
}
