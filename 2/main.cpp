#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int CurrentYear = 2021;
const int n = 5;

class Citizen{
public:
    Citizen();
    Citizen(string name, string res, int date);

    ~Citizen();

    string GetCitizenLastName();
    string GetCitizenResidence();
    int GetDateOfBirth();

    void SetCitizenLastName(string Name);
    void SetCitizenResidence(string Res);
    void SetCitizenDateOfBirth(int Date);

    void PrintCitizenInfo();
    void EditCitizenInfo();
private:
    string LastName;
    string Residence;
    int DateOfBirth;
};

Citizen::Citizen(){
    LastName = "LastNamePlaceholder";
    Residence = "ResidencePlaceholder";
    DateOfBirth = 0;
}

Citizen::Citizen(string name, string res, int date){
    LastName = name;
    Residence = res;
    DateOfBirth = date;
}

Citizen::~Citizen(){

}

string Citizen::GetCitizenLastName(){
    return LastName;
}

string Citizen::GetCitizenResidence(){
    return Residence;
}

int Citizen::GetDateOfBirth(){
    return DateOfBirth;
}

void Citizen::SetCitizenLastName(string Name){
    LastName = Name;
}

void Citizen::SetCitizenResidence(string Res){
    Residence = Res;
}

void Citizen::SetCitizenDateOfBirth(int Date){
    DateOfBirth = Date;
}


void Citizen::PrintCitizenInfo(){
    cout << LastName << " " << Residence << " " << DateOfBirth << endl;
}

void Citizen::EditCitizenInfo(){
        cout << "Enter new LastName" << endl;
        cin >> LastName;
        cout << "Enter new Residence" << endl;
        cin >> Residence;
        cout << "Enter new DateOfBirth" << endl;
        cin >> DateOfBirth;
}

void GetAverageAge(Citizen *citizens){
    int tmp = 0;
    for(int i = 0; i < n; i++){
        tmp += CurrentYear - citizens[i].GetDateOfBirth();
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
            fout << citizens[i].GetCitizenLastName() << " " << citizens[i].GetCitizenResidence() << " " << citizens[i].GetDateOfBirth() << endl;
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
    string tmpName, tmpRes;
    int tmpDate;

    // Read file
    if(fin){
        for(int i = 0; i < n; i++){
            fin >> tmpName >> tmpRes >> tmpDate;
            citizens[i].SetCitizenLastName(tmpName);
            citizens[i].SetCitizenResidence(tmpRes);
            citizens[i].SetCitizenDateOfBirth(tmpDate);
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
                for(int i = 0; i < n; ++i){
                    citizens[i].PrintCitizenInfo();
                }
                break;
            case(2):
                // Edit file
                cout << "Enter line to be changed" << endl;
                int editline;
                cin >> editline;
                if(editline >= 1 && editline <= n){
                    --editline;
                }
                else{
                    cout << "This line does't exist" << endl;
                    break;
                }
                citizens[editline].EditCitizenInfo();
                cout << "Line " << editline+1 << " has been changed" << endl;
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
