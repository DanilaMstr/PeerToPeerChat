#include "server.h"

Server::Server(const QString &Port)
{
    server = new QTcpServer(this);
    server->listen(QHostAddress::Any, Port.toInt());
    connect(server, SIGNAL(newConnection()),
            this, SLOT(slotNewConnection()));
}

void Server::slotNewConnection(){
    emit connection();
    QTcpSocket* socket = server->nextPendingConnection();
    connect(socket, SIGNAL(readyRead()),
            this, SLOT(slotReadReady()));
}

void Server::slotReadReady(){
    NextBlockSize = 0;
    QTcpSocket* socket = (QTcpSocket*)sender();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_4_2);
    for(;;){
        if(!NextBlockSize) {
            if(socket->bytesAvailable() < sizeof(quint16)) {
                break;
            }
            in >> NextBlockSize;
        }
        if(socket->bytesAvailable() < NextBlockSize){
            break;
        }
        //QTime time;
        QString str;
        QTime time;
        in >> time >> str;
        QString strMessage =time.toString() + " Client : " + str;
        NextBlockSize = 0;
        emit message(strMessage);
    }

}
