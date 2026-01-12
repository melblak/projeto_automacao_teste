#include <QCoreApplication>
#include "placa.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Placa placa;
    placa.verifica_porta_e_conecta();

    placa.desconectar();

    return a.exec();
}
