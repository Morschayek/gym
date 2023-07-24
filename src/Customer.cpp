//
// Created by spl211 on 08/11/2021.
//
# include "../include/Customer.h"


//Customer
Customer:: Customer(std::string c_name, int c_id):
        name(c_name),
        id(c_id)
{

}
std::string Customer:: getName() const
{
    return name;
}
int Customer:: getId() const
{
    return id;
}

//Sweaty Customer - swt
SweatyCustomer:: SweatyCustomer(std::string name, int id):
        Customer(name, id)
{

}
SweatyCustomer:: ~SweatyCustomer() = default;

std::vector<int> SweatyCustomer:: order(const std::vector<Workout> &workout_options)
{
    std:: vector <int> swt_plan;
    for (size_t i = 0; i < workout_options.size(); i++)
    {
        if (workout_options[i].getType() == CARDIO)
        {
            swt_plan.push_back(workout_options[i].getId());
        }
    }
    return swt_plan;
}
std::string SweatyCustomer:: toString() const
{
    std:: string toStr = "";
    toStr.append(std::to_string(getId()));
    toStr.append(" ");
    toStr.append(getName());
    return toStr;
}
std:: string SweatyCustomer:: typeToString()
{
    return "swt";
}

//Cheap Customer - CHP
CheapCustomer:: CheapCustomer(std::string name, int id):
        Customer(name, id)
{

}
CheapCustomer:: ~CheapCustomer() = default;

std::vector<int> CheapCustomer:: order(const std::vector<Workout> &workout_options)
{
    std:: vector <int> chp_plan;
    chp_plan.push_back(workout_options[0].getId());
    int minPrice = workout_options[0].getPrice();
    for (size_t i = 1; i < workout_options.size(); i++)
    {
        if ( (workout_options[i].getPrice() < minPrice) ||
             ((workout_options[i].getPrice() == minPrice) && (workout_options[i].getId() < chp_plan[0])) )
        {
            chp_plan[0] = workout_options[i].getId();
            minPrice = workout_options[i].getPrice();
        }
    }
    return chp_plan;
}
std::string CheapCustomer:: toString() const
{
    std:: string toStr = "";
    toStr.append(std::to_string(getId()));
    toStr.append(" ");
    toStr.append(getName());
    return toStr;
}
std:: string CheapCustomer:: typeToString()
{
    return "chp";
}

//HeavyMuscle Customer - MCL
HeavyMuscleCustomer:: HeavyMuscleCustomer(std::string name, int id):
    Customer(name, id)
{

}
HeavyMuscleCustomer:: ~HeavyMuscleCustomer() = default;

std::vector<int> HeavyMuscleCustomer:: order(const std::vector<Workout> &workout_options)
{
    std:: vector <int> mcl_plan;
    std:: vector<std::pair<int,int>> mclPairPlan;
    for (size_t i = 0; i < workout_options.size(); i++)
    {
        if (workout_options[i].getType() == ANAEROBIC)
        {
            std::pair<int,int> pair(workout_options[i].getPrice(), workout_options[i].getId());
            mclPairPlan.push_back(pair);
        }
    }
    std::sort(mclPairPlan.begin(), mclPairPlan.end(), mclComparator);//now the mclPairPlan vector is sorted
    for (size_t i = 0; i < mclPairPlan.size(); i++)
    {
        mcl_plan.push_back(mclPairPlan[i].second);
    }
    return mcl_plan;
}
bool mclComparator(std::pair<int, int> &pair1,std::pair<int, int> &pair2)
{
    if (pair1.first != pair2.first)
    {
        return pair1.first > pair2.first;
    }
    else
    {
        return pair1.second < pair2.second;
    }
}
std::string HeavyMuscleCustomer:: toString() const
{
    std:: string toStr = "";
    toStr.append(std::to_string(getId()));
    toStr.append(" ");
    toStr.append(getName());
    return toStr;
}
std:: string HeavyMuscleCustomer:: typeToString()
{
    return "mcl";
}

//Full Body Customer - FBD
FullBodyCustomer:: FullBodyCustomer(std::string name, int id):
        Customer(name, id)
{

}
FullBodyCustomer:: ~FullBodyCustomer() = default;

std::vector<int> FullBodyCustomer:: order(const std::vector<Workout> &workout_options)
//cheapest cardio --> most expensive mix --> cheapest anaerobic
{
    std:: vector <Workout> cardio_v;
    std:: vector <Workout> mixed_v;
    std:: vector <Workout> anaerobic_v;
    std:: vector <int> fbd_plan;
    for (size_t i = 0; i < workout_options.size(); i++)
    {
        if (workout_options[i].getType() == ANAEROBIC)
        {
            anaerobic_v.push_back(workout_options[i]);
        }
        else if (workout_options[i].getType() == CARDIO)
        {
            cardio_v.push_back(workout_options[i]);
        }
        else
        {
            mixed_v.push_back(workout_options[i]);
        }
    }

    //pushing the cheapest cardio
    int minPriceC = cardio_v[0].getPrice();
    int IDC = cardio_v[0].getId();
    for (size_t i = 1; i < cardio_v.size(); i++)
    {
        if ( (cardio_v[i].getPrice() < minPriceC) ||
             ((cardio_v[i].getPrice() == minPriceC) && (cardio_v[i].getId() < IDC)) )
        {
            minPriceC = cardio_v[i].getPrice();
            IDC = cardio_v[i].getId();
        }
    }
    fbd_plan.push_back(IDC);

    //pushing the most expensive mixed
    int maxPriceM = mixed_v[0].getPrice();
    int IDM = mixed_v[0].getId();
    for (size_t i = 1; i < mixed_v.size(); i++)
    {
        if ( (mixed_v[i].getPrice() > maxPriceM) ||
             ((mixed_v[i].getPrice() == maxPriceM) && (mixed_v[i].getId() < IDM)) )
        {
            maxPriceM = mixed_v[i].getPrice();
            IDM = mixed_v[i].getId();
        }
    }
    fbd_plan.push_back(IDM);

    //pushing the cheapest anaerobic
    int minPriceA = anaerobic_v[0].getPrice();
    int IDA = anaerobic_v[0].getId();
    for (size_t i = 1; i < anaerobic_v.size(); i++)
    {
        if ( (anaerobic_v[i].getPrice() < minPriceA) ||
             ((anaerobic_v[i].getPrice() == minPriceA) && (anaerobic_v[i].getId() < IDA)) )
        {
            minPriceA = anaerobic_v[i].getPrice();
            IDA = anaerobic_v[i].getId();
        }
    }
    fbd_plan.push_back(IDA);
    return fbd_plan;
}
std::string FullBodyCustomer:: toString() const
{
    std:: string toStr = "";
    toStr.append(std::to_string(getId()));
    toStr.append(" ");
    toStr.append(getName());
    return toStr;
}
std:: string FullBodyCustomer:: typeToString()
{
    return "fbd";
}
