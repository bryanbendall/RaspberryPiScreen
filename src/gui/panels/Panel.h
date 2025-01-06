#pragma once

class Panel {

public:
    virtual ~Panel() { }
    virtual void draw() = 0;
};