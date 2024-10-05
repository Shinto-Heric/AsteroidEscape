// AsteroidEscape.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Game.h"
#include <iostream>

using namespace asteroidescape;
int main()
{
    try
    {
        Game game;
        game.run();
    }
    catch (const std::exception& e) 
    {
        std::cerr << "Exception: " << e.what() << std::endl;
        return EXIT_FAILURE;  // Return failure status
    }
    catch (...)
    {  
        // Catch any other exceptions
        std::cerr << "An unknown error occurred!" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;  // Return success status if everything goes well
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
