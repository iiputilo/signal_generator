#include <iostream>
#include <graphics_drawer.h>
#include <signal_generator.h>

int main() {
    std::cout << "Choose the option:\n1. Generate signal\n2. Show graphics\n3. Exit program\n\nYour choice-> ";

    int userChoice;
    std::cin >> userChoice;
    std::cout << "\n\n\n";

    switch (userChoice) {
        case 1: {
            if (generate()) {
                std::cout << "Signal generated successfully.\n";
            } else {
                std::cerr << "Error generating signal.\n";
            }
            break;
        }
        case 2: {
            if (showGraphics()) {
                std::cout << "Graphics displayed successfully.\n";
            } else {
                std::cerr << "Error displaying graphics.\n";
            }
            break;
        }
        case 3:
            std::cout << "Exiting program...\n";
            break;
        default:
            std::cerr << "Invalid choice. Please try again.\n";
    }
}
