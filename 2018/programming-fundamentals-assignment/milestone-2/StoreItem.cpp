#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "StoreItem.h"
using namespace std;

StoreItem::StoreItem()
{
	item_code = "-1";
	item_name = "-1";
	item_desc = "-1";
	item_cat = "-1";
	item_mfr = "-1";
	item_unit_store = -1;
	item_unit_sold = -1;
	item_intro_year = -1;
	item_intro_month = "-1";
	item_intro_day = -1;
	item_price_sell = -1;
	item_price_cost = -1;
	disp_item_code = true;
	disp_item_cat = true;
	disp_item_mfr = true;
	disp_item_name = true;
	disp_item_desc = true;
	disp_item_unit_store = true;
	disp_item_unit_sold = true;
	disp_item_price_sell = true;
	disp_item_price_cost = true;
	disp_item_intro_year = true;
	disp_item_intro_month = true;
	disp_item_intro_day = true;
}

/*
	Fetching and updating the file.
*/
void StoreItem::file_fetch(vector<StoreItem> &inv_list)
{
	string file_name,
		   temp_str;
	int item_amt = 0;
	
	cout << "\nOpening the file from the same location as program.\n"
			"Enter '-1' to cancel the action.\n"
			"\n(Include file extension ex. (file.txt, file.db))\n"
			"Open file: ";;
	getline(cin, file_name);
//	file_name = "inventory.txt";
	if(file_name == "-1")
		return;
	
	ifstream file_read(file_name.c_str());
	
	if(!file_read.is_open())
	{
		cout << "\nError in opening file." << endl;
		system("pause");
		return;
	}
	
	item_amt = inv_list.size();
	if(item_amt > 0)
		for(int i = 0; i < item_amt; i++)
			inv_list.pop_back();
	
	item_amt = 0;
	
	while(getline(file_read, temp_str))
		item_amt++;
	item_amt /= 12;
	
	file_read.close();
	file_read.open(file_name.c_str());
	
	for(int i = 0; i < item_amt; i++)
	{
		StoreItem inv_new;
//		file_read >> item_code >> disp_item_code >> item_cat >> disp_item_cat >> item_mfr >> disp_item_mfr >>
//					 item_name >> disp_item_name >> item_desc >> disp_item_desc >>
//					 item_unit_store >> disp_item_unit_store >> item_unit_sold >> disp_item_unit_sold >>
//					 item_price_cost >> disp_item_price_cost >> item_price_sell >> disp_item_price_sell >>
//					 item_intro_year >> disp_item_intro_year >> item_intro_month >> disp_item_intro_month >> item_intro_day >> disp_item_intro_day;
//		
//		replace(item_mfr.begin(), item_mfr.end(), '`', ' ');
//		replace(item_name.begin(), item_name.end(), '`', ' ');
//		replace(item_desc.begin(), item_desc.end(), '`', ' ');
		getline(file_read, item_code);
		inv_new.set_item_code(item_code);
		getline(file_read, item_name);
		inv_new.set_item_name(item_name);
		getline(file_read, item_desc);
		inv_new.set_item_desc(item_desc);
		getline(file_read, item_cat);
		inv_new.set_item_cat(item_cat);
		getline(file_read, item_mfr);
		inv_new.set_item_mfr(item_mfr);
		file_read >> item_price_sell;
		file_read.ignore(80, '\n');
		inv_new.set_item_price_sell(item_price_sell);
		file_read >> item_price_cost;
		file_read.ignore(80, '\n');
		inv_new.set_item_price_cost(item_price_cost);
		file_read >> item_unit_store;
		file_read.ignore(80, '\n');
		inv_new.set_item_unit_store(item_unit_store);
		file_read >> item_unit_sold;
		file_read.ignore(80, '\n');
		inv_new.set_item_unit_sold(item_unit_sold);
		file_read >> item_intro_year;
		file_read.ignore(80, '\n');
		inv_new.set_item_intro_year(item_intro_year);
		file_read >> item_intro_month;
		file_read.ignore(80, '\n');
		inv_new.set_item_intro_month(item_intro_month);
		file_read >> item_intro_day;
		file_read.ignore(80, '\n');
		inv_new.set_item_intro_day(item_intro_day);
		
		inv_list.push_back(inv_new);
	}
	file_read.close();
	
	return;
}

void StoreItem::file_save(vector<StoreItem> inv_list)
{
	string file_name;
	
	cout << "\nSaving file in the same location as program.\n"
			"Enter '-1' to cancel the action.\n"
			"\n(Include file extension ex. (file.txt, file.db))\n"
			"Save as: ";
	getline(cin, file_name);
//	file_name = "inventory_save.txt";
	
	if(file_name == "-1")
		return;
	
	ofstream file_write(file_name.c_str());
	
	for(int i = 0; i < inv_list.size(); i++)
	{
		file_write << inv_list[i].get_item_code() << endl;
		file_write << inv_list[i].get_item_name() << endl;
		file_write << inv_list[i].get_item_desc() << endl;
		file_write << inv_list[i].get_item_cat() << endl;
		file_write << inv_list[i].get_item_mfr() << endl;
		file_write << inv_list[i].get_item_price_sell() << endl;
		file_write << inv_list[i].get_item_price_cost() << endl;
		file_write << inv_list[i].get_item_unit_store() << endl;
		file_write << inv_list[i].get_item_unit_sold() << endl;
		file_write << inv_list[i].get_item_intro_year() << endl;
		file_write << inv_list[i].get_item_intro_month() << endl;
		file_write << inv_list[i].get_item_intro_day() << endl;
	}
	file_write.close();
	
	return;
}

/*
	Set value to variables.
*/
void StoreItem::set_item_code(vector<StoreItem> inv_list)
{
	string str,
		   temp = "";
	int counter = 0;
	bool check_dupe = false;
	
	while(true)
	{
		counter = 0;
		temp = "";
		check_dupe = false;
		str = "";
		
		while(str == "")
		{
			cout << "Enter the item ID (At most 8 characters): ";
			cin >> str;
			cin.clear();
			cin.ignore(80, '\n');
		}
		for(int i = 0; i < str.length(); i++)
		{
			str[i] = toupper(str[i]);
			if(i < 8)
				temp += str[i];
				counter++;
		}
		if(counter >= 8)
			cout << "Too many characters." << endl;
		
		for(int i = 0; i < inv_list.size(); i++)
		{
			if(temp == inv_list[i].get_item_code())
			{
				cout << "Code already existed." << endl;
				check_dupe = true;
			}
		}
		if(!check_dupe)
			break;
	}
	item_code = temp;
	
	return;
}

void StoreItem::set_item_code(string str)
{
	string temp = "";
	for(int i=0;i<str.length();i++)
	{
		str[i]=toupper(str[i]);
		if(i < 8)
			temp += str[i];
	}
	if(str == "")
		temp = "-1";
	item_code = temp;
	
	return;
}

void StoreItem::set_item_cat()
{
	string str;
	while(str == "")
	{
		cout << "Enter the item category: ";
		getline(cin, str);
	}
	
	item_cat = str;
	
	return;
}

void StoreItem::set_item_cat(string str)
{
	if(str == "")
		str = "-1";
	item_cat = str;
	
	return;
}

void StoreItem::set_item_mfr()
{
	string str;
	while(str == "")
	{
		cout << "Enter the item manufacturer: ";
		getline(cin, str);
	}
	
	item_mfr = str;
	
	return;
}

void StoreItem::set_item_mfr(string str)
{
	if(str == "")
		str = "-1";
	item_mfr = str;
	
	
	return;
}

void StoreItem::set_item_name()
{
	string str;
	while(str == "")
	{
		cout << "Enter the item name: ";
		getline(cin, str);
	}
	
	item_name = str;
	
	return;
}

void StoreItem::set_item_name(string str)
{
	if(str == "")
		str = "-1";
	item_name = str;
	
	return;
}

void StoreItem::set_item_desc()
{
	string str;
	while(str == "")
	{
		cout << "Enter the item description: ";
		getline(cin, str);
	}
	
	item_desc = str;
	
	return;
}

void StoreItem::set_item_desc(string str)
{
	if(str == "")
		str = "-1";
	item_desc = str;
	
	return;
}

void StoreItem::set_item_unit_store()
{
	int num;
	while(true)
	{
		cout << "Enter the item unit amount in store: ";
		cin >> num;
		cin.clear();
		cin.ignore(80, '\n');
		if(cin.fail())
			cout << "Input error!\n"
					"Please enter an integer.\n";
		if(num < 0)
			cout << "Unit in store should not be less than 0" << endl;
		else
			break;
	}
	item_unit_store = num;
	
	return;
}

void StoreItem::set_item_unit_store(int num)
{
	if(num < 0)
		num = -1;
	item_unit_store = num;
	
	return;
}

void StoreItem::set_item_unit_sold()
{
	int num;
	while(true)
	{
		cout << "Enter the item unit sold in store: ";
		cin >> num;
		cin.clear();
		cin.ignore(80, '\n');
		if(cin.fail())
			cout << "Input error!\n"
					"Please enter an integer.\n";
		if(num < 0)
			cout << "Unit sold should not be less than 0" << endl;
		else
			break;
	}
	item_unit_sold = num;
	
	return;
}

void StoreItem::set_item_unit_sold(int num)
{
	if(num < 0)
		num = -1;
	item_unit_sold = num;
	
	return;
}

void StoreItem::set_item_price_cost()
{
	double num;
	while(true)
	{
		cout << "Enter the item cost: ";
		cin >> num;
		cin.clear();
		cin.ignore(80, '\n');
		if(cin.fail())
			cout << "Input error!\n"
					"Please enter a number.\n";
		if(num < 0)
			cout << "Cost price should not be less than 0" << endl;
		else
			break;
	}
	item_price_cost = num;
	
	return;
}

void StoreItem::set_item_price_cost(double num)
{
	if(num < 0)
		num = -1;
	item_price_cost = num;
	
	return;
}

void StoreItem::set_item_price_sell()
{
	double num;
	while(true)
	{
		cout << "Enter the item selling price: ";
		cin >> num;
		cin.clear();
		cin.ignore(80, '\n');
		if(cin.fail())
			cout << "Input error!\n"
					"Please enter a number.\n";
		if(num < 0)
			cout << "Selling price should not be less than 0" << endl;
		else
			break;
	}
	item_price_sell = num;
	
	return;
}

void StoreItem::set_item_price_sell(double num)
{
	if(num < 0)
		num = -1;
	item_price_sell = num;
	
	return;
}

void StoreItem::set_item_intro_year()
{
	int num;
	while(true)
	{
		cout << "Enter the item year of introduction: ";
		cin >> num;
		cin.clear();
		cin.ignore(80, '\n');
		if(cin.fail())
			cout << "Input error!\n"
					"Please enter an integer.\n";
		if(num < 1)
			cout << "Year given should not be less than 1" << endl;
		else
			break;
	}
	item_intro_year = num;
	
	return;
}

void StoreItem::set_item_intro_year(int num)
{
	if(num < 1)
		num = -1;
	item_intro_year = num;
	
	return;
}

void StoreItem::set_item_intro_month()
{
	string str;
	while(true)
	{
		cout << "Enter the item month of introduction: ";
		cin >> str;
		cin.clear();
		cin.ignore(80, '\n');
		
		for(int i=0;i<str.length();i++)
			str[i]=tolower(str[i]);
		
		if(str == "1" || str == "jan" || str == "january")
		{
			str = "January";
			break;
		}
		else if(str == "2" || str == "feb" || str == "february")
		{
			str = "February";
			break;
		}
		else if(str == "3" || str == "mar" || str == "march")
		{
			str = "March";
			break;
		}
		else if(str == "4" || str == "apr" || str == "april")
		{
			str = "April";
			break;
		}
		else if(str == "5" || str == "may")
		{
			str = "May";
			break;
		}
		else if(str == "6" || str == "jun" || str == "june")
		{
			str = "June";
			break;
		}
		else if(str == "7" || str == "jul" || str == "july")
		{
			str = "July";
			break;
		}
		else if(str == "8" || str == "aug" || str == "august")
		{
			str = "August";
			break;
		}
		else if(str == "9" || str == "sep" || str == "september")
		{
			str = "September";
			break;
		}
		else if(str == "10" || str == "oct" || str == "october")
		{
			str = "October";
			break;
		}
		else if(str == "11" || str == "nov" || str == "november")
		{
			str = "November";
			break;
		}
		else if(str == "12" || str == "dec" || str == "december")
		{
			str = "December";
			break;
		}
		else
			cout << "Could not identify the month given; please enter the standard month naming." << endl;
	}
	if(get_item_intro_day() > 28)
		set_item_intro_day(28);
	
	item_intro_month = str;
	
	return;
}

void StoreItem::set_item_intro_month(string str)
{
	for(int i=0;i<str.length();i++)
		str[i]=tolower(str[i]);
	
	if(str == "1" || str == "jan" || str == "january")
		str = "January";
	else if(str == "2" || str == "feb" || str == "february")
		str = "February";
	else if(str == "3" || str == "mar" || str == "march")
		str = "March";
	else if(str == "4" || str == "apr" || str == "april")
		str = "April";
	else if(str == "5" || str == "may")
		str = "May";
	else if(str == "6" || str == "jun" || str == "june")
		str = "June";
	else if(str == "7" || str == "jul" || str == "july")
		str = "July";
	else if(str == "8" || str == "aug" || str == "august")
		str = "August";
	else if(str == "9" || str == "sep" || str == "september")
		str = "September";
	else if(str == "10" || str == "oct" || str == "october")
		str = "October";
	else if(str == "11" || str == "nov" || str == "november")
		str = "November";
	else if(str == "12" || str == "dec" || str == "december")
		str = "December";
	else
		str = "-1";
	if(get_item_intro_day() > 28)
		set_item_intro_day(28);
	
	item_intro_month = str;
	
	return;
}

void StoreItem::set_item_intro_day()
{
	int num,
		min_day = 1,
		max_day = 31;
	while(true)
	{
		while(true)
		{
			cout << "Enter the item day of introduction: ";
			cin >> num;
			cin.clear();
			cin.ignore(80, '\n');
			if(cin.fail())
				cout << "Error; Not an integer" << endl;
			else if(num < min_day)
				cout << "Day given is less than in possible amount in a month" << endl;
			else if(num > max_day)
				cout << "Day given is more than in possible amount in a month" << endl;
			else
				break;
		}
		if(item_intro_month == "February" && ((item_intro_year % 4) == 0) && num <= 29)
			break;
		else if(item_intro_month == "February" && ((item_intro_year % 4) != 0) && num <= 28)
			break;
		else if((item_intro_month == "April" || item_intro_month == "June" ||
				 item_intro_month == "September" || item_intro_month == "November") && num <= 30)
			break;
		else if((item_intro_month == "January" || item_intro_month == "March" || item_intro_month == "May" || item_intro_month == "July" ||
				item_intro_month == "August" || item_intro_month == "October" || item_intro_month == "December") && num <= 31)
			break;
		else if(item_intro_month == "-1" && num <= 28)
			break;
		else if(item_intro_month == "-1" && num > 28)
			cout << "No input was given in months; Program will only assume from 1 to 28 days\n";
		else
			cout << "It is not possible for that specific day in this month: " << item_intro_month << endl;
	}
	
	item_intro_day = num;
	
	return;
}

void StoreItem::set_item_intro_day(int num)
{
	int min_day = 1,
		max_day = 31;
	if(item_intro_month == "February" && ((item_intro_year % 4) == 0) && num <= 29)
		item_intro_day = num;
	else if(item_intro_month == "February" && ((item_intro_year % 4) != 0) && num <= 28)
		item_intro_day = num;
	else if((item_intro_month == "April" || item_intro_month == "June" ||
			 item_intro_month == "September" || item_intro_month == "November") && num <= 30)
		item_intro_day = num;
	else if((item_intro_month == "January" || item_intro_month == "March" || item_intro_month == "May" || item_intro_month == "July" ||
			item_intro_month == "August" || item_intro_month == "October" || item_intro_month == "December") && num <= 31)
		item_intro_day = num;
	else if(item_intro_month == "-1" && num <= 28)
		item_intro_day = num;
	else if(item_intro_month == "-1" && num > 28)
		item_intro_day = 28;
	else
		item_intro_day = -1;
	
	return;
}

/*
	Get value from variables.
*/
string StoreItem::get_item_code()
{
	return item_code;
}

string StoreItem::get_item_cat()
{
	return item_cat;
}

string StoreItem::get_item_mfr()
{
	return item_mfr;
}

string StoreItem::get_item_name()
{
	return item_name;
}

string StoreItem::get_item_desc()
{
	return item_desc;
}

int StoreItem::get_item_unit_store()
{
	return item_unit_store;
}

int StoreItem::get_item_unit_sold()
{
	return item_unit_sold;
}

double StoreItem::get_item_price_cost()
{
	return item_price_cost;
}

double StoreItem::get_item_price_sell()
{
	return item_price_sell;
}

int StoreItem::get_item_intro_year()
{
	return item_intro_year;
}

string StoreItem::get_item_intro_month()
{
	return item_intro_month;
}

int StoreItem::get_item_intro_month(int i)
{
	if(item_intro_month == "January")
		return 1;
	else if(item_intro_month == "February")
		return 2;
	else if(item_intro_month == "March")
		return 3;
	else if(item_intro_month == "April")
		return 4;
	else if(item_intro_month == "May")
		return 5;
	else if(item_intro_month == "June")
		return 6;
	else if(item_intro_month == "July")
		return 7;
	else if(item_intro_month == "August")
		return 8;
	else if(item_intro_month == "September")
		return 9;
	else if(item_intro_month == "October")
		return 10;
	else if(item_intro_month == "November")
		return 11;
	else if(item_intro_month == "December")
		return 12;
	else
		return -1;
	
	return 0;
}

int StoreItem::get_item_intro_day()
{
	return item_intro_day;
}

/*
	Get boolean for display.
*/
bool StoreItem::get_disp_item_code()
{
	return disp_item_code;
}

bool StoreItem::get_disp_item_cat()
{
	return disp_item_cat;
}

bool StoreItem::get_disp_item_mfr()
{
	return disp_item_mfr;
}

bool StoreItem::get_disp_item_name()
{
	return disp_item_name;
}

bool StoreItem::get_disp_item_desc()
{
	return disp_item_desc;
}

bool StoreItem::get_disp_item_unit_store()
{
	return disp_item_unit_store;
}

bool StoreItem::get_disp_item_unit_sold()
{
	return disp_item_unit_sold;
}

bool StoreItem::get_disp_item_price_cost()
{
	return disp_item_price_cost;
}

bool StoreItem::get_disp_item_price_sell()
{
	return disp_item_price_sell;
}

bool StoreItem::get_disp_item_intro_year()
{
	return disp_item_intro_year;
}

bool StoreItem::get_disp_item_intro_month()
{
	return disp_item_intro_month;
}

bool StoreItem::get_disp_item_intro_day()
{
	return disp_item_intro_day;
}

void StoreItem::set_disp_item_code(int num)
{
	if(num == 0)
		disp_item_code = false;
	else
		disp_item_code = true;
	
	return;
}

void StoreItem::set_disp_item_cat(int num)
{
	if(num == 0)
		disp_item_cat = false;
	else
		disp_item_cat = true;
	
	return;
}

void StoreItem::set_disp_item_mfr(int num)
{
	if(num == 0)
		disp_item_mfr = false;
	else
		disp_item_cat = true;
	
	return;
}

void StoreItem::set_disp_item_name(int num)
{
	if(num == 0)
		disp_item_name = false;
	else
		disp_item_name = true;
	
	return;
}

void StoreItem::set_disp_item_desc(int num)
{
	if(num == 0)
		disp_item_desc = false;
	else
		disp_item_desc = true;
	
	return;
}

void StoreItem::set_disp_item_unit_store(int num)
{
	if(num == 0)
		disp_item_unit_store = false;
	else
		disp_item_unit_store = true;
	
	return;
}

void StoreItem::set_disp_item_unit_sold(int num)
{
	if(num == 0)
		disp_item_unit_sold = false;
	else
		disp_item_unit_sold = true;
	
	return;
}

void StoreItem::set_disp_item_price_cost(int num)
{
	if(num == 0)
		disp_item_price_cost = false;
	else
		disp_item_price_cost = true;
	
	return;
}

void StoreItem::set_disp_item_price_sell(int num)
{
	if(num == 0)
		disp_item_price_sell = false;
	else
		disp_item_price_sell = true;
	
	return;
}

void StoreItem::set_disp_item_intro_year(int num)
{
	if(num == 0)
		disp_item_intro_year = false;
	else
		disp_item_intro_year = true;
	
	return;
}

void StoreItem::set_disp_item_intro_month(int num)
{
	if(num == 0)
		disp_item_intro_month = false;
	else
		disp_item_intro_month = true;
	
	return;
}

void StoreItem::set_disp_item_intro_day(int num)
{
	if(num == 0)
		disp_item_intro_day = false;
	else
		disp_item_intro_day = true;
	
	return;
}

void StoreItem::toggle_disp_item_code()
{
	if(disp_item_code)
		disp_item_code = false;
	else
		disp_item_code = true;
	
	return;
}

void StoreItem::toggle_disp_item_cat()
{
	if(disp_item_cat)
		disp_item_cat = false;
	else
		disp_item_cat = true;
	
	return;
}

void StoreItem::toggle_disp_item_mfr()
{
	if(disp_item_mfr)
		disp_item_mfr = false;
	else
		disp_item_cat = true;
	
	return;
}

void StoreItem::toggle_disp_item_name()
{
	if(disp_item_name)
		disp_item_name = false;
	else
		disp_item_name = true;
	
	return;
}

void StoreItem::toggle_disp_item_desc()
{
	if(disp_item_desc)
		disp_item_desc = false;
	else
		disp_item_desc = true;
	
	return;
}

void StoreItem::toggle_disp_item_unit_store()
{
	if(disp_item_unit_store)
		disp_item_unit_store = false;
	else
		disp_item_unit_store = true;
	
	return;
}

void StoreItem::toggle_disp_item_unit_sold()
{
	if(disp_item_unit_sold)
		disp_item_unit_sold = false;
	else
		disp_item_unit_sold = true;
	
	return;
}

void StoreItem::toggle_disp_item_price_cost()
{
	if(disp_item_price_cost)
		disp_item_price_cost = false;
	else
		disp_item_price_cost = true;
	
	return;
}

void StoreItem::toggle_disp_item_price_sell()
{
	if(disp_item_price_sell)
		disp_item_price_sell = false;
	else
		disp_item_price_sell = true;
	
	return;
}

void StoreItem::toggle_disp_item_intro_year()
{
	if(disp_item_intro_year)
		disp_item_intro_year = false;
	else
		disp_item_intro_year = true;
	
	return;
}

void StoreItem::toggle_disp_item_intro_month()
{
	if(disp_item_intro_month)
		disp_item_intro_month = false;
	else
		disp_item_intro_month = true;
	
	return;
}

void StoreItem::toggle_disp_item_intro_day()
{
	if(disp_item_intro_day)
		disp_item_intro_day = false;
	else
		disp_item_intro_day = true;
	
	return;
}
