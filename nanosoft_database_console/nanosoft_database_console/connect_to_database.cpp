#include <thread>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include "connectpool.h"
#include "establishconnect.h"
#include "connect_to_database.h"

void Connect_to_database(std::shared_ptr<Connectpool> connectpool, std::string request)
{
	auto conn = connectpool->connection();
	int nFields;

	PQsendQuery(conn->connection().get(), request.c_str());

	while (auto res_ = PQgetResult(conn->connection().get())) {
		if (PQresultStatus(res_) == PGRES_TUPLES_OK && PQntuples(res_)) {
			std::cout << std::endl;
			nFields = PQnfields(res_);
			for (int i = 0; i < nFields; i++)
				printf("%-15s", PQfname(res_, i));
			printf("\n\n");

		
			for (int i = 0; i < PQntuples(res_); i++) {
			
				for (int j = 0; j < nFields; j++)
					printf("%-15s", PQgetvalue(res_, i, j));
				printf("\n");
			}
		}

		if (PQresultStatus(res_) == PGRES_FATAL_ERROR) {
			std::cout << PQresultErrorMessage(res_) << std::endl;
		}
		
		std::cout << std::endl << "status: " << PQcmdStatus(res_) << std::endl;

		PQclear(res_);
	}

	connectpool->freeConnection(conn);

}