#include "BudgetPlanner.hpp"

BudgetPlanner::BudgetPlanner(QWidget *parent)
    : QWidget(parent), monthlyBudget(0.0), totalSpending(0.0) {
    // Initialize UI
    setWindowTitle("Budget Planner");
    setFixedSize(400, 300);

    // Layout
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Budget input field and label
    QLabel *budgetLabel = new QLabel("Enter your monthly budget:", this);
    layout->addWidget(budgetLabel);
    budgetInput = new QLineEdit(this);
    layout->addWidget(budgetInput);

    // Set button to input budget
    QPushButton *setBudgetButton = new QPushButton("Set Budget", this);
    layout->addWidget(setBudgetButton);
    connect(setBudgetButton, &QPushButton::clicked, this, &BudgetPlanner::setBudget);

    // Expense input field and button
    QLabel *expenseLabel = new QLabel("Enter expense name:", this);
    layout->addWidget(expenseLabel);
    expenseInput = new QLineEdit(this);
    layout->addWidget(expenseInput);

    QLabel *amountLabel = new QLabel("Enter expense amount:", this);
    layout->addWidget(amountLabel);
    amountInput = new QLineEdit(this);
    layout->addWidget(amountInput);

    QPushButton *addExpenseButton = new QPushButton("Add Expense", this);
    layout->addWidget(addExpenseButton);
    connect(addExpenseButton, &QPushButton::clicked, this, &BudgetPlanner::addExpense);

    // Label for displaying the budget summary
    budgetSummary = new QLabel(this);
    layout->addWidget(budgetSummary);
}

void BudgetPlanner::setBudget() {
    double inputBudget = budgetInput->text().toDouble();
    monthlyBudget = inputBudget;
    totalSpending = 0.0;
    budgetSummary->setText("Monthly Budget: " + QString::number(monthlyBudget));
    QMessageBox::information(this, "Budget Set", "Your budget is set to " + QString::number(monthlyBudget));
}

void BudgetPlanner::addExpense() {
    QString expenseName = expenseInput->text();
    double expenseAmount = amountInput->text().toDouble();
    expenseList.push_back(expenseName);
    expenseAmounts.push_back(expenseAmount);
    totalSpending += expenseAmount;
    checkBudgetLimit();
}

void BudgetPlanner::checkBudgetLimit() {
    double limitDifference = totalSpending - monthlyBudget;
    if (totalSpending > monthlyBudget) {
        budgetSummary->setText("You are over budget by: " + QString::number(limitDifference));
    } else {
        budgetSummary->setText("You are within your budget.");
    }
}
