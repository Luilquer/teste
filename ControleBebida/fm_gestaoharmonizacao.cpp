#include "fm_gestaoharmonizacao.h"
#include "ui_fm_gestaoharmonizacao.h"

#include <QMessageBox>
#include <QtSql>
#include "funcoes_globais.h"
#include <QtDebug>

fm_gestaoHarmonizacao::fm_gestaoHarmonizacao(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fm_gestaoHarmonizacao)
{
    ui->setupUi(this);

    //abrir o banco de dados
    if(!con.aberto()){
        if(!con.abrir()){
            QMessageBox::warning(this, "ERROR", "Erro ao abrir banco de Dados");
        }
    }

    //definir o número de coluna que será exibido na tabela de consulta
    ui->tableWidget->setColumnCount(2);

    //deixar sempre na primeira aba
    ui->tabWidget->setCurrentIndex(0);

    //definições larguras ...
    ui->tableWidget->setColumnWidth(0, 50);
    ui->tableWidget->setColumnWidth(1, 200);

    //cabeçalhos
    QStringList cab = {"ID", "Descrição"};

    //inserir na tabela o cabeçalho
    ui->tableWidget->setHorizontalHeaderLabels(cab);

    //restrições, cor da linha ao ser selecionada
    ui->tableWidget->setStyleSheet("QTableView {selection-background-color:blue}");

    //desabilitando a edição
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //selecionar a linha inteira ao clicar em uma cela
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    //desabilitar os números relacionados à linhas
    ui->tableWidget->verticalHeader()->setVisible(false);

}



fm_gestaoHarmonizacao::~fm_gestaoHarmonizacao()
{
    delete ui;
}



void fm_gestaoHarmonizacao::on_pushButtonSalvar_1_clicked()
{

    QSqlQuery query;

    //insert
   query.prepare("insert into Harmonizacao (descricao_harmo) values ('" + ui->plainTextEditAddDescricao->toPlainText() + "');");

    if(query.exec()) {
        QMessageBox::information(this, "GRAVADO", "Hamonização salvo no Banco de Dados");
        ui->plainTextEditAddDescricao->setPlainText("");
    } else {
        QMessageBox::warning(this, "ERROR", "Erro ao abrir banco de Dados");
    }

}



void fm_gestaoHarmonizacao::on_pushButtonCancelar_clicked()
{
    this->close();
}



void fm_gestaoHarmonizacao::on_pushButtonFiltrar_clicked()
{
    //remover linhas da tabela, verificar se exite um valor digitado
    funcoes_globais::removerLinhas(ui->tableWidget);


    //se tiver vai verificar de acordo com a query

    QString busca;
    //verificar se tem alguma coisa digitada
    if(ui->lineEditFiltrar->text() == ""){
        if(ui->radioButtonIdHarmonizacao->isChecked()){
            busca="select id_harmonizacao, descricao_harmo from Harmonizacao order by id_harmonizacao";
        } else {
            busca="select id_harmonizacao, descricao_harmo from Harmonizacao order by id_harmonizacao";
        }
    }else {
        if(ui->radioButtonIdHarmonizacao->isChecked()){
            busca="select id_harmonizacao, descricao_harmo from Harmonizacao where id_harmonizacao="+ui->lineEditFiltrar->text()+" order by id_harmonizacao";
        } else if(ui->radioButtonIdDescricao->isChecked()){
            busca="select id_harmonizacao, descricao_harmo from Harmonizacao where descricao_harmo like '%"+ui->lineEditFiltrar->text()+"%' order by id_harmonizacao";
        } else {
            busca="select id_harmonizacao, descricao_harmo from Harmonizacao where id_harmonizacao="+ui->lineEditFiltrar->text()+" order by id_harmonizacao";
        }
    }

    int contLinhas = 0;
    QSqlQuery query;
    query.prepare(busca);

    if(query.exec()){
        while(query.next()){
            //faz a inserções de linhas
            ui->tableWidget->insertRow(contLinhas);
            //inserir a primeira coluna primeiro
            ui->tableWidget->setItem(contLinhas, 0, new QTableWidgetItem(query.value(0).toString()));
            //segunda coluna
            ui->tableWidget->setItem(contLinhas, 1, new QTableWidgetItem(query.value(1).toString()));

            //tamanho da linhas
            ui->tableWidget->setRowHeight(contLinhas, 20);
            contLinhas++;

        }
    }else{

         QMessageBox::warning(this, "ERRO", "Erro ao exibir os dados");

    }

    ui->lineEditFiltrar->clear();
    ui->lineEditFiltrar->setFocus();
}




void fm_gestaoHarmonizacao::on_pushButtonSalvar_2_clicked()
{

    //verifica se existe algum botão selecionado
    if(ui->tableWidget->currentRow() == -1){
        QMessageBox::warning(this, "ERRO", "Erro selecione um cliente");
        return;
    }


    //buscar o id
    QString id = ui->tableWidget->item(ui->tableWidget->currentRow(), 0)->text();

    //armazena cada um em seus respectivos campos
    QString descricao = ui->plainTextEditUpdtDescricao->toPlainText();


    //Atualização (update) Na tabela Clientes
    QSqlQuery query;
    //não pode ter espaços entre as ","
    query.prepare("update Harmonizacao set descricao_harmo='"+descricao+"' where id_harmonizacao="+id);

    if(query.exec()){
        //atualiza os dados
        int linha = ui->tableWidget->currentRow();
        ui->tableWidget->item(linha, 1)->setText(descricao);

        QMessageBox::information(this, "UPDATE", "Cliente atualizado com sucesso");

    }else{

        QMessageBox::warning(this, "ERRO", "Erro ao atualizar a tabela");
    }

}



void fm_gestaoHarmonizacao::on_pushButtonExcluir_clicked()
{

    //verifica se existe algum botão selecionado
    if(ui->tableWidget->currentRow() == -1){
        QMessageBox::warning(this, "ERRO", "Erro selecione a linha");
        return;
    }

    //verificar se relamente deve excluir
    QMessageBox::StandardButton opcao;
    opcao = QMessageBox::question(this, "EXCLUSÃO","Confirma a exclusão da harmonizacao?",QMessageBox::Yes|QMessageBox::No);

    if(opcao == QMessageBox::Yes){
        int linha = ui->tableWidget->currentRow();
        QString id = ui->tableWidget->item(linha, 0)->text();

        QSqlQuery query;

        //Deletar
        query.prepare("delete from Harmonizacao where id_harmonizacao="+id);

        if(query.exec()){
            ui->tableWidget->removeRow(linha);
            QMessageBox::information(this, "DELETADO", "Harmonizacao excluido com sucesso");
        }else{
            QMessageBox::warning(this, "ERRO", "Erro ao excluir na tabela harmonizacao");
        }

    }

}




void fm_gestaoHarmonizacao::on_tableWidget_itemSelectionChanged()
{
    //buscar o id do produto, para exibir na tela
    int id;
    //busca passando a linha atual, indice zero(onde está o codigo)
    id = ui->tableWidget->item(ui->tableWidget->currentRow(), 0)->text().toInt();

    QSqlQuery query;

    //consulta pelo id
    query.prepare("select descricao_harmo from Harmonizacao where id_harmonizacao="+QString::number(id));

    //verifica se rodou
    if(query.exec()){
        //toda vez que um produto for selecionado as informações serão
        //exibidas nos campos de texto(respectivamente)
        //preenche com o retorno da query
        query.first();
        //de acordo com a posição na tabela no banco de dados
        ui->plainTextEditUpdtDescricao->setPlainText(query.value(0).toString());

    }
}




void fm_gestaoHarmonizacao::on_tabWidget_currentChanged(int index)
{
    //verifica se é a primeira(0) tab ou segunda(1)
    if(index == 1){
        funcoes_globais::removerLinhas(ui->tableWidget);// chama a função para remover linhas

        int contLinhas=0;
        //Remover os produtos do tW, para não exibir duplicatas
        QSqlQuery query;

        //consulta
        query.prepare("select id_harmonizacao, descricao_harmo from Harmonizacao order by id_harmonizacao");

        if(query.exec()){

            while(query.next()){
                //faz a inserções de linhas
                ui->tableWidget->insertRow(contLinhas);
                //inserir a primeira coluna primeiro produto
                ui->tableWidget->setItem(contLinhas, 0, new QTableWidgetItem(query.value(0).toString()));
                //segunda coluna
                ui->tableWidget->setItem(contLinhas, 1, new QTableWidgetItem(query.value(1).toString()));

                //tamanho da linhas
                ui->tableWidget->setRowHeight(contLinhas, 20);
                contLinhas++;

            }

        }else{
            QMessageBox::warning(this, "ERRO", "Erro ao listar no Banco de Dados");
        }


    }
}
