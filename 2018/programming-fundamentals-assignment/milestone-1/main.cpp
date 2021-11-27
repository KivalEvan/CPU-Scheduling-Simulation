#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

//	DEFINING DISPLAY, MENU, AND CHECK FUNCTIONS
void display_record(),
	 display_menu(),
	 display_record_update(),
	 display_record_delete(),
	 display_record_display(),
	 record_new(),
	 record_update(),
	 record_delete(),
	 record_display(),
	 set_item_id(),
	 set_item_category(),
	 set_item_manufacturer(),
	 set_item_name(),
	 set_item_description(),
	 set_unit_store(),
	 set_unit_sold(),
	 set_price_sell(),
	 set_price_cost(),
	 set_introduced_year(),
	 set_introduced_month(),
	 set_introduced_day();
int menu_get_choice();

//	DATA USING GLOBAL VARIABLES FOR EASIER ACCESS AND MANAGEMENT
string item_id = "-1",
	   item_name = "-1",
	   item_description = "-1",
	   item_category = "-1",
	   item_manufacturer = "-1",
	   introduced_month = "-1";
int unit_store = -1,
	unit_sold = -1,
	introduced_year = -1,
	introduced_day = -1;
double price_sell = -1,
	   price_cost = -1;
bool display_item_id = true,
	 display_item_category = true,
	 display_item_manufacturer = true,
	 display_item_name = true,
	 display_item_description = true,
	 display_unit_store = true,
	 display_unit_sold = true,
	 display_price_sell = true,
	 display_price_cost = true,
	 display_introduced_year = true,
	 display_introduced_month = true,
	 display_introduced_day = true;

//	MAIN PROGRAM STARTS HERE
int main()
{
	int choice;
	
	cout << "\n\n\n";
	while (true)
	{
		display_record();
		display_menu();				//	DISPLAYS DATA AND MENU
		
		choice = menu_get_choice();
		
		if (choice == 1)
			record_new();			//	(RE)CREATES NEW DATA COMPLETELY
		else if (choice == 2)
			record_update();		//	UPDATES/CHANGES SPECIFIC DATA
		else if (choice == 3)
			record_delete();		//	DELETES SPECIFIC DATA TO -1
		else if (choice == 5)
			record_display();		//	SHOWS/HIDES SPECIFIC DATA
		else if (choice == 0)
		{							//	SELF-EXPLANATORY; CLOSES THE PROGRAM
			cout << "\n\n\nExiting the program...";
			break;
		}
		
		cout << "\n\n\n\n\n\n";
	}
	
	return 0;
}

//	PRINTS THE ENTIRE DATA FIELD; WILL NOT DISPLAY SPECIFIC DATA IF GIVEN FALSE STATEMENT
void display_record()
{
	cout << fixed << setprecision(2);
	cout << "     IT Store Inventory -- Item Record\n"
			"==|| ( Item Details ) ||================================\\\\\n";
	if (display_item_id == true)
		cout << "             Code : " << item_id << endl;
	if (display_item_category == true)
		cout << "         Category : " << item_category << endl;
	if (display_item_name == true)
		cout << "             Name : " << item_name << endl;
	if (display_item_manufacturer == true)
		cout << "     Manufacturer : " << item_manufacturer << endl;
	if (display_item_description == true)
		cout << "      Description : " << item_description << endl;
	if (display_unit_store == true)
		cout << "    Unit in Store : " << unit_store << endl;
	if (display_unit_sold == true)
		cout << "        Unit Sold : " << unit_sold << endl;
	if (display_price_cost == true)
		cout << " Price (Cost)(RM) : " << price_cost << endl;
	if (display_price_sell == true)
		cout << " Price (Sell)(RM) : " << price_sell << endl;
	if (display_introduced_year == true)
		cout << "   Year of Intro. : " << introduced_year << endl;
	if (display_introduced_month == true)
		cout << "  Month of Intro. : " << introduced_month << endl;
	if (display_introduced_day == true)
		cout << "    Day of Intro. : " << introduced_day << endl;
	cout << "========================================================//\n"
			"  ( -1 value indicates null or no value )\n";
}

//	PRINTS MENU SCREEN AS NAVIGATION GUIDE FOR USER
void display_menu()
{
	cout << "\nInventory management program -- IT section\n"
			"   [1] New Record\n"
			"   [2] Update Record\n" 
			"   [3] Delete Specific Data\n\n"
			"   [5] Display Specific Data\n\n"
			"   [0] Exit Program\n";
}

void display_record_update()
{
	cout << fixed << setprecision(2);
	cout << "\nInventory management program -- Update data field(s)\n"
			"   [1]             Code  >>  " << item_id << "\n"
			"   [2]         Category  >>  " << item_category << "\n"
			"   [3]             Name  >>  " << item_name << "\n"
			"   [4]     Manufacturer  >>  " << item_manufacturer << "\n"
			"   [5]      Description  >>  " << item_description << "\n"
			"   [6]    Unit in Store  >>  " << unit_store << "\n"
			"   [7]        Unit Sold  >>  " << unit_sold << "\n"
			"   [8] Price (Cost)(RM)  >>  " << price_cost << "\n"
			"   [9] Price (Sell)(RM)  >>  " << price_sell << "\n"
			"  [10]   Year of Intro.  >>  " << introduced_year << "\n"
			"  [11]  Month of Intro.  >>  " << introduced_month << "\n"
			"  [12]    Day of Intro.  >>  " << introduced_day << "\n\n"
			"   [0] Back\n\n";
}

void display_record_delete()
{
	cout << fixed << setprecision(2);
	cout << "\nInventory management program -- Delete data field(s)\n"
			"   [1]             Code  >>  " << item_id << "\n"
			"   [2]         Category  >>  " << item_category << "\n"
			"   [3]             Name  >>  " << item_name << "\n"
			"   [4]     Manufacturer  >>  " << item_manufacturer << "\n"
			"   [5]      Description  >>  " << item_description << "\n"
			"   [6]    Unit in Store  >>  " << unit_store << "\n"
			"   [7]        Unit Sold  >>  " << unit_sold << "\n"
			"   [8] Price (Cost)(RM)  >>  " << price_cost << "\n"
			"   [9] Price (Sell)(RM)  >>  " << price_sell << "\n"
			"  [10]   Year of Intro.  >>  " << introduced_year << "\n"
			"  [11]  Month of Intro.  >>  " << introduced_month << "\n"
			"  [12]    Day of Intro.  >>  " << introduced_day << "\n\n"
			"   [0] Back\n\n";
}

void display_record_display()
{
	cout << fixed << setprecision(2);
	cout << "\nInventory management program -- Display data field(s)\n"
			"   [1]             Code  >>  " << display_item_id << "\n"
			"   [2]         Category  >>  " << display_item_category << "\n"
			"   [3]             Name  >>  " << display_item_name << "\n"
			"   [4]     Manufacturer  >>  " << display_item_manufacturer << "\n"
			"   [5]      Description  >>  " << display_item_description << "\n"
			"   [6]    Unit in Store  >>  " << display_unit_store << "\n"
			"   [7]        Unit Sold  >>  " << display_unit_sold << "\n"
			"   [8] Price (Cost)(RM)  >>  " << display_price_cost << "\n"
			"   [9] Price (Sell)(RM)  >>  " << display_price_sell << "\n"
			"  [10]   Year of Intro.  >>  " << display_introduced_year << "\n"
			"  [11]  Month of Intro.  >>  " << display_introduced_month << "\n"
			"  [12]    Day of Intro.  >>  " << display_introduced_day << "\n"
			"                         1 -- Displayed\n"
			"                         0 -- Hidden\n"
			"   [0] Back\n\n";
}

//	GETS AN INPUT FROM THE USER THEN RETURN AN INPUT INTO A VARIABLE
int menu_get_choice()
{
	int input = 0;
	
	while (true)
	{
		cout << "\nEnter number from the bracket to navigate: ";
		cin >> input;
		if (cin.fail())					//	AN ERROR CHECK, IN CASE OF NON-INTEGER VALUE ENTERED
		{
			cout << "Input error!\n"
					"Please enter an integer.\n";
			cin.clear();
			cin.ignore(80, '\n');		//	CLEARS INPUT COMPLETELY
		}
		else
			break;
	}
	switch (input)
	{
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 5:
			break;
		case 0:
			break;
		default:
			cout << "Input error!\nPut the number given in the bracket.\n";
	}
	
	return input;
}

//	USER MUST INPUT ALL OF THE DATA PROMPTED
void record_new()
{
	cout << "\n\n\n\n\n\n  -- Entering New Record --";
	set_item_id();
	set_item_category();
	set_item_name();
	set_item_manufacturer();
	set_item_description();
	set_unit_store();
	set_unit_sold();
	set_price_cost();
	set_price_sell();
	set_introduced_year();
	set_introduced_month();
	set_introduced_day();
}

//	ALLOWS THE USER TO UPDATES/CHANGES SPECIFIC DATA
void record_update()
{
	int input = -1;
	while (input != 0)
		{
		display_record();
		display_record_update();
		
		while (true)
		{
			cout << "Enter number from the bracket to update specific data: ";
			cin >> input;
			if (cin.fail())
			{
				cout << "Input error!\n"
						"Please enter an integer.\n";
				cin.clear();
				cin.ignore(80, '\n');
			}
			else
				break;
		}
		switch(input)
		{
			case 1:
				set_item_id();
				break;
			case 2:
				set_item_category();
				break;
			case 3:
				set_item_name();
				break;
			case 4:
				set_item_manufacturer();
				break;
			case 5:
				set_item_description();
				break;
			case 6:
				set_unit_store();
				break;
			case 7:
				set_unit_sold();
				break;
			case 8:
				set_price_cost();
				break;
			case 9:
				set_price_sell();
				break;
			case 10:
				set_introduced_year();
				break;
			case 11:
				set_introduced_month();
				if (introduced_day > 28)
					introduced_day = 28;
				break;
			case 12:
				set_introduced_day();
				break;
			case 0:
				break;
			default:
				cout << "Input error!\nPut the number given in the bracket.\n";
				record_update();
		}
	}
}

//	ALLOWS THE USER TO DELETE SPECIFIC DATA (CHANGES THE VALUE TO -1).
void record_delete()
{
	int input = -1;
	while (input != 0)
	{
	display_record();
	display_record_delete();
	
	while (true)
		{
			cout << "Deleting the data will turn the value to -1.\n"
					"Enter number from the bracket to delete specific data: ";
			cin >> input;
			if (cin.fail())
			{
				cout << "Input error!\n"
						"Please enter an integer.\n";
				cin.clear();
				cin.ignore(80, '\n');
			}
			else
				break;
		}
		switch(input)
		{
			case 1:
				item_id = "-1";
				break;
			case 2:
				item_category = "-1";
				break;
			case 3:
				item_name = "-1";
				break;
			case 4:
				item_manufacturer = "-1";
				break;
			case 5:
				item_description = "-1";
				break;
			case 6:
				unit_store = -1;
				break;
			case 7:
				unit_sold = -1;
				break;
			case 8:
				price_cost = -1;
				break;
			case 9:
				price_sell = -1;
				break;
			case 10:
				introduced_year = -1;
				break;
			case 11:
				introduced_month = "-1";
				if (introduced_day > 28)
					introduced_day = 28;
				break;
			case 12:
				introduced_day = -1;
				break;
			case 0:
				break;
			default:
				cout << "Input error!\nPut the number given in the bracket.\n";
				record_delete();
		}
	}
}

//	ALLOWS THE USER TO DISPLAY OR HIDE SPECIFIC DATA
void record_display()
{
	int input = -1;
	
	while (input != 0)
	{
		display_record();
		display_record_display();
		
		while (true)
		{
			cout << "Enter number from the bracket to toggle display: ";
			cin >> input;
			if (cin.fail())
			{
				cout << "Input error!\n"
						"Please enter an integer.\n";
				cin.clear();
				cin.ignore(80, '\n');
			}
			else
				break;
		}
		
		switch(input)
		{
			case 1:
				if (display_item_id == true)
					display_item_id = false;
				else
					display_item_id = true;
				break;
			case 2:
				if (display_item_category == true)
					display_item_category = false;
				else
					display_item_category = true;
				break;
			case 3:
				if (display_item_name == true)
					display_item_name = false;
				else
					display_item_name = true;
				break;
			case 4:
				if (display_item_manufacturer == true)
					display_item_manufacturer = false;
				else
					display_item_manufacturer = true;
				break;
			case 5:
				if (display_item_description == true)
					display_item_description = false;
				else
					display_item_description = true;
				break;
			case 6:
				if (display_unit_store == true)
					display_unit_store = false;
				else
					display_unit_store = true;
				break;
			case 7:
				if (display_unit_sold == true)
					display_unit_sold = false;
				else
					display_unit_sold = true;
				break;
			case 8:
				if (display_price_cost == true)
					display_price_cost = false;
				else
					display_price_cost = true;
				break;
			case 9:
				if (display_price_sell == true)
					display_price_sell = false;
				else
					display_price_sell = true;
				break;
			case 10:
				if (display_introduced_year == true)
					display_introduced_year = false;
				else
					display_introduced_year = true;
				break;
			case 11:
				if (display_introduced_month == true)
					display_introduced_month = false;
				else
					display_introduced_month = true;
				break;
			case 12:
				if (display_introduced_day == true)
					display_introduced_day = false;
				else
					display_introduced_day = true;
				break;
			case 0:
				break;
			default:
				cout << "Input error!\nPut the number given in the bracket.\n";
				record_display();
		}
	}
}

//	FUNCTIONS TO CHECK IF THE INPUT GIVEN IS VALID ACCORDINGLY WITH LOGIC
void set_item_id()
{
	cin.clear();
	string temp = "";
	int counter = 0;
	
	while (true)
	{
		counter = 0;
		temp = "";
		cout << "\nEnter the item ID (Must be 5 characters): ";
		cin >> item_id;
		for (int i=0;i<item_id.length();i++)
		{
			item_id[i]=toupper(item_id[i]);
			if (i < 5)
				temp += item_id[i];
				counter++;
		}
		if (counter < 5)
		{
			cout << "Not enough characters." << endl;
			cin.clear();
			cin.ignore(80, '\n');
		}
		else
			break;
	}
}

void set_item_category()
{
	cin.clear();
	cin.ignore(80, '\n');
	cout << "Enter the item category: ";
	getline(cin, item_category);
}

void set_item_name()
{
	cin.clear();
	cout << "Enter the item name: ";
	getline(cin, item_name);
}

void set_item_manufacturer()
{
	cin.clear();
	cout << "Enter the item manufacturer: ";
	getline(cin, item_manufacturer);
}

void set_item_description()
{
	cin.clear();
	cout << "Enter the item description: ";
	getline(cin, item_description);
}

void set_unit_store()
{
	cin.clear();
	while (true)
	{
		cout << "Enter the item unit amount in store: ";
		cin >> unit_store;
		if (cin.fail())
		{
			cout << "Input error!\n"
					"Please enter an integer.\n";
			cin.clear();
			cin.ignore(80, '\n');
		}
		if (unit_store <= 0)
			cout << "Unit in store should not be less than 0" << endl;
		else
			break;
	}
	cin.ignore(80, '\n');
}

void set_unit_sold()
{
	cin.clear();
	while (true)
	{
		cout << "Enter the item unit sold in store: ";
		cin >> unit_sold;
		if (cin.fail())
		{
			cout << "Input error!\n"
					"Please enter an integer.\n";
			cin.clear();
			cin.ignore(80, '\n');
		}
		if (unit_sold <= 0)
			cout << "Unit sold should not be less than 0" << endl;
		else
			break;
	}
	cin.ignore(80, '\n');
}

void set_price_cost()
{
	cin.clear();
	while (true)
	{
		cout << "Enter the item cost: ";
		cin >> price_cost;
		if (cin.fail())
		{
			cout << "Input error!\n"
					"Please enter a number.\n";
			cin.clear();
			cin.ignore(80, '\n');
		}
		if (price_cost <= 0)
			cout << "Cost price should not be less than 0" << endl;
		else
			cin.clear();
			cin.ignore(80, '\n');
			break;
	}
}

void set_price_sell()
{
	cin.clear();
	while (true)
	{
		cout << "Enter the item selling price: ";
		cin >> price_sell;
		if (cin.fail())
		{
			cout << "Input error!\n"
					"Please enter a number.\n";
			cin.clear();
			cin.ignore(80, '\n');
		}
		if (price_sell <= 0)
			cout << "Selling price should not be less than 0" << endl;
		else
			break;
	}
	cin.ignore(80, '\n');
}

void set_introduced_year()
{
	cin.clear();
	while (true)
	{
		cout << "Enter the item year of introduction: ";
		cin >> introduced_year;
		if (cin.fail())
		{
			cout << "Input error!\n"
					"Please enter an integer.\n";
			cin.clear();
			cin.ignore(80, '\n');
		}
		if (introduced_year < 1)
			cout << "Year given should not be less than 1" << endl;
		else
			break;
	}
	cin.ignore(80, '\n');
}

void set_introduced_month()
{
	cin.clear();
	while (true)
	{
		cout << "Enter the item month of introduction: ";
		cin >> introduced_month;
		
		for (int i=0;i<introduced_month.length();i++)
			introduced_month[i]=tolower(introduced_month[i]);
		
		if (introduced_month == "1" || introduced_month == "jan" || introduced_month == "january")
		{
			introduced_month = "January";
			break;
		}
		else if (introduced_month == "2" || introduced_month == "feb" || introduced_month == "february")
		{
			introduced_month = "February";
			break;
		}
		else if (introduced_month == "3" || introduced_month == "mar" || introduced_month == "march")
		{
			introduced_month = "March";
			break;
		}
		else if (introduced_month == "4" || introduced_month == "apr" || introduced_month == "april")
		{
			introduced_month = "April";
			break;
		}
		else if (introduced_month == "5" || introduced_month == "may")
		{
			introduced_month = "May";
			break;
		}
		else if (introduced_month == "6" || introduced_month == "jun" || introduced_month == "june")
		{
			introduced_month = "June";
			break;
		}
		else if (introduced_month == "7" || introduced_month == "jul" || introduced_month == "july")
		{
			introduced_month = "July";
			break;
		}
		else if (introduced_month == "8" || introduced_month == "aug" || introduced_month == "august")
		{
			introduced_month = "August";
			break;
		}
		else if (introduced_month == "9" || introduced_month == "sep" || introduced_month == "september")
		{
			introduced_month = "September";
			break;
		}
		else if (introduced_month == "10" || introduced_month == "oct" || introduced_month == "october")
		{
			introduced_month = "October";
			break;
		}
		else if (introduced_month == "11" || introduced_month == "nov" || introduced_month == "november")
		{
			introduced_month = "November";
			break;
		}
		else if (introduced_month == "12" || introduced_month == "dec" || introduced_month == "december")
		{
			introduced_month = "December";
			break;
		}
		else
		{
			cout << "Could not identify the month given; please enter the standard month naming." << endl;
			cin.clear();
			cin.ignore(80, '\n');
		}
	}
	cin.ignore(80, '\n');
}

void set_introduced_day()
{
	cin.clear();
	int min_day = 1,
		max_day = 31;
	while (true)
	{
		while (true)
		{
			cout << "Enter the item day of introduction: ";
			cin >> introduced_day;
			if (cin.fail())
			{
				cout << "Error; Not an integer" << endl;
				cin.clear();
				cin.ignore(80, '\n');
			}
			else if (introduced_day < min_day)
			{
				cout << "Day given is less than in possible amount in a month" << endl;
				cin.clear();
				cin.ignore(80, '\n');
			}
			else if (introduced_day > max_day)
			{
				cout << "Day given is more than in possible amount in a month" << endl;
				cin.clear();
				cin.ignore(80, '\n');
			}
			else
				break;
		}
		if (introduced_month == "February" && ((introduced_year % 4) == 0) && introduced_day <= 29)
			break;
		else if (introduced_month == "February" && ((introduced_year % 4) != 0) && introduced_day <= 28)
			break;
		else if ((introduced_month == "April" || introduced_month == "June" ||
				 introduced_month == "September" || introduced_month == "November") && introduced_day <= 30)
			break;
		else if ((introduced_month == "January" || introduced_month == "March" || introduced_month == "May" || introduced_month == "July" ||
				introduced_month == "August" || introduced_month == "October" || introduced_month == "December") && introduced_day <= 31)
			break;
		else if (introduced_month == "-1" && introduced_day <= 28)
			break;
		else if (introduced_month == "-1" && introduced_day > 28)
			cout << "No input was given in months; Program will only assume from 1 to 28 days\n";
		else
			cout << "It is not possible for that specific day in this month: " << introduced_month << endl;
	}
	cin.ignore(80, '\n');
}