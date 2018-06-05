#ifndef CALENDAR_H
#define CALENDAR_H

#include <vector>
#include <iostream>
#include <string>



class Month
{
public:
    Month(std::string _name, unsigned short _duration): name(_name), duration(_duration){}

    std::string getName()
    {
        return name;
    }

    unsigned short getDuration()
    {
        return duration;
    }

private:
    std::string name;
    unsigned short duration;
};

//Decade class
class Decade
{

public:
    Decade()
    {
        days = {1,2,3,4,5,6,7,8,9,10};
    }

    Decade(int first)
    {
        days.push_back(first);
    }

    Decade(int first, int second)
    {
        days.push_back(first);
        days.push_back(second);
    }

    const std::vector<int> getDays(){return days;}

    static const std::vector<std::string> seasonsNames;
    static const int decadeDuration = 10;

private:
    std::vector<int> days;
};



class Calendar
{
public:
    Calendar();
    void printMonthly();
    void printWeekly();
    void printDecades();
    void printSeasonly();
    std::string convertToCustom(std::string s);
    std::string convertToDefault(std::string s);

private:
    const int MonthDuration31 = 31;
    const int MonthDuration30 = 30;
    const int MonthDuration28 = 28;

    const int maxOfDecades = 39;
    const int shiftToSeasone1 = 29;
    const int shiftToSeasone2 = 19;
    const int shiftToSeasone3 = 9;
    const int firstDayOfSeasone = 22;
    const int lastDayOfSeasone = 21;

    static const int decNum = 11; //December's number in the Calendar. Need for 2 functions.


    std::vector<Decade> seasons;
    std::vector<std::string> week;
    std::vector<Month> months;
    std::vector<std::vector<unsigned short>> year;

    void printMHeadline(int i, int counter);
    void printWHeadline(int next);
    void printSHeadline(int next);
    int WhatIsSeasone(int day, int month);
    std::vector<int> Parse(std::string s);
};

#endif // CALENDAR_H
