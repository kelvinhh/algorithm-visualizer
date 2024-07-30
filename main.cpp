#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <atomic>

#include "View/sortview.h"
#include "Model/sortmodel.h"
#include "Controller/sortcontroller.h"

void startMenu() {
    std::cout << "Press 'Space' to start sorting\n";
    std::cout << "Press 'R' to shuffle\n";
    std::cout << "Press 'Q' to quit\n";
}

int main() {
    startMenu();
    
    SortView view;
    SortModel model(100);
    SortController sortcontroller(view, model);

    while (view.getWindow().isOpen()) {
        sortcontroller.handleEvent();
        sortcontroller.viewRender();
    }

    return EXIT_SUCCESS;
}