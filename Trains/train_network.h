#ifndef TRAIN_NETWORK
#define TRAIN_NETWORK

#include <bits/stdc++.h>
#include "train.h"

// Information about a station
struct Station
{
    std::vector<std::pair<std::string, int>> connected_stations;

    int time_til_departure;

    // Trains approaching the station
    std::vector<Train> approaching_trains;

    // Queue for the trains in the same station
    std::queue<Train> train_queue;
};

class TrainNetwork
{
    private:
        // Train network graph using a map
        std::map<std::string, Station> stations_graph;
    
    public:
        TrainNetwork(std::map<std::string, Station>);

        void ShowNetwork();

        void Simulate(int steps);
};

#endif
