//
// Created by g.nisi on 2/26/21.
//

#ifndef QUACKENGINE_WIDGET_HPP
#define QUACKENGINE_WIDGET_HPP


class Widget
{
private:
    int position[2];
public:
    virtual void update() = 0;
};


#endif //QUACKENGINE_WIDGET_HPP
