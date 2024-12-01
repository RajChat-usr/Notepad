using System;
using System.Collections.Generic;
using System.IO;
using System.Windows.Forms;

public class BudgetPlannerForm : Form
{
    static double budget = 0.0;
    static double totalExpense = 0.0;
    static string currency = "$";  // Default currency
    static List<string> expenses = new List<string>();

    // UI Controls
    TextBox txtBudget, txtExpenseDesc, txtExpenseAmount;
    Button btnSetBudget, btnAddExpense, btnViewExpenses, btnSaveData, btnShowRemainingBudget;
    Label lblTotalExpense, lblRemainingBudget, lblCurrency, lblExpenseDesc, lblExpenseAmount;
    ComboBox cboCurrency;  // Dropdown to select currency
    
    public BudgetPlannerForm()
    {
        // Initialize the UI controls
        this.Text = "Budget Planner";
        this.Size = new System.Drawing.Size(400, 500);

        txtBudget = new TextBox() { Top = 20, Left = 150, Width = 100 };
        btnSetBudget = new Button() { Text = "Set Budget", Top = 20, Left = 270 };
        btnSetBudget.Click += new EventHandler(SetBudget);

        // Labels for expense description and amount
        lblExpenseDesc = new Label() { Top = 60, Left = 20, Text = "Expense Name:" };
        txtExpenseDesc = new TextBox() { Top = 60, Left = 150, Width = 100 };

        lblExpenseAmount = new Label() { Top = 100, Left = 20, Text = "Amount:" };
        txtExpenseAmount = new TextBox() { Top = 100, Left = 150, Width = 100 };

        btnAddExpense = new Button() { Text = "Add Expense", Top = 140, Left = 150 };
        btnAddExpense.Click += new EventHandler(AddExpense);

        btnViewExpenses = new Button() { Text = "View Expenses", Top = 180, Left = 150 };
        btnViewExpenses.Click += new EventHandler(ViewExpenses);

        lblTotalExpense = new Label() { Top = 220, Left = 20, Width = 200, Text = "Total Expenses: $0" };
        lblRemainingBudget = new Label() { Top = 250, Left = 20, Width = 200, Text = "Remaining Budget: $0" };

        // Dropdown for currency selection
        cboCurrency = new ComboBox() { Top = 280, Left = 20, Width = 100 };
        cboCurrency.Items.Add("$");
        cboCurrency.Items.Add("Rs");
        cboCurrency.SelectedItem = "$";  // Default selection
        cboCurrency.SelectedIndexChanged += new EventHandler(SetCurrency);

        btnSaveData = new Button() { Text = "Save Data", Top = 310, Left = 150 };
        btnSaveData.Click += new EventHandler(SaveDataToFile);

        // Add all controls to the form
        this.Controls.Add(txtBudget);
        this.Controls.Add(btnSetBudget);
        this.Controls.Add(lblExpenseDesc);
        this.Controls.Add(txtExpenseDesc);
        this.Controls.Add(lblExpenseAmount);
        this.Controls.Add(txtExpenseAmount);
        this.Controls.Add(btnAddExpense);
        this.Controls.Add(btnViewExpenses);
        this.Controls.Add(lblTotalExpense);
        this.Controls.Add(lblRemainingBudget);
        this.Controls.Add(cboCurrency);
        this.Controls.Add(btnSaveData);
    }

    static void Main()
    {
        Application.Run(new BudgetPlannerForm());
    }

    private void SetBudget(object sender, EventArgs e)
    {
        double.TryParse(txtBudget.Text, out budget);
        totalExpense = 0.0;  // Reset total expense when setting a new budget
        lblRemainingBudget.Text = "Remaining Budget: " + currency + (budget - totalExpense);
        lblTotalExpense.Text = "Total Expenses: " + currency + totalExpense;
    }

    private void AddExpense(object sender, EventArgs e)
    {
        string description = txtExpenseDesc.Text;
        double expenseAmount;
        if (double.TryParse(txtExpenseAmount.Text, out expenseAmount))
        {
            totalExpense += expenseAmount;
            expenses.Add(description + ": " + currency + expenseAmount);
            lblTotalExpense.Text = "Total Expenses: " + currency + totalExpense;
            lblRemainingBudget.Text = "Remaining Budget: " + currency + (budget - totalExpense);
        }
        else
        {
            MessageBox.Show("Invalid amount. Please enter a valid number.");
        }
    }

    private void ViewExpenses(object sender, EventArgs e)
    {
        string expenseList = string.Join(Environment.NewLine, expenses);
        MessageBox.Show(expenseList);
    }

    private void SetCurrency(object sender, EventArgs e)
    {
        currency = cboCurrency.SelectedItem.ToString();
        lblTotalExpense.Text = "Total Expenses: " + currency + totalExpense;
        lblRemainingBudget.Text = "Remaining Budget: " + currency + (budget - totalExpense);
    }

    private void SaveDataToFile(object sender, EventArgs e)
    {
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
            MessageBox.Show("Data saved successfully to 'budget_data.txt'.");
        }
        catch (Exception e1)
        {
            MessageBox.Show("Error saving file: " + e1.Message);
        }
    }
}
