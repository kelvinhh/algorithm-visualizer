#ifndef SEARCHCONTROLLER_H
#define SEARCHCONTROLLER_H

#include "controller.h"
#include "searchview.h"
#include "searchmodel.h"

class SearchController: public Controller {
public:
    SearchController(SearchView *view, SearchModel *model) : Controller(view, model) {}

    void handleEvent() override;
};


#endif
