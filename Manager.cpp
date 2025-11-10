#include "Manager.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <limits>
using namespace std;

void Manager::manageEmployees() {
 cout << "=== Manage Employees ===" << endl;
 vector<vector<string>> employees;

 ifstream fileIn("employees.txt");
 string line;
 while (getline(fileIn, line)) {
  stringstream ss(line);
  vector<string> data;
  string field;
  while (getline(ss, field, ',')) data.push_back(field);
  employees.push_back(data);
 }
 fileIn.close();

 int choice;
 do {
     cout << "\n1. View Employees\n2. Add Employee\n3. Remove Employee\n0. Back\nChoice: ";
     cin >> choice;
     cin.ignore();

     if (choice == 1) {
         cout << "\n--- Employee List ---" << endl;
         for (auto& emp : employees) {
             if (emp.size() >= 3)
                 cout << "ID: " << emp[0] << " | Name: " << emp[1] << " | Phone: " << emp[2] << endl;
         }
     }
     else if (choice == 2) {
         string id, name, phone;
         cout << "Enter ID: "; getline(cin, id);
         //dieu chinh: da them kiem tra ID trung lap
         while (true) {
             bool isDuplicate = false;
             for (const auto& emp : employees) {
                 if (emp[0] == id) {
                     isDuplicate = true;
                     break;
                 }
             }

             if (isDuplicate) {
                 cout << "Error:ID already exists, enter another ID\n";
                 cout << "Enter ID: "; getline(cin, id);
             }
             else {
                 break;
             }
         }
         cout << "Enter Name: "; getline(cin, name);
         cout << "Enter Phone: "; getline(cin, phone);
         employees.push_back({ id, name, phone });
         cout << "Employee added successfully.\n";
     }

  else if (choice == 3) {
   string id;
   cout << "Enter ID to remove: ";
   getline(cin, id);
   auto it = remove_if(employees.begin(), employees.end(),
    [&](vector<string>& e) { return e[0] == id; });
   if (it != employees.end()) {
    employees.erase(it, employees.end());
    cout << "Removed.\n";
   }
   else cout << "Employee not found.\n";
  }

 } while (choice != 0);

 ofstream fileOut("employees.txt");
 for (auto& emp : employees) {
  fileOut << emp[0] << "," << emp[1] << "," << emp[2] << "\n";
 }
 fileOut.close();
}

void Manager::manageMenu() {
 cout << "=== Manage Menu ===" << endl;
 vector<pair<string, double>> menu;
 string line;

 ifstream fileIn("menu.txt");
 while (getline(fileIn, line)) {
  stringstream ss(line);
  string name, priceStr;
  getline(ss, name, ',');
  getline(ss, priceStr, ',');
  menu.push_back({ name, stod(priceStr) });
 }
 fileIn.close();

 int choice;
 do {
  cout << "\n1. View Menu\n2. Add Dish\n3. Update Price\n4. Remove Dish\n0. Back\nChoice: ";
  cin >> choice;
  cin.ignore();

  if (choice == 1) {
   for (auto& m : menu)
    cout << m.first << " - " << m.second << " VND" << endl;
  }
  else if (choice == 2) {
      string name; double price;
      cout << "Enter Dish Name: "; getline(cin, name);
      // dieu chinh: da them kiem tra mon an trung lap
      bool isDuplicate = false;
      for (const auto& m : menu) {
          if (m.first == name) {
              isDuplicate = true;
              break;
          }
      }
      if (isDuplicate) {
          cout << "Error: Dish already exists, import another dish." << endl;
      }
      else {
          cout << "Enter Price: "; cin >> price;
          menu.push_back({ name, price });
          cout << "Dish added.\n";
      }
  }
   else if (choice == 3) {
       string name;
       cout << "Enter Dish to Update: "; getline(cin, name);
       bool found = false;
       for (auto& m : menu) {
    if (m.first == name) {
     cout << "New Price: "; cin >> m.second;
     found = true;
     break;
    }
   }
   if (!found) cout << "Dish not found.\n";
  }
  else if (choice == 4) {
   string name;
   cout << "Enter Dish to Remove: "; getline(cin, name);
   auto it = remove_if(menu.begin(), menu.end(),
    [&](pair<string, double>& d) { return d.first == name; });
   if (it != menu.end()) {
    menu.erase(it, menu.end());
    cout << "Removed.\n";
   }
   else cout << "Dish not found.\n";
  }

 } while (choice != 0);

 ofstream fileOut("menu.txt");
 for (auto& m : menu)
  fileOut << m.first << "," << m.second << ",\n";
 fileOut.close();
}


void Manager::manageOrders() {
	cout << endl;
	cout << "=== Manage Orders ===" << endl;
	ifstream orderFile("orders.txt");
	string line;
	int orderCount = 0;
	while (getline(orderFile, line)) {
		if (!line.empty()) {
			orderCount++;
			cout << "Order " << orderCount << ": " << line << endl;
		}
	}
	orderFile.close();
	cout << "Total orders: " << orderCount << endl;
}

void Manager::generateReports() {
	cout << endl;
	cout << "=== Generate Reports ===" << endl;
	ifstream orderFile("orders.txt");
	string line;
	double totalRevenue = 0.0;
	int orderCount = 0;
	int lineCounter = 0;
    while (getline(orderFile, line)) {
        lineCounter++;
        if (line.empty()) {
            continue;
        }
        stringstream ss(line);
        string priceStr;
        getline(ss, priceStr, ',');

        try {
            totalRevenue += std::stod(priceStr);
        }
        catch (const exception& e) {
            cout << "Warning: Could not parse revenue on line " << lineCounter
                << ". Content: \"" << line << "\"" << endl;
        }
        orderCount++;
    }
	orderFile.close();
	cout << "Total orders: " << orderCount << endl;
	cout << "Total revenue: " << totalRevenue << " VND" << endl;
}






