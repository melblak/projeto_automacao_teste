#include "placa.h"
#include <QSerialPort>  //SerialPort habilitado no CMake
#include <QSerialPortInfo>
#include <QDebug>
#include <QTimer>

//Construtor
Placa::Placa(QObject *parent)
    : QObject{parent}
{
    arduino = new QSerialPort(this);
    QObject::connect(this,&Placa::portaVerificada,this,&Placa::conectar);
    QObject::connect(this,&Placa::PlacaConectada,this,&Placa::inicia_testemunho);
    QObject::connect(this,&Placa::execucaoIniciada,this,&Placa::executar);

    timer_resposta.setInterval(10000);
    connect(&timer_resposta,&QTimer::timeout,this,&Placa::onTimerTimeout);
}
//Descontrutor
Placa::~Placa() {
    desconectar();
}


//Função para verificar os dados da Placa e chamar a conexão
void Placa::verifica_porta_e_conecta()
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

//Funções de inicialização da Placa
void Placa::conectar(QString portaNome)
{
    arduino->setPortName(portaNome);
    arduino->open(QIODevice::ReadWrite);
    arduino->setBaudRate(QSerialPort::Baud9600);
    arduino->setDataBits(QSerialPort::Data8);
    arduino->setParity(QSerialPort::NoParity);
    arduino->setStopBits(QSerialPort::OneStop);
    arduino->setFlowControl(QSerialPort::NoFlowControl);

    emit(PlacaConectada());
    qDebug() << "Inicialização completa";
}

// Função para finalização da Placa
void Placa::desconectar()
{
    if(arduino->isOpen()){
        arduino->close();
    }
}

// Função que comunica o arduino para acionar o motor
void Placa::altera_passo_rotacao()
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
void Placa::executar()
{
    setStatus(Status::emFuncionamento);
    for(int j=0; j<=passos_por_rotacao; j+=largura_passo){
        if(status_atual == Status::emFuncionamento){
            tira_foto();
            altera_passo_rotacao();
        }else{
            qDebug() << "Processo interrompido";
            setStatus(Status::emStandBy);
            break;
        }
    }
}

// Função de trigger da execução
void Placa::inicia_testemunho()
{
    // Implementar trigger para o processo iniciar
    emit(execucaoIniciada());
}

// Slot de timeout
void Placa::onTimerTimeout()
{
    qDebug() << "Tempo de resposta excedido";
    setStatus(Status::erroOcorrido);
    timer_resposta.stop();
}

/* Para mover o motor:
 * 1)Criar métodos públicos de trigger para enviar dados para a entrada serial
 * 2)Criar código no ArduinoIDE para receber o dado e mover o motor de acordo
*/
