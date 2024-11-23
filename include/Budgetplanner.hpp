#ifndef BUDGETPLANNER_HPP
#define BUDGETPLANNER_HPP

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QString>
#include <QMessageBox>
#include <QVector>

class BudgetPlanner : public QWidget {
    Q_OBJECT

public:
    explicit BudgetPlanner(QWidget *parent = nullptr);

private slots:
    void setBudget();
    void addExpense();
    void checkBudgetLimit();

private:
    double monthlyBudget;
    double totalSpending;
    QVector<QString> expenseList;
    QVector<double> expenseAmounts;

    QLineEdit *budgetInput;
    QLineEdit *expenseInput;
    QLineEdit *amountInput;
    QLabel *budgetSummary;
};

#endif // BUDGETPLANNER_HPP
