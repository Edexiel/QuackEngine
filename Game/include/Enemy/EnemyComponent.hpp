#ifndef _ENEMYWEAKNESSDISPLAY_HPP
#define _ENEMYWEAKNESSDISPLAY_HPP

#include "EnemyManagerSystem.hpp"
#include <vector>

class EnemyComponent
{
    std::vector<NoteType> _listNote;

public:

    float speed {1.f};

    const std::vector<NoteType>& GetNoteList() const;
    void AddNote(NoteType note);
    void RemoveNote(NoteType note);
};
#endif //_ENEMYWEAKNESSDISPLAY_HPP
