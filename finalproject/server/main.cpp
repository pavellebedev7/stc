#include <QCoreApplication>
#include "server.h"


int main(int argc, char *argv[])
{

    std::vector <User> registeredUsers;
    std::vector <User> loggedInUsers;

    QCoreApplication a(argc, argv);

    Server server;
    server.Start();

    return a.exec();
}
