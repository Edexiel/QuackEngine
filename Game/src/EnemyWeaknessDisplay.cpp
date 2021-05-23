#include <EnemyWeaknessDisplay.hpp>

const std::vector<NoteType>& EnemyWeaknessDisplay::GetNoteList() const
{
    return _listNote;
}

void EnemyWeaknessDisplay::AddNote(NoteType note)
{
    _listNote.push_back(note);
}

void EnemyWeaknessDisplay::RemoveNote(NoteType note)
{
    if (_listNote.empty())
        return;
    if (_listNote[0] == note)
        _listNote.erase(_listNote.begin());
}

