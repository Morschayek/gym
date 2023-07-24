//
// Created by spl211 on 08/11/2021.
//
#include "../include/Workout.h"
//constructor
Workout::Workout(int w_id, std::string w_name, int w_price, WorkoutType w_type):
        id(w_id),
        name(std::move(w_name)),
        price(w_price),
        type(w_type)
{
}
int Workout:: getId() const{
    return id;
}
std::string Workout:: getName() const{
    return name;
}
int Workout:: getPrice() const{
    return price;
}
WorkoutType Workout:: getType() const{
    return type;
}
std:: string Workout:: typeToString()
{
    if (getType() == ANAEROBIC)
    {
        return "Anaerobic";
    }
    else
    {
        if (getType() == CARDIO)
        {
            return "Cardio";
        }
        else
            return "Mixed";
    }
}
