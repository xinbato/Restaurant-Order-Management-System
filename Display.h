#pragma once
#include "role.h"
#include <string>

class Display {
public:
	Display();
	~Display();
	Role login();

	void menuManager();
	void menuEmployee();
	
};