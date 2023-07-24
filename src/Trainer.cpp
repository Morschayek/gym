//
// Created by spl211 on 08/11/2021.
//
#include "../include/Trainer.h"



Trainer:: Trainer(int t_capacity):
        capacity(t_capacity),
        open(false),
        customersList(),
        orderList(),
        salary(0)
{

}
//copy constructor
Trainer:: Trainer(Trainer &other):
        capacity(other.capacity),
        open(other.open),
        customersList(),
        orderList(other.orderList),
        salary(other.salary)
{
    for(size_t i = 0; i < other.customersList.size(); i++)
    {
        Customer* customer;
        if (other.customersList[i]->typeToString() == "swt") 
        {
            customer = new SweatyCustomer(other.customersList[i]->getName(), other.customersList[i]->getId());
        }
        else if (other.customersList[i]->typeToString() == "chp")
        {
            customer = new CheapCustomer(other.customersList[i]->getName(), other.customersList[i]->getId());
        }
        else if (other.customersList[i]->typeToString() == "mcl")
        {
            customer = new HeavyMuscleCustomer(other.customersList[i]->getName(), other.customersList[i]->getId());
        }
        else
        {
            customer = new FullBodyCustomer(other.customersList[i]->getName(), other.customersList[i]->getId());
        }
        this->customersList.push_back(customer);
    }
}

//destructor
Trainer :: ~Trainer()
{
    clear();
}
void Trainer :: clear()
{
    for (size_t i = 0; i < customersList.size(); i++)
    {
        delete customersList[i];
    }
    customersList.clear();
    orderList.clear();
    salary=0;
}
//move constructor
Trainer:: Trainer(Trainer&& other):
        capacity(other.capacity),
        open(other.open),
        customersList(other.customersList),
        orderList(other.orderList),
        salary(other.salary)
{
    other.capacity = 0;
    other.customersList.clear();
    other.orderList.clear();
    other.salary = 0;
}
//copy assignment
Trainer & Trainer:: operator=(const Trainer &aTrainer)
{
    if (this != &aTrainer)
    {
        this->clear();
        this->capacity = aTrainer.capacity;
        this->open = aTrainer.open;
        this->salary = aTrainer.salary;
        for(size_t i = 0; i < aTrainer.customersList.size(); i++)
        {
            Customer* customer;
            if (customersList[i]->typeToString() == "swt") 
            {
                customer = new SweatyCustomer(aTrainer.customersList[i]->getName(), aTrainer.customersList[i]->getId());
            }
            else if (customersList[i]->typeToString() == "chp")
            {
                customer = new CheapCustomer(aTrainer.customersList[i]->getName(), aTrainer.customersList[i]->getId());
            }
            else if (customersList[i]->typeToString() == "mcl")
            {
                customer = new HeavyMuscleCustomer(aTrainer.customersList[i]->getName(), aTrainer.customersList[i]->getId());
            }
            else
            {
                customer = new FullBodyCustomer(aTrainer.customersList[i]->getName(), aTrainer.customersList[i]->getId());
            }
            this->customersList.push_back(customer);
        }
        this->orderList = std::vector<OrderPair>(aTrainer.orderList);
        this->salary = aTrainer.salary;
    }
    return *this;
}
//move assignment
Trainer& Trainer:: operator=(Trainer &&other)
{
    if (this != &other)
    {
        this->clear();
        capacity = other.capacity;
        open = other.open;
        customersList = other.customersList;
        for (size_t i = 0; i < other.orderList.size(); i++)
        {
            orderList.push_back(other.orderList[i]);
        }
        salary = other.salary;
        other.capacity = 0;
        other.customersList.clear();
        other.orderList.clear();
        other.salary = 0;
    }
    return *this;
}

int Trainer:: getCapacity() const
{
    return capacity;
}
void Trainer:: addCustomer(Customer* customer)
{
    size_t capacity = getCapacity();
    if (customersList.size() < capacity)
    {
        customersList.push_back(customer);
    }
}
void Trainer:: removeCustomer(int id)
{
    std:: vector<Customer*> newCustomersList;
    for(size_t i = 0; i < customersList.size(); i++)
    {
        if (customersList[i]->getId() != id)
        {
            newCustomersList.push_back(customersList[i]);
        }
    }
    customersList.clear();
    for(size_t i = 0; i < newCustomersList.size(); i++)
    {
        customersList.push_back(newCustomersList[i]);
    }
    newCustomersList.clear();
    std:: vector<OrderPair> newOrderList;
    for(size_t i = 0; i < orderList.size(); i++)
    {
        if (orderList[i].first != id)
        {
            newOrderList.push_back(orderList[i]);
        }
    }
    salary = 0;
    orderList.clear();
    for(size_t i = 0; i < newOrderList.size(); i++)
    {
        orderList.push_back(newOrderList[i]);
        salary = salary + newOrderList[i].second.getPrice();
    }
    newOrderList.clear();
}

Customer* Trainer:: getCustomer(int id)
{
    for (size_t i = 0; i < customersList.size(); i++)
    {
        if (customersList[i] -> getId() == id)
        {
            return customersList[i];
        }
    }
    return nullptr;
}
std::vector<Customer*>& Trainer:: getCustomers()
{
    return customersList;
}
std::vector<OrderPair>& Trainer:: getOrders()
{
    return orderList;
}
void Trainer:: order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout>& workout_options)
{
    Customer* customer = getCustomer(customer_id);
    std:: vector<int> plan = customer->order(workout_options);
    for (size_t i = 0; i < plan.size(); i++)
    {
        Workout pairR = workout_options[plan[i]];
        OrderPair pair = OrderPair(customer->getId(), pairR);
        orderList.push_back(pair);
        salary = salary + pair.second.getPrice();
    }
}
void Trainer:: openTrainer()
{
    open = true;
}
void Trainer:: closeTrainer()
{
    open = false;
    for(size_t i = 0; i < customersList.size(); i++)
    {
        delete customersList[i];
    }
    customersList.clear();
    orderList.clear();
}
int Trainer:: getSalary()
{
    return salary;
}
bool Trainer:: isOpen()
{
    if (open)
        return true;
    else
        return false;
}
