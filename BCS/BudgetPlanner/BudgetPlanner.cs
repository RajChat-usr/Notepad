using System;
using System.Collections.Generic;
using System.IO;

class BudgetPlanner
{
    static double budget = 0.0;
    static double totalExpense = 0.0;
    static string currency = "$";
    static List<string> expenses = new List<string>();

    static void Main()
    {
        Console.WriteLine("Welcome to the Budget Planner!");
        while (true)
        {
            ShowMenu();
            string choice = Console.ReadLine();
            switch (choice)
            {
                case "1":
                    SetBudget();
                    break;
                case "2":
                    AddExpense();
                    break;
                case "3":
                    ViewExpenses();
                    break;
                case "4":
                    SetCurrency();
                    break;
                case "5":
                    SaveDataToFile();
                    break;
                case "6":
                    ShowRemainingBudget();
                    break;
                case "7":
                    Environment.Exit(0);
                    break;
                default:
                    Console.WriteLine("Invalid choice, please try again.");
                    break;
            }
        }
    }

    static void ShowMenu()
    {
        Console.Clear();
        Console.WriteLine("---- Budget Planner ----");
        Console.WriteLine("1. Enter Budget");
        Console.WriteLine("2. Add Expense");
        Console.WriteLine("3. View Expenses");
        Console.WriteLine("4. Set Currency");
        Console.WriteLine("5. Save or Export Data");
        Console.WriteLine("6. View Remaining Budget");
        Console.WriteLine("7. Exit");
        Console.Write("Choose an option: ");
    }

    static void SetBudget()
    {
        Console.Clear();
        Console.Write("Enter your budget: ");
        string input = Console.ReadLine();
        
        // Fix: Correctly use double.TryParse
        if (double.TryParse(input, out budget))
        {
            totalExpense = 0.0;  // Reset total expense when setting a new budget
            Console.WriteLine("Budget set successfully.");
        }
        else
        {
            Console.WriteLine("Invalid input. Please enter a valid number.");
        }
        Console.ReadLine();
    }

    static void AddExpense()
    {
        Console.Clear();
        Console.Write("Enter expense description: ");
        string description = Console.ReadLine();
        Console.Write("Enter expense amount: ");
        string input = Console.ReadLine();

        // Fix: Correctly handle TryParse for expenseAmount
        double expenseAmount;
        if (double.TryParse(input, out expenseAmount))
        {
            totalExpense += expenseAmount;
            expenses.Add(description + ": " + currency + expenseAmount);
            Console.WriteLine("Expense added successfully.");
        }
        else
        {
            Console.WriteLine("Invalid amount. Please enter a valid number.");
        }
        Console.ReadLine();
    }

    static void ViewExpenses()
    {
        Console.Clear();
        if (expenses.Count == 0)
        {
            Console.WriteLine("No expenses recorded yet.");
        }
        else
        {
            Console.WriteLine("----- Expenses -----");
            foreach (var expense in expenses)
            {
                Console.WriteLine(expense);
            }
        }
        Console.ReadLine();
    }

    static void SetCurrency()
    {
        Console.Clear();
        Console.Write("Enter currency (e.g., $ / Rs.): ");
        currency = Console.ReadLine();
        Console.WriteLine("Currency set to " + currency + ".");
        Console.ReadLine();
    }

    static void ShowRemainingBudget()
    {
        Console.Clear();
        double remainingBudget = budget - totalExpense;
        Console.WriteLine("Total Budget: " + currency + budget);
        Console.WriteLine("Total Expenses: " + currency + totalExpense);
        Console.WriteLine("Remaining Budget: " + currency + remainingBudget);
        if (remainingBudget < 0)
        {
            Console.WriteLine("Warning: You have exceeded your budget!");
        }
        Console.ReadLine();
    }

    static void SaveDataToFile()
    {
        Console.Clear();
        string fileName = "budget_data.txt";
        try
        {
            using (StreamWriter writer = new StreamWriter(fileName))
            {
                writer.WriteLine("Budget: " + currency + budget);
                writer.WriteLine("Total Expenses: " + currency + totalExpense);
                writer.WriteLine("Remaining Budget: " + currency + (budget - totalExpense));
                writer.WriteLine("----- Expenses -----");
                foreach (var expense in expenses)
                {
                    writer.WriteLine(expense);
                }
            }
            Console.WriteLine("Data saved successfully to 'budget_data.txt'.");
        }
        catch (Exception e)
        {
            Console.WriteLine("Error saving file: " + e.Message);
        }
        Console.ReadLine();
    }
}
