#ifndef _ENEMYWEAKNESSDISPLAY_HPP
#define _ENEMYWEAKNESSDISPLAY_HPP

#include "NoteDisplaySystem.hpp"
#include <vector>

class EnemyWeaknessDisplay
{
    std::vector<NoteType> _listNote;

public:
    const std::vector<NoteType>& GetNoteList() const;
    void AddNote(NoteType note);
    void RemoveNote(NoteType note);
};

#endif //_ENEMYWEAKNESSDISPLAY_HPP
