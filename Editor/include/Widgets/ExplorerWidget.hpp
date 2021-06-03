#ifndef QUACKENGINE_EXPLORERWIDGET_HPP
#define QUACKENGINE_EXPLORERWIDGET_HPP

#include "Widgets/Widget.hpp"

#include <vector>

class ExplorerWidget : public Widget
{
private:
    unsigned int _selected{};
    bool _newMaterial {false};
    char _newMaterialTextBuffer[32] {""};

    void AddMaterial(unsigned int& offset);
    void RemoveMaterial(const std::vector<std::string>& listMaterialName);

public:
    explicit ExplorerWidget(Editor &editor);

    void UpdateVisible() final;
    unsigned int DisplayList(std::vector<std::string> &listName, unsigned int offset);

};


#endif //QUACKENGINE_EXPLORERWIDGET_HPP
