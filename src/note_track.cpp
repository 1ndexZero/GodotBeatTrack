#include "note_track.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void NoteTrack::_bind_methods() {
    ClassDB::bind_static_method("NoteTrack", D_METHOD("create", "bpm_events", "speed_events"), &NoteTrack::create);

    ClassDB::bind_method(D_METHOD("add_note", "note"), &NoteTrack::add_note);
    ClassDB::bind_method(D_METHOD("remove_note", "note"), &NoteTrack::remove_note);
    ClassDB::bind_method(D_METHOD("remove_note_at", "index"), &NoteTrack::remove_note_at);
    ClassDB::bind_method(D_METHOD("get_note_index", "units"), &NoteTrack::get_note_index);
    ClassDB::bind_method(D_METHOD("get_note", "units"), &NoteTrack::get_note);
    ClassDB::bind_method(D_METHOD("get_note_at", "index"), &NoteTrack::get_note_at);
}

Ref<NoteTrack> NoteTrack::create(Ref<BpmEventList> p_bpm_events, Ref<SpeedEventList> p_speed_events) {
    if (p_bpm_events.is_null()) {
        UtilityFunctions::push_error("bpm_events is null");
        return Variant();
    }

    if (p_speed_events.is_null()) {
        UtilityFunctions::push_error("speed_events is null");
        return Variant();
    }

    Ref<NoteTrack> track;

    p_speed_events->bpm_events = p_bpm_events;
    p_speed_events->update_displacements(0);

    track.instantiate();
    track->bpm_events = p_bpm_events;
    track->speed_events = p_speed_events;

    return track;
}

void NoteTrack::add_note(Ref<NoteKey> p_note) {
    if (p_note.is_null()) {
        UtilityFunctions::push_error("note is null");
        return;
    }

    int units = p_note->units;
    int i = _notes.size() - 1;

    _notes.push_back(p_note);

    while (i >= 0 && _notes[i]->units >= units)
        _notes[i + 1] = _notes[i--];

    _notes[i + 1] = p_note;

    if (speed_events.is_valid())
        p_note->displacement = speed_events->get_displacement(bpm_events->get_secs(units));
}

bool NoteTrack::remove_note(Ref<NoteKey> p_note) {
    int size = _notes.size();

    for (int i = 0; i < size; i++) {
        if (_notes[i] == p_note) {
            _notes.erase(_notes.begin() + i);
            return true;
        }
    }

    return false;
}

void NoteTrack::remove_note_at(int p_index) {
    if (p_index < 0 || p_index >= _notes.size()) {
        UtilityFunctions::push_error("index out of range");
        return;
    }

    _notes.erase(_notes.begin() + p_index);
}

int NoteTrack::get_note_index(double p_units) const {
    if (_notes.empty()) return -1;

    int left = 0;
    int right = _notes.size() - 1;
    int result = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (_notes[mid]->units <= p_units) {
            result = mid; left = mid + 1;
        }

        else right = mid - 1;
    }

    return result;
}

Ref<NoteKey> NoteTrack::get_note(double p_units) const {
    int index = get_note_index(p_units);

    if (index == -1) return Variant();

    return _notes[index];
}

Ref<NoteKey> NoteTrack::get_note_at(int p_index) const {
    if (p_index < 0 || p_index >= _notes.size()) {
		UtilityFunctions::push_error("index out of range");
		return Variant();
    }

    return _notes[p_index];
}