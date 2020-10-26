#pragma once

#include <memory>
#include <mutex>
#include <libpq-fe.h>

class Establishconnect
{
public:
	Establishconnect();
	std::shared_ptr<PGconn> connection() const;
	static void set_m_dbhost(std::string str) {
		m_dbhost = str;
	}
	static void set_m_dbport(int port) {
		m_dbport = port;
	}
	static void set_m_dbname(std::string str) {
		m_dbname = str;
	}
	static void set_m_dbuser(std::string str) {
		m_dbuser = str;
	}
	static void set_m_dbpass(std::string str) {
		m_dbpass = str;
	}


private:

	static std::string m_dbhost;
	static int         m_dbport;
	static std::string m_dbname;
	static std::string m_dbuser;
	static std::string m_dbpass;

	std::shared_ptr<PGconn>  m_connection;

};
