#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QString>
#include <QMessageBox>

class BudgetPlanner : public QWidget {
    Q_OBJECT

public:
    BudgetPlanner(QWidget *parent = nullptr) : QWidget(parent) {
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

private slots:
    void setBudget() {
        double inputBudget = budgetInput->text().toDouble();
        monthlyBudget = inputBudget;
        totalSpending = 0.0;
        budgetSummary->setText("Monthly Budget: " + QString::number(monthlyBudget));
        QMessageBox::information(this, "Budget Set", "Your budget is set to " + QString::number(monthlyBudget));
    }

    void addExpense() {
        QString expenseName = expenseInput->text();
        double expenseAmount = amountInput->text().toDouble();
        expenseList.push_back(expenseName);
        expenseAmounts.push_back(expenseAmount);
        totalSpending += expenseAmount;
        checkBudgetLimit();
    }

    void checkBudgetLimit() {
        double limitDifference = totalSpending - monthlyBudget;
        if (totalSpending > monthlyBudget) {
            budgetSummary->setText("You are over budget by: " + QString::number(limitDifference));
        } else {
            budgetSummary->setText("You are within your budget.");
        }
    }

private:
    double monthlyBudget = 0.0;
    double totalSpending = 0.0;
    QVector<QString> expenseList;
    QVector<double> expenseAmounts;

    QLineEdit *budgetInput;
    QLineEdit *expenseInput;
    QLineEdit *amountInput;
    QLabel *budgetSummary;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    BudgetPlanner planner;
    planner.show();

    return app.exec();
}
