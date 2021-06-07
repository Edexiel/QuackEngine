#ifndef _ENEMYWEAKNESSDISPLAY_HPP
#define _ENEMYWEAKNESSDISPLAY_HPP

#include "Scene/Component/ComponentBase.hpp"

#include "EnemySystem.hpp"
#include <vector>

class EnemyComponent : public Component::ComponentBase
{
    std::vector<NoteType> _listNote;

public:

    float speed {1.f};

    const std::vector<NoteType>& GetNoteList() const;
    void AddNote(NoteType note);
    void RemoveNote(NoteType note);
};
#endif //_ENEMYWEAKNESSDISPLAY_HPP
