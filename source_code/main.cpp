/**
 * @file main.cpp
 * @brief This file contains the main function of the project.
 *
 * \mainpage Description
 * This project consists in a set of classes and functions that allow the user to interact with a simple Air Travel Flight system.
 * With this simple system, you can access information about the airports, airlines and flights. You can also find the best options to your flight (with less stops)
 *
 * \subsection Instructions How to use
 * You will be asked to choose an option. All the options will appear on the screen with a number near them.
 * Then, just type the number corresponding to the option you want to execute.
 */
#include <iostream>
#include "AirTravelManSys.h"
#include "UI.h"

int main() {

    UI userInterface;
    while(true) {
        int s = userInterface.mainMenu();
        if (s == 1) {
            //error during the execution;
            return 1;
        }
        else if(s == 2){
            //exit signal
            break;
        }
    }
    return 0;
}
