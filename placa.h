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
    void conectar(const QString &portaNome);
    void desconectar();

private:
    QSerialPort *arduino;
    static const quint16 id_fornecedor; // Atribuir valores fixos ao conectar o arduino
    static const quint16 id_produto;
signals:
};

#endif // PLACA_H
