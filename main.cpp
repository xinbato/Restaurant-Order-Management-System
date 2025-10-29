#include "Display.h"
#include "role.h"
#include "Manager.h"
#include "Employee.h"
#include <iostream>
using namespace std;
	Display Mydisplay;
	Manager manager; 
	Employee employee; 
void interFaceManager(Display& display, Manager& manager) {
	int choice = -1;
	do {
		display.menuManager();
		cin >> choice;
		switch (choice) {
		case 1: {
			manager.manageEmployees();
			break;
		}
		case 2: {
			manager.manageMenu();
			break;
		}
		case 3: {
			manager.manageOrders();
			break;
		}
		case 4: {
			manager.generateReports();
			break;
		}
		}

	}	while (choice != 0);
}
void interFaceEmployee(Display& display, Employee& employee) {
	int choice = -1;
	do {
		display.menuEmployee();
		cin >> choice;
		switch (choice) {
		case 1: {
			employee.viewAndSearch();
			break;
		}
		case 2: {
			employee.bookTable();
			break;
		}
		case 3: {
			employee.placeOrder();
			break;
		}
		case 4: {
			employee.cancelOrder();
			break;
		}
		}
	}	while (choice != 0);
}


int main() {
	
	Role role =	Mydisplay.login();
	switch (role) {
	case Role::MANAGER: {
		interFaceManager(Mydisplay, manager);
		Role role = Mydisplay.login();
	}
	case Role::EMPLOYEE: {
		interFaceEmployee(Mydisplay, employee);
		Role role = Mydisplay.login();
	}
	}
	return 0;
}