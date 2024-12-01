#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

double budget = 0.0;
double totalExpense = 0.0;
std::string currency = "$";  // Default currency
std::vector<std::string> expenses;
sf::Font font;

sf::Text lblTotalExpense, lblRemainingBudget, lblCurrency, lblExpenseDesc, lblExpenseAmount;
sf::Text txtBudget, txtExpenseDesc, txtExpenseAmount;
sf::Text btnSetBudget, btnAddExpense, btnViewExpenses, btnSaveData, btnShowRemainingBudget;
sf::Text cboCurrency;

sf::RectangleShape btnSetBudgetRect, btnAddExpenseRect, btnViewExpensesRect, btnSaveDataRect;

void SetBudget();
void AddExpense();
void ViewExpenses();
void SetCurrency();
void SaveDataToFile();
void DrawUI(sf::RenderWindow& window);
bool IsMouseOver(sf::RectangleShape& button, sf::Vector2i mousePos);

int main() {
    // Create window
    sf::RenderWindow window(sf::VideoMode(400, 500), "Budget Planner");

    // Load font
    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "Error loading font!" << std::endl;
        return -1;
    }

    // Initialize Text
    lblTotalExpense.setFont(font);
    lblTotalExpense.setCharacterSize(20);
    lblTotalExpense.setFillColor(sf::Color::Black);
    lblTotalExpense.setPosition(20, 220);
    
    lblRemainingBudget.setFont(font);
    lblRemainingBudget.setCharacterSize(20);
    lblRemainingBudget.setFillColor(sf::Color::Black);
    lblRemainingBudget.setPosition(20, 250);

    txtBudget.setFont(font);
    txtBudget.setCharacterSize(20);
    txtBudget.setFillColor(sf::Color::Black);
    txtBudget.setPosition(150, 20);

    txtExpenseDesc.setFont(font);
    txtExpenseDesc.setCharacterSize(20);
    txtExpenseDesc.setFillColor(sf::Color::Black);
    txtExpenseDesc.setPosition(150, 60);

    txtExpenseAmount.setFont(font);
    txtExpenseAmount.setCharacterSize(20);
    txtExpenseAmount.setFillColor(sf::Color::Black);
    txtExpenseAmount.setPosition(150, 100);

    // Initialize Buttons (as Rectangles)
    btnSetBudgetRect.setSize(sf::Vector2f(100, 30));
    btnSetBudgetRect.setPosition(270, 20);
    btnSetBudgetRect.setFillColor(sf::Color::Green);

    btnAddExpenseRect.setSize(sf::Vector2f(120, 30));
    btnAddExpenseRect.setPosition(150, 140);
    btnAddExpenseRect.setFillColor(sf::Color::Green);

    btnViewExpensesRect.setSize(sf::Vector2f(120, 30));
    btnViewExpensesRect.setPosition(150, 180);
    btnViewExpensesRect.setFillColor(sf::Color::Green);

    btnSaveDataRect.setSize(sf::Vector2f(120, 30));
    btnSaveDataRect.setPosition(150, 310);
    btnSaveDataRect.setFillColor(sf::Color::Green);

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (IsMouseOver(btnSetBudgetRect, mousePos)) {
                    SetBudget();
                } 
                else if (IsMouseOver(btnAddExpenseRect, mousePos)) {
                    AddExpense();
                } 
                else if (IsMouseOver(btnViewExpensesRect, mousePos)) {
                    ViewExpenses();
                } 
                else if (IsMouseOver(btnSaveDataRect, mousePos)) {
                    SaveDataToFile();
                }
            }
        }

        // Draw UI
        window.clear(sf::Color::White);
        DrawUI(window);
        window.display();
    }

    return 0;
}

void SetBudget() {
    try {
        budget = std::stod(txtBudget.getString());
        totalExpense = 0.0;
        lblRemainingBudget.setString("Remaining Budget: " + currency + std::to_string(budget - totalExpense));
        lblTotalExpense.setString("Total Expenses: " + currency + std::to_string(totalExpense));
    }
    catch (...) {
        std::cout << "Invalid budget input!" << std::endl;
    }
}

void AddExpense() {
    std::string description = txtExpenseDesc.getString();
    double expenseAmount;
    try {
        expenseAmount = std::stod(txtExpenseAmount.getString());
        totalExpense += expenseAmount;
        expenses.push_back(description + ": " + currency + std::to_string(expenseAmount));
        lblTotalExpense.setString("Total Expenses: " + currency + std::to_string(totalExpense));
        lblRemainingBudget.setString("Remaining Budget: " + currency + std::to_string(budget - totalExpense));
    }
    catch (...) {
        std::cout << "Invalid expense amount!" << std::endl;
    }
}

void ViewExpenses() {
    std::string expenseList = "";
    for (auto& expense : expenses) {
        expenseList += expense + "\n";
    }
    std::cout << expenseList << std::endl;
}

void SetCurrency() {
    // Toggle between currencies
    if (currency == "$") {
        currency = "Rs";
    } else {
        currency = "$";
    }
    lblTotalExpense.setString("Total Expenses: " + currency + std::to_string(totalExpense));
    lblRemainingBudget.setString("Remaining Budget: " + currency + std::to_string(budget - totalExpense));
}

void SaveDataToFile() {
    std::ofstream outFile("budget_data.txt");
    if (outFile.is_open()) {
        outFile << "Budget: " << currency << budget << "\n";
        outFile << "Total Expenses: " << currency << totalExpense << "\n";
        outFile << "Remaining Budget: " << currency << (budget - totalExpense) << "\n";
        outFile << "----- Expenses -----\n";
        for (const auto& expense : expenses) {
            outFile << expense << "\n";
        }
        outFile.close();
        std::cout << "Data saved successfully!" << std::endl;
    }
    else {
        std::cout << "Error saving data!" << std::endl;
    }
}

void DrawUI(sf::RenderWindow& window) {
    window.draw(lblTotalExpense);
    window.draw(lblRemainingBudget);

    window.draw(txtBudget);
    window.draw(txtExpenseDesc);
    window.draw(txtExpenseAmount);

    window.draw(btnSetBudgetRect);
    window.draw(btnAddExpenseRect);
    window.draw(btnViewExpensesRect);
    window.draw(btnSaveDataRect);

    // Draw text labels for buttons
    btnSetBudget.setString("Set Budget");
    btnSetBudget.setFont(font);
    btnSetBudget.setCharacterSize(20);
    btnSetBudget.setFillColor(sf::Color::White);
    btnSetBudget.setPosition(270, 20);
    window.draw(btnSetBudget);

    btnAddExpense.setString("Add Expense");
    btnAddExpense.setFont(font);
    btnAddExpense.setCharacterSize(20);
    btnAddExpense.setFillColor(sf::Color::White);
    btnAddExpense.setPosition(150, 140);
    window.draw(btnAddExpense);

    btnViewExpenses.setString("View Expenses");
    btnViewExpenses.setFont(font);
    btnViewExpenses.setCharacterSize(20);
    btnViewExpenses.setFillColor(sf::Color::White);
    btnViewExpenses.setPosition(150, 180);
    window.draw(btnViewExpenses);

    btnSaveData.setString("Save Data");
    btnSaveData.setFont(font);
    btnSaveData.setCharacterSize(20);
    btnSaveData.setFillColor(sf::Color::White);
    btnSaveData.setPosition(150, 310);
    window.draw(btnSaveData);
}

bool IsMouseOver(sf::RectangleShape& button, sf::Vector2i mousePos) {
    return button.getGlobalBounds().contains(mousePos.x, mousePos.y);
}
