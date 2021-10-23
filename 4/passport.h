#ifndef PASSPORT_H
#define PASSPORT_H
#include "document.h"

class Passport:public Document
{
public:
    Passport(string newFirstName, string newLastName, int newDateOfIssue, int newSerialNumber);
    void show();
    void edit();
    void setSerialNumber(int newSerialNumber);
private:
    int serialNumber;
};

#endif // PASSPORT_H
