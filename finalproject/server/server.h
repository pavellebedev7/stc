#ifndef SERVER
#define SERVER

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <atomic>
#include <thread>

#include <QTcpServer>
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

class User{ // id, login, password
public:
    uint32_t id;
    static std::atomic<uint32_t> currentId;
    QString login;
    QString password;
    User(QString login="none", QString password="none"):
        id(currentId++),
        login(login),
        password(password){qDebug() << "User " << login;}
    ~User(){}
};

class Message{ // id, senderId, chatId, data
public:
    uint32_t id;
    static std::atomic<uint32_t> currentId;
    int senderId;
    int chatId;
    QString data;
    Message(int senderId=-1, int chatId=-1, QString data="none"):
        id(currentId++),
        senderId(senderId),
        chatId(chatId),
        data(data){qDebug() << "Message " << id << " " << senderId << " " << chatId << " " << data;}
    ~Message(){}
};

class Chat{ // id, messages, senderId, users
public:
    uint32_t id;
    static std::atomic<uint32_t> currentId;
    std::vector<Message> messages;
    std::set<int> usersId;
    Chat():
        id(currentId++){qDebug() << "Chat " << id;}
    ~Chat(){}
    void AddMessage(Message &m){
        messages.push_back(m);
        usersId.insert(m.senderId);
    }
    void PrintMessages(){
        for (auto it = messages.begin(); it != messages.end(); ++it){
            qDebug() << it->senderId << " " << it->data;
        }
    }
    void PrintUsers(){
        for (auto it = usersId.begin(); it != usersId.end(); ++it){
            qDebug() << *it;
        }
    }
};

class Server: public QTcpServer
{
    Q_OBJECT
public:
    Server();
    ~Server();

    // Socket
    QTcpSocket* socket;

    // JSON
    QJsonDocument document;
    QJsonParseError error;
    QByteArray byteArray;

    QString currentClient;

    std::vector <User> registeredUsers;
    std::vector <User> loggedInUsers;

    void SendPackage(int command, QString s0, QString s1, QString s2, QString s3);
    ServerResponse ParsePackage();

    void RegisterUser(User &u);
    void PrintRegisteredUsers();
    void LogInUser(User &u);
    void PrintLoggedInUsers();

public slots:
    void Start();
    void Connection(int socketDescriptor);
    void SocketReady();
    void SocketDisconnect();
};

#endif // SERVER

