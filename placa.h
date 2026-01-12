#ifndef placa_H
#define placa_H

#include <QObject>
#include <QObject>
#include <QSerialPort>
#include <QTimer>

class Placa : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Status status READ getStatus WRITE setStatus NOTIFY statusChanged)

public:
    explicit Placa(QObject *parent = nullptr);
    ~Placa();

    void verifica_porta_e_conecta();
    void desconectar();
    void teste();

    enum Status{
        emStandBy = 0,
        emFuncionamento,
        erroOcorrido
    };
    Q_ENUM(Status)

private:
    QSerialPort *arduino;
    QString nome_da_porta;
    QTimer timer_resposta; // Timer para controlar o tempo de resposta do arduino
    Status status_atual; // Inicialização do status do sistema
    static const quint16 id_fornecedor = 9025; // Atribuir valores fixos ao conectar o arduino
    static const quint16 id_produto = 66;
    static const int passos_por_rotacao = 200; // Quantidade de passos em uma rotação
    static const int largura_passo = 20; // Quantidade de passos a serem feitos para cada foto
    static const int quant_ajustes = 3; // Quantidade de posições a serem fotografadas

    void tira_foto();
    void altera_passo_rotacao();
    void setStatus(Status novoStatus); // Função set para o status do sistema
    Placa::Status getStatus(); // Função get para o status do sistema
private slots:
    void conectar(QString portaNome);
    void executar();
    void inicia_testemunho();
    void onTimerTimeout();
signals:
    void portaVerificada(QString portaNome);
    void PlacaConectada();
    void execucaoIniciada();
    void statusChanged();
};

#endif // placa_H
