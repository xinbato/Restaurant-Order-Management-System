#include "Employee.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;


void Employee::viewAndSearch() {

}

void Employee::placeOrder() {
	cout << "=== Order ===" << endl;
	vector<string> items;
	vector<double> prices;
	ifstream menuFile("menu.txt");//vị trí file menu
	string line;
	while (getline(menuFile, line)) {
		stringstream ss(line);
		string name, priceStr;
		getline(ss, name, ',');
		getline(ss, priceStr, ',');
		double price = stod(priceStr);
		items.push_back(name);
		prices.push_back(price);
	}
	menuFile.close();
	vector<int> quantity(items.size(), 0);
	int choice = -1;
	do {
		cout << "=== MENU ===" << endl;
		for (int i = 0; i < items.size(); i++) {
			cout << setw(2) << (i + 1) << ". " << items[i] << " (" << prices[i] << " VND)" << " [Da chon: " << quantity[i] << "]" << endl;
		}
		cout << "0. xac nhan" << endl;
		cout << "Chon mon an (1-" << items.size() << "): ";
		cin >> choice;
		if (choice >= 0 && choice <= items.size()) {
			int idex = choice - 1;
			cout << "So luong: ";
			int qty = 0;
			cin >> qty;
			if (idex >= 0 && idex < quantity.size()) {
				quantity[idex] += qty;
			}
		}
	} while (choice != 0);
	double total = 0.0;
	for (int i = 0; i < items.size(); i++) {
		total += prices[i] * quantity[i];
	}
	if (total > 0) {
		ofstream orderFile("orders.txt", ios::app);
		orderFile << total;
		for (int i = 0; i < items.size(); ++i) {
			if (quantity[i] > 0) {
				orderFile << items[i] << ", " << prices[i] << ", " << quantity[i] << endl;
			}
		}
		orderFile << "\n";
		orderFile.close();
		cout << ">> Tong tien: " << total << " VND" << endl;
	}
}
	

void Employee::bookTable() {
	cout << "=== Book Table ===" << endl;
	
}

void Employee::cancelOrder() {
	
}