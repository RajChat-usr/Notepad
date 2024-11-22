#include <iostream>

void clearConsole() {
    // ANSI escape sequence to clear the screen
    std::cout << "\033[2J\033[H"; // Clear screen and move the cursor to home position
    std::cout.flush(); // Ensure the output is sent immediately
}

int main() {
    clearConsole(); // Call the function to clear the screen
    return 0;
}
