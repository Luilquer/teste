QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    fm_consultaralcool.cpp \
    fm_consultarcomida.cpp \
    fm_consultarendereco.cpp \
    fm_endereco.cpp \
    fm_gestaocerveja.cpp \
    fm_gestaocolaboradores.cpp \
    fm_gestaocomida.cpp \
    fm_gestaoestilo.cpp \
    fm_gestaofornecedor.cpp \
    fm_gestaoharmonizacao.cpp \
    fm_gestaovinho.cpp \
    fm_logar.cpp \
    funcoes_globais.cpp \
    main.cpp \
    fm_principal.cpp

HEADERS += \
    Conexao.h \
    fm_consultaralcool.h \
    fm_consultarcomida.h \
    fm_consultarendereco.h \
    fm_endereco.h \
    fm_gestaocerveja.h \
    fm_gestaocolaboradores.h \
    fm_gestaocomida.h \
    fm_gestaoestilo.h \
    fm_gestaofornecedor.h \
    fm_gestaoharmonizacao.h \
    fm_gestaovinho.h \
    fm_logar.h \
    fm_principal.h \
    funcoes_globais.h \
    variaveis_globais.h

FORMS += \
    fm_consultaralcool.ui \
    fm_consultarcomida.ui \
    fm_consultarendereco.ui \
    fm_endereco.ui \
    fm_gestaocerveja.ui \
    fm_gestaocolaboradores.ui \
    fm_gestaocomida.ui \
    fm_gestaoestilo.ui \
    fm_gestaofornecedor.ui \
    fm_gestaoharmonizacao.ui \
    fm_gestaovinho.ui \
    fm_logar.ui \
    fm_principal.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Arquivos_de_recursos.qrc

DISTFILES += \
    ../../../Downloads/Cadeado Aberto.png \
    ../../../Downloads/Cadeado Fechado.png
