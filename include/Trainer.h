#ifndef TRAINER_H_
#define TRAINER_H_

#include <vector>
#include "../include/Studio.h"

class Workout;
class Customer;

typedef std::pair<int, Workout> OrderPair; //id customer, workout options

class Trainer{
public:
    Trainer(int t_capacity);
    Trainer(Trainer &other);//copy constructor
    virtual ~Trainer();//destructor
    void clear();
    Trainer(Trainer &&other);//move constructor
    Trainer& operator=(const Trainer &aTrainer);//copy assignment
    Trainer& operator=(Trainer&& other);//move assignment

    int getCapacity() const;
    void addCustomer(Customer* customer);
    void removeCustomer(int id);
    Customer* getCustomer(int id);
    std::vector<Customer*>& getCustomers();
    std::vector<OrderPair>& getOrders();
    void order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout>& workout_options);
    void openTrainer();
    void closeTrainer();
    int getSalary();
    bool isOpen();

private:
    int capacity;
    bool open;
    std::vector<Customer*> customersList;
    std::vector<OrderPair> orderList; //A list of pairs for each order for the trainer - (customer_id, Workout)
    //added myself
    int salary;
};


#endif