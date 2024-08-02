#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <ranges>

#include "View/sortview.h"
#include "Model/sortmodel.h"
#include "Controller/sortcontroller.h"
#include "View/searchview.h"
#include "Model/searchmodel.h"
#include "Controller/searchcontroller.h"

void startMenu() {
    std::cout << "Press 'Space' to start sorting\n";
    std::cout << "Press 'R' to shuffle\n";
    std::cout << "Press 'Q' to quit\n";
}

int main() {
    // startMenu();
    // std::unique_ptr<SortView> view = std::make_unique<SortView>();
    // std::unique_ptr<SortModel> model = std::make_unique<SortModel>(100);
    // std::unique_ptr<SortController> sortcontroller = std::make_unique<SortController>(view.get(), model.get());
    // while (view->getWindow().isOpen()) {
    //     sortcontroller->handleEvent();
    //     sortcontroller->viewRender();
    // }

    std::unique_ptr<SearchView> view = std::make_unique<SearchView>();
    std::unique_ptr<SearchModel> model = std::make_unique<SearchModel>(1280, 720, 40);
    std::unique_ptr<SearchController> sortcontroller = std::make_unique<SearchController>(view.get(), model.get());

    while (view->getWindow().isOpen()) {
        sortcontroller->handleEvent();
        sortcontroller->viewRender();
    }

    return EXIT_SUCCESS;
}
