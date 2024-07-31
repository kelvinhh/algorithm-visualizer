#ifndef SORTVIEW_H
#define SORTVIEW_H

#include "view.h"

class SortView : public View {
private:
    using View::View;

    void render(const Model *model, std::string& title) override;
};

#endif