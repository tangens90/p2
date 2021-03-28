// Jakub Parapura

void InsertRec(char* input, int* set, int i, int power, int sum, bool reading) {
	i++;
	if (*(input + i) == ' ' || *(input + i) == '\0') {
		// nic lub znaleziono ciąg
		
		// wstawiamy znalezioną sume
		if (reading) {
			*set = *set | 1 << sum;
		}
		// resetujemy wartości
		if (*(input + i) != '\0') {
			InsertRec(input, set, i, 32, 0, false);
		}
	}
	else if (*(input + i) == '0') {
		reading = true;
		power /= 2; // TODO zamienić na przesunięćie bitowe
		InsertRec(input, set, i, power, sum, true);

	}
	else if (*(input + i) == '1') {
		reading = true;
		power /= 2; // TODO zamienić na przesunięćie bitowe
		sum += power;
		InsertRec(input, set, i, power, sum, true);
	}

}

void Emplace(char* input, int* set) {
	*set = 0;
	InsertRec(input, set, -1, 32, 0, false);
}

void Insert(char* input, int* set) {
	InsertRec(input, set, -1, 32, 0, false);
}

int strToSetElement(char* input, int* set, int i, int power) {
	power /= 2; // TODO przesunięcie bitowe
	i++;
	if (power == 0) {
		return 0;
	}
	if (*(input + i) == '0') {
		// nic
		return strToSetElement(input, set, i, power);
	}
	else {
		// cyfra == 1
		return power + strToSetElement(input, set, i, power);
	}
}

void EraseRec(char* input, int* set, int i) {
	i++;
	if (*(input + i) == '\0') {
		//std::cout << "jest \\ 0 !!!! " << i << std::endl;
		return;
	}
	else if (*(input + i) == ' ') {
		// nic
	}
	else if (*(input + i) == '0' || *(input + i) == '1') {
		// wczytaj 5 znaków
		int tmp = strToSetElement(input, set, i - 1, 32);
		//std::cout << "i=" << i << " aa " << tmp << std::endl;
		i += 4;

		// usuń wczytany element
		*set = (*set & ~(1 << tmp));
	}
	EraseRec(input, set, i);
}

void Erase(char* input, int* set) {
	EraseRec(input, set, -1);
}

bool Emptiness(int set) {
	return set == 0;
}

bool Nonempty(int set) {
	return set != 0;
}

bool Disjoint(int set1, int set2) {
	return (set1 & set2) == 0;
}

bool Conjunctive(int set1, int set2) {
	return (set1 & set2) != 0;
}

bool Equality(int set1, int set2) {
	return set1 == set2;
}

bool Inclusion(int set1, int set2) {
	return (set1 | set2) == set2;
}

void Union(int set1, int set2, int* output) {
	*output = set1 | set2;
}

void Intersection(int set1, int set2, int* output) {
	*output = set1 & set2;
}

void Symmetric(int set1, int set2, int* output) {
	*output = set1 ^ set2;
}

void Difference(int set1, int set2, int* output) {
	*output = set1 ^ (~set2);
}

void Complement(int set, int* output) {
	*output = ~set;
}

void setElementToStr(int power, int toPrint, char* output, int output_idx) {
	if (power == 0)
		return;

	if (toPrint >= power) {
		*(output + output_idx) = '1';
		toPrint -= power;
	}
	else {
		*(output + output_idx) = '0';
	}
	power /= 2; // TODO przesunięcie bitowe
	output_idx++;
	setElementToStr(power, toPrint, output, output_idx);
}

int PrintRec(int set, char* output, int i, int output_idx) {
	i--;
	if (i == -1) 
		return output_idx;

	int tmp = set;
	tmp = tmp >> i;
	if (set & (1 << i)) {
		int power = 16;
		int toPrint = i;
		setElementToStr(power, toPrint, output, output_idx);
		output_idx += 5;
		*(output + output_idx) = ' ';
		output_idx++;
		return PrintRec(set, output, i, output_idx);
	}
	else {
		// nic
		return PrintRec(set, output, i, output_idx);
	} 
}

void Print(int set, char* output) {
	if (Emptiness(set)) {
		*(output + 0) = 'e';
		*(output + 1) = 'm';
		*(output + 2) = 'p';
		*(output + 3) = 't';
		*(output + 4) = 'y';
		*(output + 5) = '\0';
		return;
	}

	// TODO bez spacji na końcu i z \0
	int output_idx = PrintRec(set, output, 32, 0);
	*(output + output_idx - 1) = '\0';
}
