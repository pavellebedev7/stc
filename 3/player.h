#pragma once
#ifndef PLAYER_H_
#define PLAYER_H_
#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

struct Track{
    int id;
    string name;
};

class Player{
public:
    Player();
    ~Player();

    void GetState();
    void SetTrack(int id);
    void NextTrack();
    void PreviousTrack();
    void VolumeUp();
    void VolumeDown();

private:
    int trackId;
    int N;
    string trackName;
    int volume;
    Track* trackList;
    static const int minVolume = 0;
    static const int maxVolume = 10;
};

#endif
