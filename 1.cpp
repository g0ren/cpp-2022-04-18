#include <iostream>
#include <iomanip>
#include <ctime>
#define ABS(X) (((X)>0)?(X):-(X))
#define MIN(X,Y) ((ABS(X)<ABS(Y))?(X):(Y))
using namespace std;

class Fraction {
	int numerator = 1;
	int denominator = 1;

public:
	Fraction(int n, int d = 1) :
			numerator { n }, denominator { d } {
		if (d == 0)
			denominator = 1;
	}

	Fraction() :
			Fraction(1, 1) {
	}
	Fraction(double d) {
		int den { 1 };
		while (d != (int) d) {
			d *= 10;
			den *= 10;
		}
		this->denominator = den;
		this->numerator = d;
		this->least_fractions();
	}

	void least_fractions() {
		bool done { };
		while (!done) {
			int n = MIN(this->denominator, this->numerator);
			done = true;
			for (int i = 2; i <= n; i++) {
				if (!(this->denominator % i) && !(this->numerator % i)) {
					this->denominator /= i;
					this->numerator /= i;
					done = false;
					break;
				}
			}
		}
	}

	void invert() {
		int t { };
		t = this->denominator;
		this->denominator = this->numerator;
		this->numerator = t;
	}

	int get_denominator() const {
		return denominator;
	}
	void set_denominator(int d) {
		if (d != 0)
			denominator = d;
	}

	int get_numerator() const {
		return numerator;
	}
	void set_numerator(int n) {
		numerator = n;
	}

	void set(int n, int d) {
		set_numerator(n);
		set_denominator(d);
	}

	void print() {
		cout << numerator << "/" << denominator << endl;
	}

	Fraction operator+(Fraction);
	Fraction operator-(Fraction);
	Fraction operator+(int);
	Fraction operator-(int);
	Fraction operator*(Fraction);
	Fraction operator/(Fraction);
	Fraction operator*(int);
	Fraction operator/(int);

	Fraction& operator/=(Fraction);
	Fraction& operator*=(Fraction);
	Fraction& operator-=(Fraction);
	Fraction& operator+=(Fraction);
	Fraction& operator/=(int);
	Fraction& operator*=(int);
	Fraction& operator-=(int);
	Fraction& operator+=(int);

	/*Fraction& operator++ ();
	 Fraction operator++ (int);
	 Fraction& operator-- ();
	 Fraction operator-- (int);

	 Fraction operator+ (const Fraction&);
	 Fraction operator- (const Fraction&);
	 Fraction& operator+= (const Fraction&);
	 Fraction& operator-= (const Fraction&);
	 */

	friend ostream& operator<<(ostream&, const Fraction&);
	friend istream& operator>>(istream&, Fraction&);
};

ostream& operator<<(ostream &out, const Fraction &f) {
	out << f.numerator << "/" << f.denominator;
	return out;
}

istream& operator>>(istream &in, Fraction &f) {
	in >> f.numerator >> f.denominator;
	return in;
}

Fraction& Fraction::operator+=(Fraction f) {
	this->numerator = (f.denominator * this->numerator)
			+ (this->denominator * f.numerator);
	this->denominator *= f.denominator;
	this->least_fractions();
	return *this;
}

Fraction& Fraction::operator*=(Fraction f) {
	this->denominator *= f.denominator;
	this->numerator *= f.numerator;
	this->least_fractions();
	return *this;
}

Fraction& Fraction::operator/=(Fraction f) {
	this->denominator *= f.numerator;
	this->numerator *= f.denominator;
	this->least_fractions();
	return *this;
}

Fraction& Fraction::operator-=(Fraction f) {
	this->numerator = f.denominator * this->numerator
			- this->denominator * f.numerator;
	this->denominator *= f.denominator;
	this->least_fractions();
	return *this;
}

Fraction& Fraction::operator/=(int v) {
	this->denominator *= v;
	this->least_fractions();
	return *this;
}

Fraction& Fraction::operator*=(int v) {
	this->numerator *= v;
	this->least_fractions();
	return *this;
}
Fraction& Fraction::operator-=(int v) {
	this->numerator -= this->denominator * v;
	this->least_fractions();
	return *this;
}
Fraction& Fraction::operator+=(int v) {
	this->numerator += this->denominator * v;
	this->least_fractions();
	return *this;
}

Fraction Fraction::operator+(Fraction f) {
	Fraction t = *this;
	t += f;
	return t;
}

Fraction Fraction::operator+(int v) {
	Fraction t = *this;
	t += v;
	return t;
}

Fraction Fraction::operator-(Fraction f) {
	Fraction t = *this;
	t -= f;
	return t;
}

Fraction Fraction::operator-(int v) {
	Fraction t = *this;
	t -= v;
	return t;
}

Fraction Fraction::operator*(Fraction f) {
	Fraction t = *this;
	t *= f;
	return t;
}
Fraction Fraction::operator/(Fraction f) {
	Fraction t = *this;
	t /= f;
	return t;
}
Fraction Fraction::operator*(int v) {
	Fraction t = *this;
	t *= v;
	return t;
}
Fraction Fraction::operator/(int v) {
	Fraction t = *this;
	t /= v;
	return t;
}

int main() {
	setlocale(LC_ALL, "Russian");
	Fraction f { 1, 3 };
	cout << "f = " << f << endl;
	f += Fraction(1, 3);
	cout << "f = " << f << endl;
	Fraction f2;
	cin >> f2;
	cout << f + f2 << endl;
	return 0;
}
