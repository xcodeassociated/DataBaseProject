#include <QApplication>
#include "Controller.h"

#include <iostream>

auto main(int argc, char *argv[]) -> int {
    std::cout << std::boolalpha;;
    
    QApplication a(argc, argv);
    
    Controller* controller = Controller::instance();
    controller->showLogin();
    
    return a.exec();
}
