#ifndef TRAIN
#define TRAIN

#include <bits/stdc++.h>

// States for the train
enum TrainStates { Arrived, Departed, Queued };

class Train
{
    private:
        std::string name;

        std::string current_station;

        int time_til_arrival;
        int time_til_departure;

        // Current state of the train
        TrainStates state;

    public:
        Train(std::string, std::string); // Constructor

        std::string GetStation(); // Returns the current station
        void SetStation(std::string); // Sets the current station

        std::string GetName() const; // Returns the name of the train

        void Wait(); // Sets the state of the train as queued
        void Start(); // Removes queued state if in it

        void Update(int, int); // Updates the time variables

        void ShowInfo(); // Prints information about the train

        int Simulate(); // Simulates x units of time
};

#endif
