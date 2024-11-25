#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

// Global Constants
const int GRID_SIZE = 3;
const int CELL_SIZE = 200;
const int WINDOW_SIZE = GRID_SIZE * CELL_SIZE;

// Game State
std::vector<std::vector<char>> board(GRID_SIZE, std::vector<char>(GRID_SIZE, ' '));
char currentPlayer = 'X';

// Draw the board grid
void drawGrid(sf::RenderWindow &window) {
    sf::RectangleShape line(sf::Vector2f(WINDOW_SIZE, 5));
    line.setFillColor(sf::Color::Black);

    // Draw horizontal lines
    for (int i = 1; i < GRID_SIZE; ++i) {
        line.setPosition(0, i * CELL_SIZE - 2);
        window.draw(line);
    }

    // Draw vertical lines
    line.setSize(sf::Vector2f(5, WINDOW_SIZE));
    for (int i = 1; i < GRID_SIZE; ++i) {
        line.setPosition(i * CELL_SIZE - 2, 0);
        window.draw(line);
    }
}

// Draw the X and O symbols on the board
void drawSymbols(sf::RenderWindow &window) {
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/DejaVuSans-Bold.ttf")) {
        std::cerr << "Error: Could not load font.\n";
        return;
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(150);
    text.setFillColor(sf::Color::Black);

    for (int row = 0; row < GRID_SIZE; ++row) {
        for (int col = 0; col < GRID_SIZE; ++col) {
            if (board[row][col] != ' ') {
                text.setString(board[row][col]);
                text.setPosition(col * CELL_SIZE + 50, row * CELL_SIZE);
                window.draw(text);
            }
        }
    }
}

// Check if a player has won
bool checkWin() {
    // Check rows and columns
    for (int i = 0; i < GRID_SIZE; ++i) {
        if (board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer)
            return true;
        if (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer)
            return true;
    }

    // Check diagonals
    if (board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer)
        return true;
    if (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer)
        return true;

    return false;
}

// Check if the game is a draw
bool checkDraw() {
    for (const auto &row : board) {
        for (char cell : row) {
            if (cell == ' ') return false;
        }
    }
    return true;
}

// Handle a player's move
void handleMove(int row, int col) {
    if (board[row][col] == ' ') {
        board[row][col] = currentPlayer;
        if (!checkWin()) {
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Tic Tac Toe");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                int row = event.mouseButton.y / CELL_SIZE;
                int col = event.mouseButton.x / CELL_SIZE;

                if (row < GRID_SIZE && col < GRID_SIZE) {
                    handleMove(row, col);

                    if (checkWin()) {
                        std::cout << "Player " << currentPlayer << " wins!\n";
                        window.close();
                    } else if (checkDraw()) {
                        std::cout << "It's a draw!\n";
                        window.close();
                    }
                }
            }
        }

        // Draw the board
        window.clear(sf::Color::White);
        drawGrid(window);
        drawSymbols(window);
        window.display();
    }

    return 0;
}
