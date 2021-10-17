#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int CurrentYear = 2021;
const int n = 5;

struct Citizen{
    string LastName;
    string Residence;
    int DateOfBirth;
};

void PrintFile(Citizen *citizens){
    for(int i = 0; i < n; i++){
        cout << citizens[i].LastName << " " << citizens[i].Residence << " " << citizens[i].DateOfBirth << endl;
    }
}

void EditFile(Citizen *citizens){
    int editline;
    cout << "Enter the line to be changed" << endl;
    cin >> editline;
    if(editline >= 1 && editline <= n){
        editline--;
        cout << "Enter new LastName" << endl;
        cin >> citizens[editline].LastName;
        cout << "Enter new Residence" << endl;
        cin >> citizens[editline].Residence;
        cout << "Enter new DateOfBirth" << endl;
        cin >> citizens[editline].DateOfBirth;
        cout << "Line " << editline+1 << " has been changed" << endl;
    }
    else{
        cout << "This line doesn't exist" << endl;
    }
}

void GetAverageAge(Citizen *citizens){
    int tmp = 0;
    for(int i = 0; i < n; i++){
        tmp += CurrentYear - citizens[i].DateOfBirth;
    }
    float avg = (float)tmp/n;
    cout << "Average age: " << avg << endl;
}

void SaveFile(Citizen *citizens){
    string filename;
    cout << "Enter filename to save to" << endl;
    cin >> filename;
    ofstream fout;
    fout.open(filename.c_str());
    if(fout){
        for(int i = 0; i < n; i++){
            fout << citizens[i].LastName << " " << citizens[i].Residence << " " << citizens[i].DateOfBirth << endl;
        }
        fout.close();
        cout << "Saved to " << filename << endl;
    }
    else{
        cout << "Error" << endl;
    }
}

int main()
{
    // 20 var
    // Memory allocation
    Citizen* citizens = new Citizen[n];

    // File I/O
    ifstream fin;
    fin.open("input.txt");

    // Read file
    if(fin){
        for(int i = 0; i < n; i++){
            fin >> citizens[i].LastName >> citizens[i].Residence >> citizens[i].DateOfBirth;
        }
        fin.close();
    }
    else{
        cout << "Error" << endl;
    }

    // Menu
    int command, exitflag = 0;
    while(true && !exitflag){
        cout << "Enter 1 - Print, 2 - Edit, 3 - Get average age, 4 - Save, 5 - Exit" << endl;
        cin >> command;
        switch(command){
            case(1):
                // Print file
                PrintFile(citizens);
                break;
            case(2):
                // Edit file
                EditFile(citizens);
                break;
            case(3):
                // Get average age
                GetAverageAge(citizens);
                break;
            case(4):
                // Save file
                SaveFile(citizens);
                break;
            case(5):
                // Exit
                cout << "Exit" << endl;
                exitflag = 1;
                break;
            default:
                break;
        }
    }

    // Memory deallocation
    delete[] citizens;
}
