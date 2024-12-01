#include "raylib.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

static double budget = 0.0;
static double totalExpense = 0.0;
static std::string currency = "$";  // Default currency
static std::vector<std::string> expenses;

TextBox txtBudget, txtExpenseDesc, txtExpenseAmount;
Button btnSetBudget, btnAddExpense, btnViewExpenses, btnSaveData, btnShowRemainingBudget;
Label lblTotalExpense, lblRemainingBudget, lblCurrency, lblExpenseDesc, lblExpenseAmount;
ComboBox cboCurrency;  // Dropdown to select currency

// Function prototypes
void SetBudget();
void AddExpense();
void ViewExpenses();
void SetCurrency();
void SaveDataToFile();
void DrawUI();

int main()
{
    // Initialize window
    InitWindow(400, 500, "Budget Planner");

    // Initialize UI controls (simulated for Raylib)
    Vector2 txtBudgetPos = {150, 20};
    Vector2 txtExpenseDescPos = {150, 60};
    Vector2 txtExpenseAmountPos = {150, 100};
    Vector2 btnSetBudgetPos = {270, 20};
    Vector2 btnAddExpensePos = {150, 140};
    Vector2 btnViewExpensesPos = {150, 180};
    Vector2 btnSaveDataPos = {150, 310};
    Vector2 lblTotalExpensePos = {20, 220};
    Vector2 lblRemainingBudgetPos = {20, 250};
    
    // Set budget button callback
    SetBudget();

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update and draw the interface
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw UI
        DrawUI();

        EndDrawing();
    }

    // De-Initialization
    CloseWindow(); // Close window and OpenGL context

    return 0;
}

void DrawUI()
{
    // Draw UI elements here
    DrawText("Budget: ", 20, 20, 20, BLACK);
    DrawText(TextFormat("%.2f", budget), 150, 20, 20, BLACK);
    
    DrawText("Expense Name:", 20, 60, 20, BLACK);
    DrawText("Expense Amount:", 20, 100, 20, BLACK);

    // Set Budget button
    if (CheckCollisionPointRec(GetMousePosition(), Rectangle{270, 20, 100, 30}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        SetBudget();
    }

    // Add Expense button
    if (CheckCollisionPointRec(GetMousePosition(), Rectangle{150, 140, 100, 30}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        AddExpense();
    }

    // View Expenses button
    if (CheckCollisionPointRec(GetMousePosition(), Rectangle{150, 180, 100, 30}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        ViewExpenses();
    }

    // Save Data button
    if (CheckCollisionPointRec(GetMousePosition(), Rectangle{150, 310, 100, 30}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        SaveDataToFile();
    }

    // Display labels
    DrawText("Total Expenses: " + std::string(currency) + std::to_string(totalExpense), 20, 220, 20, BLACK);
    DrawText("Remaining Budget: " + std::string(currency) + std::to_string(budget - totalExpense), 20, 250, 20, BLACK);
}

void SetBudget()
{
    // Simulating the logic for setting budget
    budget = 1000.0;  // Example value
    totalExpense = 0.0;  // Reset total expense
}

void AddExpense()
{
    // Simulate adding expense
    double expenseAmount = 50.0;  // Example expense value
    std::string description = "Groceries";  // Example description

    totalExpense += expenseAmount;
    expenses.push_back(description + ": " + std::string(currency) + std::to_string(expenseAmount));
}

void ViewExpenses()
{
    // Display all expenses
    std::string expenseList;
    for (const auto& expense : expenses)
    {
        expenseList += expense + "\n";
    }
    // You can use Raylib to show this string as a simple window
    DrawText(expenseList.c_str(), 20, 20, 20, BLACK);
}

void SetCurrency()
{
    // Change currency
    currency = "$"; // Set a currency for now
}

void SaveDataToFile()
{
    std::ofstream outFile("budget_data.txt");
    outFile << "Budget: " << currency << budget << "\n";
    outFile << "Total Expenses: " << currency << totalExpense << "\n";
    outFile << "Remaining Budget: " << currency << (budget - totalExpense) << "\n";
    outFile << "----- Expenses -----\n";

    for (const auto& expense : expenses)
    {
        outFile << expense << "\n";
    }
    
    outFile.close();
}
