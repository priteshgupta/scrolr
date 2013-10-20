#include <iostream>

#include "Driver.h"
#include "Game.h"
#include "Poster.h"
#include "archived/SimInput.h"
#include "Tracker.h"

int main(int argc, char* argv[])
{
    Tracker d;
    d.initialize();

    for(int i = 0; i < 1000; i++)
    {
        std::cout << d.track() << std::endl;
    }

    return 0;
}

