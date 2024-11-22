#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Currency conversion rates (These can be dynamically updated or fetched from an API)
const double USD_TO_INR = 82.0;  // Example conversion rate
const double INR_TO_USD = 1 / USD_TO_INR;

// Function to display the menu
void displayMenu() {
    cout << "--------------------------\n";
    cout << "Budget Planner\n";
    cout << "1. Set Monthly Budget\n";
    cout << "2. Add Expense\n";
    cout << "3. Delete Expense\n";
    cout << "4. List Expenses\n";
    cout << "5. View Budget Summary\n";
    cout << "6. Set Currency (USD/INR)\n";
    cout << "7. Exit\n";
    cout << "--------------------------\n";
    cout << "Please select an option: ";
}

// Function to check if the budget limit is exceeded
void checkBudgetLimit(double budget, double totalSpending, string currency) {
    double limitDifference = totalSpending - budget;
    if (totalSpending > budget) {
        cout << "Warning: You have exceeded your budget!\n";
        cout << "You are over by: " << limitDifference << " " << currency << endl;
    } else {
        cout << "Your spending is within the budget.\n";
    }
}

// Function to convert budget to the desired currency
double convertCurrency(double amount, string currency) {
    if (currency == "INR") {
        return amount * USD_TO_INR;
    } else {
        return amount * INR_TO_USD;
    }
}

// Main function
int main() {
    double monthlyBudget = 0.0;
    double totalSpending = 0.0;
    vector<string> expenseList;
    vector<double> expenseAmounts;
    string currency = "USD"; // Default currency
    int choice;
    
    while (true) {
        displayMenu();
        cin >> choice;
        
        switch (choice) {
            case 1: {
                // Set Monthly Budget
                cout << "Enter your monthly budget in " << currency << ": ";
                double inputBudget;
                cin >> inputBudget;
                monthlyBudget = convertCurrency(inputBudget, currency);
                totalSpending = 0.0; // Reset total spending when budget is updated
                cout << "Your monthly budget is set to " << monthlyBudget << " " << currency << endl;
                break;
            }
            case 2: {
                // Add Expense
                string expenseName;
                double expenseAmount;
                
                cout << "Enter the name of the expense: ";
                cin.ignore(); // To discard the newline character
                getline(cin, expenseName);
                
                cout << "Enter the amount for " << expenseName << " in " << currency << ": ";
                cin >> expenseAmount;
                
                expenseList.push_back(expenseName);
                expenseAmounts.push_back(expenseAmount);
                
                totalSpending += expenseAmount;
                cout << "Expense added: " << expenseName << " for " << expenseAmount << " " << currency << endl;
                checkBudgetLimit(monthlyBudget, totalSpending, currency);
                break;
            }
            case 3: {
                // Delete Expense
                cout << "Enter the index of the expense to delete (1 to " << expenseList.size() << "): ";
                int index;
                cin >> index;
                
                if (index > 0 && index <= expenseList.size()) {
                    string deletedExpense = expenseList[index - 1];
                    double deletedAmount = expenseAmounts[index - 1];
                    
                    // Remove the expense
                    expenseList.erase(expenseList.begin() + index - 1);
                    expenseAmounts.erase(expenseAmounts.begin() + index - 1);
                    totalSpending -= deletedAmount;
                    
                    cout << "Expense '" << deletedExpense << "' removed. Amount: " << deletedAmount << " " << currency << endl;
                    checkBudgetLimit(monthlyBudget, totalSpending, currency);
                } else {
                    cout << "Invalid expense index.\n";
                }
                break;
            }
            case 4: {
                // List Expenses
                cout << "---- Expense List ----\n";
                for (size_t i = 0; i < expenseList.size(); i++) {
                    cout << i + 1 << ". " << expenseList[i] << ": " << expenseAmounts[i] << " " << currency << endl;
                }
                break;
            }
            case 5: {
                // View Budget Summary
                cout << "---- Budget Summary ----\n";
                cout << "Monthly Budget: " << monthlyBudget << " " << currency << endl;
                cout << "Total Spending: " << totalSpending << " " << currency << endl;
                cout << "Expenses List:\n";
                for (size_t i = 0; i < expenseList.size(); i++) {
                    cout << expenseList[i] << ": " << expenseAmounts[i] << " " << currency << endl;
                }
                checkBudgetLimit(monthlyBudget, totalSpending, currency);
                break;
            }
            case 6: {
                // Set Currency (USD/INR)
                cout << "Enter currency (USD/INR): ";
                cin >> currency;
                if (currency != "USD" && currency != "INR") {
                    cout << "Invalid currency. Defaulting to USD.\n";
                    currency = "USD";
                }
                cout << "Currency set to " << currency << endl;
                break;
            }
            case 7: {
                // Exit the program
                cout << "Exiting Budget Planner. Goodbye!" << endl;
                return 0;
            }
            default:
                cout << "Invalid option, please try again." << endl;
                break;
        }
    }
    return 0;
}
