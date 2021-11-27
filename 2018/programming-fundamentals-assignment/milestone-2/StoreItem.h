#ifndef STOREITEM_H
#define STOREITEM_H

#include <vector>
#include <string>
using namespace std;

class StoreItem
{
private:
	string item_code,
		   item_cat,
		   item_mfr,
		   item_name,
		   item_desc,
		   item_intro_month;
	int item_unit_store,
		item_unit_sold,
		item_intro_year,
		item_intro_day;
	double item_price_cost,
		   item_price_sell;
	bool disp_item_code,
		 disp_item_cat,
		 disp_item_mfr,
		 disp_item_name,
		 disp_item_desc,
		 disp_item_unit_store,
		 disp_item_unit_sold,
		 disp_item_price_cost,
		 disp_item_price_sell,
		 disp_item_intro_year,
		 disp_item_intro_month,
		 disp_item_intro_day;
public:
	StoreItem();
	
	void file_fetch(vector<StoreItem> &inv_list),
		 file_save(vector<StoreItem> inv_list),
		 set_item_code(vector<StoreItem> inv_list),
		 set_item_code(string str),
		 set_item_cat(),
		 set_item_cat(string str),
		 set_item_mfr(),
		 set_item_mfr(string str),
		 set_item_name(),
		 set_item_name(string str),
		 set_item_desc(),
		 set_item_desc(string str),
		 set_item_unit_store(),
		 set_item_unit_store(int num),
		 set_item_unit_sold(),
		 set_item_unit_sold(int num),
		 set_item_price_cost(),
		 set_item_price_cost(double num),
		 set_item_price_sell(),
		 set_item_price_sell(double num),
		 set_item_intro_year(),
		 set_item_intro_year(int num),
		 set_item_intro_month(),
		 set_item_intro_month(string str),
		 set_item_intro_day(),
		 set_item_intro_day(int num),
		 set_disp_item_code(int num),
		 set_disp_item_cat(int num),
		 set_disp_item_mfr(int num),
		 set_disp_item_name(int num),
		 set_disp_item_desc(int num),
		 set_disp_item_unit_store(int num),
		 set_disp_item_unit_sold(int num),
		 set_disp_item_price_cost(int num),
		 set_disp_item_price_sell(int num),
		 set_disp_item_intro_year(int num),
		 set_disp_item_intro_month(int num),
		 set_disp_item_intro_day(int num),
		 toggle_disp_item_code(),
		 toggle_disp_item_cat(),
		 toggle_disp_item_mfr(),
		 toggle_disp_item_name(),
		 toggle_disp_item_desc(),
		 toggle_disp_item_unit_store(),
		 toggle_disp_item_unit_sold(),
		 toggle_disp_item_price_cost(),
		 toggle_disp_item_price_sell(),
		 toggle_disp_item_intro_year(),
		 toggle_disp_item_intro_month(),
		 toggle_disp_item_intro_day();
	
	string get_item_code(),
		   get_item_cat(),
		   get_item_mfr(),
		   get_item_name(),
		   get_item_desc(),
		   get_item_intro_month();
	int get_item_unit_store(),
		get_item_unit_sold(),
		get_item_intro_year(),
		get_item_intro_month(int i),
		get_item_intro_day();
	double get_item_price_cost(),
		   get_item_price_sell();
	bool get_disp_item_code(),
		 get_disp_item_cat(),
		 get_disp_item_mfr(),
		 get_disp_item_name(),
		 get_disp_item_desc(),
		 get_disp_item_unit_store(),
		 get_disp_item_unit_sold(),
		 get_disp_item_price_cost(),
		 get_disp_item_price_sell(),
		 get_disp_item_intro_year(),
		 get_disp_item_intro_month(),
		 get_disp_item_intro_day();
	
};

#endif