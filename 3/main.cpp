#include "player.h"

using namespace std;

int main()
{
    // 20 var, Player
    Player player1;

    // Menu
    cout << "Enter 1 - Next Track, 2 - Previous Track, 3 - Set Track, 4 - Volume Up, 5 - Volume Down, 6 - Exit" << endl;
    int command, exitflag = 0;
    while(true && !exitflag){
        player1.GetState();
        cin >> command;
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter an integer" << endl;
        }
        switch(command){
            case(1):
                // Next Track
                player1.NextTrack();
                break;
            case(2):
                // Previous Track
                player1.PreviousTrack();
                break;
            case(3):
                // Set track
                cout << "Enter track id" << endl;
                int tmpId;
                cin >> tmpId;
                player1.SetTrack(tmpId);
                break;
            case(4):
                // Volume Up
                player1.VolumeUp();
                break;
            case(5):
                // Volume Down
                player1.VolumeDown();
                break;
            case(6):
                // Exit
                exitflag = 1;
                break;
            default:
                break;
        }
    }
}
