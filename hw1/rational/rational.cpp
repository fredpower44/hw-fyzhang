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

static int Rational::gcd(int a, int b) {
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

static int Rational::lcm(int a, int b) {
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
	int gcd = gcd(n,d);
	n /= gcd;
	d /= gcd;
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
	Rational result(num, den);
	result.reduce();
	result.normalize0;
	return result;
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
	int num = r.n * x;
	Rational result(num, d);
	result.reduce();
	result.normalize0();
	return result;
}

Rational Rational::operator^(const int &x) {
	int num = 1;
	int den = 1;
	for (int i=0; ((i<x) || (i>(-1 * x))); i++) {
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

bool Rational::operator==(Rational r) {
	Rational temp(n, d);
	r.reduce();
	return ((temp.n == r.n) && (temp.d == r.d));
}

Rational Rational::operator=(const Rational &r) {
	n = r.n;
	d = d.n;
	result.reduce();
	result.normalize0();
	return *this;
}
Rational Rational::operator=(const int &x) {
	n = x;
	d = 1;
	return *this;
}
