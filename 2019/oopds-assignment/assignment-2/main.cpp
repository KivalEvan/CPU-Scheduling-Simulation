#include <iostream>															//  Standard library
#include <iomanip>															//  For user interface purposes
#include <fstream>															//  File streaming; for input and output of the file(s)
#include <sstream>															//	Converting string to integer
#include <string>															//	Self-explanatory
#include <vector>															//	To dynamically allocate words
#include <map>																//	To sort and pair the words with indexes
#include <algorithm>														//	For string modification
using namespace std;

string clean_word(string word) {											//	Filter out non-alphanumeric character and lowercasing the alphabet
	string temp = "";
	for(int i = 0; i < word.length(); i++) {
		if(isalnum(word[i])) {
			if(isalpha(word[i])) {
				word[i] = tolower(word[i]);
				temp += word[i];
			}
			else temp += word[i];
		}
	}

	return temp;
}
void get_word_stop(vector<string>& word_list) {								//	Open and read the file, stores word stop into vector
	string file_name,
		   temp_str;

	file_name = "StopWords.txt";
	ifstream file_read(file_name.c_str());
	
	if(!file_read.is_open()) {												//	Return if file is not found
		cout << file_name << " not found.\n";
		return;
	}
	
	while(file_read >> temp_str) word_list.push_back(clean_word(temp_str));

	file_read.close();

	return;
}
																			//	Open and read the file, stores word index into multimap
void get_word_index(multimap<string, string>& word_list, const vector<string> word_forbid) {
	string file_name,
		   temp_str,
		   temp_str2,
		   index;

	for(int i = 1; i <= 10; i++) {
		file_name = to_string(i) + ".txt";
		ifstream file_read(file_name.c_str());

		if(file_read.is_open()) {
			bool check;
			int line = 1;
			while(getline(file_read, temp_str)) {
				string token;
				index = to_string(line) + '_' + file_name;					//	Index is stored as (line number)_(file name); '_' indicates line
				while (token != temp_str) {
					check = true;
					token = temp_str.substr(0, temp_str.find_first_of(" "));
					temp_str = temp_str.substr(temp_str.find_first_of(" ") + 1);
					temp_str2 = clean_word(token);
					for(int i = 0; i < word_forbid.size(); i++)
						if(word_forbid[i] == temp_str2) check = false;
					if(check && temp_str2 != "") word_list.insert(pair<string, string>(temp_str2, index));
				}
				line++;
			}
			file_read.close();
		}
		else cout << file_name << " not found.\n";
	}

	return;
}
																			//	Search for word from index and display results with line and text file it occurs
void search_result(multimap<string, string> word_list, string word_search) {
	string temp,
		   temp_str,
		   line,
		   file_name;
	int line_int,
		count = 0,
		i;
	
	for(multimap<string, string>::iterator it = word_list.begin(); it != word_list.end(); it++) {
		if(it->first == word_search) {										//	If the iterator matched the word search, begin to look up the file
			file_name = "";
			line = "";
			temp = it->second;
			for(i = 0; i < temp.length(); i++) {							//	Breaking apart index into line number and file name
				if(temp[i] != '_') line += temp[i];
				else break;
			}
			for(int j = i + 1; j < temp.length(); j++) file_name += temp[j];
			
			line_int = atoi(line.c_str());

			ifstream file_read(file_name.c_str());

			if(file_read.is_open()) {										//	In case of the file was deleted while program was running
				count = 0;
				while(getline(file_read, temp_str)) {
					count++;
					if(count == line_int) {									//	Match the line number with count
						cout << "word \"" <<word_search << "\" found inside " << file_name << " file on line " << line_int << " : " << temp_str << endl;
						break;												//	Once found, break the loop
					}
				}
				file_read.close();
			}
		}
	}

	return;
}
string input_string() {														//	Filtering input string
	string str = "",
		   temp = "";
	while(str == "") {
		cout << "Enter '0' to exit the program \n"
			 << "Search for words: ";
		cin >> str;
		cin.clear();
		cin.ignore(80, '\n');
	}
	for(int i = 0; i < str.length(); i++) {
		str[i] = tolower(str[i]);
		temp += str[i];
	}
	
	return temp;
}
void printUI(int idx_stop, int idx_word) {									//	Prints user interface menu
	cout << "\n\n\n";
	if(idx_stop > 0)
		cout << idx_stop << " word(s) filtered" << endl;
	if(idx_word > 0)
		cout << idx_word << " word occurrence(s) found" << endl;
	cout << "\n >|>|  Word Search\n";

	return;
}
int main()																	//	Main program starts here
{
	vector<string> word_stop;												//	List of word stop
	multimap<string, string> word_index;									//	List of word index as (words, index)
	string input_word;
	
	get_word_stop(word_stop);												//	Loads word stop from the text file
	get_word_index(word_index, word_stop);									//	Loads word index from the text file with filtered word

	system("cls");
	while(true) {
		printUI(word_stop.size(), word_index.size());
		input_word = input_string();
		if(input_word == "0") break;
																			//	Count the input_word occurrences in word_index
		cout << endl << word_index.count(input_word) << " occurrence(s) for word \"" << input_word << "\"" << endl;
		search_result(word_index, input_word);								//	Prints result from the search
	}
	system("pause");

	return 0;
}