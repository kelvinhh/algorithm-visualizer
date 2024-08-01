#ifndef SORTCONTROLLER_H
#define SORTCONTROLLER_H

#include "controller.h"
#include "sortview.h"
#include "sortmodel.h"

class SortController: public Controller {
public:
    SortController(SortView *view, SortModel *model) : Controller(view, model) {}

    void handleEvent() override;
};


#endif
