#include "funcoes_globais.h"

funcoes_globais::funcoes_globais()
{

}

void funcoes_globais::removerLinhas(QTableWidget *tw){
    while(tw->rowCount()>0){
        //remove a linha enquanto for maior que zero
        tw->removeRow(0);// primeira linha(0)
    }
}
