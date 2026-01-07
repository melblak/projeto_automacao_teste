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

    void conectar(const QString &portaNome); // Ex: "COM3" ou "/dev/ttyUSB0"
    void desconectar();

private:
    QSerialPort *arduino;

signals:
};

#endif // PLACA_H
