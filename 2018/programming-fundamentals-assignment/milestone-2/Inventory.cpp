#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include "StoreItem.h"
using namespace std;

//	Defining function; done to prevent clutter to the main code.
void menu_view(vector<StoreItem>, int, int),
	 menu_search(vector<StoreItem>, int, int),
	 menu_sort(vector<StoreItem>&, int, int),
	 menu_display(vector<StoreItem>, int, int),
	 menu_edit(vector<StoreItem>&, int&, int&),
	 disp_menu_main(const int),
	 disp_menu_view(),
	 disp_menu_search(string, string, string, string, string, string, string, string, string, string, string, bool),
	 disp_menu_sort(),
	 disp_menu_display(),
	 disp_menu_edit(const int),
	 disp_inv_table(vector<StoreItem>, const int),
	 disp_item_detail(vector<StoreItem>, int, const int),
	 disp_item_update(vector<StoreItem>, int),
	 disp_item_delete(vector<StoreItem>, int),
	 disp_item_display(vector<StoreItem>, int),
	 index_prev(int&, const int),
	 index_next(int&, const int),
	 index_jump(int&, const int),
	 search_item_sort(vector<StoreItem>&, int&, string, string, string, string, string, string, string, string, string, string, string, bool),
	 sort_item_code(vector<StoreItem>&, int),
	 sort_item_cat(vector<StoreItem>&, int),
	 sort_item_mfr(vector<StoreItem>&, int),
	 sort_item_name(vector<StoreItem>&, int),
	 sort_item_unit_sold(vector<StoreItem>&, int),
	 sort_item_unit_store(vector<StoreItem>&, int),
	 sort_item_price_cost(vector<StoreItem>&, int),
	 sort_item_price_sell(vector<StoreItem>&, int),
	 sort_item_intro_year(vector<StoreItem>&, int),
	 sort_item_intro_month(vector<StoreItem>&, int),
	 sort_item_intro_day(vector<StoreItem>&, int),
	 record_new(vector<StoreItem>&, int&),
	 record_update(vector<StoreItem>&, int, int),
	 record_delete(vector<StoreItem>&, int, int),
	 record_delete_all(vector<StoreItem>&, int&, int&),
	 record_display(vector<StoreItem>&, int, int);
string set_search_str(),
	   set_search_str_line(),
	   set_search_num(),
	   repl_date_str(string&),
	   repl_month_str(string&),
	   repl_sym_str(string&),
	   get_bool_str(bool);
bool toggle_bool(bool&),
	 table_disp_item_id = true,
	 table_disp_item_code = true,
	 table_disp_item_cat = true,
	 table_disp_item_mfr = true,
	 table_disp_item_name = true,
	 table_disp_item_unit_store = true,
	 table_disp_item_unit_sold = true,
	 table_disp_item_price_cost = true,
	 table_disp_item_price_sell = true,
	 table_disp_item_intro_year = true,
	 table_disp_item_intro_month = true,
	 table_disp_item_intro_day = true;

//	Global constant variable for repetitive usage.
const string STR_HIDDEN = "HIDDEN";
const int MAX_ENDL = 64;

/*
	Main code starts here.
*/
int main()
{
	vector<StoreItem> inv_list;
	StoreItem inv;
	
	int item_index = 0,
		item_index_max = -1;
	char choice;
	
	while(true)
	{
		system("cls");
		for(int i = 0; i < MAX_ENDL; i++)
			cout << endl;
		disp_inv_table(inv_list, item_index_max);
		disp_menu_main(item_index_max);
		
		cout << "Enter number from the bracket to navigate: ";
		cin >> choice;
		cin.clear();
		cin.ignore(80, '\n');
		
		if(choice == '1' && item_index_max == -1)
			record_new(inv_list, item_index_max);
		else if(choice == '1' && item_index_max != -1)
			menu_view(inv_list, item_index, item_index_max);
		else if(choice == '2' && item_index_max != -1)
			menu_search(inv_list, item_index, item_index_max);
		else if(choice == '3' && item_index_max != -1)
			menu_sort(inv_list, item_index, item_index_max);
		else if(choice == '4' && item_index_max != -1)
			menu_display(inv_list, item_index, item_index_max);
		else if(choice == '5' && item_index_max != -1)
			menu_edit(inv_list, item_index, item_index_max);
		else if(choice == '6')
		{
			inv.file_fetch(inv_list);
			item_index = 0;
			item_index_max = inv_list.size() - 1;
		}
		else if(choice == '7' && item_index_max != -1)
			inv.file_save(inv_list);
		else if(choice == '0')
		{
			cout << "\n\n\nExiting the program...";
			break;
		}
	}
	
	return 0;
}

//	Look up on each item(s) in inventory.
void menu_view(vector<StoreItem> inv_list, int item_index, int item_index_max)
{	
	char choice;
	
	while(true)
	{
		system("cls");
		for(int i = 0; i < MAX_ENDL; i++)
			cout << endl;
		disp_item_detail(inv_list, item_index, item_index_max);
		disp_menu_view();
		
		cout << "Enter character from the bracket to navigate: ";
		cin >> choice;
		cin.clear();
		cin.ignore(80, '\n');
		
		if(choice == 'q' || choice == 'Q')
			index_prev(item_index, item_index_max);
		else if(choice == 'e' || choice == 'E')
			index_next(item_index, item_index_max);
		else if(choice == 'w' || choice == 'W')
			index_jump(item_index, item_index_max);
		else if(choice == '0' && item_index_max != -1)
			break;
	}
	
	return;
}

//	Search for an item(s) in inventory.
void menu_search(vector<StoreItem> inv_list, int item_index, int item_index_max)
{
	int input = -1;
	string temp,
		   temp_2;
	int temp_i;
	stringstream ss;
	double temp_d;
	static string search_item_code,
				  search_item_cat,
				  search_item_mfr,
				  search_item_name,
				  search_item_intro_month,
				  search_item_unit_store,
				  search_item_unit_sold,
				  search_item_intro_year,
				  search_item_intro_day,
				  search_item_price_cost,
				  search_item_price_sell;
	static bool table_show_all = false;
	
	while(input != 0)
	{
		system("cls");
		for(int i = 0; i < MAX_ENDL; i++)
			cout << endl;
		
		temp = "";
		temp_2 = "";
		temp_i = 0;
		search_item_sort(inv_list, item_index_max, search_item_code, search_item_cat, search_item_mfr, search_item_name, search_item_intro_month,
					     search_item_unit_store, search_item_unit_sold, search_item_intro_year, search_item_intro_day,
					     search_item_price_cost, search_item_price_sell, table_show_all);
		if(item_index_max >= 0)
			disp_inv_table(inv_list, item_index_max);
		else
			cout << "     IT Store Inventory -- Item Record\n"
					"========================================================\\\\\n"
					"\nNO ITEM(S) FOUND FOR THE SEARCH IN THE TABLE.\n\n"
					"========================================================//\n"
					"  ( -1 value indicates null or no value )\n";
		disp_menu_search(search_item_code, search_item_cat, search_item_mfr, search_item_name, search_item_intro_month,
						 search_item_unit_store, search_item_unit_sold, search_item_intro_year, search_item_intro_day,
						 search_item_price_cost, search_item_price_sell, table_show_all);
		
		while(true)
		{
			cout << "Enter number from the bracket to search: ";
			cin >> input;
			if(cin.fail())
			{
				cout << "Input error!\n"
						"Please enter an integer.\n";
				cin.clear();
				cin.ignore(80, '\n');
			}
			else
				break;
		}
		cin.clear();
		cin.ignore(80, '\n');
		switch(input)
		{
			case 1:
				cout << endl << "Enter '-1' to clear\n"
								"Search for code: ";
				search_item_code = set_search_str();
				if(search_item_code != "")
				{
					for(int i=0;i<search_item_code.length();i++)
					{
						search_item_code[i] = toupper(search_item_code[i]);
						if(i < 8)
							temp += search_item_code[i];
					}
					search_item_code = temp;
				}
				break;
			case 2:
				cout << endl << "Enter '-1' to clear\n"
								"Search for category: ";
				search_item_cat = set_search_str_line();
				break;
			case 3:
				cout << endl << "Enter '-1' to clear\n"
								"Search for manufacturer: ";
				search_item_mfr = set_search_str_line();
				break;
			case 4:
				cout << endl << "Enter '-1' to clear\n"
								"Search for name: ";
				search_item_name = set_search_str_line();
				break;
			case 5:
				cout << endl << "Enter '-1' to clear\n"
								"You can enter '<' (less than) or '>' (more than) at the beginning.\n"
								"Search for unit in store: ";
				search_item_unit_store = set_search_num();
				if(search_item_unit_store != "")
				{
					for(int i = 0; i < search_item_unit_store.size(); i++)
					{
						if(search_item_unit_store[i] == '.')
							break;
						temp += search_item_unit_store[i];
					}
					search_item_unit_store = temp;
					temp.erase(remove(temp.begin(), temp.end(), '<'), temp.end());
					temp.erase(remove(temp.begin(), temp.end(), '>'), temp.end());
					temp_i = atoi(temp.c_str());
					cout << temp << endl;
					cout << temp_i << endl;
					if(temp_i <= 0)
					{
						ss << 0;
						temp = ss.str();
						search_item_unit_store.erase(remove(search_item_unit_store.begin(), search_item_unit_store.end(), '<'), search_item_unit_store.end());
					}
					for(int i = 0; i < temp.size(); i++)
					{
						if(search_item_unit_store[i] == '<' || search_item_unit_store[i] == '>')
							temp_2 += search_item_unit_store[i];
						temp_2 += temp[i];
					}
					search_item_unit_store = temp_2;
				}
				break;
			case 6:
				cout << endl << "Enter '-1' to clear\n"
								"You can enter '<' (less than) or '>' (more than) at the beginning.\n"
								"Search for unit sold: ";
				search_item_unit_sold = set_search_num();
				if(search_item_unit_sold != "")
				{
					for(int i = 0; i < search_item_unit_sold.size(); i++)
					{
						if(search_item_unit_sold[i] == '.')
							break;
						temp += search_item_unit_sold[i];
					}
					search_item_unit_sold = temp;
					temp.erase(remove(temp.begin(), temp.end(), '<'), temp.end());
					temp.erase(remove(temp.begin(), temp.end(), '>'), temp.end());
					temp_i = atoi(temp.c_str());
					if(temp_i <= 0)
					{
						ss << 0;
						temp = ss.str();
						search_item_unit_sold.erase(remove(search_item_unit_sold.begin(), search_item_unit_sold.end(), '<'), search_item_unit_sold.end());
					}
					for(int i = 0; i < temp.size(); i++)
					{
						if(search_item_unit_sold[i] == '<' || search_item_unit_sold[i] == '>')
							temp_2 += search_item_unit_sold[i];
						temp_2 += temp[i];
					}
					search_item_unit_sold = temp_2;
				}
				break;
			case 7:
				cout << endl << "Enter '-1' to clear\n"
								"You can enter '<' (less than) or '>' (more than) at the beginning.\n"
								"Search for price (Cost): ";
				search_item_price_cost = set_search_num();
				if(search_item_price_cost != "")
				{
					temp = search_item_price_cost;
					temp.erase(remove(temp.begin(), temp.end(), '<'), temp.end());
					temp.erase(remove(temp.begin(), temp.end(), '>'), temp.end());
					temp_d = atof(temp.c_str());
					if(temp_d <= 0)
					{
						ss << 0;
						temp = ss.str();
						search_item_price_cost.erase(remove(search_item_price_cost.begin(), search_item_price_cost.end(), '<'), search_item_price_cost.end());
					}
					for(int i = 0; i < temp.size(); i++)
					{
						if(search_item_price_cost[i] == '<' || search_item_price_cost[i] == '>')
							temp_2 += search_item_price_cost[i];
						temp_2 += temp[i];
					}
					search_item_price_cost = temp_2;
				}
				break;
			case 8:
				cout << endl << "Enter '-1' to clear\n"
								"You can enter '<' (less than) or '>' (more than) at the beginning.\n"
								"Search for price (Sell): ";
				search_item_price_sell = set_search_num();
				if(search_item_price_sell != "")
				{
					temp = search_item_price_sell;
					temp.erase(remove(temp.begin(), temp.end(), '<'), temp.end());
					temp.erase(remove(temp.begin(), temp.end(), '>'), temp.end());
					temp_d = atof(temp.c_str());
					if(temp_d <= 0)
					{
						ss << 0;
						temp = ss.str();
						search_item_price_sell.erase(remove(search_item_price_sell.begin(), search_item_price_sell.end(), '<'), search_item_price_sell.end());
					}
					for(int i = 0; i < temp.size(); i++)
					{
						if(search_item_price_sell[i] == '<' || search_item_price_sell[i] == '>')
							temp_2 += search_item_price_sell[i];
						temp_2 += temp[i];
					}
					search_item_price_sell = temp_2;
				}
				break;
			case 9:
				cout << endl << "Enter '-1' to clear\n"
								"You can enter '<' (before) or '>' (after) at the beginning.\n"
								"Search for year(s) of introduction: ";
				search_item_intro_year = set_search_num();
				if(search_item_intro_year != "")
				{
					for(int i = 0; i < search_item_intro_year.size(); i++)
					{
						if(search_item_intro_year[i] == '.')
							break;
						temp += search_item_intro_year[i];
					}
					search_item_intro_year = temp;
					temp.erase(remove(temp.begin(), temp.end(), '<'), temp.end());
					temp.erase(remove(temp.begin(), temp.end(), '>'), temp.end());
					temp_i = atoi(temp.c_str());
					if(temp_i <= 1)
					{
						ss << 1;
						temp = ss.str();
						search_item_intro_year.erase(remove(search_item_intro_year.begin(), search_item_intro_year.end(), '<'), search_item_intro_year.end());
					}
					for(int i = 0; i < temp.size(); i++)
					{
						if(search_item_intro_year[i] == '<' || search_item_intro_year[i] == '>')
							temp_2 += search_item_intro_year[i];
						temp_2 += temp[i];
					}
					search_item_intro_year = temp_2;
				}
				break;
			case 10:
				cout << endl << "Enter '-1' to clear\n"
								"You can enter '<' (before) or '>' (after) at the beginning.\n"
								"Search for month(s) of introduction: ";
				search_item_intro_month = set_search_num();
				if(search_item_intro_month != "")
				{
					for(int i = 0; i < search_item_intro_month.size(); i++)
					{
						if(search_item_intro_month[i] == '.')
							break;
						temp += search_item_intro_month[i];
					}
					search_item_intro_month = temp;
					temp.erase(remove(temp.begin(), temp.end(), '<'), temp.end());
					temp.erase(remove(temp.begin(), temp.end(), '>'), temp.end());
					temp_i = atoi(temp.c_str());
					if(temp_i >= 12)
					{
						ss << 12;
						temp = ss.str();
						search_item_intro_month.erase(remove(search_item_intro_month.begin(), search_item_intro_month.end(), '>'), search_item_intro_month.end());
					}
					else if(temp_i <= 1)
					{
						ss << 1;
						temp = ss.str();
						search_item_intro_month.erase(remove(search_item_intro_month.begin(), search_item_intro_month.end(), '<'), search_item_intro_month.end());
					}
					for(int i = 0; i < temp.size(); i++)
					{
						if(search_item_intro_month[i] == '<' || search_item_intro_month[i] == '>')
							temp_2 += search_item_intro_month[i];
						temp_2 += temp[i];
					}
					search_item_intro_month = temp_2;
				}
				break;
			case 11:
				cout << endl << "Enter '-1' to clear\n"
								"You can enter '<' (before) or '>' (after) at the beginning.\n"
								"Search for day(s) of introduction: ";
				search_item_intro_day = set_search_num();
				if(search_item_intro_day != "")
				{
					for(int i = 0; i < search_item_intro_day.size(); i++)
					{
						if(search_item_intro_day[i] == '.')
							break;
						temp += search_item_intro_day[i];
					}
					search_item_intro_day = temp;
					temp.erase(remove(temp.begin(), temp.end(), '<'), temp.end());
					temp.erase(remove(temp.begin(), temp.end(), '>'), temp.end());
					temp_i = atoi(temp.c_str());
					if(temp_i >= 31)
					{
						ss << 31;
						temp = ss.str();
						search_item_intro_day.erase(remove(search_item_intro_day.begin(), search_item_intro_day.end(), '>'), search_item_intro_day.end());
					}
					else if(temp_i <= 1)
					{
						ss << 1;
						temp = ss.str();
						search_item_intro_day.erase(remove(search_item_intro_day.begin(), search_item_intro_day.end(), '<'), search_item_intro_day.end());
					}
					for(int i = 0; i < temp.size(); i++)
					{
						if(search_item_intro_day[i] == '<' || search_item_intro_day[i] == '>')
							temp_2 += search_item_intro_day[i];
						temp_2 += temp[i];
					}
					search_item_intro_day = temp_2;
				}
				break;
			case 12:
				toggle_bool(table_show_all);
				break;
			case 13:
				search_item_code = "";
				search_item_cat = "";
				search_item_mfr = "";
				search_item_name = "";
				search_item_unit_store = "";
				search_item_unit_sold = "";
				search_item_price_cost = "";
				search_item_price_sell = "";
				search_item_intro_year = "";
				search_item_intro_month = "";
				search_item_intro_day = "";
				break;
			case 0:
				break;
			default:
				cout << "Input error!\nPut the number given in the bracket.\n";
		}
	}
	
	return;
}

//	Sort the inventory given by type(s).
void menu_sort(vector<StoreItem> &inv_list, int item_index, int item_index_max)
{
	int input = -1;
	
	while(input != 0)
	{
		system("cls");
		for(int i = 0; i < MAX_ENDL; i++)
			cout << endl;
		disp_inv_table(inv_list, item_index_max);
		disp_menu_sort();
		
		while(true)
		{
			cout << "Enter number from the bracket to sort: ";
			cin >> input;
			if(cin.fail())
			{
				cout << "Input error!\n"
						"Please enter an integer.\n";
				cin.clear();
				cin.ignore(80, '\n');
			}
			else
				break;
		}
		cin.clear();
		cin.ignore(80, '\n');
		switch(input)
		{
			case 1:
				sort_item_code(inv_list, item_index_max);
				break;
			case 2:
				sort_item_cat(inv_list, item_index_max);
				break;
			case 3:
				sort_item_mfr(inv_list, item_index_max);
				break;
			case 4:
				sort_item_name(inv_list, item_index_max);
				break;
			case 5:
				sort_item_unit_store(inv_list, item_index_max);
				break;
			case 6:
				sort_item_unit_sold(inv_list, item_index_max);
				break;
			case 7:
				sort_item_price_cost(inv_list, item_index_max);
				break;
			case 8:
				sort_item_price_sell(inv_list, item_index_max);
				break;
			case 9:
				sort_item_intro_year(inv_list, item_index_max);
				break;
			case 10:
				sort_item_intro_month(inv_list, item_index_max);
				break;
			case 11:
				sort_item_intro_day(inv_list, item_index_max);
				break;
			case 12:
				reverse(inv_list.begin(),inv_list.end());
				break;
			case 0:
				break;
			default:
				cout << "Input error!\nPut the number given in the bracket.\n";
		}
	}
	
	return;
}

//	Display specific data field(s) of the table.
void menu_display(vector<StoreItem> inv_list, int item_index, int item_index_max)
{
	int input = -1;
	
	while(input != 0)
	{
		system("cls");
		for(int i = 0; i < MAX_ENDL; i++)
			cout << endl;
		disp_inv_table(inv_list, item_index_max);
		disp_menu_display();
		
		while(true)
		{
			cout << "Enter number from the bracket to toggle display: ";
			cin >> input;
			if(cin.fail())
			{
				cout << "Input error!\n"
						"Please enter an integer.\n";
				cin.clear();
				cin.ignore(80, '\n');
			}
			else
				break;
		}
		cin.clear();
		cin.ignore(80, '\n');
		switch(input)
		{
			case 1:
				toggle_bool(table_disp_item_code);
				break;
			case 2:
				toggle_bool(table_disp_item_cat);
				break;
			case 3:
				toggle_bool(table_disp_item_mfr);
				break;
			case 4:
				toggle_bool(table_disp_item_name);
				break;
			case 5:
				toggle_bool(table_disp_item_unit_store);
				break;
			case 6:
				toggle_bool(table_disp_item_unit_sold);
				break;
			case 7:
				toggle_bool(table_disp_item_price_cost);
				break;
			case 8:
				toggle_bool(table_disp_item_price_sell);
				break;
			case 9:
				toggle_bool(table_disp_item_intro_year);
				break;
			case 10:
				toggle_bool(table_disp_item_intro_month);
				break;
			case 11:
				toggle_bool(table_disp_item_intro_day);
				break;
			case 0:
				break;
			default:
				cout << "Input error!\nPut the number given in the bracket.\n";
		}
	}
	
	return;
}

//	Edit the inventory and the item(s).
void menu_edit(vector<StoreItem> &inv_list, int &item_index, int &item_index_max)
{
	StoreItem inv;
	char choice;
	
	while(true)
	{
		system("cls");
		for(int i = 0; i < MAX_ENDL; i++)
			cout << endl;
		disp_item_detail(inv_list, item_index, item_index_max);
		disp_menu_edit(item_index_max);
		
		cout << "Enter number from the bracket to navigate: ";
		cin >> choice;
		cin.clear();
		cin.ignore(80, '\n');
		
		if(choice == 'q' || choice == 'Q' && item_index_max != -1)
			index_prev(item_index, item_index_max);
		else if(choice == 'e' || choice == 'E' && item_index_max != -1)
			index_next(item_index, item_index_max);
		else if(choice == 'w' || choice == 'W' && item_index_max != -1)
			index_jump(item_index, item_index_max);
		else if(choice == '1')
		{
			record_new(inv_list, item_index_max);
			item_index = inv_list.size() - 1;
		}
		else if(choice == '2' && item_index_max != -1)
			record_update(inv_list, item_index, item_index_max);
		else if(choice == '3' && item_index_max != -1)
			record_display(inv_list, item_index, item_index_max);
		else if(choice == '4' && item_index_max != -1)
			record_delete(inv_list, item_index, item_index_max);
		else if(choice == '5' && item_index_max != -1)
			record_delete_all(inv_list, item_index, item_index_max);
		else if(choice == '6' && item_index_max == -1)
		{
			inv.file_fetch(inv_list);
			item_index = 0;
			item_index_max = inv_list.size() - 1;
		}
		else if(choice == '0')
			break;
	}
	
	return;
}

/*
	Prints menu screen as navigation guide for user.
*/
void disp_menu_main(const int index_max)
{
	cout << "\n    Inventory management program\n"
			"  --  [ Main menu ] --\n";
	if(index_max != -1)
		cout << "   [1] View Item(s) Detail\n"
				"   [2] Search Table\n"
				"   [3] Sort Table\n"
				"   [4] Display Table\n\n"
				"   [5] Edit Inventory\n"
				"   [6] Open Inventory\n"
				"   [7] Save Inventory\n\n";
	else
		cout << "   [1] New Record\n"
				"   [6] Open Inventory\n\n";
	cout << "   [0] Exit Program\n\n";
	
	return;
}

void disp_menu_view()
{
	cout << "\n    Inventory management program\n"
			"  --  [ View each records in detail ] --\n"
			"   [Q] Previous Record"
			"   [E] Next Record\n"
			"     [W] Jump to Record\n\n"
			"   [0] Back\n\n";
	
	return;
}

void disp_menu_search(string code, string cat, string mfr, string name, string month, string u_store, string u_sold, string year, string day, string p_cost, string p_sell, bool tab_show_a)
{
	cout << "\n    Inventory management program\n"
			"  --  [Search from table ] --\n"
			"   [1]             Code";
	if(code == "")
		cout << endl;
	else
		cout << "  >>  " << code << endl;
	cout << "   [2]         Category";
	if(cat == "")
		cout << endl;
	else
		cout << "  >>  " << cat << endl;
	cout << "   [3]     Manufacturer";
	if(mfr == "")
		cout << endl;
	else
		cout << "  >>  " << mfr << endl;
	cout << "   [4]             Name";
	if(name == "")
		cout << endl;
	else
		cout << "  >>  " << name << endl;
	cout << "   [5]    Unit in Store";
	if(u_store == "")
		cout << endl;
	else
	{
		repl_sym_str(u_store);
		cout << "  >>  " << u_store << endl;
	}
	cout << "   [6]        Unit Sold";
	if(u_sold == "")
		cout << endl;
	else
	{
		repl_sym_str(u_sold);
		cout << "  >>  " << u_sold << endl;
	}
	cout << "   [7] Price (Cost)(RM)";
	if(p_cost == "")
		cout << endl;
	else
	{
		repl_sym_str(p_cost);
		cout << "  >>  " << p_cost << endl;
	}
	cout << "   [8] Price (Sell)(RM)";
	if(p_sell == "")
		cout << endl;
	else
	{
		repl_sym_str(p_sell);
		cout << "  >>  " << p_sell << endl;
	}
	cout << "   [9]   Year of Intro.";
	if(year == "")
		cout << endl;
	else
	{
		repl_date_str(year);
		cout << "  >>  " << year << endl;
	}
	cout << "  [10]  Month of Intro.";
	if(month == "")
		cout << endl;
	else
	{
		repl_month_str(month);
		cout << "  >>  " << month << endl;
	}
	cout << "  [11]    Day of Intro.";
	if(day == "")
		cout << endl << endl;
	else
	{
		repl_date_str(day);
		cout << "  >>  " << day << endl << endl;
	}
	cout << "  [12] Show All Anyway -- [" << get_bool_str(tab_show_a) << "]\n"
			"  [13] Clear Search\n\n"
			"   [0] Back\n\n";
	
	return;
}

void disp_menu_sort()
{
	cout << "\n    Inventory management program\n"
			"  --  [Sort the table ] --\n"
			"   [1] Sort by Code\n"
			"   [2] Sort by Category\n"
			"   [3] Sort by Manufacturer\n"
			"   [4] Sort by Name\n"
			"   [5] Sort by Unit in Store\n"
			"   [6] Sort by Unit Sold\n"
			"   [7] Sort by Price (Cost)\n"
			"   [8] Sort by Price (Sell)\n"
			"   [9] Sort by Year of Introduction\n"
			"  [10] Sort by Month of Introduction\n"
			"  [11] Sort by Day of Introduction\n\n"
			"  [12] Reverse Order\n\n"
			"   [0] Back\n\n";
	
	return;
}

void disp_menu_display()
{
	cout << "\n    Inventory management program\n"
			"  --  [Displayed in table ] --\n"
			"   [1]             Code  >>  " << get_bool_str(table_disp_item_code) << "\n"
			"   [2]         Category  >>  " << get_bool_str(table_disp_item_cat) << "\n"
			"   [3]     Manufacturer  >>  " << get_bool_str(table_disp_item_mfr) << "\n"
			"   [4]             Name  >>  " << get_bool_str(table_disp_item_name) << "\n"
			"   [5]    Unit in Store  >>  " << get_bool_str(table_disp_item_unit_store) << "\n"
			"   [6]        Unit Sold  >>  " << get_bool_str(table_disp_item_unit_sold) << "\n"
			"   [7] Price (Cost)(RM)  >>  " << get_bool_str(table_disp_item_price_cost) << "\n"
			"   [8] Price (Sell)(RM)  >>  " << get_bool_str(table_disp_item_price_sell) << "\n"
			"   [9]   Year of Intro.  >>  " << get_bool_str(table_disp_item_intro_year) << "\n"
			"  [10]  Month of Intro.  >>  " << get_bool_str(table_disp_item_intro_month) << "\n"
			"  [11]    Day of Intro.  >>  " << get_bool_str(table_disp_item_intro_day) << "\n\n"
			"   [0] Back\n\n";
	
	return;
}

void disp_menu_edit(const int index_max)
{
	cout << "\n    Inventory management program\n"
			"  --  [Editing the inventory ] --\n";
	if(index_max != -1)
		cout << "   [Q] Previous Record"
				"   [E] Next Record\n"
				"      [W] Jump to Record\n\n"
				"   [1] New Record\n"
				"   [2] Update Record\n" 
				"   [3] Display Specific Data\n\n"
				"   [4] Delete Specific Data\n"
				"   [5] Delete Record\n";
	else
		cout << "   [1] New Record\n"
				"   [6] Open Inventory\n";
	cout << "\n   [0] Back\n\n";
	
	return;
}

void disp_inv_table(vector<StoreItem> list, const int index_max)
{
	cout << fixed << setprecision(2);
	cout << "     IT Store Inventory -- Item Record\n";
	if(index_max == -1)
		cout << "========================================================\\\\\n"
				"\nNO ITEM(S) RECORDED IN THE LIST, PLEASE ENTER NEW RECORD.\n\n";
	else
	{
		cout << "==|| ( Inventory Table ) ||=============================\\\\\n";
		if(table_disp_item_id)
			cout << " ID  | ";
		if(table_disp_item_code)
			cout << "    CODE | ";
		if(table_disp_item_cat)
			cout << "CATEGORY     | ";
		if(table_disp_item_mfr)
			cout << "            MANUFACTURER | ";
		if(table_disp_item_name)
			cout << "NAME                     | ";
		if(table_disp_item_unit_store)
			cout << "UNIT (STORE) | ";
		if(table_disp_item_unit_sold)
			cout << " UNIT (SOLD) | ";
		if(table_disp_item_price_cost)
			cout << "PRICE (COST) | ";
		if(table_disp_item_price_sell)
			cout << "PRICE (SELL) | ";
		if(table_disp_item_intro_year || table_disp_item_intro_month || table_disp_item_intro_day)
			cout << "INTRODUCED DATE";
		cout << endl;
		if(table_disp_item_id)
			cout << "-----+-";
		if(table_disp_item_code)
			cout << "---------+-";
		if(table_disp_item_cat)
			cout << "-------------+-";
		if(table_disp_item_mfr)
			cout << "-------------------------+-";
		if(table_disp_item_name)
			cout << "-------------------------+-";
		if(table_disp_item_unit_store)
			cout << "-------------+-";
		if(table_disp_item_unit_sold)
			cout << "-------------+-";
		if(table_disp_item_price_cost)
			cout << "-------------+-";
		if(table_disp_item_price_sell)
			cout << "-------------+-";
		if(table_disp_item_intro_year || table_disp_item_intro_month || table_disp_item_intro_day)
			cout << "-----------------";
		cout << endl;
	
		for(int i = 0; i <= index_max; i++)
		{
			if(table_disp_item_id)
				cout << setw(4) << right << i + 1 << " | ";
			if(table_disp_item_code)
			{
				cout << setw(8) << right;
				if(list[i].get_disp_item_code())
					cout << list[i].get_item_code();
				else
					cout << STR_HIDDEN;
				cout << " | ";
			}
			if(table_disp_item_cat)
			{
				cout << setw(12) << left; 
				if(list[i].get_disp_item_cat())
					cout << list[i].get_item_cat();
				else
					cout << STR_HIDDEN;
				cout << " | ";
			}
			if(table_disp_item_mfr)
			{
				cout << setw(24) << right;
				if(list[i].get_disp_item_mfr())
					cout << list[i].get_item_mfr();
				else
					cout << STR_HIDDEN;
				cout << " | ";
			}
			if(table_disp_item_name)
			{
				cout << setw(24) << left;
				if(list[i].get_disp_item_name())
					cout << list[i].get_item_name();
				else
					cout << STR_HIDDEN;
				cout << " | ";
			}
			if(table_disp_item_unit_store)
			{
				cout << setw(12) << right;
				if(list[i].get_disp_item_unit_store())
					cout << list[i].get_item_unit_store();
				else
					cout << STR_HIDDEN;
				cout << " | ";
			}
			if(table_disp_item_unit_sold)
			{
				cout << setw(12) << right;
				if(list[i].get_disp_item_unit_sold())
					cout << list[i].get_item_unit_sold();
				else
					cout << STR_HIDDEN;
				cout << " | ";
			}
			if(table_disp_item_price_cost)
			{
				cout << setw(12) << right;
				if(list[i].get_disp_item_price_cost())
					cout << list[i].get_item_price_cost();
				else
					cout << STR_HIDDEN;
				cout << " | ";
			}
			if(table_disp_item_price_sell)
			{
				cout << setw(12) << right;
				if(list[i].get_disp_item_price_sell())
					cout << list[i].get_item_price_sell();
				else
					cout << STR_HIDDEN;
				cout << " | ";
			}
			if(table_disp_item_intro_year)
			{
				cout << setw(4) << right;
				if(list[i].get_disp_item_intro_year())
					cout << list[i].get_item_intro_year();
				else
					cout << STR_HIDDEN;
			}
			if(table_disp_item_intro_month)
			{
				if(table_disp_item_intro_year)
					cout << ", ";
				cout << left;
				if(list[i].get_disp_item_intro_month())
					cout << list[i].get_item_intro_month();
				else
					cout << STR_HIDDEN << endl;
			}
			if(table_disp_item_intro_day)
			{
				if(!table_disp_item_intro_month)
				{
					if(table_disp_item_intro_year)
						cout << ", ";
					cout << "Monthly day";
				}
				if(list[i].get_disp_item_intro_day())
					cout << " " << list[i].get_item_intro_day();
				else
					cout << " "  << STR_HIDDEN << endl;
			}
			cout << endl;
		}
	}
	cout << "========================================================//\n"
			"  ( -1 value indicates null or no value )\n";
	
	return;
}

void disp_item_detail(vector<StoreItem> list, int index, const int index_max)
{
	cout << fixed << setprecision(2);
	cout << "     IT Store Inventory -- Item Record\n";
	if(index_max != -1)
	{
		cout << "==|| ( Item Details ) ||================================\\\\\n";
		cout << "               ID : ( " << index + 1 << " / " << index_max + 1 << " )\n";
		cout << "             Code : ";
		if(list[index].get_disp_item_code())
			cout << list[index].get_item_code() << endl;
		else
			cout << STR_HIDDEN << endl;
		cout << "         Category : ";
		if(list[index].get_disp_item_cat())
			cout << list[index].get_item_cat() << endl;
		else
			cout << STR_HIDDEN << endl;
		cout << "     Manufacturer : ";
		if(list[index].get_disp_item_mfr())
			cout << list[index].get_item_mfr() << endl;
		else
			cout << STR_HIDDEN << endl;
		cout << "             Name : ";
		if(list[index].get_disp_item_cat())
			cout << list[index].get_item_name() << endl;
		else
			cout << STR_HIDDEN << endl;
		cout << "      Description : ";
		if(list[index].get_disp_item_desc())
			cout << list[index].get_item_desc() << endl;
		else
			cout << STR_HIDDEN << endl;
		cout << "    Unit in Store : ";
		if(list[index].get_disp_item_unit_store())
			cout << list[index].get_item_unit_store() << endl;
		else
			cout << STR_HIDDEN << endl;
		cout << "        Unit Sold : ";
		if(list[index].get_disp_item_unit_sold())
			cout << list[index].get_item_unit_sold() << endl;
		else
			cout  << STR_HIDDEN << endl;
		cout << " Price (Cost)(RM) : ";
		if(list[index].get_disp_item_price_cost())
			cout << list[index].get_item_price_cost() << endl;
		else
			cout << STR_HIDDEN << endl;
		cout << " Price (Sell)(RM) : ";
		if(list[index].get_disp_item_price_sell())
			cout << list[index].get_item_price_sell() << endl;
		else
			cout << STR_HIDDEN << endl;
		cout << "   Year of Intro. : ";
		if(list[index].get_disp_item_intro_year())
			cout << list[index].get_item_intro_year() << endl;
		else
			cout << STR_HIDDEN << endl;
		cout << "  Month of Intro. : ";
		if(list[index].get_disp_item_intro_month())
			cout << list[index].get_item_intro_month() << endl;
		else
			cout << STR_HIDDEN << endl;
		cout << "    Day of Intro. : ";
		if(list[index].get_disp_item_intro_day())
			cout << list[index].get_item_intro_day() << endl;
		else
			cout << STR_HIDDEN << endl;
	}
	else
		cout << "==|| ( Item Details ) ||================================\\\\\n\n"
				"NO ITEM(S) RECORDED IN THE LIST, PLEASE ENTER NEW RECORD.\n\n";
	cout << "========================================================//\n"
			"  ( -1 value indicates null or no value )\n";
	
	return;
}

void disp_item_update(vector<StoreItem> list, int index)
{
	cout << fixed << setprecision(2);
	cout << "\n    Inventory management program\n"
			"  --  [Update data field(s) ] --\n"
			"   [1]             Code  >>  " << list[index].get_item_code() << "\n"
			"   [2]         Category  >>  " << list[index].get_item_cat() << "\n"
			"   [3]     Manufacturer  >>  " << list[index].get_item_mfr() << "\n"
			"   [4]             Name  >>  " << list[index].get_item_name() << "\n"
			"   [5]      Description  >>  " << list[index].get_item_desc() << "\n"
			"   [6]    Unit in Store  >>  " << list[index].get_item_unit_store() << "\n"
			"   [7]        Unit Sold  >>  " << list[index].get_item_unit_sold() << "\n"
			"   [8] Price (Cost)(RM)  >>  " << list[index].get_item_price_cost() << "\n"
			"   [9] Price (Sell)(RM)  >>  " << list[index].get_item_price_sell() << "\n"
			"  [10]   Year of Intro.  >>  " << list[index].get_item_intro_year() << "\n"
			"  [11]  Month of Intro.  >>  " << list[index].get_item_intro_month() << "\n"
			"  [12]    Day of Intro.  >>  " << list[index].get_item_intro_day() << "\n\n"
			"   [0] Back\n\n";
	
	return;
}

void disp_item_delete(vector<StoreItem> list, int index)
{
	cout << fixed << setprecision(2);
	cout << "\n    Inventory management program\n"
			"  --  [Delete data field(s) ] --\n"
			"   [1]             Code  >>  " << list[index].get_item_code() << "\n"
			"   [2]         Category  >>  " << list[index].get_item_cat() << "\n"
			"   [3]     Manufacturer  >>  " << list[index].get_item_mfr() << "\n"
			"   [4]             Name  >>  " << list[index].get_item_name() << "\n"
			"   [5]      Description  >>  " << list[index].get_item_desc() << "\n"
			"   [6]    Unit in Store  >>  " << list[index].get_item_unit_store() << "\n"
			"   [7]        Unit Sold  >>  " << list[index].get_item_unit_sold() << "\n"
			"   [8] Price (Cost)(RM)  >>  " << list[index].get_item_price_cost() << "\n"
			"   [9] Price (Sell)(RM)  >>  " << list[index].get_item_price_sell() << "\n"
			"  [10]   Year of Intro.  >>  " << list[index].get_item_intro_year() << "\n"
			"  [11]  Month of Intro.  >>  " << list[index].get_item_intro_month() << "\n"
			"  [12]    Day of Intro.  >>  " << list[index].get_item_intro_day() << "\n\n"
			"   [0] Back\n\n";
	
	return;
}

void disp_item_display(vector<StoreItem> list, int index)
{
	char s = 's';
	
	cout << fixed << setprecision(2);
	cout << "\n    Inventory management program\n"
			"  --  [Displayed data field(s) ] --\n"
			"   [1]             Code  >>  " << get_bool_str(list[index].get_disp_item_code()) << "\n"
			"   [2]         Category  >>  " << get_bool_str(list[index].get_disp_item_cat()) << "\n"
			"   [3]     Manufacturer  >>  " << get_bool_str(list[index].get_disp_item_mfr()) << "\n"
			"   [4]             Name  >>  " << get_bool_str(list[index].get_disp_item_name()) << "\n"
			"   [5]      Description  >>  " << get_bool_str(list[index].get_disp_item_desc()) << "\n"
			"   [6]    Unit in Store  >>  " << get_bool_str(list[index].get_disp_item_unit_store()) << "\n"
			"   [7]        Unit Sold  >>  " << get_bool_str(list[index].get_disp_item_unit_sold()) << "\n"
			"   [8] Price (Cost)(RM)  >>  " << get_bool_str(list[index].get_disp_item_price_cost()) << "\n"
			"   [9] Price (Sell)(RM)  >>  " << get_bool_str(list[index].get_disp_item_price_sell()) << "\n"
			"  [10]   Year of Intro.  >>  " << get_bool_str(list[index].get_disp_item_intro_year()) << "\n"
			"  [11]  Month of Intro.  >>  " << get_bool_str(list[index].get_disp_item_intro_month()) << "\n"
			"  [12]    Day of Intro.  >>  " << get_bool_str(list[index].get_disp_item_intro_day()) << "\n\n"
			"   [0] Back\n\n";
	
	return;
}

/*
	Index switching function; used to go to specific index.
*/
void index_prev(int &index, const int index_max)
{
	if(index > 0)
		index--;
	else
		index = index_max;
	
	return;
}

void index_next(int &index, const int index_max)
{
	if(index < index_max)
		index++;
	else
		index = 0;
	
	return;
}

//	This jumps to user input index, automated attempts to correct if given out of index with specified logic.
void index_jump(int &index, const int index_max)
{
	int input;
	
	cout << "Jump to: ";
	cin >> input;
	cin.clear();
	cin.ignore(80, '\n');
	if(input > index_max)
		index = index_max;
	else if(input < 1)
		index = 0;
	else
		index = input - 1;
	
	return;
}

/*
	An inefficient but effective method of searching technique for table.
	The way it works:
		1.	Sets the index_max to the size of the vector.
		2.	For every condition; if the search type is not empty, it will search through the table to match the given input.
		3a.	If match found from the index, the index of the list will swap to the front index and incremented by count.;
		3b. The count will increase for each match found from the index; if not found, then it will remain.
		4.	As the index swapped, the index_max will change to the count at the end of search.;
		5a.	With the list index swapped and index_max changed, the table will now only show what was matched from the search.
		5b.	If show all anyway set to true, the successful search result will be on the first index.
*/
void search_item_sort(vector<StoreItem> &list, int &index_max, string code, string cat, string mfr, string name, string month, string u_store, string u_sold, string year, string day, string p_cost, string p_sell, bool tab_show_a)
{
	int pos = -1,
		count = 0,
		temp_i;
	string temp;
	
	index_max = list.size() - 1;
	
	if(code != "")
	{
		for(int i = 0; i <= index_max; i++)
		{
			pos = list[i].get_item_code().find(code);
			if(pos != -1)
			{
				swap(list.at(i), list.at(count));
				count++;
				pos = -1;
			}
		}
		if(!tab_show_a)
			index_max = count - 1;
		count = 0;
	}
	if(cat != "")
	{
		for(int i = 0; i <= index_max; i++)
		{
			for(int j = 0; j < cat.size(); j++)
				cat[j] = toupper(cat[j]);
			temp = list[i].get_item_cat();
			for(int j = 0; j < temp.size(); j++)
				temp[j] = toupper(temp[j]);
			pos = temp.find(cat);
			if(pos != -1)
			{
				swap(list.at(i), list.at(count));
				count++;
				pos = -1;
			}
		}
		if(!tab_show_a)
			index_max = count - 1;
		count = 0;
	}
	if(mfr != "")
	{
		for(int i = 0; i <= index_max; i++)
		{
			for(int j = 0; j < mfr.size(); j++)
				mfr[j] = toupper(mfr[j]);
			temp = list[i].get_item_mfr();
			for(int j = 0; j < temp.size(); j++)
				temp[j] = toupper(temp[j]);
			pos = temp.find(mfr);
			if(pos != -1)
			{
				swap(list.at(i), list.at(count));
				count++;
				pos = -1;
			}
		}
		if(!tab_show_a)
			index_max = count - 1;
		count = 0;
	}
	if(name != "")
	{
		for(int i = 0; i <= index_max; i++)
		{
			for(int j = 0; j < name.size(); j++)
				name[j] = toupper(name[j]);
			temp = list[i].get_item_name();
			for(int j = 0; j < temp.size(); j++)
				temp[j] = toupper(temp[j]);
			pos = temp.find(name);
			if(pos != -1)
			{
				swap(list.at(i), list.at(count));
				count++;
				pos = -1;
			}
		}
		if(!tab_show_a)
			index_max = count - 1;
		count = 0;
	}
	if(u_store != "")
	{
		cout << count << endl << endl;
		for(int i = 0; i <= index_max; i++)
		{
			temp = u_store;
			if(temp[0] == '<')
			{
				temp.erase(remove(temp.begin(), temp.end(), '<'), temp.end());
				temp_i = atoi(temp.c_str());
				if(temp_i > list[i].get_item_unit_store())
				{
					swap(list.at(i), list.at(count));
					count++;
				}
			}
			else if(temp[0] == '>')
			{
				temp.erase(remove(temp.begin(), temp.end(), '>'), temp.end());
				temp_i = atoi(temp.c_str());
				if(temp_i < list[i].get_item_unit_store())
				{
					swap(list.at(i), list.at(count));
					count++;
				}
			}
			else
			{
				temp_i = atoi(temp.c_str());
				if(temp_i == list[i].get_item_unit_store())
				{
					swap(list.at(i), list.at(count));
					count++;
				}
			}
		}
		if(!tab_show_a)
			index_max = count - 1;
		count = 0;
	}
	if(u_sold != "")
	{
		for(int i = 0; i <= index_max; i++)
		{
			temp = u_sold;
			if(temp[0] == '<')
			{
				temp.erase(remove(temp.begin(), temp.end(), '<'), temp.end());
				temp_i = atoi(temp.c_str());
				if(temp_i > list[i].get_item_unit_sold())
				{
					swap(list.at(i), list.at(count));
					count++;
				}
			}
			else if(temp[0] == '>')
			{
				temp.erase(remove(temp.begin(), temp.end(), '>'), temp.end());
				temp_i = atoi(temp.c_str());
				if(temp_i < list[i].get_item_unit_sold())
				{
					swap(list.at(i), list.at(count));
					count++;
				}
			}
			else
			{
				temp_i = atoi(temp.c_str());
				if(temp_i == list[i].get_item_unit_sold())
				{
					swap(list.at(i), list.at(count));
					count++;
				}
			}
		}
		if(!tab_show_a)
			index_max = count - 1;
		count = 0;
	}
	if(p_cost != "")
	{
		for(int i = 0; i <= index_max; i++)
		{
			temp = p_cost;
			if(temp[0] == '<')
			{
				temp.erase(remove(temp.begin(), temp.end(), '<'), temp.end());
				temp_i = atoi(temp.c_str());
				if(temp_i > list[i].get_item_price_cost())
				{
					swap(list.at(i), list.at(count));
					count++;
				}
			}
			else if(temp[0] == '>')
			{
				temp.erase(remove(temp.begin(), temp.end(), '>'), temp.end());
				temp_i = atoi(temp.c_str());
				if(temp_i < list[i].get_item_price_cost())
				{
					swap(list.at(i), list.at(count));
					count++;
				}
			}
			else
			{
				temp_i = atoi(temp.c_str());
				if(temp_i == list[i].get_item_price_cost())
				{
					swap(list.at(i), list.at(count));
					count++;
				}
			}
		}
		if(!tab_show_a)
			index_max = count - 1;
		count = 0;
	}
	if(p_sell != "")
	{
		for(int i = 0; i <= index_max; i++)
		{
			temp = p_sell;
			if(temp[0] == '<')
			{
				temp.erase(remove(temp.begin(), temp.end(), '<'), temp.end());
				temp_i = atoi(temp.c_str());
				if(temp_i > list[i].get_item_price_sell())
				{
					swap(list.at(i), list.at(count));
					count++;
				}
			}
			else if(temp[0] == '>')
			{
				temp.erase(remove(temp.begin(), temp.end(), '>'), temp.end());
				temp_i = atoi(temp.c_str());
				if(temp_i < list[i].get_item_price_sell())
				{
					swap(list.at(i), list.at(count));
					count++;
				}
			}
			else
			{
				temp_i = atoi(temp.c_str());
				if(temp_i == list[i].get_item_price_sell())
				{
					swap(list.at(i), list.at(count));
					count++;
				}
			}
		}
		if(!tab_show_a)
			index_max = count - 1;
		count = 0;
	}
	if(year != "")
	{
		for(int i = 0; i <= index_max; i++)
		{
			temp = year;
			if(temp[0] == '<')
			{
				temp.erase(remove(temp.begin(), temp.end(), '<'), temp.end());
				temp_i = atoi(temp.c_str());
				if(temp_i > list[i].get_item_intro_year())
				{
					swap(list.at(i), list.at(count));
					count++;
				}
			}
			else if(temp[0] == '>')
			{
				temp.erase(remove(temp.begin(), temp.end(), '>'), temp.end());
				temp_i = atoi(temp.c_str());
				if(temp_i < list[i].get_item_intro_year())
				{
					swap(list.at(i), list.at(count));
					count++;
				}
			}
			else
			{
				temp_i = atoi(temp.c_str());
				if(temp_i == list[i].get_item_intro_year())
				{
					swap(list.at(i), list.at(count));
					count++;
				}
			}
		}
		if(!tab_show_a)
			index_max = count - 1;
		count = 0;
	}
	if(month != "")
	{
		for(int i = 0; i <= index_max; i++)
		{
			temp = month;
			if(temp[0] == '<')
			{
				temp.erase(remove(temp.begin(), temp.end(), '<'), temp.end());
				temp_i = atoi(temp.c_str());
				if(temp_i > list[i].get_item_intro_month(i))
				{
					swap(list.at(i), list.at(count));
					count++;
				}
			}
			else if(temp[0] == '>')
			{
				temp.erase(remove(temp.begin(), temp.end(), '>'), temp.end());
				temp_i = atoi(temp.c_str());
				if(temp_i < list[i].get_item_intro_month(i))
				{
					swap(list.at(i), list.at(count));
					count++;
				}
			}
			else
			{
				temp_i = atoi(temp.c_str());
				if(temp_i == list[i].get_item_intro_month(i))
				{
					swap(list.at(i), list.at(count));
					count++;
				}
			}
		}
		if(!tab_show_a)
			index_max = count - 1;
		count = 0;
	}
	if(day != "")
	{
		for(int i = 0; i <= index_max; i++)
		{
			temp = day;
			if(temp[0] == '<')
			{
				temp.erase(remove(temp.begin(), temp.end(), '<'), temp.end());
				temp_i = atoi(temp.c_str());
				if(temp_i > list[i].get_item_intro_day())
				{
					swap(list.at(i), list.at(count));
					count++;
				}
			}
			else if(temp[0] == '>')
			{
				temp.erase(remove(temp.begin(), temp.end(), '>'), temp.end());
				temp_i = atoi(temp.c_str());
				if(temp_i < list[i].get_item_intro_day())
				{
					swap(list.at(i), list.at(count));
					count++;
				}
			}
			else
			{
				temp_i = atoi(temp.c_str());
				if(temp_i == list[i].get_item_intro_day())
				{
					swap(list.at(i), list.at(count));
					count++;
				}
			}
		}
		if(!tab_show_a)
			index_max = count - 1;
		count = 0;
	}
	
	return;
}

/*
	A sort function that modifies the arrangement of the index, in which changes the row position in the table.
*/
void sort_item_code(vector<StoreItem> &list, int index_max)
{
	bool swap_check = true;
	
	while(swap_check)
	{
		swap_check = false;
		for(int i = 0; i < index_max; i++)
		{
			if(list[i].get_item_code() > list[i + 1].get_item_code())
			{
				swap(list.at(i), list.at(i + 1));
				swap_check = true;
			}
		}
	}
	
	return;
}

void sort_item_cat(vector<StoreItem> &list, int index_max)
{
	bool swap_check = true;
	
	while(swap_check)
	{
		swap_check = false;
		for(int i = 0; i < index_max; i++)
		{
			if(list[i].get_item_cat() > list[i + 1].get_item_cat())
			{
				swap(list.at(i), list.at(i + 1));
				swap_check = true;
			}
		}
	}
	
	return;
}

void sort_item_mfr(vector<StoreItem> &list, int index_max)
{
	bool swap_check = true;
	
	while(swap_check)
	{
		swap_check = false;
		for(int i = 0; i < index_max; i++)
		{
			if(list[i].get_item_mfr() > list[i + 1].get_item_mfr())
			{
				swap(list.at(i), list.at(i + 1));
				swap_check = true;
			}
		}
	}
	
	return;
}

void sort_item_name(vector<StoreItem> &list, int index_max)
{
	bool swap_check = true;
	
	while(swap_check)
	{
		swap_check = false;
		for(int i = 0; i < index_max; i++)
		{
			if(list[i].get_item_name() > list[i + 1].get_item_name())
			{
				swap(list.at(i), list.at(i + 1));
				swap_check = true;
			}
		}
	}
	
	return;
}

void sort_item_unit_store(vector<StoreItem> &list, int index_max)
{
	bool swap_check = true;
	
	while(swap_check)
	{
		swap_check = false;
		for(int i = 0; i < index_max; i++)
		{
			if(list[i].get_item_unit_store() > list[i + 1].get_item_unit_store())
			{
				swap(list.at(i), list.at(i + 1));
				swap_check = true;
			}
		}
	}
	
	return;
}

void sort_item_unit_sold(vector<StoreItem> &list, int index_max)
{
	bool swap_check = true;
	
	while(swap_check)
	{
		swap_check = false;
		for(int i = 0; i < index_max; i++)
		{
			if(list[i].get_item_unit_sold() > list[i + 1].get_item_unit_sold())
			{
				swap(list.at(i), list.at(i + 1));
				swap_check = true;
			}
		}
	}
	
	return;
}

void sort_item_price_cost(vector<StoreItem> &list, int index_max)
{
	bool swap_check = true;
	
	while(swap_check)
	{
		swap_check = false;
		for(int i = 0; i < index_max; i++)
		{
			if(list[i].get_item_price_cost() > list[i + 1].get_item_price_cost())
			{
				swap(list.at(i), list.at(i + 1));
				swap_check = true;
			}
		}
	}
	
	return;
}

void sort_item_price_sell(vector<StoreItem> &list, int index_max)
{
	bool swap_check = true;
	
	while(swap_check)
	{
		swap_check = false;
		for(int i = 0; i < index_max; i++)
		{
			if(list[i].get_item_price_sell() > list[i + 1].get_item_price_sell())
			{
				swap(list.at(i), list.at(i + 1));
				swap_check = true;
			}
		}
	}
	
	return;
}

void sort_item_intro_year(vector<StoreItem> &list, int index_max)
{
	bool swap_check = true;
	int i = 0;
	
	while(swap_check)
	{
		swap_check = false;
		for(int i = 0; i < index_max; i++)
		{
			if(list[i].get_item_intro_day() > list[i + 1].get_item_intro_day())
			{
				swap(list.at(i), list.at(i + 1));
				swap_check = true;
			}
		}
	}
	swap_check = true;
	while(swap_check)
	{
		swap_check = false;
		for(int i = 0; i < index_max; i++)
		{
			if(list[i].get_item_intro_month(i) > list[i + 1].get_item_intro_month(i))
			{
				swap(list.at(i), list.at(i + 1));
				swap_check = true;
			}
		}
	}
	swap_check = true;
	while(swap_check)
	{
		swap_check = false;
		for(int i = 0; i < index_max; i++)
		{
			if(list[i].get_item_intro_year() < list[i + 1].get_item_intro_year())
			{
				swap(list.at(i), list.at(i + 1));
				swap_check = true;
			}
		}
	}
	
	return;
}

void sort_item_intro_month(vector<StoreItem> &list, int index_max)
{
	bool swap_check = true;
	int i = 0;
	
	while(swap_check)
	{
		swap_check = false;
		for(int i = 0; i < index_max; i++)
		{
			if(list[i].get_item_intro_day() > list[i + 1].get_item_intro_day())
			{
				swap(list.at(i), list.at(i + 1));
				swap_check = true;
			}
		}
	}
	swap_check = true;
	while(swap_check)
	{
		swap_check = false;
		for(int i = 0; i < index_max; i++)
		{
			if(list[i].get_item_intro_year() < list[i + 1].get_item_intro_year())
			{
				swap(list.at(i), list.at(i + 1));
				swap_check = true;
			}
		}
	}
	swap_check = true;
	while(swap_check)
	{
		swap_check = false;
		for(int i = 0; i < index_max; i++)
		{
			if(list[i].get_item_intro_month(i) > list[i + 1].get_item_intro_month(i))
			{
				swap(list.at(i), list.at(i + 1));
				swap_check = true;
			}
		}
	}
	
	return;
}

void sort_item_intro_day(vector<StoreItem> &list, int index_max)
{
	bool swap_check = true;
	int i = 0;
	
	while(swap_check)
	{
		swap_check = false;
		for(int i = 0; i < index_max; i++)
		{
			if(list[i].get_item_intro_year() < list[i + 1].get_item_intro_year())
			{
				swap(list.at(i), list.at(i + 1));
				swap_check = true;
			}
		}
	}
	swap_check = true;
	while(swap_check)
	{
		swap_check = false;
		for(int i = 0; i < index_max; i++)
		{
			if(list[i].get_item_intro_month(i) > list[i + 1].get_item_intro_month(i))
			{
				swap(list.at(i), list.at(i + 1));
				swap_check = true;
			}
		}
	}
	swap_check = true;
	while(swap_check)
	{
		swap_check = false;
		for(int i = 0; i < index_max; i++)
		{
			if(list[i].get_item_intro_day() > list[i + 1].get_item_intro_day())
			{
				swap(list.at(i), list.at(i + 1));
				swap_check = true;
			}
		}
	}
	
	return;
}

/*
	Look up on each item(s) in inventory and allowing modification of the inventory.
*/
//	User must input all of the data prompted.
void record_new(vector<StoreItem> &inv_list, int &item_index_max)
{
	StoreItem inv_new;
	
	system("cls");
	for(int i = 0; i < MAX_ENDL; i++)
		cout << endl;
	cout << "  --  [ Entering New Record ]  --\n";
	inv_new.set_item_code(inv_list);
	inv_new.set_item_cat();
	inv_new.set_item_mfr();
	inv_new.set_item_name();
	inv_new.set_item_desc();
	inv_new.set_item_unit_store();
	inv_new.set_item_unit_sold();
	inv_new.set_item_price_cost();
	inv_new.set_item_price_sell();
	inv_new.set_item_intro_year();
	inv_new.set_item_intro_month();
	inv_new.set_item_intro_day();
	
	inv_list.push_back(inv_new);
	item_index_max = inv_list.size() - 1;
	
	for(int i = 0; i < MAX_ENDL; i++)
		cout << endl;
	
	return;
}

//	Modifying an item in inventory by updating/changing specific data.
void record_update(vector<StoreItem> &inv_list, int item_index, int item_index_max)
{
	int input = -1;
	while(input != 0)
	{
		system("cls");
		for(int i = 0; i < MAX_ENDL; i++)
			cout << endl;
		disp_item_detail(inv_list, item_index, item_index_max);
		disp_item_update(inv_list, item_index);
		
		while(true)
		{
			cout << "Enter number from the bracket to update specific data: ";
			cin >> input;
			if(cin.fail())
			{
				cout << "Input error!\n"
						"Please enter an integer.\n";
				cin.clear();
				cin.ignore(80, '\n');
			}
			else
				break;
		}
		cin.clear();
		cin.ignore(80, '\n');
		switch(input)
		{
			case 1:
				inv_list[item_index].set_item_code(inv_list);
				break;
			case 2:
				inv_list[item_index].set_item_cat();
				break;
			case 3:
				inv_list[item_index].set_item_mfr();
				break;
			case 4:
				inv_list[item_index].set_item_name();
				break;
			case 5:
				inv_list[item_index].set_item_desc();
				break;
			case 6:
				inv_list[item_index].set_item_unit_store();
				break;
			case 7:
				inv_list[item_index].set_item_unit_sold();
				break;
			case 8:
				inv_list[item_index].set_item_price_cost();
				break;
			case 9:
				inv_list[item_index].set_item_price_sell();
				break;
			case 10:
				inv_list[item_index].set_item_intro_year();
				break;
			case 11:
				inv_list[item_index].set_item_intro_month();
				break;
			case 12:
				inv_list[item_index].set_item_intro_day();
				break;
			case 0:
				break;
			default:
				cout << "Input error!\nPut the number given in the bracket.\n";
		}
	}
	
	return;
}

//	Deleting a specific data of an item in inventory (by changing the data value to -1).
//	Does not delete the item in the inventory.
void record_delete(vector<StoreItem> &inv_list, int item_index, int item_index_max)
{
	int input = -1;
	while(input != 0)
	{
		system("cls");
		for(int i = 0; i < MAX_ENDL; i++)
			cout << endl;
		disp_item_detail(inv_list, item_index, item_index_max);
		disp_item_delete(inv_list, item_index);
	
		while(true)
		{
			cout << "Deleting the data will turn the value to -1.\n"
					"Enter number from the bracket to delete specific data: ";
			cin >> input;
			if(cin.fail())
			{
				cout << "Input error!\n"
						"Please enter an integer.\n";
				cin.clear();
				cin.ignore(80, '\n');
			}
			else
				break;
		}
		cin.clear();
		cin.ignore(80, '\n');
		switch(input)
		{
			case 1:
				inv_list[item_index].set_item_code("-1");
				break;
			case 2:
				inv_list[item_index].set_item_cat("-1");
				break;
			case 3:
				inv_list[item_index].set_item_mfr("-1");
				break;
			case 4:
				inv_list[item_index].set_item_name("-1");
				break;
			case 5:
				inv_list[item_index].set_item_desc("-1");
				break;
			case 6:
				inv_list[item_index].set_item_unit_store(-1);
				break;
			case 7:
				inv_list[item_index].set_item_unit_sold(-1);
				break;
			case 8:
				inv_list[item_index].set_item_price_cost(-1);
				break;
			case 9:
				inv_list[item_index].set_item_price_sell(-1);
				break;
			case 10:
				inv_list[item_index].set_item_intro_year(-1);
				break;
			case 11:
				inv_list[item_index].set_item_intro_month("-1");
				break;
			case 12:
				inv_list[item_index].set_item_intro_day(-1);
				break;
			case 0:
				break;
			default:
				cout << "Input error!\nPut the number given in the bracket.\n";
		}
	}
	
	return;
}

//	Prompts the user to delete the item from the inventory completely.
void record_delete_all(vector<StoreItem> &inv_list, int &item_index, int &item_index_max)
{
	char choice;
	
	system("cls");
	for(int i = 0; i < MAX_ENDL; i++)
		cout << endl;
	do
	{
		cout << "You are deleting ID " << item_index + 1 << " | CODE " << inv_list[item_index].get_item_code() << endl;
		cout << endl << "Enter 'Y' to confirm or 'N' to cancel" << endl;
		cin >> choice;
	} while(tolower(choice) != 'y' && tolower(choice) != 'n');
	if(tolower(choice) == 'y')
	{
		for(int i = 0; i < MAX_ENDL; i++)
			cout << endl;
		inv_list.erase(inv_list.begin()+item_index);
		item_index_max = inv_list.size() - 1;
		if(item_index > item_index_max)
			item_index--;
	}
	
	return;
}

//	Displaying/hiding the specific data of the specific item.
void record_display(vector<StoreItem> &inv_list, int item_index, int item_index_max)
{
	int input = -1;
	
	while(input != 0)
	{
		system("cls");
		for(int i = 0; i < MAX_ENDL; i++)
			cout << endl;
		disp_item_detail(inv_list, item_index, item_index_max);
		disp_item_display(inv_list, item_index);
		
		while(true)
		{
			cout << "Enter number from the bracket to toggle display: ";
			cin >> input;
			if(cin.fail())
			{
				cout << "Input error!\n"
						"Please enter an integer.\n";
				cin.clear();
				cin.ignore(80, '\n');
			}
			else
				break;
		}
		cin.clear();
		cin.ignore(80, '\n');
		switch(input)
		{
			case 1:
				inv_list[item_index].toggle_disp_item_code();
				break;
			case 2:
				inv_list[item_index].toggle_disp_item_cat();
				break;
			case 3:
				inv_list[item_index].toggle_disp_item_mfr();
				break;
			case 4:
				inv_list[item_index].toggle_disp_item_name();
				break;
			case 5:
				inv_list[item_index].toggle_disp_item_desc();
				break;
			case 6:
				inv_list[item_index].toggle_disp_item_unit_store();
				break;
			case 7:
				inv_list[item_index].toggle_disp_item_unit_sold();
				break;
			case 8:
				inv_list[item_index].toggle_disp_item_price_cost();
				break;
			case 9:
				inv_list[item_index].toggle_disp_item_price_sell();
				break;
			case 10:
				inv_list[item_index].toggle_disp_item_intro_year();
				break;
			case 11:
				inv_list[item_index].toggle_disp_item_intro_month();
				break;
			case 12:
				inv_list[item_index].toggle_disp_item_intro_day();
				break;
			case 0:
				break;
			default:
				cout << "Input error!\nPut the number given in the bracket.\n";
		}
	}
	
	return;
}

/*
	Used in search function; allowing only valid string input.
*/
string set_search_str()
{
	string str;
	cin >> str;
	cin.clear();
	cin.ignore(80, '\n');
	if(str == "-1")
		return "";
	
	return str;
}

string set_search_str_line()
{
	string str;
	getline(cin, str);
	if(str == "-1")
		return "";
	
	return str;
}

//	Due to search being used completely out from string, this is used to determine whether the input is integer.
//	This function allows the use of '<' and '>' character as an indication.
string set_search_num()
{
	string str;
	getline(cin, str);
	if(str == "-1")
		return "";
	if(str != "")
	{
		for(int i = 1; i < str.size(); i++)
			if(!isdigit(str[i]) && str[i] != '.')
				return "";
		if(!isdigit(str[0]) && str[0] != '<' && str[0] != '>')
			return "";
	}
	
	return str;
}

/*
	Used in search function; replaces the part of the string with another.
*/
//	Replaces '<' or '>' in string to "Before" or "After".
string repl_date_str(string &str)
{
	if(str[0] == '<')
	{
		str.replace(0, 0, "Before ");
		str.erase(remove(str.begin(), str.end(), '<'), str.end());
	}
	if(str[0] == '>')
	{
		str.replace(0, 0, "After ");
		str.erase(remove(str.begin(), str.end(), '>'), str.end());
	}
	
	return str;
}

//	Replaces '<' or '>' in string to "Before" or "After", as well as integer to standard month name.
string repl_month_str(string &str)
{
	string temp = "";
	
	if(str[0] == '<')
	{
		temp = "Before ";
		str.erase(remove(str.begin(), str.end(), '<'), str.end());
	}
	if(str[0] == '>')
	{
		temp = "After ";
		str.erase(remove(str.begin(), str.end(), '>'), str.end());
	}
	if(str == "1")
		str = "January";
	else if(str == "2")
		str = "February";
	else if(str == "3")
		str = "March";
	else if(str == "4")
		str = "April";
	else if(str == "5")
		str = "May";
	else if(str == "6")
		str = "June";
	else if(str == "7")
		str = "July";
	else if(str == "8")
		str = "August";
	else if(str == "9")
		str = "September";
	else if(str == "10")
		str = "October";
	else if(str == "11")
		str = "November";
	else if(str == "12")
		str = "December";
	
	if(temp != "")
		str.replace(0, 0, temp);
	
	return str;
}

//	Replaces '<' or '>' in string to "Less than" or "More than".
string repl_sym_str(string &str)
{
	if(str[0] == '<')
	{
		str.replace(0, 0, "Less than ");
		str.erase(remove(str.begin(), str.end(), '<'), str.end());
	}
	if(str[0] == '>')
	{
		str.replace(0, 0, "More than ");
		str.erase(remove(str.begin(), str.end(), '>'), str.end());
	}
	
	return str;
}

/*
	Short simple code for boolean.
*/
//	Return the boolean as a string.
string get_bool_str(bool boolean)
{
	if(boolean)
		return "True";
	
	return "False";
}

//	Toggle the boolean by switching from true to false and false to true.
bool toggle_bool(bool &boolean)
{
	if(boolean)
		boolean = false;
	else
		boolean = true;
	
	return 0;
}