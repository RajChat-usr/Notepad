#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Message.H>
#include <vector>
#include <string>
#include <sstream>

class BudgetPlanner : public Fl_Window {
public:
    BudgetPlanner(int w, int h, const char* title) : Fl_Window(w, h, title) {
        // Initialize UI
        this->begin();

        // Budget input field and label
        budgetLabel = new Fl_Box(20, 20, 180, 30, "Enter your monthly budget:");
        budgetInput = new Fl_Input(200, 20, 150, 30);

        // Set button to input budget
        setBudgetButton = new Fl_Button(200, 60, 150, 30, "Set Budget");
        setBudgetButton->callback(SetBudgetCallback, this);

        // Expense input field and button
        expenseLabel = new Fl_Box(20, 100, 180, 30, "Enter expense name:");
        expenseInput = new Fl_Input(200, 100, 150, 30);

        amountLabel = new Fl_Box(20, 140, 180, 30, "Enter expense amount:");
        amountInput = new Fl_Input(200, 140, 150, 30);

        addExpenseButton = new Fl_Button(200, 180, 150, 30, "Add Expense");
        addExpenseButton->callback(AddExpenseCallback, this);

        // Label for displaying the budget summary
        budgetSummary = new Fl_Box(20, 220, 330, 30, "Monthly Budget: $0.00");

        this->end();
    }

    static void SetBudgetCallback(Fl_Widget* widget, void* data) {
        BudgetPlanner* planner = (BudgetPlanner*)data;
        double inputBudget = std::stod(planner->budgetInput->value());
        planner->monthlyBudget = inputBudget;
        planner->totalSpending = 0.0;
        std::ostringstream oss;
        oss << "Monthly Budget: $" << planner->monthlyBudget;
        planner->budgetSummary->label(oss.str().c_str());
        Fl_Message("Budget Set", "Your budget is set to $" + std::to_string(planner->monthlyBudget));
    }

    static void AddExpenseCallback(Fl_Widget* widget, void* data) {
        BudgetPlanner* planner = (BudgetPlanner*)data;
        std::string expenseName = planner->expenseInput->value();
        double expenseAmount = std::stod(planner->amountInput->value());
        planner->expenseList.push_back(expenseName);
        planner->expenseAmounts.push_back(expenseAmount);
        planner->totalSpending += expenseAmount;
        planner->CheckBudgetLimit();
    }

    void CheckBudgetLimit() {
        double limitDifference = totalSpending - monthlyBudget;
        std::ostringstream oss;
        if (totalSpending > monthlyBudget) {
            oss << "You are over budget by: $" << limitDifference;
        } else {
            oss << "You are within your budget.";
        }
        budgetSummary->label(oss.str().c_str());
    }

private:
    double monthlyBudget = 0.0;
    double totalSpending = 0.0;
    std::vector<std::string> expenseList;
    std::vector<double> expenseAmounts;

    Fl_Input *budgetInput;
    Fl_Input *expenseInput;
    Fl_Input *amountInput;
    Fl_Box *budgetLabel;
    Fl_Box *expenseLabel;
    Fl_Box *amountLabel;
    Fl_Box *budgetSummary;
    Fl_Button *setBudgetButton;
    Fl_Button *addExpenseButton;
};

int main(int argc, char* argv[]) {
    BudgetPlanner planner(400, 300, "Budget Planner");
    planner.show(argc, argv);
    return Fl::run();
}
