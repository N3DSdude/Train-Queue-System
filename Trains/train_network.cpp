#include <bits/stdc++.h>
#include "train_network.h"

TrainNetwork::TrainNetwork(std::map<std::string, Station> stations_graph)
{
    this->stations_graph = stations_graph;
}

void TrainNetwork::ShowNetwork()
{
    for (auto const &x : stations_graph)
    {
        Station current_station = stations_graph[x.first];

        if (current_station.train_queue.empty() && current_station.approaching_trains.empty())
        {
            continue;
        }

        std::cout << "Station: " << x.first << "\n\n";

        if (!current_station.train_queue.empty())
        {
            std::cout << "Stationed trains\n";
            
            while (!current_station.train_queue.empty())
            {
                current_station.train_queue.front().ShowInfo();
                current_station.train_queue.pop();

                std::cout << '\n';
            }
        }

        if (!current_station.approaching_trains.empty())
        {
            std::cout << "Approaching trains\n";

            for (int i = 0; i < current_station.approaching_trains.size(); ++i)
            {
                current_station.approaching_trains[i].ShowInfo();
                
                std::cout << '\n';
            }

            std::cout << '\n';
        }
    }
}

void TrainNetwork::Simulate(int steps)
{
    for (int i = 0; i < steps; ++i)
    {
        for (auto const &x : stations_graph)
        {
            Station current_station = stations_graph[x.first];

            // Simulating the first train in the queue inside a station
            if (!current_station.train_queue.empty())
            {
                Train &current_train = current_station.train_queue.front();
                current_train.Start();

                int signal = current_train.Simulate();

                if (signal == 1)
                {
                    int connected_stations_count = current_station.connected_stations.size();
                    std::pair<std::string, int> next_station = current_station.connected_stations[rand() % connected_stations_count];

                    current_train.SetStation(next_station.first);

                    Station &new_station = stations_graph[current_train.GetStation()];
                    current_train.Update(next_station.second, new_station.time_til_departure);

                    new_station.approaching_trains.push_back(current_train);

                    current_station.train_queue.pop();
                }
            }

            // Simulating all the approching trains to this station
            for (int i = 0; i < current_station.approaching_trains.size(); ++i)
            {
                Train &current_train = current_station.approaching_trains[i];

                int signal = current_train.Simulate();

                if (signal == 1)
                {
                    if (!current_station.train_queue.empty())
                    {
                        current_train.Wait();
                    }

                    current_station.train_queue.push(current_train);

                    current_station.approaching_trains.erase(current_station.approaching_trains.begin() + i);

                    --i;
                }
            }

            stations_graph[x.first] = current_station;
        }
    }

    for (auto const &x : stations_graph)
    {
        Station current_station = stations_graph[x.first];

        if (current_station.train_queue.empty())
        {
            continue;
        }

        Train &current_train = current_station.train_queue.front();
        current_train.Start();

        stations_graph[x.first] = current_station;
    }
}
