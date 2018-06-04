#include "calendar.h"

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

        if(next<seasons[i].getSeasonsNames().size() && (seasons[i].getDays().size()<seasons[i].decadeDuration || (seasons[i].getSeasonsNames()[next]=="Spring" && counter==seasons[i].decadeDuration)))
        {
            printSHeadline(next++);
            counter =1;
        }
    }
    std::cout<<std::endl;
}

void Calendar::convertToDefault(int day, int dec, int tSeasone)
{
    int counter=0, sCounter=1;
    int month =0, dayOfWeek=4;
    int dDay=0;

    for(int i=0; i<seasons.size();++i)
    {
        for(int j=0; j<seasons[i].getDays().size();++j)
        {
            if(i==shiftToSeasone1 || i==shiftToSeasone2 || shiftToSeasone3)
            {
                sCounter++;
            }

            counter++;
            dayOfWeek++;

            if(counter==year[month].size())
            {
                month++;
                counter=0;
            }

            if(dayOfWeek>week.size())
            {
                dayOfWeek=1;
            }

        }
        if(sCounter == tSeasone)
        {
            break;
        }
    }
    std::cout<<"\n\t\t\t C O N V E R T  T O  D E F A U L T";
    std::cout<<"\n"<<dDay<<"."<<dayOfWeek<<"."<<month<<std::endl;
}

void Calendar::convertToCustom(int day, int month)
{
    int count = 0, dec = 1;
    int start = 0;
    int tSeasone = WhatIsSeasone(day, month);
    switch (tSeasone)
    {
    case 2:
        start = 3;
        break;
    case 3:
        start = 6;
        break;
    case 4:
        start = 9;
        break;
    default:
        start =12;
        break;
    }

    if(start ==12)
    {
        if(month!=12)
        {
            start =0;
        }
    }

    for(int i = month; i>=start; --i)
    {
        if(i==start)
        {
            count+=(day-firstDayOfSeasone+1);
        }
        else
        {
            count+= day;
        }

        dec+= count/10;
        count=count%10;

        if(start ==0 && i==1)
        {
            day = year[11].size();
        }
        else
        {
            day=year[i-2].size();
        }
    }
    if(count==0) count=10;
    std::cout<<"\n\t\t\t C O N V E R T  T O  C U S T O M";
    std::cout<<"\n"<<count<<"."<<dec<<"."<<tSeasone<<std::endl;
}

void Calendar::printSHeadline(int next)
{
    std::cout<<"\n*********************************************************\n";
    std::cout<<"\t\t\t"<<seasons[0].getSeasonsNames()[next]<<"\n";
}

int Calendar::WhatIsSeasone(int day, int month)
{
    switch (month)
    {
    case 3:
        if(day>=firstDayOfSeasone) return 2;
        else return 1;
    case 4:
        return 2;
    case 5:
        return 2;
    case 6:
        if(day>=firstDayOfSeasone) return 3;
        else return 2;
    case 7:
        return 3;
    case 8:
        return 3;
    case 9:
        if(day>=firstDayOfSeasone) return 4;
        else return 3;
    case 10:
        return 4;
    case 11:
        return 4;
    case 12:
        if(day>=firstDayOfSeasone) return 1;
        else return 4;
    default:
        return 1;
    }
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
