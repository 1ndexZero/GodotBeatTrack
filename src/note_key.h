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
    Dictionary properties;

	int get_units() const { return units; }
	double get_displacement() const { return displacement; }
    Dictionary get_properties() const { return properties; }
    void set_properties(const Dictionary &p_value) { properties = p_value; }
};

} // namespace godot