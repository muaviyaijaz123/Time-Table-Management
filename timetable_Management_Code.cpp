
#include<iostream>
#include<string.h>
#include<conio.h>
#include<fstream>
using namespace std;

//-----------------------------CLASSES-----------------------------------//

class List;
class Course;
class helper;
class Day;
class Rooms;
class Time;
class section;
class classlist;
//-----------------------------------------------------------------------------//

                                //-----HELPER CLASS----//

class helper
{

public:
	static bool find_substring(const char str1[], const char str2[]);

};

bool helper::find_substring(const char str1[], const char str2[])
{

	for (int i = 0; str1[i] != '\0'; i++)
	{

		bool found = true;
		for (int j = 0; str2[j] != '\0'; j++)

		{
			if (str2[j] != str1[i + j])
			{
				found = false;
				break;
			}
		}

		if (found == true)
		{
			return true;
		}

	}
	return false;

}
//--------------------------------------------------------------------------------//

                             //----STRUCT CLASSLIST----//

struct classlist
{
public:
	char name[60][20];
	int count;
	char roll[60][10];

	classlist()                 //Constructor
	{
		count = 0;
		for (int i = 0; i < 60; i++)
		{
			for (int j = 0; j < 20; j++)
				name[i][j] = '\0';
		}

		for (int i = 0; i < 60; i++)
		{
			for (int j = 0; j < 10; j++)
				roll[i][j] = '\0';
		}
	}

	classlist(const classlist& rhs)       //Copy Constructor
	{
		count = rhs.count;
		if (count > 0)
		{
			for (int i = 0; i < count; i++)
			{
				strcpy(name[i], rhs.name[i]);
				strcpy(roll[i], rhs.roll[i]);
			}
		}
	}
	classlist& operator=(const classlist& rhs)  //Assignment Operator
	{
		count = rhs.count;
		if (count > 0)
		{
			for (int i = 0; i < count; i++)
			{
				strcpy(name[i], rhs.name[i]);
				strcpy(roll[i], rhs.roll[i]);
			}
		}
	}

	bool findRoll(const char roll_no[])             //find roll_no
	{
		if (strlen(roll_no) >= strlen(roll[0]))
		{
			if (strlen(roll_no) == strlen(roll[0]))
			{
				for (int i = 0; roll[0][i] != '\0';)
				{
					if (roll_no[i] < roll[0][i])
						return false;
					else if (roll_no[i] == roll[0][i])
						i++;
					else
						break;
				}
			}

			for (int i = 0; i < count; i++)
			{
				if (strcmp(roll_no, roll[i]) == false)
				{
					return true;
				}
			}
		}
		return false;
	}
	
	void fill_student_info(const char _roll[], const char names[])         //copy student name and roll no
	{

		strcpy_s(name[count], names);
		strcpy_s(roll[count], _roll);
		count++;
	}
	~classlist()                        //Destructor
	{

	}
};
//-----------------------------------------------------------------------------------//

                                         //----SECTION CLASS----//

class section
{
	
public:
	char name[9];
	classlist* students;
	
	section()                           //Constructor
	{
		name[0] = '\0';
		students = NULL;
	}

	section(const section& rhs)          //Copy Constructor
	{
		int i;

		for (i = 0; rhs.name[i] != '\0'; i++)
		{
			name[i] = rhs.name[i];
		}
		name[i] = '\0';

		if (rhs.students != 0)
		{
			students = new classlist(rhs.students[0]);
		}
		else
			students = 0;
	}

	section& operator=(const section& rhs)    //Assignment Operator
	{
		if (this != &rhs)
		{
			if (rhs.name[0] != '\0')
				strcpy_s(name, rhs.name);

			if (rhs.students != 0)
			{
				if (students != 0)
					delete[] students;

				students = new classlist(rhs.students[0]);

			}
			else
				students = 0;
		}
		return *this;
	}

	~section()                 //Destructor
	{
		if (students != 0)
		{
			if (this != nullptr  && (students->count>0 && students->count<60))
			{
				delete students;
			}
		}
		students = 0;
	}
};

//--------------------------------------------------------------------------------//

                                      //----COURSE CLASS----//
class course
{
	friend ostream& operator<<(ostream&, course&);

public:
	
	char name[50];
	section** sections;
	int count = 0;
	
	course()                                    //Constructor
	{
		
		for (int i = 0; i < 40; i++)
			name[i] = '\0';

		sections = 0;
		count = 0;
	}
	~course()                                     //Destructor
	{
		if (sections != 0)
		{
			
			for (int i = 0; i < count; i++)
			{
				if (sections[i] != 0 &&(strcmp(this->name,"no_name")==true))
					delete sections[i];
			}
			delete[] sections;
			//sections = 0;    //abi
		}
		sections = 0;
	}
	course(const course & rhs)                        //Copy Constructor
	{
		int j;
		for (j = 0; rhs.name[j] != '\0'; j++)
		{
			name[j] = rhs.name[j];
		}
		name[j] = '\0';
		count = rhs.count;
		if (count > 0)
		{
			sections = new section *[rhs.count];
			for (int i = 0; i < rhs.count; i++)
			{

				sections[i] = new section(rhs.sections[i][0]);
			}
		}
		else
			sections = NULL;
	}

	course& operator=(const course & rhs)        //Assignment Operator
	{
		if (this != &rhs)
		{
			int i;

			for (i = 0; rhs.name[i] != '\0'; i++)
			{
				name[i] = rhs.name[i];
			}

			name[i] = '\0';
			count = rhs.count;
			if (count > 0)
			{
				sections = new section *[count];
				for (int i = 0; i < count; i++)
				{
					sections[i] = new section;
				}
				for (int i = 0; i < count; i++)
				{
					sections[i][0] = rhs.sections[i][0];
				}
			}
			else
				sections = NULL;
		}
		return *this;
	}

	bool operator==(const course & rhs)              //equal to operator
	{
		if (strcmp(name, rhs.name) == false)
		{
			for (int i = 0; i < count; i++)
			{
				if (strcmp(sections[i]->name, rhs.sections[0]->name) == false)
					return true;
			}
		}
		return false;
	}

};

ostream& operator<<(ostream & out, course & rhs)               //cout operator
{
	out << rhs.name;
	for (int i = 0; i < rhs.count; i++)
	{
		out << "   " << rhs.sections[i]->name;
	}

	return out;
}

//------------------------------LIST DATA STRUCTURE-----------------------------//

//template<class T>
class List
{
private:
	course* list; int size, count;

public:

	List();


	course* getlist()
	{
		return list;
	}
	void Insert(course);
	void Display();
	void DisplayAtIndex(int);
	void Remove(course);
	int search(course);
	~List();
};

//template<class T>
List::List()
{
	size = 27;
	count = 0;
	list = new course[size];
}

//template<class T>
List::~List()
{
	if (list != 0)
		delete[] list;
}

//template<class T>

void List::Insert(course num)
{
	if (size != count)
	{
		list[count] = num;
	}
	count++;
}

//template<class T>
void List::Remove(course key)
{
	bool found = false;
	for (int i = 0; i < size; i++)
	{
		/*if (list[i] == key)
		{
		found = true;
		size = size - 1;
		count--;
		}*/
	}
	if (found == false)
	{
		cout << "\n\n  Key Not Found ( doesn't exist in the list ) !! \n\n";
	}
}

//template <class T>
int List::search(course num)                //Searching
{

	for (int i = 0; i < count; i++)
	{
		if (num == list[i])                     //just find the occurrence by checking whole list.
			return i;
	}

	return -1;

}

//template<class T>
void List::Display()
{
	cout << "\n Your List : \n\n";
	for (int i = 0; i < size; i++)
	{
		cout << "\t\t" << list[i] << endl;
	}
}

void List::DisplayAtIndex(int index)
{
	cout << list[index];
}
//-----------------------------------------------------------------------------//

                     //----TIME CLASS----//

class Time
{
public:
	char st_time[10];
	char ed_time[10];
	List courses;
    
	Time()
	{
		st_time[0] = '\0';
		ed_time[0] = '\0';
	}
	~Time()
	{

	}
};
//-------------------------------------------------------------------------------//

                            //---- ROOMS CLASS----//
class Rooms
{
public:
	char name[20];
	Rooms()
	{
		name[0] = '\0';
	}
	~Rooms()
	{

	}
};
//--------------------------------------------------------------------------------//

								//----DAY CLASS----//

class Day
{
public:
	char name[10];
	Day()
	{
		name[0] = '\0';
	}
	~Day()
	{

	}
};
//------------------------------------------------------------------------------//

								//----TTADT CLASS----//

class TTADT
{
public:
	Day days[5];
	Time time[5][8];
	Rooms rooms[27];

	TTADT()
	{
	}

	void load(const char[]);
	void loadStudentInfo(const char filename[]);
	void Pointing_to_same_memory(course*& temp, int, int, int);
	void saveClashes();
	bool clashes_in_next_courses(course*&, const char _roll[], const char _name[], int, ofstream&);
	void printCourse(const char day[], const char time[], const char classroom[]);
	void printCourseTimings(const char coursename[], const char section[]);

	void printStudentCourses(const char rollno[]);
	void printStudentTimetable(const char rollno[]);
	~TTADT()
	{
	}
};
//---------------------------------------------------------------------------------//

//TTADAT CLASS DEFINITIONS//


void TTADT::load(const char file[])
{
	ifstream fin;
	fin.open(file);

	for (int i = 0; i < 5; i++)        //reading days
	{
		fin >> days[i].name;
	}

	for (int i = 0; i < 27; i++)       //reading rooms
	{
		int x = 0;
		fin >> rooms[i].name[x];

		while (rooms[i].name[x] != ',')
		{
			x++;
			fin.get(rooms[i].name[x]);

		}
		rooms[i].name[x] = '\0';
	}


	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 8; j++)

		{
			bool sec = false;

			int x = 0;
			fin >> time[i][j].st_time[x];

			while (time[i][j].st_time[x] != '-')
			{
				x++;
				fin >> time[i][j].st_time[x];

			}
			time[i][j].st_time[x] = '\0';

			x = 0;
			fin >> time[i][j].ed_time[x];

			while (time[i][j].ed_time[x] != ',')
			{
				x++;
				fin >> time[i][j].ed_time[x];

			}
			time[i][j].ed_time[x] = '\0';


			for (int k = 0; k < 27; k++)
			{
				course temp;

				x = 0;
				fin >> temp.name[x];

				while (temp.name[x] != ',' && temp.name[x] != '|')
				{
					x++;
					fin.get(temp.name[x]);
				}

				if (temp.name[x] == '|')
				{
					temp.count = 2;
					sec = true;
				}
				else if (temp.name[0] != 'n')   // x
				{
					temp.count = 1;
				}

				temp.name[x] = '\0';

				if (temp.count != 0)   //temp.name[0] != 'x'
				{
					temp.sections = new section *[temp.count];

					for (int i = 0; i < temp.count; i++)
						temp.sections[i] = new section;

					fin >> temp.sections[0]->name;

					if (sec)
					{
						fin >> temp.sections[1]->name;
					}

				}
				else //abi
				{    //abi
					temp.sections = 0;
				}

				time[i][j].courses.Insert(temp);

				sec = false;
				temp.count = 0;
			}

		}
	}
	fin.close();
}

void TTADT::loadStudentInfo(const char file[])
{
	ifstream fin;
	bool check = false;
	char roll[10], buffer[7], sec[12], subj[50];

	fin.open(file);
	int lol = 1;


	int _count = 1;

	while (lol < 7762)
	{
		fin >> roll;
		fin >> buffer;

		int x = 0;

		fin >> subj[x];
		while (subj[x] != ',')
		{
			x++;
			fin.get(subj[x]);
		}
		subj[x] = '\0';
		fin >> sec;

		check = false;

		for (int i = 0; i < 5; i++)                         //respective day_slot
		{
			for (int j = 0; j < 8; j++)                     //repective time_slot
			{
				course* temp1 = time[i][j].courses.getlist();

				for (int k = 0; k < 27; k++)               //respective course_slot
				{
					if (strcmp(temp1[k].name, subj) == false)
					{
						for (int a = 0; a < temp1[k].count; a++)
						{
							if (strcmp(temp1[k].sections[a]->name, sec) == false)
							{
								if (temp1[k].sections[a]->students == 0)
									temp1[k].sections[a]->students = new classlist;
								temp1[k].sections[a]->students->fill_student_info(roll, buffer);
								Pointing_to_same_memory(temp1, i, j, k);

								check = true;
								break;

							}
						}
					}
					if (check == true)
						break;
				}
				if (check == true)
					break;
			}
			if (check == true)
				break;
		}
		lol++;
	}
	fin.close();
}

void TTADT::Pointing_to_same_memory(course * &temp1, int day_index, int time_slot, int course_slot)
{
	course* temp2 = 0;
	if (time_slot < 7)
	{
		temp2 = time[day_index][time_slot + 1].courses.getlist();
	}
	if (strcmp(temp2[course_slot].name, temp1[course_slot].name) == false)
	{
		for (int a = 0; a < temp2[course_slot].count; a++)
		{
			if (strcmp(temp2[course_slot].sections[a]->name, temp1[course_slot].sections[a]->name) == false)
			{
				temp2[course_slot].sections[a]->students = temp1[course_slot].sections[a]->students;
				return;
			}
		}
	}


	for (int i = day_index + 1; i < 5; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			temp2 = time[i][j].courses.getlist();

			for (int k = 0; k < 27; k++)
			{
				if (strcmp(temp2[k].name, temp1[course_slot].name) == false)
				{
					for (int a = 0; a < temp2[k].count; a++)
					{
						if (strcmp(temp2[k].sections[a]->name, temp1[course_slot].sections[a]->name) == false)
						{
							temp2[k].sections[a]->students = temp1[course_slot].sections[a]->students;
							return;
						}
					}
				}
			}
		}
	}

	return;
}

void TTADT::printCourse(const char day[], const char _time[], const char classroom[])
{
	int i = 0, j = 0, k = 0;
	while (strcmp(day, days[i].name) == true)
	{
		i++;
	}
	while (strcmp(_time, time[i][j].st_time) == true)
	{
		j++;
	}
	while (strcmp(classroom, rooms[k].name) == true)
	{
		k++;
	}
	time[i][j].courses.DisplayAtIndex(k);
}


void TTADT::printCourseTimings(const char coursename[], const char _section[])
{
	int i, j = 0;
	course temp;
	strcpy_s(temp.name, coursename);
	temp.count = 1;
	temp.sections = new section *[temp.count];
	temp.sections[temp.count - 1] = new section;
	strcpy_s(temp.sections[temp.count - 1]->name, _section);

	bool check = false;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 8; j++)
		{

			int search_chk = time[i][j].courses.search(temp);

			if (search_chk != -1)
			{
				if (helper::find_substring(coursename, "Lab") == true && helper::find_substring(coursename, "Skills Lab") == false)
					cout << "\t" << days[i].name << "   " << time[i][j].st_time << "  -  " << time[i][j + 1].ed_time << "   " << rooms[i].name << " || ";
				else

					cout << "\t" << days[i].name << "   " << time[i][j].st_time << "  -  " << time[i][j].ed_time << "   " << rooms[i].name << " || ";
				j = 8;
				break;

			}
		}

	}

}

void TTADT::printStudentCourses(const char rollno[])
{
	List temp2;
	for (int i = 0, j = 0; i < 5;)
	{
		course* temp = time[i][j].courses.getlist();

		for (int k = 0; k < 27; k++)
		{
			if (strcmp(temp[k].name, "no_class") != false)
			{
				if (temp[k].sections[0]->students != NULL)
				{
					if (temp[k].sections[0]->students->findRoll(rollno))
					{
						if (temp2.search(temp[k]) == -1)
						{
							temp2.Insert(temp[k]);
							cout << "\t" << temp[k].name << "     " << temp[k].sections[0]->name << endl;
						}
					}
					else if (temp[k].count > 1 && temp[k].sections[1]->students != NULL)
					{
						if (temp[k].sections[1]->students->findRoll(rollno))                    
						{
							if (temp2.search(temp[k]) == -1)
							{
								temp2.Insert(temp[k]);
								cout << "\t" << temp[k].name << "     " << temp[k].sections[1]->name << endl;
							}
						}
					}
				}
			}
		}
		j++;
		if (j == 8)
		{
			i++;
			j = 0;
		}

	}
}

void TTADT::printStudentTimetable(const char rollno[])
{
	int y = 0;
	List temp2;
	for (int i = 0, j = 0; i < 5;)
	{
		course* temp = time[i][j].courses.getlist();
		for (int k = 0; k < 27; k++)
		{
			if (strcmp(temp[k].name, "no_class") != false)
			{
				if (temp[k].sections[0]->students != NULL)
				{
					if (temp[k].sections[0]->students->findRoll(rollno) && temp2.search(temp[k]) == -1)
					{
						temp2.Insert(temp[k]);
						cout << "\t" << temp[k].name << "   " << temp[k].sections[0]->name << endl;
						printCourseTimings(temp[k].name, temp[k].sections[0]->name);
						cout << endl << endl;
						y = k;  //
						break;
					}
					else if (temp[k].count > 1 && temp[k].sections[1]->students != NULL)
					{
						if (temp[k].sections[1]->students->findRoll(rollno) && temp2.search(temp[k]) == -1)   
						{
							temp2.Insert(temp[k]);
							cout << "\t" << temp[k].name << "   " << temp[k].sections[1]->name << endl;
							printCourseTimings(temp[k].name, temp[k].sections[1]->name);
							cout << endl << endl;
							y = k; //
							break; 
						}
					}
				}
			}
		}
		if (helper::find_substring(temp[y].name, "Lab") == true && helper::find_substring(temp[y].name, "Skills Lab") == false)  
			j++;   
		j++;
		if (j == 8)
		{
			i++;
			j = 0;
		}
	}
}

void TTADT::saveClashes()
{

	int student_count = 0;
	char roll_no[30], _name[30];
	bool clash_found = false;

	ofstream fout;

	fout.open("clash.txt", ios::app);
	for (int i = 0, j = 0; i < 5;)
	{
		course* temp = time[i][j].courses.getlist();
		for (int k = 0; k < 27; k++)
		{
			if (strcmp(temp[k].name, "no_class") != false)
			{
				if (temp[k].sections[0]->students != NULL)
				{
					while (student_count < temp[k].sections[0]->students->count)
					{
						strcpy_s(roll_no, temp[k].sections[0]->students->roll[student_count]);
						strcpy_s(_name, temp[k].sections[0]->students->name[student_count]);
						clash_found = clashes_in_next_courses(temp, roll_no, _name, k + 1, fout);
						if (clash_found)
							fout << temp[k].name << " " << temp[k].sections[0]->name << " on " << days[i].name << "  " << time[i][j].st_time << " " << endl;

						clash_found = false;
						student_count++;
					}
				}
				student_count = 0;
				if (temp[k].count > 1 && temp[k].sections[1]->students != NULL)
				{
					while (student_count < temp[k].sections[1]->students->count)
					{
						strcpy_s(roll_no, temp[k].sections[1]->students->roll[student_count]);
						strcpy_s(_name, temp[k].sections[1]->students->name[student_count]);
						clash_found = clashes_in_next_courses(temp, roll_no, _name, k + 1, fout);
						if (clash_found)
							fout << temp[k].name << " " << temp[k].sections[1]->name << " on " << days[i].name << "  " << time[i][j].st_time << " " << endl;

						clash_found = false;    
						student_count++;             
					}
				}
			}

			student_count = 0;
		}

		j++;
		if (j == 8)
		{
			i++;
			j = 0;
		}

	}
	fout.close();
}

bool TTADT::clashes_in_next_courses(course * &temp, const char _roll[], const char _name[], int next_course, ofstream & fout)
{

	for (int i = next_course; i < 27; i++)
	{
		if (strcmp(temp[i].name, "no_class") != false)
		{
			if (temp[i].sections[0]->students != NULL)
			{
				if (temp[i].sections[0]->students->findRoll(_roll))
				{

					fout << _roll << "  " << _name << "  " << temp[i].name << "  " << temp[i].sections[0]->name << "  ,  ";
					return true;
				}

				if (temp[i].count > 1 && temp[i].sections[1]->students != NULL)
				{
					if (temp[i].sections[1]->students->findRoll(_roll))    
					{
						fout << _roll << "  " << _name << "  " << temp[i].name << "  " << temp[i].sections[1]->name << "  ,  ";
						return true;
					}
				}
			}
		}
	}
	return false;

}

int main()
{
	{
		TTADT timetable;

		//---------------Part A-------------------//
		timetable.load("timetabledata.txt");

		//---------------Part B-------------------//
		timetable.loadStudentInfo("students.txt");

		//---------------Part C-------------------//

		cout << "---------------------------------------------------------------";
		cout << "\n\n Printing Course at Monday 8:00 a.m ( CS-7 ) \n";
		timetable.printCourse("Monday", "8:00a.m.", "CS-7");

		cout << "\n\n------------------------------------------------------------";
		cout << "\n\n Printing Course Timings Of Applied Physics , CS-H \n";
		timetable.printCourseTimings("Applied Physics", "CS-H");

		cout << "\n\n---------------------------------------------------------------";
		cout << "\n\n Printing Courses Of Student : \n";
		timetable.printStudentCourses("11");

		cout << "\n\n---------------------------------------------------------------";
		cout << "\n\n Printing Timetable Of Student : \n";
		timetable.printStudentTimetable("11");

		cout << "\n\n---------------------------------------------------------------";
		cout << "\n\n Printing clashes of timetable in clash.txt file";
		timetable.saveClashes();
	}
	system("pause");
	return 0;
}
