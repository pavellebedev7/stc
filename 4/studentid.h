#ifndef STUDENTID_H
#define STUDENTID_H
#include "document.h"

class StudentID:public Document
{
public:
    StudentID(string newFirstName, string newLastName, int newDateOfIssue, string newGroup);
    void show();
    void edit();
    void setGroup(string newGroup);
private:
    string group;
};

#endif // STUDENTID_H
