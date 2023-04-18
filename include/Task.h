#pragma once
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <string>
#include <functional>

class Task {
public:
	Task(std::string taskName = "Task", uint16_t stackSize = 10000, uint8_t priority = 5);
	virtual ~Task();
	void setStackSize(uint16_t stackSize);
	void setPriority(uint8_t priority);
	void setName(std::string name);
	void setCore(BaseType_t coreId);
    void setFn(std::function<void()> fn);
	void start(void* taskData = nullptr);
	void stop();
	/**
	 * @brief Body of the task to execute.
	 *
	 * This function must be implemented in the subclass that represents the actual task to run.
	 * When a task is started by calling start(), this is the code that is executed in the
	 * newly created task.
	 *
	 * @param [in] data The data passed in to the newly started task.
	 */
	static void delay(int ms);

private:

	virtual void run(void* data); // Make run pure virtual
	xTaskHandle m_handle;
	void*       m_taskData;
	static void runTask(void* data);
	std::string m_taskName;
	uint16_t    m_stackSize;
	uint8_t     m_priority;
	BaseType_t  m_coreId;
    std::function<void()> m_fn;

};