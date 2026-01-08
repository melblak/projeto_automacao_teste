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


//Função para verificar os dados da placa e chamar a conexão
void placa::verifica_porta_e_conecta()
{
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()){
            if(serialPortInfo.vendorIdentifier() == id_fornecedor){
                if(serialPortInfo.productIdentifier() == id_produto){
                    QObject::connect(this,&placa::portaVerificada,this,&placa::conectar);
                    emit(portaVerificada(serialPortInfo.portName()));
                }
            }
        }
    }
}

//Funções de inicialização da placa
void placa::conectar(QString portaNome)
{
    arduino->setPortName(portaNome);
    arduino->open(QIODevice::ReadWrite);
    arduino->setBaudRate(QSerialPort::Baud9600);
    arduino->setDataBits(QSerialPort::Data8);
    arduino->setParity(QSerialPort::NoParity);
    arduino->setStopBits(QSerialPort::OneStop);
    arduino->setFlowControl(QSerialPort::NoFlowControl);

    QObject::connect(this,&placa::placaConectada,this,&placa::inicia_testemunho);
    emit(placaConectada());
    qDebug() << "Inicialização completa";
}

// Função para finalização da placa
void placa::desconectar()
{
    if(arduino->isOpen()){
        arduino->close();
    }
}

// Função que comunica o arduino para acionar o motor
void placa::altera_passo_rotacao()
{
    arduino->write("R");
}

// Função que faz o loop que ajusta a posição, tira foto e rotaciona
void placa::executar()
{
    for(int i=1; i<=quant_ajustes; i++){
        for(int j=0; j<=passos_por_rotacao; j+=largura_passo){
            tira_foto();
            altera_passo_rotacao();
        }
        altera_passo_ajuste();
    }
}

// Função de trigger da execução
void placa::inicia_testemunho()
{
    // Implementar trigger para o processo iniciar
    QObject::connect(this,&placa::execucaoIniciada,this,&placa::executar);
    emit(execucaoIniciada());
}

/* Para mover o motor:
 * 1)Criar métodos públicos de trigger para enviar dados para a entrada serial
 * 2)Criar código no ArduinoIDE para receber o dado e mover o motor de acordo
*/
