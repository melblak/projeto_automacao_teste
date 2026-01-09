#include "placa.h"
#include <QSerialPort>  //SerialPort habilitado no CMake
#include <QSerialPortInfo>
#include <QDebug>
#include <QTimer>

//Construtor
placa::placa(QObject *parent)
    : QObject{parent}
{
    arduino = new QSerialPort(this);
    QObject::connect(this,&placa::portaVerificada,this,&placa::conectar);
    QObject::connect(this,&placa::placaConectada,this,&placa::inicia_testemunho);
    QObject::connect(this,&placa::execucaoIniciada,this,&placa::executar);

    timer_resposta.setInterval(10000);
    connect(&timer_resposta,&QTimer::timeout,this,&placa::onTimerTimeout);
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
    timer_resposta.start();
    QByteArray dados = arduino->readAll();
    if(dados.contains('P')){
        timer_resposta.stop();
    }else{
        setStatus(Status::erroOcorrido);
    }
}

// Função que faz o loop que ajusta a posição, tira foto e rotaciona
void placa::executar()
{
    setStatus(Status::emFuncionamento);
    for(int j=0; j<=passos_por_rotacao; j+=largura_passo){
        if(status_atual == Status::emFuncionamento){
            tira_foto();
            altera_passo_rotacao();
        }else{
            qDebug() << "Processo interrompido";
            break;
        }
    }
}

// Função de trigger da execução
void placa::inicia_testemunho()
{
    // Implementar trigger para o processo iniciar
    emit(execucaoIniciada());
}

// Slot de timeout
void placa::onTimerTimeout()
{
    qDebug() << "Tempo de resposta excedido";
    setStatus(Status::erroOcorrido);
    timer_resposta.stop();
}

/* Para mover o motor:
 * 1)Criar métodos públicos de trigger para enviar dados para a entrada serial
 * 2)Criar código no ArduinoIDE para receber o dado e mover o motor de acordo
*/
