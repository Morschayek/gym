//
// Created by spl211 on 08/11/2021.
//
#include "../include/Studio.h"
#include "../include/Action.h"


//empty constructor
Studio:: Studio():
    open(false),
    trainers(),
    workout_options(),
    actionsLog()
{

}
//constructor with configFile
//open 2 Shalom,swt Dan,chp Alice,mcl Bob,fbd
Studio:: Studio(const std::string &configFilePath)
{
    Studio studio = Studio();
    int wo_id = 0;
    int counter = 0;
    std:: ifstream inFile(configFilePath);
    if (inFile.is_open())
    {
        std::string line;
        while(std:: getline(inFile,line))
        {
            if (line[0] == '#')
            {
                continue;
            }
            if (line[0] == '\0')
            {
                continue;
            }
            if (counter == 0)
            {
                counter++;
                continue;
            }
            if (counter == 1)
            {
                int len = 0;
                int from = 0;
                int i = 0;

                std::string str(line);
                while (str[i] != '\0')
                {
                    if (str[i] != ',')
                    {
                        i++;
                        len++;
                    }
                    else
                    {
                        Trainer *t = new Trainer(stoi(str.substr(from, len)));
                        trainers.push_back(t);
                        i++;
                        from = i;
                        len = 0;
                    }
                }
                Trainer *t = new Trainer(stoi(str.substr(from, len)));
                trainers.push_back(t);
                counter++;
                continue;
            }
            if (counter > 1)
            {
                int len1 = 0;
                int from1 = 0;
                int j = 0;
                std::string str1(line);
                while (str1[j] != ',')
                {
                    j++;
                    len1++;
                }
                std:: string wo_name = str1.substr(from1, len1);
                j++;
                from1 = j;
                len1 = 0;
                while (str1[j] != ',')
                {
                    j++;
                    len1++;
                }
                while(str1[from1] == ' ')
                {
                    from1++;
                }
                std:: string wo_type_str = str1.substr(from1, len1-1);
                WorkoutType wo_type;
                if(wo_type_str == "Anaerobic")
                {
                    wo_type = ANAEROBIC;
                }
                if(wo_type_str == "Mixed")
                {
                    wo_type = MIXED;
                }
                if(wo_type_str == "Cardio")
                {
                    wo_type = CARDIO;
                }
                j++;
                from1 = j;
                len1 = 0;
                while (str1[j] != '\0')
                {
                    j++;
                    len1++;
                }
                while(str1[from1] == ' ')
                {
                    from1++;
                }
                int wo_price = stoi(str1.substr(from1, len1));
                workout_options.push_back(Workout(wo_id, wo_name, wo_price, wo_type));
                wo_id++;
                counter++;
            }
        }
        inFile.close();
    }

}
//copy constructor
Studio:: Studio(Studio &other):
        open(other.open),
        workout_options(other.workout_options)
{
    for (size_t i=0;i<other.trainers.size();i++){
        Trainer* t=new Trainer(*(other.trainers[i])) ;
        trainers.push_back(t);
    }
    for (size_t i = 0; i < other.actionsLog.size(); i++) {
        this->actionsLog.push_back(other.actionsLog[i]->clone());
    }
}
//destructor
Studio:: ~Studio()
{
    clear();
}

void Studio::clear()
{
    for (size_t i = 0; i < trainers.size(); i++)
    {
        delete trainers[i];
    }
    trainers.clear();
    workout_options.clear();
    for (size_t i = 0; i < actionsLog.size(); i++)
    {
        delete actionsLog[i];
    }
    actionsLog.clear();
}
//move constructor
Studio:: Studio(Studio&& other):
        open(other.open),
        trainers(other.trainers),
        workout_options(other.workout_options),
        actionsLog(other.actionsLog)
{
    other.trainers.clear();
    other.workout_options.clear();
    other.actionsLog.clear();
}
//copy assignment
Studio& Studio:: operator=(const Studio &aStudio)
{
    if (this != &aStudio)
    {
        this->clear();
        this->open = aStudio.open;
        this->workout_options = std::vector<Workout> (aStudio.workout_options);
        for(size_t i = 0; i < aStudio.trainers.size(); i++)
        {
            this->trainers.push_back(new Trainer(*aStudio.trainers[i]));
        }
        for(size_t i = 0; i < aStudio.actionsLog.size(); i++)
        {
            this->actionsLog.push_back(aStudio.actionsLog[i]->clone());
        }
    }
    return *this;
}
//move assignment
Studio& Studio:: operator=(Studio&& other)
{
    if (this != &other) {
        this->clear();
        open = other.open;
        trainers = other.trainers;
        workout_options.clear();
        for (size_t i = 0; i < other.workout_options.size(); i++) {
            workout_options.push_back(other.workout_options[i]);
        }
        actionsLog = other.actionsLog;
        other.actionsLog.clear();
        other.trainers.clear();
        other.workout_options.clear();
        other.open = false;
    }
    return *this;
}
//start
//open 2 Shalom,swt Dan,chp Alice,mcl Bob,fbd
//open 3 Alice,chp Bob,mcl
void Studio::start()
{
    open = true;
    std::cout << "Studio is now open!" << std::endl;
    int customerId = 0;
    while (open)
    {
        std::string input = "";
        getline(std::cin, input);
        std:: vector<Customer*> cL;
        std:: string sub_op_mo = input.substr(0,4);
        std:: string sub_cl_or = input.substr(0,5);
        std:: string sub_st = input.substr(0,6);
        std:: string sub_CA = input.substr(0,8);
        if (sub_op_mo == "open")
        {
            int from = 5;
            int len = 0;
            while (input[from+len] != ' ')
            {
                len++;
            }
            //open 2
            int trainerId = std:: stoi(input.substr(from, len));
            Trainer *t = getTrainer(trainerId);
            int capacity = t->getCapacity();
            from = from + len + 1;
            len = 0;
            std::vector<std::string> cusName;
            std::vector<std::string> cusType;
            std:: vector<Customer*> customersList;
            while(input[from + len] != '\0')
            {
                while ((input[from + len] != ',') && (input[from + len] != '\0'))
                {
                    if (input[from + len] == ' ')
                    from++;
                    len++;
                }
                cusName.push_back(input.substr(from, len));
                from = from + len + 1;
                len = 0;
                while ((input[from + len] != ' ') && (input[from + len] != '\0'))
                {
                    len++;
                }
                cusType.push_back(input.substr(from, len));
                from = from + len;
                len = 0;
            }
            int j = 0;
            for (size_t i = 0; i < cusName.size(); i++)
            {
                if (j < capacity)
                {
                    if (cusType[i] == "swt")
                    {
                        SweatyCustomer *swt = new SweatyCustomer(cusName[i], customerId);
                        customersList.push_back(swt);
                    }
                    if (cusType[i] == "chp")
                    {
                        CheapCustomer *chp = new CheapCustomer(cusName[i], customerId);
                        customersList.push_back(chp);
                    }
                    if (cusType[i] == "mcl")
                    {
                        HeavyMuscleCustomer *mcl = new HeavyMuscleCustomer(cusName[i], customerId);
                        customersList.push_back(mcl);
                    }
                    if (cusType[i] == "fbd")
                    {
                        FullBodyCustomer *fbd = new FullBodyCustomer(cusName[i], customerId);
                        customersList.push_back(fbd);
                    }
                    customerId++;
                    j++;
                }

            }
            OpenTrainer* openTrainerAction = new OpenTrainer(trainerId, customersList);
            openTrainerAction->act(*this);
            actionsLog.push_back(openTrainerAction);
            from = 0;
            len = 0;
        }
        else if(sub_op_mo == "move")
        {
            int from = 5;
            int len = 0;
            while (input[from+len] != ' ')
            {
                len++;
            }
            int srcTrainerId = std:: stoi(input.substr(from, len));
            from = from + len + 1;
            len = 0;
            while (input[from+len] != ' ')
            {
                len++;
            }
            int dstTrainerId = std:: stoi(input.substr(from, len));
            from = from + len + 1;
            len = 0;
            while ((input[from+len] != ' ') && (input[from+len] != '\0'))
            {
                len++;
            }
            int moveCustomerId = std:: stoi(input.substr(from, len));
            MoveCustomer* moveCustomerAction = new MoveCustomer(srcTrainerId, dstTrainerId, moveCustomerId);
            moveCustomerAction->act(*this);
            actionsLog.push_back(moveCustomerAction);
            from = 0;
            len = 0;
        }
        else if(sub_cl_or == "order")
        {
            int from = 6;
            int len = 0;
            while ((input[from+len] != ' ') && (input[from + len] != '\0'))
            {
                len++;
            }
            int trainerOrderId = std:: stoi(input.substr(from, len));
            Order* orderAction = new Order(trainerOrderId);
            orderAction->act(*this);
            actionsLog.push_back(orderAction);
        }
        else if (sub_CA == "closeall")
        {
            CloseAll* closeAllAction = new CloseAll();
            closeAllAction->act(*this);
            actionsLog.push_back(closeAllAction);
            open = false;
            return;
        }
        else if(sub_cl_or == "close")
        {
            int from = 6;
            int len = 0;
            while ((input[from+len] != ' ') && (input[from + len] != '\0'))
            {
                len++;
            }
            int trainerCloseId = std:: stoi(input.substr(from, len));
            Close* closeAction = new Close(trainerCloseId);
            closeAction->act(*this);
            actionsLog.push_back(closeAction);
            from = 0;
            len = 0;
        }
        else if (sub_st == "status")
        {
            int from = 7;
            int len = 0;
            while ((input[from+len] != ' ') && (input[from + len] != '\0'))
            {
                len++;
            }
            int trainerStatusId = std:: stoi(input.substr(from, len));
            PrintTrainerStatus* printTrainerStatusAction = new PrintTrainerStatus(trainerStatusId);
            printTrainerStatusAction->act(*this);
            actionsLog.push_back(printTrainerStatusAction);
            from = 0;
            len = 0;
        }
        else if (input == "workout_options")
        {
            PrintWorkoutOptions* printWorkoutOptionsAction = new PrintWorkoutOptions();
            printWorkoutOptionsAction->act(*this);
            actionsLog.push_back(printWorkoutOptionsAction);
        }
        else if (input == "log")
        {
            PrintActionsLog* printActionsLogAction = new PrintActionsLog();
            printActionsLogAction->act(*this);
            actionsLog.push_back(printActionsLogAction);
        }
        else if (input == "backup")
        {
            BackupStudio* backupStudioAction = new BackupStudio();
            backupStudioAction->act(*this);
            actionsLog.push_back(backupStudioAction);
        }
        else if (input == "restore")
        {
            RestoreStudio* restoreStudioAction = new RestoreStudio();
            restoreStudioAction->act(*this);
            actionsLog.push_back(restoreStudioAction);
        }
    }
}

int Studio:: getNumOfTrainers() const
{
    return trainers.size();
}
Trainer* Studio::getTrainer(int tid)
{
    if (tid >= getNumOfTrainers())
        return nullptr;
    else
        return trainers[tid];
}
// Return a reference to the history of actions
const std::vector<BaseAction*>& Studio:: getActionsLog() const
{
    return actionsLog;
}
std::vector<Workout>& Studio:: getWorkoutOptions()
{
    return workout_options;
}
std::vector<Trainer*> Studio:: getTrainers()
{
    return trainers;
}
