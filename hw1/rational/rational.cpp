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
}

static int Rational::gcd(int a, int b) {
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

void Rational::reduce(){

}

void Rational::normalize0() {

}

void Rational::normalize0()
{
    if (n == 0 && d != 1) d = 1;
}

