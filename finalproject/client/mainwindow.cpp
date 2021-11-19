#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    socket = new QTcpSocket(this);
    connect(socket,SIGNAL(readyRead()),this,SLOT(socketReady()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(socketDisconnect()));

    socket->connectToHost(IP_ADRESS, PORT);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::socketReady(){
    if(socket->waitForConnected(DELAY)){
        socket->waitForReadyRead(DELAY);
        ParsePackage();
    }
}

void MainWindow::socketDisconnect(){
    socket->deleteLater();
}

/*
 *          Package structure
 *
 *          name    |   type    |   purpose
 *          ----------------------------------------------
 *          command |   int     |   Command name
 *          s0      |   QString |   First string operand
 *          s1      |   QString |   Second string operand
 *          s2      |   QString |   Third string operand
 *          s3      |   QString |   Fourth string operand
 *
 */

// Send Package
void MainWindow::SendPackage(int command, QString s0, QString s1, QString s2, QString s3){
    byteArray = "{\"command\":\"";
    byteArray.append(QString::number(command));
    byteArray.append("\",\"s0\":\"");
    byteArray.append(s0);
    byteArray.append("\",\"s1\":\"");
    byteArray.append(s1);
    byteArray.append("\",\"s2\":\"");
    byteArray.append(s2);
    byteArray.append("\",\"s3\":\"");
    byteArray.append(s3);
    byteArray.append("\"}");
    socket->write(byteArray);
    socket->waitForBytesWritten(DELAY);
}

// Parse Package
void MainWindow::ParsePackage(){
    byteArray = socket->readAll();
    qDebug() << byteArray;
    ui->textEdit->append(byteArray);
    document = QJsonDocument::fromJson(byteArray, &error);
    if(error.errorString() == "no error occurred"){
        int command = document.object().value("command").toString().toInt();
        QString s0 = document.object().value("s0").toString();
        QString s1 = document.object().value("s1").toString();
        QString s2 = document.object().value("s2").toString();
        QString s3 = document.object().value("s3").toString();
        QString newRegisteredClient;

        switch(command){
        case(REGISTER_OK):
            break;
        case(LOGIN_OK):
            break;
        case(CHAT_OK):
            break;
        case(MESSAGE_OK):
            break;
        case(REGISTER_ERROR):
            break;
        case(LOGIN_ERROR):
            break;
        case(CHAT_ERROR):
            break;
        case(MESSAGE_ERROR):
            break;
        default:
            break;
        }
    }else{
        qDebug() << "Client Parse JSON Package Error";
    }
}

// Register button handler / Register request
void MainWindow::on_pushButton_2_clicked()
{
    command = REGISTER;
    login = ui->lineEdit_2->text();
    password = ui->lineEdit_3->text();

    SendPackage(command, login, password, PLACE_HOLDER, PLACE_HOLDER);

    // UI correction
    ui->pushButton_3->setEnabled(true);
}

// Login button handler / Login request
void MainWindow::on_pushButton_3_clicked()
{
    command = LOGIN;
    login = ui->lineEdit_2->text();
    password = ui->lineEdit_3->text();

    SendPackage(command, login, password, PLACE_HOLDER, PLACE_HOLDER);

    // UI correction
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->lineEdit_2->setEnabled(false);
    ui->lineEdit_3->setEnabled(false);
}

// Send message button handler / Send message request
void MainWindow::on_pushButton_clicked()
{
    command = MESSAGE;
    login = ui->lineEdit_2->text();
    message = ui->lineEdit->text();

    if(message == "")return;
    ui->lineEdit->clear();

    SendPackage(command, login, message, PLACE_HOLDER, PLACE_HOLDER);
}


