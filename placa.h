#ifndef PLACA_H
#define PLACA_H

#include <QObject>
#include <QObject>
#include <QSerialPort>

class placa : public QObject
{
    Q_OBJECT
public:
    explicit placa(QObject *parent = nullptr);
    ~placa();

    void verifica_porta_e_conecta();
    void desconectar();
    void tira_foto();
    void altera_passo_rotacao();
    void altera_passo_ajuste();
private:
    QSerialPort *arduino;
    QString nome_da_porta;
    static const quint16 id_fornecedor; // Atribuir valores fixos ao conectar o arduino
    static const quint16 id_produto;
    static const int passos_por_rotacao; // Quantidade de passos em uma rotação
    static const int largura_passo; // Quantidade de passos a serem feitos para cada foto
    static const int quant_ajustes; // Quantidade de posições a serem fotografadas
public slots:
    void conectar(QString portaNome);
    void executar();
    void inicia_testemunho();
signals:
    void portaVerificada(QString portaNome);
    void placaConectada();
    void execucaoIniciada();
};

#endif // PLACA_H
