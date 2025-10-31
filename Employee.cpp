#include "Employee.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <map>
using namespace std;


void Employee::viewAndSearch() {
    cout << "=== View and Search ===" << endl;

    ifstream menuFile("D:/menu.txt");
    if (!menuFile.is_open()) {
        cout << "Cannot open menu file!" << endl;
        return;
    }

    vector<string> items;
    vector<double> prices;
    string line;
    while (getline(menuFile, line)) {
        stringstream ss(line);
        string name, priceStr;
        getline(ss, name, ',');
        getline(ss, priceStr, ',');
        items.push_back(name);
        prices.push_back(stod(priceStr));
    }
    menuFile.close();

    cout << "\n--- All Items ---" << endl;
    for (int i = 0; i < items.size(); ++i) {
        cout << i + 1 << ". " << items[i] << " - " << prices[i] << " VND" << endl;
    }

    cout << "\nEnter keyword to search (press Enter to skip): ";
    cin.ignore();
    string keyword;
    getline(cin, keyword);

    if (!keyword.empty()) {
        cout << "\n--- Search Results ---" << endl;
        bool found = false;
        for (int i = 0; i < items.size(); ++i) {
            if (items[i].find(keyword) != string::npos) {
                cout << items[i] << " - " << prices[i] << " VND" << endl;
                found = true;
            }
        }
        if (!found)
            cout << "No results found.\n";
    }
}


void Employee::placeOrder() {
	cout << "=== Order ===" << endl;
	vector<string> items;
	vector<double> prices;
	ifstream menuFile("D:/menu.txt");//vị trí file menu
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
		ofstream orderFile("D:/orders.txt", ios::app);
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

	ifstream tableFile("table.txt");
	if (!tableFile.is_open()) {
		cout << "Cannot open table file!" << endl;
		return;
	}

	vector<int> tableNumbers;
	vector<string> tableStatus;

	string line;
	while (getline(tableFile, line)) {
		stringstream ss(line);
		string numStr, status;
		getline(ss, numStr, ',');
		getline(ss, status, ',');

		// Xóa khoảng trắng thừa
		numStr.erase(0, numStr.find_first_not_of(" \t"));
		numStr.erase(numStr.find_last_not_of(" \t") + 1);
		status.erase(0, status.find_first_not_of(" \t"));
		status.erase(status.find_last_not_of(" \t") + 1);

		tableNumbers.push_back(stoi(numStr));
		tableStatus.push_back(status);
	}
	tableFile.close();

	cout << "\n--- Danh sách ban ---" << endl;
	for (size_t i = 0; i < tableNumbers.size(); ++i) {
		cout << setw(2) << tableNumbers[i] << ". " << tableStatus[i] << endl;
	}

	cout << "\nNhap so ban muon dat: ";
	int tableChoice;
	cin >> tableChoice;

	if (tableChoice < 1 || tableChoice >(int)tableNumbers.size()) {
		cout << "Số bàn không hợp lệ!\n";
		return;
	}

	if (tableStatus[tableChoice - 1] != "Trong") {
		cout << "Bàn này đã được đặt rồi!\n";
		return;
	}

	// Đánh dấu bàn được đặt
	tableStatus[tableChoice - 1] = "Da dat";

	ofstream outFile("table.txt");
	for (size_t i = 0; i < tableNumbers.size(); ++i) {
		outFile << tableNumbers[i] << ", " << tableStatus[i] << endl;
	}
	outFile.close();

	cout << ">> Ban " << tableChoice << " da duoc dat thanh cong!\n";
}


void Employee::cancelOrder() {
	cout << "=== Cancel Order ===" << endl;
	ifstream orderFile("orders.txt");
	if (!orderFile.is_open()) {
		cout << "Cannot open orders file!" << endl;
		return;
	}
	string content((istreambuf_iterator<char>(orderFile)), (istreambuf_iterator<char>()));
	orderFile.close();
	ofstream tempFile("temp.txt");
	cout << "Enter order details to cancel: ";
	string orderDetails;
	cin.ignore();
	getline(cin, orderDetails);
	size_t pos = content.find(orderDetails);
	if (pos != string::npos) {
		content.erase(pos, orderDetails.length());
		tempFile << content;
		tempFile.close();
		remove("orders.txt");
		rename("temp.txt", "orders.txt");
		cout << "Order canceled successfully!" << endl;
	}
	else {
		cout << "Order not found!" << endl;
		tempFile.close();
		remove("temp.txt");
	}



}
void Employee::cancelTable() {
	cout << "=== Cancel Table Booking ===\n";

	ifstream f("table.txt");
	if (!f.is_open()) {
		cout << "Cannot open tables file!\n";
		return;
	}

	vector<string> num, status;
	string a, b, line;
	while (getline(f, line)) {
		stringstream ss(line);
		getline(ss, a, ',');
		getline(ss, b);
		if (!b.empty() && b[0] == ' ') b.erase(0, 1);
		num.push_back(a);
		status.push_back(b);
	}
	f.close();

	cout << "Booked Tables:\n";
	bool any = false;
	for (int i = 0; i < num.size(); i++)
		if (status[i] == "Da dat") {
			cout << "Table " << num[i] << '\n';
			any = true;
		}

	if (!any) {
		cout << "Không có bàn nào được đặt!\n";
		return;
	}

	cout << "Enter table number to cancel booking: ";
	string t; cin >> t;

	bool found = false;
	for (int i = 0; i < num.size(); i++) {
		if (num[i] == t) {
			if (status[i] == "Da dat") {
				status[i] = "Trong";
				found = true;
			}
			break;
		}
	}

	if (!found) {
		cout << "Invalid table number or table is not booked!\n";
		return;
	}

	ofstream o("table.txt");
	for (int i = 0; i < num.size(); i++)
		o << num[i] << ", " << status[i] << '\n';
	o.close();

	cout << "Table " << t << " booking canceled successfully!\n";
}
