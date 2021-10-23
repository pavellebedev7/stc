#ifndef DOCUMENT_H
#define DOCUMENT_H
#include <iostream>
#include <string>
#include <limits>
#include <memory>
#include <vector>

using namespace std;

class Document
{
public:
    Document(string newFirstName, string newLastName, int newDateOfIssue);
    virtual void show();
    virtual void edit();
    void setFirstName(string newFirstName);
    void setLastName(string newLastName);
    void setDateOfIssue(int newDateOfIssue);
    int getDateOfIssue();
protected:
    string firstName;
    string lastName;
    int dateOfIssue;
};

#endif // DOCUMENT_H
