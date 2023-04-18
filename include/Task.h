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
	bool isDone();
	
	static void delay(int ms);

private:

	virtual void run(void* data);
	xTaskHandle m_handle;
	void*       m_taskData;
	static void runTask(void* data);
	std::string m_taskName;
	uint16_t    m_stackSize;
	uint8_t     m_priority;
	BaseType_t  m_coreId;
    std::function<void()> m_fn;

};