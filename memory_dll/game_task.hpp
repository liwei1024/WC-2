#pragma once

void TraverseAllTaskInfo(DWORD &start_address,size_t &task_count)
{
	start_address = read_offset<DWORD>(__任务基址, { 104 });
	start_address = (read_offset<size_t>(__任务基址, { 108 }) - start_address) / 4;
}

void TraverseReceivedTaskInfo(DWORD &start_address, DWORD &task_count)
{
	start_address = read_offset<DWORD>(__任务基址, { 8 });
	start_address = (read_offset<DWORD>(__任务基址, { 12 }) - start_address) / 12;
}

TASK_STRUCT TraverseTaskObject(DWORD ObjectPointer)
{
	TASK_STRUCT task;
	if (ObjectPointer != 0)
	{
		task.address = ObjectPointer;
		task.task_id = read<int>(ObjectPointer);
		task.type = read<DWORD>(ObjectPointer + 308);
		task.copy_id = read<int>(read<DWORD>(ObjectPointer + 0x2B8));
		task.materials = read<int>(ObjectPointer + 1428); //材料
		task.task_length = read<int>(ObjectPointer + 28);
		task.condition_type = read_wstring(read<DWORD>(ObjectPointer + 720), 100);
		if (task.task_length > 7)
		{
			task.name = read_wstring(read<DWORD>(ObjectPointer + 8), 100);
		}
		else {

			task.name = read_wstring(ObjectPointer + 8, 100);
		}
	}

	return task;
}


bool task_is_jump_over()
{

}

bool task_is_received()
{

}

void auto_master_task()
{
	DWORD task_start_address;
	size_t task_count;
	TASK_STRUCT task;
	TraverseAllTaskInfo(task_start_address, task_count);
	for (size_t i = 0; i < task_count; i++)
	{
		task = TraverseTaskObject(read<DWORD>(task_start_address + i * 4));

		if (
			task.copy_id > 0 &&
			task.完成次数 > 0 &&
			task.condition_type != L"'[quest clear]'"
			)
		{

		}
	}
}