#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include <vector>
#include <string>

#include "../include/Workout.h"

#include <iostream>
#include <algorithm>
class Workout;
class Customer{
public:
    Customer(std::string c_name, int c_id);
    virtual ~Customer() = default;
    virtual std::vector<int> order(const std::vector<Workout> &workout_options)=0;
    virtual std::string toString() const = 0;
    std::string getName() const;
    int getId() const;
    virtual std:: string typeToString() = 0;
private:
    const std::string name;
    const int id;

};
bool mclComparator(std::pair<int, int> &pair1,std::pair<int, int> &pair2);

class SweatyCustomer : public Customer {
public:
    SweatyCustomer(std::string name, int id);
    ~SweatyCustomer();
    std::vector<int> order(const std::vector<Workout> &workout_options);
    std::string toString() const;
    std:: string typeToString();
private:
};


class CheapCustomer : public Customer {
public:
    CheapCustomer(std::string name, int id);
    ~CheapCustomer();
    std::vector<int> order(const std::vector<Workout> &workout_options);
    std::string toString() const;
    std:: string typeToString();
private:
};


class HeavyMuscleCustomer : public Customer {
public:
    HeavyMuscleCustomer(std::string name, int id);
    ~HeavyMuscleCustomer();
    std::vector<int> order(const std::vector<Workout> &workout_options);
    std::string toString() const;
    std:: string typeToString();
private:
};


class FullBodyCustomer : public Customer {
public:
    FullBodyCustomer(std::string name, int id);
    ~FullBodyCustomer();
    std::vector<int> order(const std::vector<Workout> &workout_options);
    std::string toString() const;
    std:: string typeToString();
private:
};


#endif