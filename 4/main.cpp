#include "document.h"
#include "passport.h"
#include "studentid.h"
#define ARRAYSIZE 5

using namespace std;

// Find the earliest document from the beginning of array
void findTheEarliestDocumentFrom(Document* input[]){
    int minIndex = 0;
    int minValue = input[minIndex]->getDateOfIssue();
    for(int i = 0; i < ARRAYSIZE; i++){
        if(input[i]->getDateOfIssue() < minValue){
            minValue = input[i]->getDateOfIssue();
            minIndex = i;
        }
    }
    input[minIndex]->show();
}

int main()
{
    // 20 var, Document and passport
    Document* documents[ARRAYSIZE];
    Document  d1("FirstName1", "LastName1", 1992);
    Passport  p1("FirstName2", "LastName2", 1994, 900001);
    Passport  p2("FirstName3", "LastName3", 1990, 900002);
    StudentID s1("FirstName4", "LastName4", 1996, "1010");
    StudentID s2("FirstName5", "LastName5", 1998, "1050");
    documents[0] = &d1;
    documents[1] = &p1;
    documents[2] = &p2;
    documents[3] = &s1;
    documents[4] = &s2;

    // Menu
    int command, exitflag = 0;
    while(true && !exitflag){
        cout << "Enter 1 - Print array, 2 - Edit, 3 - Find the earliest, 4 - Exit" << endl;
        cin >> command;
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter an integer" << endl;
        }
        switch(command){
            case(1):
                // Print array
                for(int i = 0; i < ARRAYSIZE; i++){
                    documents[i]->show();
                }
                break;
            case(2):
                // Edit
                cout << "Enter a line number to be changed" << endl;
                int editline;
                cin >> editline;
                if(cin.fail()){
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Enter an integer" << endl;
                    break;
                }
                editline--;
                if(editline >= 0 && editline < ARRAYSIZE)
                    documents[editline]->edit();
                else
                    cout << "Line doesn't exist" << endl;
                break;
            case(3):
                // Find the earliest document
                cout << "The earliest document: " << endl;
                findTheEarliestDocumentFrom(documents);
                break;
            case(4):
                // Exit
                exitflag = 1;
                break;
            default:
                break;
        }
    }
}

