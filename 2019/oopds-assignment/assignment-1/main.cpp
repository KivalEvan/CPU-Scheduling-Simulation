#include <iostream>															//  Standard library
#include <iomanip>															//  For user interface purposes
#include <fstream>															//  File streaming; for input and output of the file(s)
#include <string>															//  Self-explanatory
#include <vector>															//  To dynamically allocate with an array
#include <cstdlib>															//  For rand() function
#include <ctime>															//  Using time as seed for srand() function
using namespace std;

class Shape {																//	Abstract class object
	private:
		char tag;															//	Shape tagged with a character symbol
		int x, y;															//	Used to set origin point of the shape
	public:
		Shape() {															//	Default constructor
			setTag('A');
			setPos(0, 0);
			cout << "Construct Shape " << tag << " at (" << getX() << "," << getY() << ")..." << endl;
			}
		Shape(char t) {														//	Constructor with only one parameter
			setTag(t);
			setPos(0, 0);
			cout << "Construct Shape " << tag << " at (" << getX() << "," << getY() << ")..." << endl;
			}
		Shape(char t, int pos_x, int pos_y) {								//	Constructor with three parameters
			setTag(t);
			setPos(pos_x, pos_y);
			cout << "Construct Shape " << tag << " at (" << getX() << "," << getY() << ")..." << endl;
			}
		void setPos(int pos_x, int pos_y) { setX(pos_x); setY(pos_y); }		//	Set position
		void setX(int pos_x) { x = pos_x; }									//	Set individual position
		void setY(int pos_y) { y = pos_y; }
		void setTag(char t) { tag = (t == '.') ? 'A' : t; }					//	Set character tag
		int getX() { return x; }											//	Return variables
		int getY() { return y; }
		char getTag() { return tag; }
		virtual bool findSpot(vector<vector<char>> reso) = 0;				//	Pure virtual functions
		virtual bool checkArea(vector<vector<char>> reso) = 0;
		virtual void draw(vector<vector<char>>& reso) = 0;
		~Shape() { cout << "Destruct Shape " << tag << "..." << endl; }
};

class Square: public Shape {												//	Shape-type classes inhereted with Shape class object
	private:
		int side;															//	Square only have one variable, which is the side of the square; all sides are equal
	public:
		Square(): Shape() {
			side = 1;
			cout << "Construct Square " << getTag() << " with size of " << side << 'x' << side << "..." << endl;
		}
		Square(char t, int s): Shape(t) {
			side = s;
			cout << "Construct Square " << getTag() << " with size of " << side << 'x' << side << "..." << endl;
		}
		Square(char t, int x, int y, int s): Shape(t, x, y) {
			side = s;
			cout << "Construct Square " << getTag() << " with size of " << side << 'x' << side << "..." << endl;
		}
		void setSide(int s) { side = s; }
		int getSide() { return side; }
		bool findSpot(vector<vector<char>> reso) {							//	To find the available point; temporary variable(s) are created which consisted of
			int temp_sl = reso.size() - side;								//	the length/height of the area subtracted by the length/height of the shape.
			int temp_sh = reso[0].size() - side;							//	Using the temporary variable, the available area are smaller to fit the size of the shape.
																			//	Hence, lower workload. A random integer is assigned and added up to each position of the point.
																			//	It continues to add up until a position found to be available to be used.
			if(reso.size() < side || reso[0].size() < side) {
				cout << "Shape " << getTag() << " is too large to fit the current area." << endl;
				return false;
			}
			if(temp_sl <= 0 && temp_sh <= 0) {
				setPos(0, 0);
				return true;
			}
			else if(temp_sl > 0 && temp_sh <= 0) {
				setPos(rand() % (temp_sl + 1), 0);
				return true;
			}
			else if(temp_sl <= 0 && temp_sh > 0) {
				setPos(0, rand() % (temp_sh + 1));
				return true;
			}
			for(int i = rand() % (temp_sl + 1); i < temp_sl; i++) {
				for(int j = rand() % (temp_sh + 1); j < temp_sh; j++) {
					if(reso[i][j] == '.') {
						setPos(i, j);
						return true;
					}
				}
			}
			
			return false;
		}
		bool checkArea(vector<vector<char>> reso) {							//	Similarly to findSpot function, but in this case, it checks all.
			if(reso.size() < getX() + side || reso[0].size() < getY() + side)
				return false;
			for(int i = getX(); i < getX() + side; i++)
				for(int j = getY(); j < getY() + side; j++)
					if(reso[i][j] != '.')
						return false;
			
			return true;
		}
		void draw(vector<vector<char>>& reso) {								//	If both condition findSpot and checkArea functions are true, shape will be drawn in the area
			for(int i = getX(); i < getX() + side; i++)						//	from the origin point set by the findSpot function.
				for(int j = getY(); j < getY() + side; j++)
					reso[i][j] = getTag();
		}
		~Square() { cout << "Destruct Square " << getTag() << "..." << endl; }
};

class Rectangle: public Shape {
	private:
		int length, height;
	public:
		Rectangle(): Shape() {
			length = 1;
			height = 1;
			cout << "Construct Rectangle " << getTag() << " with size of " << length << 'x' << height << "..." << endl;
		}
		Rectangle(char t, int l, int h): Shape(t) {
			length = l;
			height = h;
			cout << "Construct Rectangle " << getTag() << " with size of " << length << 'x' << height << "..." << endl;
		}
		Rectangle(char t, int x, int y, int l, int h): Shape(t, x, y) {
			length = l;
			height = h;
			cout << "Construct Rectangle " << getTag() << " with size of " << length << 'x' << height << "..." << endl;
		}
		void setLength(int l) { length = l; }
		void setHeight(int h) { height = h; }
		int getLength() { return length; }
		int getHeight() { return height; }
		bool findSpot(vector<vector<char>> reso) {
			int temp_l = reso.size() - length;
			int temp_h = reso[0].size() - height;
			if(reso.size() < length || reso[0].size() < height) {
				cout << "Shape " << getTag() << " is too large to fit the current area." << endl;
				return false;
			}
			if(temp_l <= 0 && temp_h <= 0) {
				if(reso[0][0] == '.') {
					setPos(0, 0);
					return true;
				}
				else
					return false;
			}
			else if(temp_l > 0 && temp_h <= 0) {
				int temp = rand() % (temp_l + 1);
				if(reso[temp][0] == '.') {
					setPos(temp, 0);
					return true;
				}
				else
					return false;
			}
			else if(temp_l <= 0 && temp_h > 0) {
				int temp = rand() % (temp_l + 1);
				if(reso[0][temp] == '.') {
					setPos(0, temp);
					return true;
				}
				else
					return false;
			}
			for(int i = rand() % (temp_l + 1); i <= temp_l; i++) {
				for(int j = rand() % (temp_h + 1); j <= temp_h; j++) {
					if(reso[i][j] == '.') {
						setPos(i, j);
						return true;
					}
				}
			}
			
			return false;
		}
		bool checkArea(vector<vector<char>> reso) {
			if(reso.size() < getX() + length || reso[0].size() < getY() + height)
				return false;
			for(int i = getX(); i < getX() + length; i++)
				for(int j = getY(); j < getY() + height; j++)
					if(reso[i][j] != '.')
						return false;
			
			return true;
		}
		void draw(vector<vector<char>>& reso) {
			for(int i = getX(); i < getX() + length; i++)
				for(int j = getY(); j < getY() + height; j++)
					reso[i][j] = getTag();
		}
		~Rectangle() { cout << "Destruct Rectangle " << getTag() << "..." << endl; }
};

class Triangle: public Shape {
	private:
		int height;
	public:
		Triangle(): Shape() {
			height = 1;
			cout << "Construct Triangle " << getTag() << " with size of " << height * 2 + 1 << 'x' << height << "..." << endl;
		}
		Triangle(char t, int h): Shape(t) {
			height = h;
			cout << "Construct Triangle " << getTag() << " with size of " << height * 2 + 1 << 'x' << height  << "..." << endl;
		}
		Triangle(char t, int x, int y, int h): Shape(t, x, y) {
			height = h;
			cout << "Construct Triangle " << getTag() << " with size of " << height * 2 + 1 << 'x' << height  << "..." << endl;
		}
		void setHeight(int h) { height = h; }
		int getHeight() { return height; }
		bool findSpot(vector<vector<char>> reso) {							//	Unlike the findSpot function from the Square and Rectangle, the formula used here is a bit special.
			int temp_r = reso.size() - height * 2 + 1;						//	It's not convenient to use up all the length and height area, therefore the formula used ignores
			int temp_h = reso[0].size() - height;							//	the empty bit of triangles and searches for the middle part of the triangle instead.
			if(reso.size() < height * 2 - 1 || reso[0].size() < height) {
				cout << "Shape " << getTag() << " is too large to fit the current area." << endl;
				return false;
			}
			if(temp_r <= 0 && temp_h <= 0) {
				if(reso[0][0] == '.') {
					setPos(0, 0);
					return true;
				}
				else
					return false;
			}
			else if(temp_r > 0 && temp_h <= 0) {
				int temp = rand() % (temp_r + 1);
				if(reso[temp][0] == '.') {
					setPos(temp, 0);
					return true;
				}
				else
					return false;
			}
			else if(temp_r <= 0 && temp_h > 0) {
				int temp = rand() % (temp_h + 1);
				if(reso[0][temp] == '.') {
					setPos(0, temp);
					return true;
				}
				else
					return false;
			}
			for(int i = rand() % (temp_r + 1); i < reso.size() - height - 1; i++) {
				for(int j = rand() % (temp_h + 1); j <= temp_h; j++) {
					if(reso[i + height - 1][j] == '.') {
						setPos(i, j);
						return true;
					}
				}
			}
			
			return false;
		}
		bool checkArea(vector<vector<char>> reso) {							//	Similar cases,	except it doesn't look up on the empty bit and visualises the pyramid shape.
			int side = 0;
			int space = height - 1;
			if(reso.size() < getX() + height * 2 - 1 || reso[0].size() < getY() + height)
				return false;
			for(int j = getY(); j < getY() + height; j++, side++, space--)
				for(int i = getX() + space; i < getX() + height + side; i++)
					if(reso[i][j] != '.')
						return false;
			
			return true;
		}
		void draw(vector<vector<char>>& reso) {
			int side = 0;
			int space = height - 1;
			for(int j = getY(); j < getY() + height; j++, side++, space--)
				for(int i = getX() + space; i < getX() + height + side; i++)
					reso[i][j] = getTag();
		}
		~Triangle() { cout << "Destruct Triangle " << getTag() << "..." << endl; }
};

void fileOpen(vector<Shape*>& obj_shape, int& x, int& y) {					//	Opening the file functions; creates new one by itself if Batch.txt file doesn't exist.
	string file_name,
		   temp_str,
		   temp_str1;
	char temp_char;
	int line = 0,
		temp_int1,
		temp_int2;

	file_name = "Batch.txt";
	
	ifstream file_read(file_name.c_str());
	
	if(!file_read.is_open()) {
		ofstream file_write(file_name.c_str());

		file_write << "Size M 32 24" << endl
				   << "Square A 4 0" << endl
				   << "Rectangle B 6 3" << endl
				   << "Triangle C 4 0" << endl
				   << "Triangle D 9 0" << endl
				   << "Square E 5 0" << endl
				   << "Rectangle F 8 2" << endl
				   << "Rectangle G 3 8" << endl
				   << "Triangle H 6 0" << endl
				   << "Square I 7 0" << endl;

		file_write.close();
		file_read.open(file_name.c_str());
	}
	
	line = obj_shape.size();
	if(line > 0)
		for(int i = 0; i < line; i++)
			obj_shape.pop_back();
	line = 0;
	
	while(getline(file_read, temp_str))
		line++;
	
	file_read.close();
	file_read.open(file_name.c_str());
	
	for(int i = 0; i < line; i++) {
		file_read >> temp_str1 >> temp_char >> temp_int1 >> temp_int2;
		file_read.ignore(80, '\n');
		
		if(temp_str1 == "Size") { x = (temp_int1 > 0 || temp_int1 < 41) ? temp_int1 : 1; y = (temp_int2 > 0 || temp_int2 < 41) ? temp_int2 : 1; }
		else if(temp_str1 == "Square") obj_shape.push_back(new Square((temp_char != '.') ? temp_char : 'A', (temp_int1 > 0 || temp_int1 < 41) ? temp_int1 : 1));
		else if(temp_str1 == "Rectangle") obj_shape.push_back(new Rectangle((temp_char != '.') ? temp_char : 'A', (temp_int1 > 0 || temp_int1 < 41) ? temp_int1 : 1, (temp_int2 > 0 || temp_int2 < 41) ? temp_int2 : 1));
		else if(temp_str1 == "Triangle") obj_shape.push_back(new Triangle((temp_char != '.') ? temp_char : 'A', (temp_int1 > 0 || temp_int1 < 41) ? temp_int1 : 1));
		else cout << "Error in line " << line << ", skipping to the next line."; 
	}
	file_read.close();
}
																			//	Save files function, content include the area content, attempt, and the result.
void fileSave(vector<vector<char>> reso, bool result, const int att, const int att_max, int amt) {
	string file_name,
		   outcome;
	if(result)
		outcome = "Success";
	else
		outcome = "Failed";

	file_name = outcome + '.' + to_string(att) + ".txt";
	ofstream file_write(file_name.c_str());
	
	for(int j = 0; j < reso[0].size(); j++) {
		for(int i = 0; i < reso.size(); i++)
			file_write << reso[i][j] << ' ';
		file_write << endl;
	}
	file_write << endl << outcome << " outcome!" << endl;
	file_write << endl << "Amount of shape(s) : " << amt << endl;
	file_write << "Area Size [ " << reso.size() << " X " << reso[0].size() << " ]" << endl;
	file_write << endl << "Attempt : " << att << endl;
	file_write << "Max attempt(s) allowed : " << att_max << endl;

	file_write.close();
}

int changeValue() {															//	Return a positive value integer; avoids error.
	int num;
	while(true) {
		cin >> num;
		cin.clear();
		cin.ignore(80, '\n');
		if(cin.fail())
			cout << "Input error!\n"
					"Please enter an integer.\n";
		if(num < 1)
			cout << "Value should not be less than 1" << endl;
		else
			break;
	}

	return num;
}

void defineArea(int& val1, int& val2) {										//	Pass by reference functions for area_x and area_y
	cout << "Enter x value : ";
	int num1 = changeValue();
	cout << "Enter y value : ";
	int num2 = changeValue();

	val1 = num1;
	val2 = num2;
}

void setArea(vector<vector<char>>& reso) {									//	Fills the area with '.' tag by the length and height of the vector.
	for(int j = 0; j < reso[0].size(); j++)
		for(int i = 0; i < reso.size(); i++)
			reso[i][j] = '.';
}

void printArea(const vector<vector<char>> reso) {							//	Fancy print function for vector; prints the contents of the vector.
	cout << '|';
	for(int i = 0; i < reso.size() * 2 + 1; i++)
		cout << '=';
	cout << '|' << endl;
	for(int j = 0; j < reso[0].size(); j++) {
		cout << '|' << ' ';
		for(int i = 0; i < reso.size(); i++)
			cout << reso[i][j] << ' ';
		cout << '|' << endl;
	}
	cout << '|';
	for(int i = 0; i < reso.size() * 2 + 1; i++)
		cout << '=';
	cout << '|' << endl;
}
																			//	Prints user interface menu
void printUI(const vector<vector<char>> reso, const vector<Shape*> drawing, const int count, const int att, const int att_max, const int ret_max) {
	string str1 = "|<  Area Size [ " + to_string(reso.size()) + " X " + to_string(reso[0].size()) + " ]  >|",
		   str2 = "->  Max Computer Attempt : " + to_string(att_max),
		   str3 = "->  Max Shape Retry : " + to_string(ret_max),
		   str4 = "!!  Successfully fitted all the shape(s) into the area  !!",
		   str5 = "!!  " + to_string(drawing.size() - count) + " out of " + to_string(drawing.size()) + " shape(s) could not fit.  !!",
		   str6 = ">>  Attempt Count : " + to_string(att) + "  <<",
		   str7 = "->  Number of Shape(s) : " + to_string(drawing.size());
																			//	Print string with the scale according to the length of the vector.
	cout << setw(reso.size() + 2 + str1.length() / 2) << right << str1 << endl;
	if(count == drawing.size())
		cout << setw(reso.size() + 2 + str4.length() / 2) << right << str4 << endl;
	else if(count > 0)
		cout << setw(reso.size() + 2 + str5.length() / 2) << right << str5 << endl;
	if(att > 0)
		cout << setw(reso.size() + 2 + str6.length() / 2) << right << str6 << endl << endl;
	cout << setw(reso.size() - str1.length() / 2) << right << ' ' << left << str7 << endl;
	cout << setw(reso.size() - str1.length() / 2) << right << ' ' << left << str2 << endl;
	cout << setw(reso.size() - str1.length() / 2) << right << ' ' << left << str3 << endl << endl;
	cout << " >|>|  Shape Fitter" << endl
		 << "  [1] Start the program" << endl << endl
		 << "  [3] Max computer attempt" << endl
		 << "  [4] Max shape retry" << endl
		 << "  [5] Set area size" << endl
		 << "  [6] Clear area" << endl << endl
		 << "  [7] Refresh Batch.txt file" << endl << endl
		 << "  [0] Exit the program" << endl << endl;
}
																			//	Main program starts here
int main()
{
	vector<Shape*> drawing;
	int area_x = 20,
		area_y = 20,
		count = 0,
		retry_max = 2,
		attempt = 0,
		attempt_max = 5;
	char choice;
	srand(time(NULL));
	vector<vector<char>> area(area_x, vector<char>(area_y));
	setArea(area);

	fileOpen(drawing, area_x, area_y);
	area.clear();
	area.resize(area_x, vector<char>(area_y));
	setArea(area);

	system("cls");
	while(true) {
		cout << endl << endl << endl;
		printArea(area);
		printUI(area, drawing, count, attempt, attempt_max, retry_max);

		cout << "Enter number from the bracket to navigate : ";
		cin >> choice;
		cin.clear();
		cin.ignore(80, '\n');
		
		if(choice == '1') {													//	Starts the program
			attempt = 0;
			while(true) {
				setArea(area);
				count = 0;
				for(int k = 0; k < drawing.size(); k++) {
					for(int retry = 0; retry <= retry_max; retry++) {		//	Retry by repositioning
						if(drawing[k]->findSpot(area)) {					//	Explained in the class functions
							cout << "-> Shape " << drawing[k]->getTag() << " origin point set to "
								 << "(" << drawing[k]->getX() << ',' << drawing[k]->getY() << ")." << endl;
							if(drawing[k]->checkArea(area)) {
								drawing[k]->draw(area);
								cout << "-> Shape " << drawing[k]->getTag() << " successfully drawn!" << endl;
								count++;
								break;
							}												//	Reason of failure
							else											//	Due to obstructed space while drawing
								cout << "-> Shape " << drawing[k]->getTag() << " failed to draw!" << endl;
							}
						else												//	Due to findSpot function not being to find the available position given by random integer and addition
							cout << "-> Shape " << drawing[k]->getTag() << " could not find free point!" << endl;
						if(retry < retry_max)								//	If the max retry is more than 1, it will retry by repositioning
							cout << "-> Shape " << drawing[k]->getTag() << " retrying... [" << retry + 1 << "/" << retry_max << "]" << endl;
					}
				}
				attempt++;													//	Saves file for each attempt run
				fileSave(area, (count == drawing.size()) ? true : false, attempt, attempt_max, drawing.size());
				if(count == drawing.size() || attempt >= attempt_max) break;
				else {
					printArea(area);
					cout << "Attempt [" << attempt << "/" << attempt_max << "]" << endl;
					cout << drawing.size() - count << " out of " << drawing.size() << " of the shape(s) did not fit." << endl;
				}
			}
		}
		else if(choice == '3') {											//	Sets the number of computer attempt(s)
			cout << "Enter the max amount of computer attempt : ";
			attempt_max = changeValue();
		}
		else if(choice == '4') {											//	Sets the number of shape retry
			cout << "Enter the max amount of shape retry : ";
			retry_max = changeValue();
		}
		else if(choice == '5') {											//	Sets the size of the vector, which resets the content of vector, count and attempt made
			count = 0;
			attempt = 0;
			defineArea(area_x, area_y);
			area.clear();
			area.resize(area_x, vector<char>(area_y));
			setArea(area);
		}
		else if(choice == '6') {											//	Similar as above without setting the size of the vector
			count = 0;
			attempt = 0;
			area.clear();
			area.resize(area_x, vector<char>(area_y));
			setArea(area);
		}
		else if(choice == '7') {											//	Reloads the files and reset the program
			count = 0;
			attempt = 0;
			area.clear();
			fileOpen(drawing, area_x, area_y);
			area.resize(area_x, vector<char>(area_y));
			setArea(area);
		}
		else if(choice == '0') {											//	Exit the program
			cout << endl << endl << "Exiting the program..." << endl;
			break;
		}
	}
	system("pause");

	return 0;
}