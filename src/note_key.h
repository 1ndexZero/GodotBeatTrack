#pragma once

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/ref_counted.hpp>

namespace godot {

class NoteKey : public RefCounted {
	GDCLASS(NoteKey, RefCounted)

protected:
	static void _bind_methods();

public:
    NoteKey() = default;
    static Ref<NoteKey> create(int p_units);

    int units;
    double displacement;   

	int get_units() const { return units; }
	double get_displacement() const { return displacement; }
};

} // namespace godot