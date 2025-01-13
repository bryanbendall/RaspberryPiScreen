#pragma once

class Panel {

public:
    virtual ~Panel() { }
    virtual void draw(int width, int height) = 0;
};