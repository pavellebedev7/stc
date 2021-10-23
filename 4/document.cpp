#include "document.h"

Document::Document(string newFirstName="DocumentFirstNamePlaceHolder",
                   string newLastName="DocumentLastNamePlaceHolder",
                   int newDateOfIssue=0)
    : firstName(newFirstName)
    , lastName(newLastName)
    , dateOfIssue(newDateOfIssue)
{}

void Document::show(){
    cout << "Document\t First Name: " << firstName << " Last Name: " << lastName << " Date Of Issue: " << dateOfIssue << endl;
}

void Document::edit(){
    string tmp;
    int intTmp;
    cout << "Enter the first name:" << endl;
    cin >> tmp;
    setFirstName(tmp);
    cout << "Enter the last name:" << endl;
    cin >> tmp;
    setLastName(tmp);
    cout << "Enter the Date Of Issue:" << endl;
    cin >> intTmp;
    if(cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Date of Issue has not been changed" << endl;
    }
    else{
        setDateOfIssue(intTmp);
    }
    cout << "Document edited" << endl;
}

void Document::setFirstName(string newFirstName){
    firstName = newFirstName;
}

void Document::setLastName(string newLastName){
    lastName = newLastName;
}

void Document::setDateOfIssue(int newDateOfIssue){
    dateOfIssue = newDateOfIssue;
}

int Document::getDateOfIssue(){
    return dateOfIssue;
}
