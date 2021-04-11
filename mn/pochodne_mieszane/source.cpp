// Jakub Parapura
#include <iostream>
#include <iomanip>
#include <math.h>
#include "funkcja.h"

using std::cout;
using std::cin;
using std::endl;
using std::ostream;
using std::istream;

class FAD {
public:
	double val;
	double dx;
	double dy;
	double dxdx;
	double dxdy;
	double dydy;

	FAD(double val, double dx, double dy, double dxdx, double dxdy, double dydy) : val(val), dx(dx), dy(dy), dxdx(dxdx), dxdy(dxdy), dydy(dydy) {}

	void operator=(const FAD& fad) {
		val = fad.val;
		dx = fad.dx;
		dy = fad.dy;
		dxdx = fad.dxdx;
		dxdy = fad.dxdy;
		dydy = fad.dydy;
	}

	FAD() {
		val   = 0;
		dx    = 0;
		dy    = 0;
		dxdx  = 0;
		dxdy  = 0;
		dydy  = 0;
	}

	FAD(const FAD& fad) {
		val = fad.val;
		dx = fad.dx;
		dy = fad.dy;
		dxdx = fad.dxdx;
		dxdy = fad.dxdy;
		dydy = fad.dydy;
	}

	friend ostream& operator<<(ostream& out, const FAD& fad) {
		out << fad.val << " " << fad.dx << " " << fad.dy << " " << fad.dxdx << " " << fad.dxdy << " " << fad.dydy << endl;
		return out;
	}

	FAD operator+(const FAD& fad) const {
		FAD ret;
		ret.val = this->val + fad.val;
		ret.dx = this->dx + fad.dx;
		ret.dy = this->dy + fad.dy;
		ret.dxdx = this->dxdx + fad.dxdx;
		ret.dydy = this->dydy + fad.dydy;
		ret.dxdy = this->dxdy + fad.dxdy;
		return ret;
	}


	FAD operator-(const FAD& fad) const {
		FAD ret;
		ret.val = this->val - fad.val;
		ret.dx = this->dx - fad.dx;
		ret.dy = this->dy - fad.dy;
		ret.dxdx = this->dxdx - fad.dxdx;
		ret.dydy = this->dydy - fad.dydy;
		ret.dxdy = this->dxdy - fad.dxdy;
		return ret;
	}

	FAD operator*(const FAD& fad) const{
		FAD ret;
		ret.val = this->val * fad.val;
		ret.dx = this->dx * fad.val + this->val * fad.dx;
		ret.dy = this->dy * fad.val + this->val * fad.dy;
		ret.dxdx = 2 * (this->dx * fad.dx) + this->dxdx * fad.val + this->val * fad.dxdx;
		ret.dydy = 2 * (this->dy * fad.dy) + this->dydy * fad.val + this->val * fad.dydy;
		ret.dxdy = this->dx * fad.dy + this->dy * fad.dx + this->dxdy * fad.val + this->val * fad.dxdy;
		return ret;
	}

	FAD operator/(const FAD& fad) const{
		FAD ret;
		ret.val = this->val / fad.val;
		ret.dx = (this->dx * fad.val - this->val * fad.dx) / (fad.val * fad.val);
		ret.dy = (this->dy * fad.val - this->val * fad.dy) / (fad.val * fad.val);
		ret.dxdx = (-fad.val * (2 * (this->dx * fad.dx) + this->val * fad.dxdx) + this->dxdx * (fad.val * fad.val) + 2 * this->val * (fad.dx * fad.dx)) / (fad.val * fad.val * fad.val);
		ret.dydy = (-fad.val * (2 * (this->dy * fad.dy) + this->val * fad.dydy) + this->dydy * (fad.val * fad.val) + 2 * this->val * (fad.dy * fad.dy)) / (fad.val * fad.val * fad.val);
		ret.dxdy = (-fad.val * (this->dx * fad.dy + this->dy * fad.dx + this->val * fad.dxdy) + this->dxdy * (fad.val * fad.val) + 2 * this->val * fad.dy * fad.dx) / (fad.val * fad.val * fad.val);
		return ret;
	}

	FAD operator-() const {
		FAD ret(-this->val, -this->dx, -this->dy, -this->dxdx, -this->dxdy, -this->dydy);
		return ret;
	}

};

FAD operator+(double value, const FAD& rhs) {
	FAD ret(rhs.val + value, rhs.dx, rhs.dy, rhs.dxdx, rhs.dxdy, rhs.dydy);
	return ret;
}

FAD operator+(const FAD& lhs, double value) {
	FAD ret(lhs.val + value, lhs.dx, lhs.dy, lhs.dxdx, lhs.dxdy, lhs.dydy);
	return ret;
}

FAD operator-(double value, const FAD& rhs) {
	FAD ret(value - rhs.val, -rhs.dx, -rhs.dy, -rhs.dxdx, -rhs.dxdy, -rhs.dydy);
	return ret;
}

FAD operator-(const FAD& lhs, double value) {
	FAD ret(lhs.val - value, lhs.dx, lhs.dy, lhs.dxdx, lhs.dxdy, lhs.dydy);
	return ret;
}

FAD operator*(double value, const FAD& rhs) {
	FAD ret(rhs.val * value, value * rhs.dx, value * rhs.dy, value * rhs.dxdx, value * rhs.dxdy, value * rhs.dydy);
	return ret;
}

FAD operator*(const FAD& lhs, double value) {
	FAD ret(lhs.val * value, value * lhs.dx, value * lhs.dy, value * lhs.dxdx, value * lhs.dxdy, value * lhs.dydy);
	return ret;
}

// value / FAD
FAD operator/(double value, const FAD& rhs) {
	FAD ret(rhs.val / value, 
			-value * rhs.dx / (rhs.val * rhs.val), 
			-value * rhs.dy / (rhs.val * rhs.val),
			(value * (2 * (rhs.dx * rhs.dx) - rhs.val * rhs.dxdx)) / (rhs.val * rhs.val * rhs.val), 
			(value * (2 * (rhs.dx * rhs.dy) - rhs.val * rhs.dxdy)) / (rhs.val * rhs.val * rhs.val), 
			(value * (2 * (rhs.dy * rhs.dy) - rhs.val * rhs.dydy)) / (rhs.val * rhs.val * rhs.val));
	return ret;
}

// FAD / value
FAD operator/(const FAD& lhs, double value) {
	FAD ret(lhs.val / value, 
			lhs.dx / value, 
			lhs.dy / value, 
			lhs.dxdx / value, 
			lhs.dxdy / value, 
			lhs.dydy / value);
	return ret;
}

FAD sin(const FAD& x) {
	FAD ret(sin(x.val), 
			x.dx * cos(x.val), 
			x.dy * cos(x.val), 
			x.dxdx * cos(x.val) - (x.dx * x.dx) * sin(x.val), 
			x.dxdy * cos(x.val) - x.dy * x.dx * sin(x.val), 
			x.dydy * cos(x.val) - (x.dy * x.dy) * sin(x.val));
	return ret;
}

FAD cos(const FAD& x) {
	FAD ret(cos(x.val), 
		x.dx * (-sin(x.val)), 
		x.dy * (-sin(x.val)),
		(x.dx * x.dx) * (-cos(x.val)) - x.dxdx * sin(x.val),
		x.dy * x.dx * (-cos(x.val)) - x.dxdy * sin(x.val),
		(x.dy * x.dy) * (-cos(x.val)) - x.dydy * sin(x.val));
	return ret;
}

FAD exp(const FAD& x) {
	FAD ret(exp(x.val),
		exp(x.val) * x.dx,
		exp(x.val) * x.dy,
		exp(x.val) * ((x.dx * x.dx) + x.dxdx),
		exp(x.val) * (x.dy * x.dx + x.dxdy),
		exp(x.val) * ((x.dy * x.dy) + x.dydy)
		);
	return ret;
}

void testCase(double x, double y) {
	FAD fad_x(x, 1, 0, 0, 0, 0);
	FAD fad_y(y, 0, 1, 0, 0, 0);
	cout << std::setprecision(15) << std::showpoint << funkcja(fad_x, fad_y);
}

int main() {
	int M;
	cin >> M;
	while (M > 0) {
		M--;
		double x, y;
		cin >> x >> y;
		testCase(x, y);
	}
}

