#include "calendar.h"

int main()
{
    Calendar c;
    //c.printMonthly();
    //c.printWeekly();
    c.printSeasonly();
    c.printDecades();

    //CONVERTS

    // 22.03 -> 01.01
    c.convertToCustom(31, 3);

    // 05.07 -> 02.04
    c.convertToCustom(5, 7);

    // 08.07 -> 2.7
    c.convertToCustom(8, 7);

    // 21.09 ->
    c.convertToCustom(21, 9);

    // 30.06 ->
    c.convertToCustom(30, 6);

    // 03.01 -> 03.02.01
    c.convertToCustom(3, 1);

    // 27.12 -> 06.01.01
    c.convertToCustom(27, 12);


    //06.01.01 -> 27.3.12
    c.convertToDefault(6,1,1);


    return 0;
}
