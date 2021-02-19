#include "client.h"

Client::Client(const QString& IP, const QString& Port)
{
    socket = new QTcpSocket(this);
    socket->connectToHost(IP, Port.toInt());
    connect(socket, SIGNAL(connected()), this, SLOT(slotConnection()));


}

void Client::slotConnection(){
    emit ConnectToServer();
}

void Client::slotSendMessage(const QString &msg){
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_2);
    out << quint16(0) << QTime::currentTime() << msg;
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));
    socket->write(arrBlock);
}
