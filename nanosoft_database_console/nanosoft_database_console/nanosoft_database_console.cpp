// nanosoft_database_console.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <thread>
#include <iostream>
#include <string>
#include <regex>
#include "connectpool.h"
#include "establishconnect.h"
#include "connect_to_database.h" 

std::string Establishconnect::m_dbhost = "localhost";
int         Establishconnect::m_dbport = 5432;
std::string Establishconnect::m_dbname = "postgres";
std::string Establishconnect::m_dbuser = "postgres";
std::string Establishconnect::m_dbpass = "password";


int main(int argc, char const *argv[])
{
	std::string dbhost;
	int         dbport;
	std::string dbname;
	std::string dbuser;
	std::string dbpass; 

	std::cout << "Server [localhost]: ";
	std::cin >> dbhost;

	std::cout << "Port [5432]: ";
	std::cin >> dbport;

	std::cout << "Database: ";
	std::cin >> dbname;

	std::cout << "Username: ";
	std::cin >> dbuser;

	std::cout << "Password: ";
	std::cin >> dbpass;
	std::cout << std::endl << std::endl;
    
	Establishconnect::set_m_dbhost(dbhost);
	Establishconnect::set_m_dbport(dbport);
	Establishconnect::set_m_dbname(dbname);
	Establishconnect::set_m_dbuser(dbuser);
	Establishconnect::set_m_dbpass(dbpass);

	std::string request, command;
	std::smatch result; 
	bool first = true;
	auto connectpool = std::make_shared<Connectpool>();
	std::vector<std::shared_ptr<std::thread>> vec;
	
	while (true) {

		std::cout << "> ";
		getline(std::cin, command); 
		std::regex regular("([\\w]+)"
			"([\\s]*)"
			"([\\w]*)");
		std::regex_search(command, result, regular);
		if ((result.str(1) == "exit") && (result.str(3) == "")) {
			break;
		}
		if ((result.str(1) == "help") && (result.str(3) == "")) {
			std::cout << std::endl << "1. Execute reqursive query: gettree [block_id] // Example: gettree 2" << std::endl<< std::endl;
			std::cout << "2. Add a new tree item: newnode [node_id] [parent_id] // Example: newnode 11 10" << std::endl << std::endl;
			std::cout << "3. Add a new LOD and geometry chunk: newlod [node_id] [LOD] [geometry] // Example: newlod 5 567 '243abc'" << std::endl << std::endl;
			std::cout << "4. Add a new block: newblock [block_id] [node_id] [depth] // Example: newblock 4 3 4" << std::endl << std::endl;
			std::cout << "5. Remove tree item: deletenode [node_id] // Example: deletenode 3" << std::endl << std::endl;
			std::cout << "6. Remove LOD and geometry chunk: deletelod [LOD] // Example: deletelod 23" << std::endl << std::endl;
			std::cout << "7. Remove block: deleteblock [block_id] // Example: deleteblock 3" << std::endl << std::endl;
			std::cout << "8. Exit the application: exit" << std::endl << std::endl;
		}

		else if (result.str(1) == "gettree") {
			std::regex regular("([\\w]+)"
				"([\\s]+)"
				"([\\d]+)");
			std::regex_search(command, result, regular);
			
			request = "SELECT * FROM tree_output(";
			request += result.str(3);
			request += ");";

			vec.push_back(std::make_shared<std::thread>(std::thread(Connect_to_database, connectpool, request)));  
			connectpool = std::make_shared<Connectpool>(); 
			
        }

		else if (result.str(1) == "newnode") {
			std::regex regular("([\\w]+)"
				"([\\s]+)"
				"([\\d]+)"
				"([\\s]+)"
				"([\\d]+)");
			std::regex_search(command, result, regular);

			request = "CALL create_new_node(";
			request += result.str(3);
			request += ",";
			request += result.str(5);
			request += ");";

			vec.push_back(std::make_shared<std::thread>(std::thread(Connect_to_database, connectpool, request))); 
			connectpool = std::make_shared<Connectpool>();

		}

		else if (result.str(1) == "newlod") {
			std::regex regular("([\\w]+)"
				"([\\s]+)"
				"([\\d]+)"
				"([\\s]+)"
				"([\\d]+)"
				"([\\s]+)"
				"(')"
				"([\\w]+)"
			     "(')");
			std::regex_search(command, result, regular);

			request = "CALL create_new_geometry(";
			request += result.str(3);
			request += ",";
			request += result.str(5);
			request += ",'";
			request += result.str(8);
			request += "');";

			vec.push_back(std::make_shared<std::thread>(std::thread(Connect_to_database, connectpool, request)));
			connectpool = std::make_shared<Connectpool>(); 

		}

		else if (result.str(1) == "newblock") {
			std::regex regular("([\\w]+)"
				"([\\s]+)"
				"([\\d]+)"
				"([\\s]+)"
				"([\\d]+)"
				"([\\s]+)"
				"([\\d]+)");
			std::regex_search(command, result, regular);

			request = "CALL create_new_block(";
			request += result.str(3);
			request += ",";
			request += result.str(5);
			request += ",";
			request += result.str(7);
			request += ");";

			vec.push_back(std::make_shared<std::thread>(std::thread(Connect_to_database, connectpool, request)));
			connectpool = std::make_shared<Connectpool>();

		}

		else if (result.str(1) == "deletenode") {
			std::regex regular("([\\w]+)"
				"([\\s]+)"
				"([\\d]+)");
			std::regex_search(command, result, regular);

			request = "CALL delete_node(";
			request += result.str(3);
			request += ");";

			vec.push_back(std::make_shared<std::thread>(std::thread(Connect_to_database, connectpool, request)));
			connectpool = std::make_shared<Connectpool>();

		}

		else if (result.str(1) == "deletelod") {
			std::regex regular("([\\w]+)"
				"([\\s]+)"
				"([\\d]+)");
			std::regex_search(command, result, regular);

			request = "CALL delete_geometry(";
			request += result.str(3);
			request += ");";

			vec.push_back(std::make_shared<std::thread>(std::thread(Connect_to_database, connectpool, request)));
			connectpool = std::make_shared<Connectpool>();

		}

		else if (result.str(1) == "deleteblock") {
			std::regex regular("([\\w]+)"
				"([\\s]+)"
				"([\\d]+)");
			std::regex_search(command, result, regular);

			request = "CALL delete_block(";
			request += result.str(3);
			request += ");";

			vec.push_back(std::make_shared<std::thread>(std::thread(Connect_to_database, connectpool, request)));
			connectpool = std::make_shared<Connectpool>();

		}

		else if (first != true) {
			std::cout << "Command not found" << std::endl;
        }

		first = false;
		std::cout << std::endl;
	}

	for (auto &i : vec) {
		i.get()->join();
	}


	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
