#include "studentid.h"

StudentID::StudentID(string newFirstName="StudentIdFirstNamePlaceHolder",
                     string newLastName="StudentIdLastNamePlaceHolder",
                     int newDateOfIssue=0,
                     string newGroup="StudentIdGroupPlaceHolder")
    : Document(newFirstName, newLastName, newDateOfIssue)
    , group(newGroup)
{}

void StudentID::show(){
    cout << "StudentID\t First Name: " << firstName << " Last Name: " << lastName << " Date Of Issue: " << dateOfIssue << " Gropup: " << group << endl;
}

void StudentID::edit(){
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
    cout << "Enter the Group:" << endl;
    cin >> tmp;
    setGroup(tmp);
    cout << "Document edited" << endl;
}

void StudentID::setGroup(string newGroup){
    group = newGroup;
}
