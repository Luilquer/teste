#ifndef CONEXAO_H
#define CONEXAO_H
#include <QtSql>

class Conexao{
public:
    QSqlDatabase bancoDeDados;
    //conexão com o banco de dados
    QString banco;

    Conexao(){
        //conexão com o banco de dados 
        banco = "/Users/Carlos Luilquer/Desktop/Sistema de bebida/build-ControlEstoque-Desktop_Qt_5_15_0_clang_64bit-Debug/db/bancoProjeto.db";
        bancoDeDados=QSqlDatabase::addDatabase("QSQLITE");
    }

    void fechar(){
        bancoDeDados.close();
    }

    bool abrir(){
        bancoDeDados.setDatabaseName(banco);

        if(!bancoDeDados.open())
        {
            return false;

        }else{

            return true;
        }
    }

    bool aberto(){
        if(bancoDeDados.isOpen()){

            return true;

        }else{

            return false;

        }
    }
};

#endif // CONEXAO_H
