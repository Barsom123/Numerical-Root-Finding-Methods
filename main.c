#include "functions.h"
#include <stdlib.h> // for system() function
#include <stdio.h>

/*
Use this command to run the code or include "tinyexpr.c" && functions.c directly:
>> gcc main.c tinyexpr.c functions.c -o main.exe; ./main.exe

Note: "Running the code and testing it using the main.exe file is better than using the terminal."
*/

int main()
{
    // variable to store the method number
    // 1 for Bisection Method, 2 for False Position Method, 3 for Secant Method, 4 for Newton Raphson Method
    double BFSN, error = -1.0;
    do
    {
        //  clear screen
        // system("clear"); // for Linux and MacOS
        system("cls"); // for Windows
        printf("Welcome to the Root Finding Program!\n");
        printf("This program finds the root of a function using various methods.\n");
        do
        {
            get_number(
                "\t1- Bisection Method\n"
                "\t2- False Position Method\n"
                "\t3- Secant Method\n"
                "\t4- Newton Raphson Method\n"
                "\t5- exit program\n"
                "Select method {1, 2, 3, 4, 5}: ",
                &BFSN);
            if ((int)BFSN < 1 || (int)BFSN > 5)
            {
                system("cls"); // for Windows
                printf("Invalid method selected. Please try again. enter valid number (1, 2, 3, 4, 5)\n");
                continue;
            }
            break;
        } while (1);
        // get error tolerance from user
        // if error is -1.0, skip error calculation
        ((int)BFSN != 5) ? get_number("Enter the error tolerance (e.g., 0.001), or -1.0 to skip error calculation: ", &error) : 0;
        switch ((int)BFSN)
        {
        case 1:
            printf("This program finds the root of a function using the Bisection Method.\n");
            bisection_and_false_position(BFSN, error);
            continue_prompt();
            break;
        case 2:
            printf("This program finds the root of a function using the False Position Method.\n");
            bisection_and_false_position(BFSN, error);
            continue_prompt();
            break;
        case 3:
            printf("This program finds the root of a function using the Secant Method.\n");
            Secant_Method(error);
            continue_prompt();
            break;
        case 4:
            printf("This program finds the root of a function using the Newton Raphson Method.\n");
            Newton_Raphson_Method(error);
            continue_prompt();
            break;
        case 5:
            printf("Exiting program...\n");
            return 0;
        default:
            printf("Invalid method selected.\n");
        }
    } while (1);
    return 0;
}
