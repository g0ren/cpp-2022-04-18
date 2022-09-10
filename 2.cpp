#include <iostream>
#include <iomanip>
#include <cstring>
#include <list>
#include <string>
using namespace std;
class Person;
class Phonebook;

/*
 * Создайте приложение "Телефонная книга". Необходимо
 хранить данные об абоненте (ФИО, домашний телефон,
 рабочий телефон, мобильный телефон, дополнительная
 информация о контакте) внутри соответствующего клас-
 са. Наполните класс переменными-членами, функция-
 ми-членами, конструкторами, inline-функциями-членами,
 используйте инициализаторы, реализуйте деструктор.
 Обязательно необходимо выделять динамически память
 под ФИО. Предоставьте пользователю возможность до-
 бавлять новых абонентов, удалять абонентов, искать або-
 нентов по ФИО, показывать всех абонентов, сохранять
 информацию в файл и загружать из файла.
 *
 */

class Person {
	char *full_name;
	int home_phone;
	int work_phone;
	char *additional_info;
public:
	Person();
	Person(char*);
	Person(char*, int);
	Person(char*, int, int);
	Person(char*, int, int, char*);
	Person(const Person&);
	~Person();

	const char* get_full_name();
	int get_work_phone();
	int get_home_phone();
	const char* get_additional_info();
	void set_full_name(const char*);
	void set_work_phone(int);
	void set_home_phone(int);
	void set_additional_info(const char*);
	void print();
	friend ostream& operator<<(ostream &out, Person p);
	string toString();
};

Person::Person(char *name, int home, int work, char *comment) :
		home_phone { home }, work_phone { work } {
	if (name) {
		this->full_name = new char[strlen(name) + 1];
		strcpy(this->full_name, name);
	} else {
		this->full_name = nullptr;
	}
	if (comment) {
		this->additional_info = new char[strlen(comment) + 1];
		strcpy(this->additional_info, comment);
	} else {
		this->additional_info = nullptr;
	}
}

Person::Person(char *name, int home, int work) :
		Person(name, home, work, nullptr) {
}
Person::Person(char *name, int home) :
		Person(name, home, 0, nullptr) {
}
Person::Person(char *name) :
		Person(name, 0, 0, nullptr) {
}
Person::Person() :
		Person(nullptr, 0, 0, nullptr) {
}

Person::Person(const Person &p) :
		Person(p.full_name, p.home_phone, p.work_phone, p.additional_info) {
}

Person::~Person() {
	if (this->full_name)
		delete[] this->full_name;
	if (this->additional_info)
		delete[] this->additional_info;
}

const char* Person::get_full_name() {
	return this->full_name;
}

int Person::get_work_phone() {
	return this->work_phone;
}

int Person::get_home_phone() {
	return this->home_phone;
}

const char* Person::get_additional_info() {
	return this->additional_info;
}

void Person::set_full_name(const char *name) {
	if (this->full_name)
		delete[] this->full_name;
	if (name) {
		this->full_name = new char[strlen(name) + 1];
		strcpy(this->full_name, name);
	} else {
		this->full_name = nullptr;
	}
}

void Person::set_work_phone(int phone) {
	this->work_phone = phone;
}

void Person::set_home_phone(int phone) {
	this->home_phone = phone;
}

void Person::set_additional_info(const char *comment) {
	if (this->additional_info)
		delete[] this->additional_info;
	if (comment) {
		this->additional_info = new char[strlen(comment) + 1];
		strcpy(this->additional_info, comment);
	} else {
		this->additional_info = nullptr;
	}
}

void Person::print() {
	if (this->full_name)
		cout << this->full_name;
	cout << endl;
	cout << "Home phone: ";
	if (this->home_phone)
		cout << this->home_phone;
	cout << endl;
	cout << "Work phone: ";
	if (this->work_phone)
		cout << this->work_phone;
	cout << endl;
	cout << "Additional info: ";
	if (this->additional_info)
		cout << this->additional_info;
	cout << endl;
	cout << endl;
}

ostream& operator<<(ostream &out, Person p) {
	if (p.full_name)
		out << p.full_name;
	out << endl;
	out << "Home phone: ";
	if (p.home_phone)
		out << p.home_phone;
	out << endl;
	out << "Work phone: ";
	if (p.work_phone)
		out << p.work_phone;
	cout << endl;
	cout << "Additional info: ";
	if (p.additional_info)
		out << p.additional_info;
	out << endl;
	out << endl;
	return out;
}

string Person::toString() {
	string r = "";
	if (this->full_name)
		r += (string) this->full_name;
	r += ";";
	if (this->home_phone)
		r += to_string(this->home_phone);
	r += ";";
	if (this->work_phone)
		r += to_string(this->work_phone);
	r += ";";
	if (this->additional_info)
		r += (string) this->additional_info;
	r += "\n";
	return r;
}

class Phonebook {
	list<Person> book;
public:
	Phonebook();
	~Phonebook();
	void add_person();
	void add_person(Person);
	void add_person(Person, int);
	void swap(int, int);
	Person& operator[](int);
	int size();
	void print();
	void search(string) const;
	void to_file(string);
	void from_file(string);
};

Phonebook::Phonebook() {

}

Phonebook::~Phonebook() {

}

void Phonebook::add_person(Person p) {
	this->book.push_back(p);
}

void Phonebook::add_person(Person p, int idx) {
	list<Person>::iterator it;
	it = this->book.begin();
	for (int i = 0; i < idx; i++, it++)
		;
	this->book.insert(it, p);
}

void Phonebook::add_person() {
	char name[256] { };
	char comment[256] { };
	int home { }, work { };
	cout << "Enter the person's name" << endl;
	cin.getline(name, 256);
	cout << "Enter home phone" << endl;
	cin >> home;
	cout << "Enter work phone" << endl;
	cin >> work;
	cout << "Enter additional details" << endl;
	cin.getline(comment, 256);
	Person p { name, home, work, comment };
	this->book.push_back(p);
}

void Phonebook::swap(int idx, int jdx) {
	list<Person>::iterator it;
	it = this->book.begin();
	for (int i = 0; i < idx; i++, it++)
		;
	list<Person>::iterator jt;
	jt = this->book.begin();
	for (int j = 0; j < jdx; j++, jt++)
		;
	this->book.splice(it, this->book, jt);
}

Person& Phonebook::operator[](int idx) {
	list<Person>::iterator it;
	it = this->book.begin();
	for (int i = 0; i < idx; i++, it++)
		;
	return *it;
}

int Phonebook::size() {
	return this->book.size();
}

void Phonebook::print() {
	for (Person p : this->book)
		p.print();
}

void Phonebook::search(string s) const {
	for (Person p : this->book) {
		string str = p.get_full_name();
		if (str.find(s) != string::npos) {
			p.print();
		}
	}
}

void Phonebook::to_file(string f) {
	FILE *output = fopen(f.c_str(), "w+");
	if (output) {
		for (Person p : this->book) {
			string text = p.toString();
			fwrite(text.c_str(), 1, text.size(), output);
		}
	} else {
		cout << "Can't open file " << f << " for writing!" << endl;
	}
	fclose(output);
}

string parse(string &fullLine) {
	if (fullLine == "")
		return "";
	unsigned semicol = fullLine.find_first_of(";");
	if (semicol == string::npos)
		return "";
	string part = fullLine.substr(0, semicol);
	fullLine = fullLine.substr(semicol+1);
	return part;
}

void Phonebook::from_file(string f) {
	FILE *input = fopen(f.c_str(), "r");
	if (input) {
		char *line { };
		size_t len { };
		while (getline(&line, &len, input) != -1) {
			string fullLine = line;
			if (fullLine.find(";") == string::npos)
				continue;
			Person p;
			p.set_full_name(parse(fullLine).c_str());
			string phone = parse(fullLine);
			if (!phone.empty())
				p.set_home_phone(stoi(phone));
			phone = parse(fullLine);
			if (!phone.empty())
				p.set_work_phone(stoi(phone));
			p.set_additional_info(parse(fullLine).c_str());
			this->add_person(p);
		}
	} else {
		cout << "Can't open  file " << f << " for reading!" << endl;
	}
	fclose(input);
}
////Minniee Levrez;1229487;1643507;God only knows what they are up to.

int main() {
	Phonebook ph;
	Person p { (char*) "Saba Simarleen Mazurchenko" };
	ph.from_file("text2.txt");
	ph.add_person(Person((char*) "Holly-Skye Kobrzynski", 1231212));
	ph.add_person(Person((char*) "Robbie Hardwell", 1234585, 1273400));
	ph.add_person(
			Person((char*) "Donat von Auersperg", 1831212, 1373448,
					(char*) "Identifies as a Martian. Do not approach."));
	ph.add_person(Person((char*) "Chiel Feldtman", 1037891), 1);
	cout << ph.size() << endl;
	ph.print();
	cout << "---------swapping---------" << endl;
	ph.swap(1, 2);
	ph.add_person(p);
	ph[4].set_additional_info(
			"Doesn't use phones, lives in an Amish community. Contact via homing pigeon in office 326.");
	ph.print();
	ph.search("von");

	ph.to_file("text.txt");

	return 0;
}
