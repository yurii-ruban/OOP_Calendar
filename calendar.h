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

    const int decadeDuration = 10;
    const std::vector<int> getDays(){return days;}
    const std::vector<std::string> getSeasonsNames(){return seasonsNames;}

private:
   std::vector<int> days;
   const std::vector<std::string> seasonsNames = {"Winter", "Spring", "Summer", "Autumn"};
};

class Calendar
{
public:
    Calendar();
    void printMonthly();
    void printWeekly();
    void printDecades();
    void printSeasonly();
    void convertToCustom(int fst, int month);

private:
    const int MonthDuration31 = 31;
    const int MonthDuration30 = 30;
    const int MonthDuration28 = 28;
    const int maxOfDecades = 39;
    const int shiftToSeasone1 = 29;
    const int shiftToSeasone2 = 19;


    std::vector<Decade> seasons;
    std::vector<std::string> week;
    std::vector<Month> months;
    std::vector<std::vector<unsigned short>> year;

    void printMHeadline(int i, int counter);
    void printWHeadline(int next);
    void printSHeadline(int next);
    int WhatIsSeasone(int day, int month);
};

#endif // CALENDAR_H
