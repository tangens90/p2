// link do repozytorium:
// https://github.com/tangens90/homework/tree/main/p2/lab

#include <iostream>
#include <bitset>

using namespace std;

int bitsetToDecimal(bitset<8> b) {
	int res = 0;
	int pow = 1;
	for (int i = 0; i < 8; i++) {
		res += b[i] * pow;
		pow *= 2;
	}
	return res;
}

struct IP {
	const static int size = 4;
	int oktet[size];

	friend istream& operator>>(istream &input, IP& ip) {
		char ch[3];
		input >> ip.oktet[0] >> ch[0] >> ip.oktet[1] >> ch[1] >> ip.oktet[2] >> ch[2] >> ip.oktet[3];
		for (int i = 0; i < 4; i++) {
			if (ip.oktet[i] < 0 || ip.oktet[i] >= 256)
				throw "podane ip jest nieprawidłowe";
		}
		
		for (int i = 0; i < 3; i++) {
			if (ch[i] != '.')
				throw "podane ip jest nieprawidłowe";
		}
		return input;
	}

	friend ostream& operator<<(ostream &output, const IP& ip) {
		for (int i = 0; i < size; i++) {
			bitset<8> tmp = bitset<8>(ip.oktet[i]);
			output << tmp;
			if (i != size - 1) output << '.';
		}
		cout << endl;
		for (int i = 0; i < size; i++) {
			output << dec << ip.oktet[i];
			if (i != size - 1) output << '.';
		}
		cout << endl;
		for (int i = 0; i < size; i++) {
			output << hex << uppercase << ip.oktet[i];
			if (i != size - 1) output << '.';
		}
		return output;
	}

	IP calcAdresPodsieci(const IP& maska) {
		IP tmp;
		for (int i = 0; i < size; i++) {
			bitset<8> maska_oktet = bitset<8>(maska.oktet[i]);
			bitset<8> this_oktet = bitset<8>(this->oktet[i]);
			//bitset<8> maska_bitowa = bitset<8>(((~maska_oktet) | this_oktet) & maska_oktet);
			bitset<8> maska_bitowa = bitset<8>(this_oktet & maska_oktet);

			tmp.oktet[i] = bitsetToDecimal(maska_bitowa);
		}
		return tmp;
	}
};

int main() {
	IP adres, maska;
	cin >> adres >> maska;
	cout << "ip:" << endl;
	cout << adres << endl;
	cout << "maska:" << endl;
	cout << maska << endl;
	cout << "adres podsieci:" << endl;
	cout << adres.calcAdresPodsieci(maska) << endl;
}
