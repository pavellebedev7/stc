#include "passport.h"

Passport::Passport(string newFirstName="PassportLastNamePlaceHolder",
                   string newLastName="PassportFirstNamePlaceHolder",
                   int newDateOfIssue=0,
                   int newSerialNumber=0)
    : Document(newFirstName, newLastName, newDateOfIssue)
    , serialNumber(newSerialNumber)
{}

void Passport::show(){
    cout << "Passport\t First Name: " << firstName << " Last Name: " << lastName << " Date Of Issue: " << dateOfIssue << " Serial Number: " << serialNumber << endl;
}

void Passport::edit(){
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
    cout << "Enter the Serial number:" << endl;
    cin >> intTmp;
    if(cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Date of Issue has not been changed" << endl;
    }
    else{
        setSerialNumber(intTmp);
    }
    cout << "Document edited" << endl;
}

void Passport::setSerialNumber(int newSerialNumber){
    serialNumber = newSerialNumber;
}
