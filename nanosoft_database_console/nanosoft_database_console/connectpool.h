#pragma once

#include <memory>
#include <mutex>
#include <string>
#include <queue>
#include <condition_variable>
#include <libpq-fe.h>
#include "establishconnect.h"


class Connectpool
{
public:
	Connectpool();
	std::shared_ptr<Establishconnect> connection();
	void freeConnection(std::shared_ptr<Establishconnect>);

private:
	void createPool();

	std::mutex m_mutex;
	std::condition_variable m_condition;
	std::queue<std::shared_ptr<Establishconnect>> m_pool;

	const int POOL = 25;


};
