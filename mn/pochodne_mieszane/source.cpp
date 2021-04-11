#include <iostream>
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

	FAD() {}

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

};

void testCase(int x, int y) {
	FAD fad_x(x, 1, 0, 0, 0, 0);
	FAD fad_y(y, 0, 1, 0, 0, 0);
	cout << funkcja(fad_x, fad_y);
}

int main() {
	int M;
	cin >> M;
	while (M > 0) {
		M--;
		int x, y;
		cin >> x >> y;
		testCase(x, y);
	}
}

