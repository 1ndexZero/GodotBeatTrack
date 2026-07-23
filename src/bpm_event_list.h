#pragma once

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <vector>

#include "bpm_event.h"

namespace godot {

class BpmEventList : public RefCounted {
    GDCLASS(BpmEventList, RefCounted)

private:
    std::vector<Ref<BpmEvent>> _events;

protected:
    static void _bind_methods();

public:
    BpmEventList() = default;
    static Ref<BpmEventList> create(double p_init_bpm, int p_units_abeat);

    double init_bpm;
    int units_abeat;

    double get_init_bpm() const { return init_bpm; }
    void set_init_bpm(double p_init_bpm);

    int get_units_abeat() const { return units_abeat; }

    void add_event(Ref<BpmEvent> p_event);
    bool remove_event(Ref<BpmEvent> p_event);
    void remove_event_at(int p_index);
    int get_event_index(double p_units) const;
    Ref<BpmEvent> get_event(double p_units) const;
    Ref<BpmEvent> get_event_at(int p_index) const;
    int size() const { return _events.size(); }

    void add_bpm(int p_units, double p_bpm);
    double get_bpm(double p_units) const;

    double get_secs(double p_units) const;
    double get_units(double p_secs) const;
    double get_beats(double p_secs) const { return get_units(p_secs) / units_abeat; }

    double to_units(double beats) const { return beats * units_abeat; }
    double to_beats(double units) const { return units / units_abeat; }

    void update_secs(int from);
};

} // namespace godot