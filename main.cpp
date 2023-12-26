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
