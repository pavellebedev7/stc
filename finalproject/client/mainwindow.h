#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <atomic>
#include <thread>

#include <QMainWindow>
#include <QMessageBox>

#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QStringListModel>
#include <QDateTime>
#include <QDebug>

#define IP_ADRESS "127.0.0.1"
#define PORT 1234
#define DELAY 200
#define PLACE_HOLDER " "

namespace Ui {
class MainWindow;
}

enum ClientRequest{
    REGISTER,   // Register new user
    LOGIN,      // Log in user
    CHAT,       // Open chat
    MESSAGE,    // Send message to opened chat
};

enum ServerResponse{
    REGISTER_OK = 100,
    LOGIN_OK,
    CHAT_OK,
    MESSAGE_OK,

    REGISTER_ERROR = 200,
    LOGIN_ERROR,
    CHAT_ERROR,
    MESSAGE_ERROR
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void SendPackage(int command, QString s0, QString s1, QString s2, QString s3);
    void ParsePackage();

public slots:
    void socketReady();
    void socketDisconnect();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;

    // Socket
    QTcpSocket* socket;

    // JSON
    QJsonDocument document;
    QJsonParseError error;

    // User data
    int command;                            // Package command
    QString login;                          // User login
    QString password;                       // User password
    QString message;                        // Message to be sent
    QByteArray byteArray;                   // Json byte array
    std::set<QString> registeredUsers;      // Registered Users array
};

#endif // MAINWINDOW_H
