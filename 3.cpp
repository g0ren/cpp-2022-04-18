/*
 * Разработать класс String, который в дальнейшем будет
 использоваться для работы со строками. Класс должен
 содержать:
 • Конструктор по умолчанию, позволяющий создать
 строку длиной 80 символов;
 • Конструктор, позволяющий создавать строку произ-
 вольного размера;
 • Конструктор, который создаёт строку и инициализи-
 рует её строкой, полученной от пользователя.
 Необходимо создать деструктор, а также использовать
 механизмы делегирования конструкторов, если это воз-
 можно.
 Класс должен содержать методы для ввода строк с клави-
 атуры и вывода строк на экран. Также нужно реализовать
 статическую функцию-член, которая будет возвращать
 количество созданных объектов строк.
 *
 */

#include <iostream>
#include <cstring>
using namespace std;

class String {
	char *data;
	int size;
public:
	String(int);
	String(const String&);
	String(const char*);
	~String();
	void input();
	void print();
	static int number;

	String operator=(const String&);
	String operator=(const char*);
	friend ostream& operator<<(ostream&, const String&);
	friend istream& operator>>(istream&, String&);
};
int String::number = 0;

String::String(int size = 80) {
	this->size = size;
	this->data = new char[size] { };
	number++;
}

String::String(const String &s) :
		String(s.size) {
	for (int i = 0; i < this->size; i++)
		this->data[i] = s.data[i];
}

String::String(const char *c) :
		String(strlen(c) + 1) {
	for (size_t i = 0; i < strlen(c); i++)
		this->data[i] = c[i];
}

String::~String() {
	if (this->data)
		delete[] this->data;
}

void String::input() {
	char *in = new char[this->size] { };
	cout << "Enter your string (no more than " << this->size << " symbols)"
			<< endl;
	cin.getline(in, this->size);
	if (this->data)
		delete[] this->data;
	this->data = in;
}

void String::print() {
	for (int i = 0; i < this->size && this->data[i]; i++)
		cout << this->data[i];
}

String String::operator=(const String &s) {
	if (this->data)
		delete[] this->data;
	this->size = s.size;
	this->data = new char[this->size] { };
	for (int i = 0; i < this->size; i++)
		this->data[i] = s.data[i];
	return *this;
}

String String::operator=(const char *c) {
	if (this->data)
		delete[] this->data;
	this->size = strlen(c) + 1;
	this->data = new char[this->size] { };
	for (size_t i = 0; i < strlen(c); i++)
		this->data[i] = c[i];
	return *this;
}

ostream& operator<<(ostream &out, const String &s) {
	for (int i = 0; i < s.size && s.data[i]; i++)
		out << s.data[i];
	return out;
}

istream& operator>>(istream &in, String &s) {
	char*input=new char[s.size]{};
	in.getline(input, s.size);
	if (s.data)
		delete[] s.data;
	s.data=input;
	return in;
}

int main() {
	String s;
	String s2(256);
	s2.input();
	String s3(s2);
	s3.print();
	cout << endl;
	String s4="What a beautiful day!";
	String s5=s4;
	String s6("Hello world!");
	cin>>s;
	cout<<s<<endl<<s6<<" "<<s5<<endl;
	cout << String::number << endl;
	return 0;
}
