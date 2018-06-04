#include "calendar.h"

int main()
{
    Calendar c;
    //c.printMonthly();
    //c.printWeekly();
    c.printSeasonly();
    c.printDecades();
    std::cout<<"\n \t\t\t\tT E S T  C O N V E R T E R\n";
    std::cout<<"22.03";
    c.convertToCustom(22,3);

//    std::cout<<"07.03";
//    c.convertToCustom(7,3);

    std::cout<<"21.06";
    c.convertToCustom(21,6);

    std::cout<<"22.06";
    c.convertToCustom(22,6);

    std::cout<<"22.09";
    c.convertToCustom(22,9);
    return 0;
}
