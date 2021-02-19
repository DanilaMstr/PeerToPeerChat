#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QTcpSocket>
#include <QTime>

class Client : public QWidget
{
    Q_OBJECT
public:
    Client(const QString& IP, const QString& Port);
    QTcpSocket* socket;
public slots:
    void slotConnection();
    void slotSendMessage(const QString& msg);
signals:
    void ConnectToServer();
};

#endif // CLIENT_H
