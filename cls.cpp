#include <iostream>

void clearConsole() {
    // ANSI escape sequence to clear the scrollback buffer, screen, and reset cursor
    std::cout << "\033[3J";  // Clear the scrollback buffer
    std::cout << "\033[2J\033[H";  // Clear the screen and reset cursor to top-left
    std::cout.flush();  // Ensure output is sent immediately
}

int main() {
    clearConsole();  // Call the function to clear the screen
    return 0;
}
