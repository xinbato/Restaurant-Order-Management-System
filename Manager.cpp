#include "Manager.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;
void Manager::manageEmployees() {


}

void Manager::manageMenu() {


}

void Manager::manageOrders() {
	cout << endl;
	cout << "=== Manage Orders ===" << endl;
	ifstream orderFile("orders.txt");
	string line;
	int orderCount = 0;
	cout << "cac don hang" << endl;
	while (getline(orderFile, line)) {
		cout << "Don " << (orderCount + 1) << ": " << line << endl;
		orderCount++;
	}
	orderFile.close();
	cout << "Tong so don: " << orderCount << endl;
}

void Manager::generateReports() {
	cout << endl;
	cout << "=== Generate Reports ===" << endl;
	ifstream orderFile("orders.txt");
	string line;
	double totalRevenue = 0.0;
	int orderCount = 0;
	while (getline(orderFile, line)) {
		stringstream ss(line);
		string priceStr;
		getline(ss, priceStr, ',');
		totalRevenue += stod(priceStr);
		orderCount++;
	}
	orderFile.close();
	cout << "Tong so don hang: " << orderCount << endl;
	cout << "Tong doanh thu: " << totalRevenue << " VND" << endl;
}