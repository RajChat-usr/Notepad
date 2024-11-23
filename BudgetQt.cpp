#include "BudgetPlanner.hpp"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    BudgetPlanner planner;
    planner.show();

    return app.exec();
}
