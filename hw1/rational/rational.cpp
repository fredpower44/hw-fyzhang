#include <stdexcept>
#include "rational.h"

Rational::Rational()
{
    n = 0;
    d = 1;
}
Rational::Rational(int num, int denom)
{
    if (denom == 0) throw std::invalid_argument("Can't have denom = 0");
    // Continue your implementation below.
    // You should likely call this->reduce() and this->normalize0()
    n = num;
    d = denom;
    this->reduce();
    this->normalize0();
}

int Rational::gcd(int a, int b) {
	if (a < 0) a *= -1; //take abs value
	if (b < 0) b *= -1;
	if (b < a) { //swap so that a is the smaller number
		int temp = b;
		b = a;
		a = temp;
	}
	int gcd = 1;
	for (int i=a; i>0; i--) {
		if (!(b%i) && !(a%i)) {
			gcd = i;
			break;
		}
	}
	return gcd;
}

int Rational::lcm(int a, int b) {
	if (a < 0) a *= -1; //take abs value
	if (b < 0) b *= -1;
	if (b < a) { //swap so that a is the smaller number
		int temp = b;
		b = a;
		a = temp;
	}
	int lcm = a*b;
	for (int i=b; i<=a*b; i++) {
		if (!(i%a) && !(i%b)) {
			lcm = i;
			break;
		}
	}
	return lcm;
}

void Rational::reduce() {
	if (d < 0) {
		n *= -1;
		d *= -1;
	} 
	int x = gcd(n,d);
	n /= x;
	d /= x;
}

void Rational::normalize0()
{
    if (n == 0 && d != 1) d = 1;
}

Rational Rational::operator+(const Rational &r) {
	int num = n * r.d + r.n * d;
	int den = d * r.d;
	Rational result(num, den);
	result.reduce();
	result.normalize0();
	return result;
}

Rational Rational::operator+(const int &x) {
	int num = n + d * x;
	Rational result(num, d);
	result.reduce();
	result.normalize0();
	return result;
}

Rational Rational::operator+=(const Rational &r) {
	n = n * r.d + r.n * d;
	d = d * r.d;
	reduce();
	normalize0();
	return *this;
}

Rational Rational::operator+=(const int &x) {
	n += d * x;
	reduce();
	normalize0();
	return *this;
}

Rational Rational::operator*(const Rational &r) {
	int num = r.n * n;
	int den = r.d * d;
	Rational result(num, den);
	result.reduce();
	result.normalize0();
	return result;
}

Rational Rational::operator*(const int &x) {
	int num = n * x;
	Rational result(num, d);
	result.reduce();
	result.normalize0();
	return result;
}

Rational Rational::operator*=(const Rational &r) {
	n *= r.n;
	d *= r.d;
	reduce();
	normalize0();
	return *this;
}

Rational Rational::operator*=(const int &x) {
	n *= x;
	reduce();
	normalize0();
	return *this;
}

Rational Rational::operator^(const int &x) {
	int size = x;
	if (size < 0) {
		size *= -1;
	}
	int num = 1;
	int den = 1;
	for (int i=0; i<size; i++) {
		num *= n;
		den *= d;
	}
	if (x < 0) {
		int temp = num;
		num = den;
		den = temp;
	}
	Rational result(num, den);
	result.reduce();
	result.normalize0();
	return result;

}

bool Rational::operator==(const Rational &r) {
	Rational temp(r.n, r.d);
	reduce();
	return ((temp.n == n) && (temp.d == d));
}

bool Rational::operator!=(const Rational &r) {
	Rational temp(r.n, r.d);
	reduce();
	return !((temp.n == n) && (temp.d == d));
}

bool Rational::operator<(const Rational &r) {
	return n*r.d < r.n*d;
}

Rational Rational::operator=(const Rational &r) {
	n = r.n;
	d = r.d;
	reduce();
	normalize0();
	return *this;
}
Rational Rational::operator=(const int &x) {
	n = x;
	d = 1;
	return *this;
}
