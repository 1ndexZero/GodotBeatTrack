# GodotBeatTrack

[English](README.md)

Godot 4 的节奏游戏音符轨道扩展（GDExtension / godot-cpp），提供 BPM 事件、变速事件与音符管理。

**需要 Godot 4.7 或更高版本。**

## 快速示例

以下示例演示创建 `NoteTrack`，并在此基础上使用 `add_note`、`add_speed`、`add_bpm`、`get_speed`、`get_bpm`：

```gdscript
extends Node

func _ready() -> void:
	# 1. 创建事件列表
	#    BpmEventList.create(初始BPM, 每拍units数)
	var bpm_events := BpmEventList.create(120.0, 4)
	#    SpeedEventList.create(初始速度, BPM事件列表)
	var speed_events := SpeedEventList.create(100.0, bpm_events)

	# 2. 创建 NoteTrack
	var track := NoteTrack.create(bpm_events, speed_events)

	# 3. 添加 BPM 变化
	#    add_bpm(起始units, BPM)
	track.add_bpm(0, 120.0)
	track.add_bpm(64, 150.0)

	# 4. 添加变速事件
	#    add_speed(起始units, 结束units, 起始速度, 结束速度)
	track.add_speed(0, 64, 100.0, 100.0)   # 匀速
	track.add_speed(64, 128, 50.0, 200.0)  # 加速

	# 5. 添加音符
	#    NoteKey.create(所在units)
	track.add_note(NoteKey.create(0))
	track.add_note(NoteKey.create(32))
	track.add_note(NoteKey.create(96))

	# 6. 查询
	#    get_bpm(units) -> 该位置的BPM
	print(track.get_bpm_events().get_bpm(32))    # 120.0
	print(track.get_bpm_events().get_bpm(96))    # 150.0

	#    get_speed(secs) -> 该秒数的滚动速度
	var secs := get_bpm_events().get_secs(32)
	print(track.get_speed_events().get_speed(secs))  # 100.0

	# 音符按units有序，可按下标或units访问
	print(track.size())                      # 3
	print(track.get_note_at(1).get_units())  # 32
```

## 核心类

- `BpmEventList`：BPM 变化列表，负责 units ↔ 秒（secs）换算。`get_bpm(units)` 查询指定位置的 BPM。
- `SpeedEventList`：变速事件列表，负责秒 ↔ 位移（displacement）换算。`get_speed(secs)` 查询指定秒数的速度。
- `NoteTrack`：音符轨道，组合上述两个列表。通过 `add_note` / `add_bpm` / `add_speed` 添加数据，事件变更后自动更新音符位移。
- `NoteKey`：单个音符，包含 `units`（时间位置）、`displacement`（空间位置）与自定义 `properties`。
- `BpmEvent` / `SpeedEvent`：单个 BPM / 变速事件，可用 `create(...)` 构造后经 `add_bpm_event` / `add_speed_event` 加入。
