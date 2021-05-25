#include <Enemy/EnemyComponent.hpp>

const std::vector<NoteType>& EnemyComponent::GetNoteList() const
{
    return _listNote;
}

void EnemyComponent::AddNote(NoteType note)
{
    _listNote.push_back(note);
}

void EnemyComponent::RemoveNote(NoteType note)
{
    if (_listNote.empty())
        return;
    if (_listNote[0] == note)
        _listNote.erase(_listNote.begin());
}

