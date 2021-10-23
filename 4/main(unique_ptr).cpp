#include "document.h"
#include "passport.h"
#include "studentid.h"
#define ARRAYSIZE 5

using namespace std;

int main()
{

    // 20 var
    vector<unique_ptr<Document>> documents;
    documents.push_back(make_unique<Document>("FirstName1", "LastName1", 1992));
    documents.push_back(make_unique<Passport>("FirstName2", "LastName2", 1994, 900001));
    documents.push_back(make_unique<Passport>("FirstName3", "LastName3", 1990, 900002));
    documents.push_back(make_unique<StudentID>("FirstName4", "LastName4", 1996, "1010"));
    documents.push_back(make_unique<StudentID>("FirstName5", "LastName5", 1998, "1050"));


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
                for(int i = 0; i < documents.size(); i++){
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
                if(editline >= 0 && editline < documents.size())
                    documents[editline]->edit();
                else
                    cout << "Line doesn't exist" << endl;
                break;
            case(3):{
                // Find the earliest document
                cout << "The earliest document: " << endl;
                int minIndex = 0;
                int minValue = documents[minIndex]->getDateOfIssue();
                for(int i = 0; i < documents.size(); i++){
                    if(documents[i]->getDateOfIssue() < minValue){
                        minValue = documents[i]->getDateOfIssue();
                        minIndex = i;
                    }
                }
                documents[minIndex]->show();
                }
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

