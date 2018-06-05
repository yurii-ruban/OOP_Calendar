#include "calendar.h"


const std::vector<std::string> Decade::seasonsNames = {"Winter", "Spring", "Summer", "Autumn"};

Calendar::Calendar()
{
    week.push_back("Mon");
    week.push_back("Tue");
    week.push_back("Wed");
    week.push_back("Thu");
    week.push_back("Fri");
    week.push_back("Sat");
    week.push_back("Sun");

    months.push_back(Month("January", MonthDuration31));
    months.push_back(Month("February", MonthDuration28));
    months.push_back(Month("March", MonthDuration31));
    months.push_back(Month("April", MonthDuration30));
    months.push_back(Month("May", MonthDuration31));
    months.push_back(Month("June", MonthDuration30));
    months.push_back(Month("July", MonthDuration31));
    months.push_back(Month("August", MonthDuration31));
    months.push_back(Month("September", MonthDuration30));
    months.push_back(Month("October", MonthDuration31));
    months.push_back(Month("November", MonthDuration30));
    months.push_back(Month("December", MonthDuration31));
    year.reserve(months.size());

    //FILLING THE CALENDAR
    for (int i=0; i<months.size(); ++i)
    {
        std::vector<unsigned short> temp(months[i].getDuration());
        for(int j=0;j<months[i].getDuration();++j)
        {
            temp[j]=j+1;
        }
        year.push_back(temp);
    }

    //Filling decade clendar
    for(int i=1; i<=maxOfDecades; ++i)
    {
        if(i==shiftToSeasone1 || i==shiftToSeasone2)
        {
            seasons.push_back(Decade(1,2));
        }
        else if(i == maxOfDecades)
        {
            seasons.push_back(Decade(1));
        }
        else
        {
            seasons.push_back(Decade());
        }
    }
}

void Calendar::printMonthly()
{
    int counter=0;
    for(int i=0;i<months.size();++i)
    {
        printMHeadline(i, counter);
        for (int j=0; j <months[i].getDuration(); j++)
        {
            if(counter!=week.size())
            {
                std::cout<<year[i][j]<<"\t";
                counter++;
            }
            else
            {
                std::cout<<"\n"<<year[i][j]<<"\t";
                counter=1;
            }
        }
    }
    std::cout<<"\n*********************************************************\n";
}

void Calendar::printWeekly()
{
    int counter=0, next=1;
    printWHeadline(next);
    for (int i=0; i<months.size(); i++)
    {
        for (int j=0; j < months[i].getDuration(); j++)
        {
            if(counter!=week.size())
            {
                std::cout<<"\t"<<year[i][j]<<"."<<i+1;
                counter++;
            }
            else
            {
                std::cout<<"\nWeek "<<++next<<":";
                if(i>=2) std::cout<<"\t"<<year[i][j]<<"."<<i+1;
                else std::cout<<"\t\t"<<year[i][j]<<"."<<i+1;
                counter=1;
            }
        }
    }
    std::cout<<std::endl;
}

void Calendar::printDecades()
{
    int counter =1;

    std::cout<<"\n\t\t\t\t D E C A D E S"<<"\n\t";
    for(int i=0;i<seasons.size();++i)
    {
        std::cout<<"\nDec"<<counter++<<":\t";
        for(int j= 0; j<seasons[i].getDays().size();++j)
        {
            std::cout<<" "<<seasons[i].getDays()[j];
        }
    }
    std::cout<<std::endl;
}

void Calendar::printSeasonly()
{
    int next =0;
    int counter =1;
    printSHeadline(next++);
    for(int i=0;i<seasons.size();++i)
    {
        std::cout<<"\nDec"<<counter++<<":\t";

        for(int j=0; j<seasons[i].getDays().size(); ++j)
        {
            std::cout<<" "<<seasons[i].getDays()[j];
        }

        if(next<Decade::seasonsNames.size() && (seasons[i].getDays().size()<seasons[i].decadeDuration || (Decade::seasonsNames[next]=="Spring" && counter==seasons[i].decadeDuration)))
        {
            printSHeadline(next++);
            counter =1;
        }
    }
    std::cout<<std::endl;
}

std::string Calendar::convertToDefault(std::string s)
{
    int counter=0, sCounter=1, dCounter=1;//I need this vars that give me an exit from a loop

    //this means that our callendar will calculate from start point of my Calendar
    int month =11;
    int dDay=21;
    int dayOfWeek=4;


    bool flag = false;//I use this for exit from double loop

    //Parse input data
    std::vector<int> temp = Parse(s);
    int day = temp[0];
    int dec = temp[1];
    int tSeasone = temp[2];


    for(int i=0; i<seasons.size();++i)
    {
        if(i==shiftToSeasone1 || i==shiftToSeasone2 || i==shiftToSeasone3) //Check to change seasone
        {
            sCounter++;
            dCounter=1;
        }

        for(int j=0; j<seasons[i].getDays().size();++j) //Just go on a decades and count our vars
        {
            counter++;
            dayOfWeek++;
            dDay++;

            if(dDay>year[month].size())
            {
                if(month == decNum)//It means that i need go back to January or forward from current month
                {
                    month = 0;
                    dDay=1;
                }
                else
                {
                    month++;
                    dDay=1;
                }
            }

            if(dayOfWeek>week.size()) //Counting a day in a week
            {
                dayOfWeek=1;
            }

            if(sCounter == tSeasone && dCounter==dec && counter==day)//Condition for exit from a loop
            {
                flag= true;
                break;
            }
        }
        if(flag)
        {
            break;
        }
        dCounter++;
        counter=0;
    }

    return std::to_string(dDay)+"."+std::to_string(dayOfWeek)+"."+std::to_string(++month);
}

std::string Calendar::convertToCustom(std::string s)
{
    const int startSeasone1 = 12;
    const int startSeasone2 = 3;
    const int startSeasone3 = 6;
    const int startSeasone4 = 9;

    int count = 0, dec = 1;//I need this vars for count number of decade and day

    int start = 0;//It helps me to realise the Point where should i go

    //Parse input data
    std::vector<int> temp = Parse(s);
    int day = temp[0];
    int month = temp[1];

    int tSeasone = WhatIsSeasone(day, month);
    switch (tSeasone)
    {
    case 2:
        start = startSeasone2;
        break;
    case 3:
        start = startSeasone3;
        break;
    case 4:
        start = startSeasone4;
        break;
    default:
        start = startSeasone1;
        break;
    }

    //Check and give start point =0 if there's December. It makes me easier to go in array
    if(start == startSeasone1)
    {
        if(month!=months.size())
        {
            start =0;
        }
    }

    for(int i = month; i>=start; --i)
    {
        if(i==start)
        {
            count+=(day-firstDayOfSeasone+1); //Numbers between start point of seasone and our day in this month
        }
        else
        {
            count+= day;
        }

        dec+= count/Decade::decadeDuration; //Number of decades
        count=count%Decade::decadeDuration; //Number of days in decades

        if(start == 0 && i==1) //If we have a new month then we need to use it size
        {
            day = year[decNum].size();
        }
        else
        {
            day=year[i-2].size();
        }
    }

    //Mod 10 sometimes can give 0. It means that a decade has exactly 10 days
    if(count==0)
    {
        count = Decade::decadeDuration;
    }

    return std::to_string(count)+"."+std::to_string(dec)+"."+std::to_string(tSeasone);
}

void Calendar::printSHeadline(int next)
{
    std::cout<<"\n*********************************************************\n";
    std::cout<<"\t\t\t"<<Decade::seasonsNames[next]<<"\n";
}

int Calendar::WhatIsSeasone(int day, int month)
{
    enum season {Winter=1, Spring, Summer, Autumn} s;
    switch (month)
    {
    case 3:
        return day>=firstDayOfSeasone?Spring:Winter;
    case 4:
        return Spring;
    case 5:
        return Spring;
    case 6:
        return day>=firstDayOfSeasone?Summer:Spring;
    case 7:
        return Summer;
    case 8:
        return Summer;
    case 9:
        return day>=firstDayOfSeasone?Autumn:Summer;
    case 10:
        return Autumn;
    case 11:
        return Autumn;
    case 12:
        return day>=firstDayOfSeasone?Winter:Autumn;
    default:
        return Winter;
    }
}

std::vector<int> Calendar::Parse(std::string s)
{
    std::vector<int> line;
    std::string delimiter = ".";
    size_t pos = 0;
    std::string token;

    while ((pos = s.find(delimiter)) != std::string::npos)
    {
        token = s.substr(0, pos);
        if(token[0]=='0')
        {
            token.erase(0,1);
        }

        line.push_back(stoi(token));
        s.erase(0, pos + delimiter.length());
    }

    token = s.substr(0, pos);
    if(token[0]=='0')
    {
        token.erase(0,1);
    }
    line.push_back(stoi(token));

    return line;
}

void Calendar::printWHeadline(int next)
{
    std::cout<<"\n\t\t\t\t W E E K S"<<"\n\t";
    for(int j=0;j<week.size();j++)
    {
        std::cout<<"\t"<<week[j];
    }

    std::cout<<"\nWeek "<<next<<":\t";
}

void Calendar::printMHeadline(int i, int counter)
{
    std::cout<<"\n*********************************************************\n";
    std::cout<<"\t\t\t"<<months[i].getName()<<"\n";

    for(int j=0;j<week.size();j++)
    {
        std::cout<<week[j]<<"\t";
    }
    std::cout<<std::endl;

    for(int i=0;i<counter;++i)
    {
        std::cout<<"\t";
    }
}
