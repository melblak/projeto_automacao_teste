#include "placa.h"
#include <QSerialPort>  //SerialPort habilitado no CMake
#include <QSerialPortInfo>
#include <QDebug>

//Construtor
placa::placa(QObject *parent)
    : QObject{parent}
{
    arduino = new QSerialPort(this);
}
//Descontrutor
placa::~placa() {
    desconectar();
}

void placa::verifica_porta_e_conecta()
{
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()){
            if(serialPortInfo.vendorIdentifier() == id_fornecedor){
                if(serialPortInfo.productIdentifier() == id_produto){
                    conectar(serialPortInfo.portName());
                }
            }
        }
    }
}

//Funções de inicialização da placa
void placa::conectar(const QString &portaNome)
{
    arduino->setPortName(portaNome);
    arduino->open(QIODevice::ReadWrite);
    arduino->setBaudRate(QSerialPort::Baud9600);
    arduino->setDataBits(QSerialPort::Data8);
    arduino->setParity(QSerialPort::NoParity);
    arduino->setStopBits(QSerialPort::OneStop);
    arduino->setFlowControl(QSerialPort::NoFlowControl);

    qDebug() << "Inicialização completa";
}

//Função para finalização da placa
void placa::desconectar()
{
    if(arduino->isOpen()){
        arduino->close();
    }
}

/* Para mover o motor:
 * 1)Criar métodos públicos de trigger para enviar dados para a entrada serial
 * 2)Criar código no ArduinoIDE para receber o dado e mover o motor de acordo
