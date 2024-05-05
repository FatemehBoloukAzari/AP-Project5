#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>
#include "carwash.h"

const bool IN_STAGE = true;
const bool IN_THE_STAGE = true;
const int NO_MORE_STAGE = 0;
const bool WORKER_FOUND = true;
const bool WORKER_NOT_FOUND = false;


void CarWash::add_stage(int stage_id, int price)
{
    stages.push_back(new Stage(stage_id, price));
}

void CarWash::add_worker(int worker_id, int stage_id, int time_to_finish)
{
    Stage* stage = find_stage_by_id(stage_id);
    stage->add_worker(worker_id, time_to_finish);
}

void CarWash::car_arrival(vector <int> stages_ids, Time current_time)
{
    for (auto stage : stages_ids)
    {
        if (find_stage_by_id(stage) == NULL)
        {
            cout << "NOT FOUND" << endl;
            return;
        }
    }
    int id = cars.size() + 1;
    cars.push_back(new Car(id, stages_ids));
    int first_stage_id = stages_ids[0];
    cout << current_time.get_time() << " Car " << id << ": Arrived -> ";
    Stage* stage = find_stage_by_id(first_stage_id);
    if (stage->add_car(cars.back(), current_time) == IN_STAGE)
        cout << "Stage " << first_stage_id << endl;
    else
        cout << "Queue " << first_stage_id << endl;
}

Stage* CarWash::find_stage_by_id(int stage_id)
{
    for (auto &stage : stages)
        if (stage->get_id() == stage_id)
            return stage;
    return NULL;
}

void CarWash::get_stage_status(int stage_id)
{
    Stage* stage = find_stage_by_id(stage_id);
    if (stage == NULL)
    {
        cout << "NOT FOUND" << endl;
        return;
    }
    stage->output_stage_status();
}

void CarWash::get_worker_status(int worker_id)
{
    for (auto &stage : stages)
    {
        if (stage->output_worker_status(worker_id) == WORKER_FOUND)
            return;
    }
    cout << "NOT FOUND" << endl;
}

void CarWash::get_car_status(int car_id)
{
    if (car_id >= cars.size() || car_id <= 0)
    {
        cout << "NOT FOUND" << endl;
        return;
    }
    for (auto &stage : stages)
        if (stage->output_car_status(car_id) == IN_THE_STAGE)
            return;
    cout << "Done" << endl;
}

bool changes_cmp(Change a, Change b)
{
    return a.get_id() < b.get_id();
}

void CarWash::pass_time(int number_of_time_units, Time &current_time)
{
    while (number_of_time_units--)
    {
        current_time.next_time();
        vector <pair<Car*, int>> finished_cars;
        vector <Change> changes;
        for (auto &stage : stages)
        {
            auto ret = stage->update_time(current_time);
            for (auto &finished_car : ret.first)
                finished_cars.push_back({finished_car, stage->get_id()});
            for (auto change : ret.second)
                changes.push_back(change);
        }
        for (auto &[car, id] : finished_cars)
        {
            string status_string = "Stage ";
            status_string += to_string(id) +  " -> ";
            int next_stage_id = car->get_first_remaining_stage();
            if (next_stage_id == NO_MORE_STAGE)
            {
                status_string += "Done";
                changes.push_back(Change(car->get_id(), status_string));
                continue;
            }
            for (auto &stage : stages)
            {
                if (stage->get_id() == next_stage_id)
                {
                    if (stage->add_car(car, current_time) == IN_STAGE)
                        status_string += "Stage " + to_string(next_stage_id);
                    else
                        status_string += "Queue " + to_string(next_stage_id);
                }
            }
            changes.push_back(Change(car->get_id(), status_string));
        }
        sort(changes.begin(), changes.end(), changes_cmp);
        for (auto change : changes)
            cout << current_time.get_time() << " Car " << change.get_id() << ": " << change.get_status() << endl;
    }
}