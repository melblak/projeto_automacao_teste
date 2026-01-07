#include "placa.h"
#include <QSerialPort>  //SerialPort habilitado no CMake
#include <QSerialPortInfo>

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
