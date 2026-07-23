# GodotBeatTrack

[中文文档](README.zh-CN.md)

A rhythm-game note track extension for Godot 4 (GDExtension / godot-cpp), providing BPM events, speed-change events and note management.

**Requires Godot 4.7 or later.**

## Build

```bash
build.bat
# i.e. scons platform=windows target=template_debug
```

Build artifacts are output to `demo/addons/beat_track/bin/`.

## Quick Example

The following example shows how to create a `NoteTrack` and use `add_note`, `add_speed`, `add_bpm`, `get_speed`, `get_bpm` on top of it:

```gdscript
extends Node

func _ready() -> void:
	# 1. Create event lists
	#    BpmEventList.create(initial BPM, units per beat)
	var bpm_events := BpmEventList.create(120.0, 4)
	#    SpeedEventList.create(initial speed, BPM event list)
	var speed_events := SpeedEventList.create(100.0, bpm_events)

	# 2. Create the NoteTrack
	var track := NoteTrack.create(bpm_events, speed_events)

	# 3. Add BPM changes
	#    add_bpm(units, BPM)
	track.add_bpm(0, 120.0)
	track.add_bpm(64, 150.0)

	# 4. Add speed events
	#    add_speed(units_start, units_end, speed_start, speed_end)
	track.add_speed(0, 64, 100.0, 100.0)   # constant speed
	track.add_speed(64, 128, 50.0, 200.0)  # accelerating

	# 5. Add notes
	#    NoteKey.create(units)
	track.add_note(NoteKey.create(0))
	track.add_note(NoteKey.create(32))
	track.add_note(NoteKey.create(96))

	# 6. Query
	#    get_bpm(units) -> BPM at the given units
	print(track.bpm_events.get_bpm(32))    # 120.0
	print(track.bpm_events.get_bpm(96))    # 150.0

	#    get_speed(secs) -> scroll speed at the given seconds
	var secs := bpm_events.get_secs(32)
	print(track.speed_events.get_speed(secs))  # 100.0

	# Notes are ordered by units; access by index or units
	print(track.size())                      # 3
	print(track.get_note_at(1).get_units())  # 32
```

## Core Classes

- `BpmEventList`: BPM change list; converts between units and seconds. `get_bpm(units)` returns the BPM at a position.
- `SpeedEventList`: speed change list; converts between seconds and displacement. `get_speed(secs)` returns the speed at a time.
- `NoteTrack`: note track combining the two lists above. Add data via `add_note` / `add_bpm` / `add_speed`; note displacements update automatically when events change.
- `NoteKey`: a single note with `units` (time position), `displacement` (spatial position) and custom `properties`.
- `BpmEvent` / `SpeedEvent`: single BPM / speed event; construct with `create(...)` and add via `add_bpm_event` / `add_speed_event`.
