#include "player.h"

using namespace std;

Player::Player(){
    cout << "Player sterted" << endl;
    ifstream fin;
    fin.open("state.txt");

    // Read last state and playlist
    if(fin){
        fin >> trackId >> N >> volume;
        cout << trackId << "/" << N << " " << volume << "/" << maxVolume << endl;
        trackList = new Track[N];
        for(int i = 0; i < N; ++i){
            fin >> trackList[i].id >> trackList[i].name;
            cout << trackList[i].id << " " << trackList[i].name << endl;
        }
        trackName = trackList[trackId-1].name;
        fin.close();
    }
    else{
        cout << "Loading error" << endl;
    }
}

Player::~Player(){
    ofstream fout;
    fout.open("state.txt");
    // Save state
    if(fout){
        fout << trackId << " " << N << " " << volume << endl;
        for(int i = 0; i < N; ++i){
            fout << trackList[i].id << " " << trackList[i].name << endl;
        }
        fout.close();
        cout << "Saved" << endl;
        }
        else{
            cout << "Saving error" << endl;
        }
    delete[] trackList;
    cout << "Player closed" << endl;
}

void Player::GetState(){
    cout << "Current state: " << trackId << "/" << N << " " << trackName << " " << volume << "/" << maxVolume << endl;
}

void Player::SetTrack(int id){
    if(id <= N && id >= 1){
        trackId = id;
        trackName = trackList[trackId-1].name;
    }
    else{
        cout << "Track doesn't exist" << endl;
    }
}

void Player::NextTrack(){
    if(trackId < N){
        ++trackId;
    }
    else{
        trackId = 1;
    }
    trackName = trackList[trackId-1].name;
}

void Player::PreviousTrack(){
    if(trackId > 1){
        --trackId;
    }
    else{
        trackId = N;
    }
    trackName = trackList[trackId-1].name;
}

void Player::VolumeUp(){
    if(volume < maxVolume){
        ++volume;
    }
}

void Player::VolumeDown(){
    if(volume > minVolume){
        --volume;
    }
}
