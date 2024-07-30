#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"
#include "view.h"

class Controller {
protected:
    View& view;
    Model& model;

public:
    Controller(View& view, Model& model) : view{view}, model{model} {}
    virtual ~Controller() = default;
    
    virtual void viewRender() = 0;

    void handleEvent();
};

#endif