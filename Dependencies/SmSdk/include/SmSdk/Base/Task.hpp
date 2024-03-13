#pragma once

class Task
{
public:
	virtual ~Task() {}
	virtual __int64 update(float delta_time) { return 0; }

}; // Size: 0x8

static_assert(sizeof(Task) == 0x8, "Task: Incorrect Size");