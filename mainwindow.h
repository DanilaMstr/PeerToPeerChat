#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "server.h"
#include "client.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
     Server *_server;
     Client *_client;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void NewMessage(const QString &msg);
    void clientConnected();
    void NewServer(const QString& Port);
    void NewClient(const QString& IP, const QString& Port);
    void ConnectedToServer();
signals:
    void getPort(const QString& Port);
    void getIPandPort(const QString& IP, const QString& Port);
    void sendMessage(const QString& msg);


private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:

    Ui::MainWindow *ui;
    //Server* _server;
};

#endif // MAINWINDOW_H
