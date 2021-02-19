#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTime>

class Server : public QWidget
{
    Q_OBJECT
public:
    Server(const QString& Port);
signals:
    void message(const QString& msg);
    void connection();
private:
    QTcpServer* server;
    QTcpSocket* socket;
    quint16 NextBlockSize;
public slots:
    void slotNewConnection();
    void slotReadReady();

};

#endif // SERVER_H
