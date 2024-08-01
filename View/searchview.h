#ifndef SEARCHVIEW_H
#define SEARCHVIEW_H

#include "view.h"
#include "searchmodel.h"

class SearchView : public View {
private:
    using View::View;

    void render(Model *model, std::string& title) override;
};

#endif