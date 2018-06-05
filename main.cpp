#include "calendar.h"

int main()
{
    Calendar c;
    c.printMonthly();
    c.printWeekly();
    c.printSeasonly();
    c.printDecades();



    //TEST CASES

    std::cout<<"\n\t\t\t\t C O N V E R T S\n";

    // 21.09 -> 2.10.3                                  2.10.3 -> 21.5.09
    std::cout<<c.convertToCustom("21.9")<<" = "<<c.convertToDefault("2.10.3")<<std::endl;

    // 27.12 -> 06.01.01                                06.01.01 -> 27.3.12
    std::cout<<c.convertToCustom("27.12")<<" = "<<c.convertToDefault("6.1.1")<<std::endl;

    // 03.01 -> 03.02.1                                 03.02.01 -> 03.3.01
    std::cout<<c.convertToCustom("03.01")<<" = "<<c.convertToDefault("3.2.1")<<std::endl;

    //22.12 -> 01.01.01                                 01.01.01 -> 22.5.12
    std::cout<<c.convertToCustom("22.12")<<" = "<<c.convertToDefault("1.1.1")<<std::endl;

    //23.12 ->02.01.01                                  02.01.01 -> 23.6.12
    std::cout<<c.convertToCustom("23.12")<<" = "<<c.convertToDefault("2.1.1")<<std::endl;

    //21.1 -> 01.04.1                                   01.04.1 -> 21.7.1
    std::cout<<c.convertToCustom("21.1")<<" = "<<c.convertToDefault("1.4.1")<<std::endl;

    //28.02 -> 07.09.1                                   09.07.1  -> 28.3.2
    std::cout<<c.convertToCustom("28.2")<<" = "<<c.convertToDefault("09.07.1")<<std::endl;

    return 0;
}
