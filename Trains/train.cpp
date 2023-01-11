#include <iostream>
#include "train.h"

Train::Train(std::string name, std::string current_station)
{
    this->name = name;

    time_til_arrival = 0;
    time_til_departure = 1;

    this->current_station = current_station;

    state = Arrived;
}

std::string Train::GetStation()
{
    return current_station;
}

void Train::SetStation(std::string station)
{
    current_station = station;
}

std::string Train::GetName() const
{
    return name;
}

void Train::Wait()
{
    state = Queued;
}

void Train::Start()
{
    if (state == Queued)
    {
        state = Arrived;
    }
}


void Train::Update(int time_til_arrival, int time_til_departure)
{
    this->time_til_arrival = time_til_arrival;
    this->time_til_departure = time_til_departure;
}

void Train::ShowInfo()
{
    std::cout << name << '\n';

    switch (state)
    {
    case Arrived:
        std::cout << "Time 'til departure: " << time_til_departure << '\n';

        break;

    case Departed:
        std::cout << "Time 'til arrival: " << time_til_arrival << '\n';

        break;

    case Queued:
        std::cout << "Train is in queue.\n";

        break;
    }
}

int Train::Simulate()
{
    // State machine
    switch (state)
    {
    case Arrived:
        --time_til_departure;

        if (time_til_departure == 0)
        {
            state = Departed;

            return 1;
        }

        break;

    case Departed:
        --time_til_arrival;

        if (time_til_arrival == 0)
        {
            state = Arrived;

            return 1;
        }

        break;
    }

    return 0;
}
