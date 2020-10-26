#include <iostream>
#include <thread>
#include <fstream>
#include <sstream>
#include "connectpool.h"

Connectpool::Connectpool()
{

	createPool();

}

void Connectpool::createPool()
{
	std::lock_guard<std::mutex> locker_(m_mutex);

	for (auto i = 0; i < POOL; ++i) {
		m_pool.emplace(std::make_shared<Establishconnect>());
	}
}

std::shared_ptr<Establishconnect> Connectpool::connection()
{

	std::unique_lock<std::mutex> lock_(m_mutex);

	while (m_pool.empty()) {
		m_condition.wait(lock_);
	}

	auto conn_ = m_pool.front();
	m_pool.pop();

	return  conn_;
}


void Connectpool::freeConnection(std::shared_ptr<Establishconnect> conn_)
{
	std::unique_lock<std::mutex> lock_(m_mutex);
	m_pool.push(conn_);
	lock_.unlock();
	m_condition.notify_one();
}