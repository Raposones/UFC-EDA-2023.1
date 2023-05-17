#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct Date
{
    int day;
    int month;
    int year;
};

struct Person
{
    string name;
    string natID;
    Date birthday;
    string city;

    Person(string name, string natID, Date birthday, string city)
    {
        this->name = name;
        this->natID = natID;
        this->birthday = birthday;
        this->city = city;
    }
};

Date str_to_date(string date_str)
{
    istringstream ss(date_str);
    string part;
    int month, day, year;
    getline(ss, part, '/');
    month = stoi(part);
    getline(ss, part, '/');
    day = stoi(part);
    getline(ss, part, '/');
    year = stoi(part);

    Date date = {month, day, year};
    return date;
}

string date_to_str(Date date)
{
    return to_string(date.day) + "/" + to_string(date.month) + "/" + to_string(date.year);
}

#endif