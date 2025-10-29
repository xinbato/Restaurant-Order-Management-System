#include "Display.h"
#include <iostream>
#include <string>
using namespace std;

Display::Display() {}
Display::~Display() {}
Role Display::login() {
	string username, password;
	cout << "=== Restaurant Order Management System ===" << endl;
	cout << "Username: ";
	cin >> username;
	cout << "Password: ";
	cin >> password;
	if (username == "manager" && password == "1234") {
		cout << "System Manager" << endl;
		return Role::MANAGER;
	} 
	else if (username == "employee" && password == "1234") {
		cout << "System Employee" << endl;
		return Role::EMPLOYEE;
	}
	else {
		return Role::EXIT;
	}
	
}
void Display::menuManager() {
	cout << endl;
	cout << "=== Manager Menu ===" << endl;
	cout << "0. logout" << endl;
	cout << "1. Employee management" << endl;
	cout << "2. Menu management" << endl;
	cout << "3. Order management" << endl;
	cout << "4. Reports" << endl;
}
void Display::menuEmployee() {
	cout << endl;
	cout << "=== Employee Menu ===" << endl;
	cout << "0. logout" << endl;
	cout << "1. Search & check order" << endl;
	cout << "2. Book a table" << endl;
	cout << "3. Create order" << endl;
	cout << "4. Cancel order" << endl;
}