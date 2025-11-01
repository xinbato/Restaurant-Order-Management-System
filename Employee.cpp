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

    ifstream menuFile("menu.txt");
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
	ifstream menuFile("menu.txt");
	string line;
	while (getline(menuFile, line)) {
		if (line.empty()) continue; 
		stringstream ss(line);
		string name, priceStr;
		getline(ss, name, ',');
		getline(ss, priceStr, ',');
		try { 
			double price = stod(priceStr);
			items.push_back(name);
			prices.push_back(price);
		}
		catch (...) {
			cout << "Warning: Bo qua mon do dinh dang gia bi loi." << endl;
		}
	}
	menuFile.close();
	vector<int> quantity(items.size(), 0);
	int choice = -1;
	do {
		cout << "\n=== MENU ===" << endl;
		for (size_t i = 0; i < items.size(); i++) { 
			cout << setw(2) << (i + 1) << ". " << items[i] << " (" << prices[i] << " VND)" << " [Da chon: " << quantity[i] << "]" << endl;
		}
		cout  << endl;
		cout << "0. Xac nhan" << endl;
		cout << "Chon mon an (1-" << items.size() << "): ";

		if (!(cin >> choice)) {
			cout << "Loi: Vui long nhap mot SO." << endl;
			cin.clear(); 
			cin.ignore(std::numeric_limits<streamsize>::max(), '\n'); 
			choice = -1; 
			continue;  
		}
		if (choice == 0) {
			break; 
		}
		if (choice > 0 && choice <= static_cast<int>(items.size())) {
			int index = choice - 1; 
			cout << "So luong cho " << items[index] << ": ";
			int qty = 0;
			if (!(cin >> qty)) {
				cout << "Loi: So luong khong hop le." << endl;
				cin.clear();
				cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
				continue; 
			}
			if (qty > 0) {
				quantity[index] += qty;
				cout << "-> Da them " << qty << " " << items[index] << "." << endl;
			}
			else {
				cout << "-> So luong khong hop le. Khong them." << endl;
			}
		}
		else {
			cout << "Loi: Lua chon khong hop le. Vui long chon tu 0 den " << items.size() << "." << endl;
		}

	} while (choice != 0);

		double total = 0.0;
	for (size_t i = 0; i < items.size(); i++) {
		total += prices[i] * quantity[i];
	}
	if (total > 0) {
		cout << "\n=== Xac nhan don hang ===" << endl;
		ofstream orderFile("orders.txt", ios::app);
		orderFile << total; 
		for (size_t i = 0; i < items.size(); ++i) {
			if (quantity[i] > 0) {
				
				orderFile << "," << items[i] << " x" << quantity[i];
			}
		}
		orderFile << "\n";
		orderFile.close();

		cout << "Don hang da duoc ghi lai." << endl;
		cout << ">> Tong tien: " << total << " VND" << endl;
	}
	else {
		cout << "Don hang rong. Da huy." << endl;
	}
}
	


void Employee::bookTable() {
    cout << "=== Book Table ===\n";
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
        if (!b.empty() && b[0] == ' ') b.erase(0, 1);// xoá dấu cách dư
        num.push_back(a);
        status.push_back(b);
    }
    f.close();
    cout << "Available Tables:\n";
    bool any = false;
    for (int i = 0; i < num.size(); i++)
        if (status[i] == "Trong") {
            cout << "Table " << num[i] << ", " << status[i] << '\n';
            any = true;
        }

    if (!any) {
        cout << "Không còn bàn trống!\n";
        return;
    }
    cout << "Enter table number to book: ";
    string t; cin >> t;
    bool booked = false;
    for (int i = 0; i < num.size(); i++) {
        if (num[i] == t) {
            if (status[i] == "Trong") {
                status[i] = "Da dat";
                booked = true;
            }
            break;
        }
    }
    if (!booked) {
        cout << "Invalid table number or table already booked!\n";
        return;
    }
    ofstream o("table.txt");
    for (int i = 0; i < num.size(); i++)
        o << num[i] << ", " << status[i] << '\n';
    o.close();
    cout << "Table " << t << " booked successfully!\n";
}


void Employee::cancelOrder() {
	cout << "=== Cancel Order ===\n";
	ifstream f("orders.txt");
	if (!f.is_open()) {
		cout << "Cannot open orders file!\n";
		return;
	}
	vector<string> orders;
	string line, current;
	while (getline(f, line)) {
		if (line.empty()) {
			if (!current.empty()) {
				orders.push_back(current);
				current.clear();
			}
		}
		else {
			current += line + "\n";
		}
	}
	if (!current.empty()) orders.push_back(current);
	f.close();

	if (orders.empty()) {
		cout << "No orders found!\n";
		return;
	}
	cout << "\n--- All Orders ---\n";
	for (int i = 0; i < orders.size(); i++) {
		cout << "Order #" << (i + 1) << ":\n" << orders[i] << '\n';
		cout << "------------------------\n";
	}
	cout << "Enter order number to cancel (0 to exit): ";
	int choice;
	cin >> choice;

	if (choice == 0) {
		cout << "Canceled.\n";
		return;
	}
	if (choice < 1 || choice > orders.size()) {
		cout << "Invalid order number!\n";
		return;
	}
	orders.erase(orders.begin() + (choice - 1));
	ofstream o("orders.txt");
	for (int i = 0; i < orders.size(); i++) {
		o << orders[i] << "\n";
	}
	o.close();
	cout << "Order #" << choice << " canceled successfully!\n";
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
