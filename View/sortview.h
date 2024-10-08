#ifndef SORTVIEW_H
#define SORTVIEW_H

#include "view.h"
#include "sortmodel.h"

class SortView : public View {
private:
    using View::View;

    void render(Model *model, std::string& title) override;
};

#endif