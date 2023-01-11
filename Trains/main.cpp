#include <bits/stdc++.h>
#include "train_network.h"

void clear()
{
#if defined _WIN32
    system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
#elif defined (__APPLE__)
    system("clear");
#endif
}

int main()
{
    // Opening a stream to read the network info text file
    std::ifstream info;
    info.open("network_info.txt");

    int stations_count;
    info >> stations_count;

    std::map<std::string, Station> stations_graph;
    while (stations_count--)
    {
        std::string station_name;
        info >> station_name;

        int time_til_departure;
        info >> time_til_departure;

        int connected_stations_count;
        info >> connected_stations_count;

        std::vector<std::pair<std::string, int>> connected_stations;
        while (connected_stations_count--)
        {
            std::string connected_staion_name;
            int time_til_arrival;
            info >> connected_staion_name >> time_til_arrival;

            connected_stations.push_back({connected_staion_name, time_til_arrival});
        }

        stations_graph[station_name] = {connected_stations, time_til_departure};
    }

    int trains_count;
    info >> trains_count;

    while (trains_count--)
    {
        std::string train_name;
        std::string current_station;
        info >> train_name >> current_station;

        stations_graph[current_station].train_queue.push(Train(train_name, current_station));
    }

    TrainNetwork train_network = TrainNetwork(stations_graph);

    int step = 1;

    // Run the simulation infinitely
    while (true)
    {
        std::cout << "Step " << step << '\n';

        train_network.ShowNetwork();

        std::cout << "Enter the number of steps to simulate: ";
        
        int steps;
        std::cin >> steps;

        train_network.Simulate(steps);

        step += steps;

        clear();
    }
}
