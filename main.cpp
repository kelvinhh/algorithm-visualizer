#include <SFML/Graphics.hpp>
#include <iostream>

#include "View/sortview.h"
#include "Model/sortmodel.h"
#include "Controller/sortcontroller.h"

int main() {
    SortView view;
    SortModel model(100);
    SortController sortcontroller(view, model);

    while (view.getWindow().isOpen()) {
        sortcontroller.handleEvent();

        sortcontroller.viewRender();
    }

    return EXIT_SUCCESS;
}