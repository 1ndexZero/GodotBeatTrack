#pragma once

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <vector>

#include "note_key.h"
#include "bpm_event_list.h"
#include "speed_event_list.h"

namespace godot {

class NoteTrack : public RefCounted {
	GDCLASS(NoteTrack, RefCounted)

private:
    std::vector<Ref<NoteKey>> _notes;

protected:
	static void _bind_methods();

public:
    NoteTrack() = default;
    static Ref<NoteTrack> create(
        Ref<BpmEventList> p_bpm_events, Ref<SpeedEventList> p_speed_events);

    Ref<BpmEventList> bpm_events;
    Ref<SpeedEventList> speed_events;

    void add_note(Ref<NoteKey> p_note);
    bool remove_note(Ref<NoteKey> p_note);
    void remove_note_at(int index);
    int get_note_index(double p_units) const;
    Ref<NoteKey> get_note(double p_units) const;
    Ref<NoteKey> get_note_at(int index) const;
};

} // namespace godot