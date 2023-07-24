#ifndef STUDIO_H_
#define STUDIO_H_

#include <vector>
#include <string>
#include "../include/Customer.h"
#include "../include/Trainer.h"
#include "../include/Workout.h"
#include <iostream>
#include <fstream>
#include <sstream>
//Forward declaration
class Trainer;
//Forward declaration
class BaseAction;

class Studio{
public:
    Studio();
    Studio(const std::string &configFilePath);
    Studio(Studio &other);//copy constructor
    virtual ~Studio();//destructor
    void clear();
    Studio(Studio&& other);//move constructor
    Studio& operator=(const Studio &aStudio);//copy assignment
    Studio& operator=(Studio&& other);//move assignment
    void start();
    int getNumOfTrainers() const;
    Trainer* getTrainer(int tid);
    const std::vector<BaseAction*>& getActionsLog() const; // Return a reference to the history of actions
    std::vector<Workout>& getWorkoutOptions();
    std::vector<Trainer*> getTrainers();
private:
    bool open;
    std::vector<Trainer*> trainers;
    std::vector<Workout> workout_options;
    std::vector<BaseAction*> actionsLog;
};

#endif