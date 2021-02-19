#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "server.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this, SIGNAL(getPort(QString)), this, SLOT(NewServer(QString)));
    connect(this, SIGNAL(getIPandPort(QString,QString)), this, SLOT(NewClient(QString,QString)));


    //Server *_server = new Server(Port);


//connect(_server, SIGNAL(connection()), this, SLOT(clientConnected()));
//connect(_server, SIGNAL(message(QString)), this, SLOT(NewMessage(QString)));
}

MainWindow::~MainWindow()
{
 delete ui;
}

void MainWindow::NewMessage(const QString &msg){
    qDebug() << __func__ << msg;
    ui->textEdit->append(msg);
}

void MainWindow::clientConnected(){
    qDebug() << __func__;
    ui->textEdit->append("Client connected");
}

void MainWindow::on_pushButton_3_clicked()
{
    QString Port = ui->lineEdit_4->text();
    ui->textEdit->append("Server listen port : " + Port);
    emit getPort(Port);
}

void MainWindow::NewServer(const QString &Port){
    Server *_server = new Server(Port);
    connect(_server, SIGNAL(connection()), this, SLOT(clientConnected()));
    connect(_server, SIGNAL(message(QString)), this, SLOT(NewMessage(QString)));

}

void MainWindow::on_pushButton_2_clicked()
{
    QString IP = ui->lineEdit_3->text();
    QString Port = ui->lineEdit_2->text();
    emit getIPandPort(IP, Port);
}

void MainWindow::NewClient(const QString &IP, const QString &Port){
    Client *_client = new Client(IP, Port);
    connect(_client, SIGNAL(ConnectToServer()), this, SLOT(ConnectedToServer()));
    connect(this, SIGNAL(sendMessage(QString)), _client, SLOT(slotSendMessage(QString)));
}

void MainWindow::ConnectedToServer(){
    ui->textEdit->append("Connected to Server");
}

void MainWindow::on_pushButton_clicked()
{
    QString msg = ui->lineEdit->text();
    ui->textEdit->append("Me : " + msg);
    emit sendMessage(msg);
}
