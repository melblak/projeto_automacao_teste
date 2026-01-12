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
    status_atual = Placa::emStandBy;
    QObject::connect(this,&Placa::portaVerificada,this,&Placa::conectar);
    QObject::connect(this,&Placa::PlacaConectada,this,&Placa::inicia_testemunho);
    QObject::connect(this,&Placa::execucaoIniciada,this,&Placa::executar);

    timer_resposta.setInterval(5000);
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

void Placa::teste()
{
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        qDebug() << "O fornecedor é: " << serialPortInfo.vendorIdentifier();
        qDebug() << "O produto é: " << serialPortInfo.productIdentifier();
    }
}

void Placa::tira_foto()
{
    qDebug() <<"Click!";
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

    QEventLoop loop;
    connect(&timer_resposta, &QTimer::timeout, &loop, &QEventLoop::quit);
    connect(arduino, &QSerialPort::readyRead, &loop, &QEventLoop::quit);

    timer_resposta.start();
    while(timer_resposta.isActive()) {
        loop.exec();
        QByteArray dados = arduino->readAll();
        if(dados.contains('P')){
            qDebug() << "Sinal de pronto recebido";
            timer_resposta.stop();
            break;
        }
    }
}

void Placa::setStatus(Status novoStatus)
{
    if(status_atual == novoStatus){
        return;
    }else{
        status_atual = novoStatus;
        emit statusChanged();
    }
}

Placa::Status Placa::getStatus()
{
    return status_atual;
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
    timer_resposta.stop();
    qDebug() << "Tempo de resposta excedido";
    setStatus(Status::erroOcorrido);
}

/* Para mover o motor:
 * 1)Criar métodos públicos de trigger para enviar dados para a entrada serial
 * 2)Criar código no ArduinoIDE para receber o dado e mover o motor de acordo
*/
