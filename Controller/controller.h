#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"
#include "view.h"

class Controller {
protected:
    View *view;
    Model *model;

    std::string title;

    int mode = 0;

public:
    Controller(View *view, Model *model) : view{view}, model{model} {}
    virtual ~Controller() = default;
    
    void viewRender();

    virtual void handleEvent() = 0;
};

#endif