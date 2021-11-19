#include "server.h"

std::atomic<uint32_t> User::currentId;
std::atomic<uint32_t> Message::currentId;
std::atomic<uint32_t> Chat::currentId;

Server::Server(){}

Server::~Server(){}

void Server::Start()
{
    if (this->listen(QHostAddress::Any,PORT))
    {
        std::cout << "Server started" << std::endl;
    }
    else
    {
        std::cout << "Server starting error" << std::endl;
    }
}

void Server::Connection(int socketDescriptor)
{
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket,SIGNAL(readyRead()),this,SLOT(SocketReady()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(SocketDisconnect()));

    std::cout << "Socket descriptor " << socketDescriptor << std::endl;
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
void Server::SendPackage(int command, QString s0, QString s1, QString s2, QString s3){
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

// Get client request
ServerResponse Server::ParsePackage(){
    document = QJsonDocument::fromJson(byteArray, &error);
    if(error.errorString() == "no error occurred"){
        int command = document.object().value("command").toString().toInt();
        QString s0 = document.object().value("s0").toString();
        QString s1 = document.object().value("s1").toString();
        QString s2 = document.object().value("s2").toString();
        QString s3 = document.object().value("s3").toString();

        switch(command){
        case(REGISTER):{
            for (auto it = registeredUsers.begin(); it != registeredUsers.end(); ++it){
                if(it->login == s0){
                    return REGISTER_ERROR;
                }
            }
            User u(s0, s1);
            registeredUsers.push_back(u);
            PrintRegisteredUsers();
            return REGISTER_OK;
            break;
        }
        case(LOGIN):{
            for (auto it = registeredUsers.begin(); it != registeredUsers.end(); ++it){
                if(it->login == s0 && it->password == s1){
                    User u(s0, s1);
                    loggedInUsers.push_back(u);
                    PrintLoggedInUsers();
                    return LOGIN_OK;
                }
            }
            return LOGIN_ERROR;
            break;
        }
        case(CHAT):{
            return CHAT_OK;
            break;
        }
        case(MESSAGE):{
            return MESSAGE_OK;
            break;
        }
        default:
            break;
        }
    }else{
        qDebug() << "Server Parse JSON Package Error";
    }
}

// Response to the client
void Server::SocketReady()
{
    byteArray = socket->readAll();
    socket->write(byteArray);    // Echo
    qDebug() << "Raw data from client" << byteArray;
    ServerResponse response;
    response = ParsePackage();

    switch(response){
    case(REGISTER_OK):
        SendPackage(REGISTER_OK, PLACE_HOLDER, PLACE_HOLDER, PLACE_HOLDER, PLACE_HOLDER);
        break;
    case(LOGIN_OK):
        SendPackage(LOGIN_OK, PLACE_HOLDER, PLACE_HOLDER, PLACE_HOLDER, PLACE_HOLDER);
        break;
    case(CHAT_OK):
        break;
    case(MESSAGE_OK):
        break;
    case(REGISTER_ERROR):
        SendPackage(REGISTER_ERROR, PLACE_HOLDER, PLACE_HOLDER, PLACE_HOLDER, PLACE_HOLDER);
        break;
    case(LOGIN_ERROR):
        SendPackage(LOGIN_ERROR, PLACE_HOLDER, PLACE_HOLDER, PLACE_HOLDER, PLACE_HOLDER);
        break;
    case(CHAT_ERROR):
        break;
    case(MESSAGE_ERROR):
        break;
    default:
        break;
    }
}

void Server::SocketDisconnect()
{
    std::cout << "Disconnect" << std::endl;
    socket->deleteLater();
}

void Server::RegisterUser(User &u){
    registeredUsers.push_back(u);
}

void Server::PrintRegisteredUsers(){
    qDebug() << "Table of Registered Users";
    for (auto it = registeredUsers.begin(); it != registeredUsers.end(); ++it){
        qDebug() << it->id << " " << it->login << " " << it->password;
    }
}

void Server::LogInUser(User &u){
    loggedInUsers.push_back(u);
}

void Server::PrintLoggedInUsers(){
    qDebug() << "Table of Logged In Users";
    for (auto it = loggedInUsers.begin(); it != loggedInUsers.end(); ++it){
        qDebug() << it->id << " " << it->login << " " << it->password;
    }
}
