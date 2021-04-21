// Jakub Parapura

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ccmp(const char* a, const char* b) {
	int i;
	for (i = 0; i < 3; i++) {
		if (*(a + i) != *(b + i))
			return 0;
	}
	return 1;
}

void moveColumnsRight(int* tab, int start, int end) {
	int i;
	for (i = start; i < end; i++) {
		// swap
		int tmp = *(tab + i);
		*(tab + i) = *(tab + end);
		*(tab + end) = tmp;
	}
}

void moveColumnsLeft(int* tab, int start, int end) {
	int i;
	for (i = end; i > start; i--) {
		// swap
		int tmp = *(tab + i);
		*(tab + i) = *(tab + start);
		*(tab + start) = tmp;
	}
}

void moveColumnsDown(short unsigned int* tab, int start, int end) {
	//moveColumnsRight(tab, start, end);
	int i;
	for (i = start; i < end; i++) {
		// swap
		int tmp = *(tab + i);
		*(tab + i) = *(tab + end);
		*(tab + end) = tmp;
	}
}

void moveColumnsUp(short unsigned int* tab, int start, int end) {
	//moveColumnsLeft(tab, start, end);
	int i;
	for (i = end; i > start; i--) {
		// swap
		int tmp = *(tab + i);
		*(tab + i) = *(tab + start);
		*(tab + start) = tmp;
	}
}
void moveRowsDown(int** tab, int start, int end) {
	int i;
	for (i = start; i < end; i++) {
		// swap
		int* tmp = *(tab + i);
		*(tab + i) = *(tab + end);
		*(tab + end) = tmp;
	}
}

void moveRowsUp(int** tab, int start, int end) {
	int i;
	for (i = end; i > start; i--) {
		// swap
		int* tmp = *(tab + i);
		*(tab + i) = *(tab + start);
		*(tab + start) = tmp;
	}
}

void writeToArray(int* tab, int n) {
	int i;
	for (i = 0; i < n; i++) {
		int e;
		scanf("%d", &e);
		*(tab + i) = e;
	}
}

int main() {
	unsigned short rows = 0;
	unsigned short* cols = NULL;
	int** tab = NULL;
	char* op = malloc(3 * sizeof(char));
	int end = 0;
	int argc;

	while (1) {
		scanf("%s", op);
	 	if (ccmp(op, "IBR") || ccmp(op, "IAR") ||
				 ccmp(op, "AFR") || ccmp(op, "ALR")) {
			int r;
			if (ccmp(op, "IBR") || ccmp(op, "IAR"))
				scanf("%d %d", &r, &argc);
			else
				scanf("%d", &argc);

			if (ccmp(op, "AFR")) 
				r = 0;
			if (ccmp(op, "ALR")) 
				r = rows;
			
			if (r > rows - 1 && (ccmp(op, "IBR") || ccmp(op, "IAR")))
				continue;

			tab = realloc(tab, (rows + 1) * sizeof(*tab));
			cols = realloc(cols, (rows + 1) * sizeof(*cols));

			if (ccmp(op, "IAR")) r++;

			int* newRow = malloc(argc * sizeof(*newRow));
			writeToArray(newRow, argc);

			moveRowsDown(tab, r, rows);
			moveColumnsDown(cols, r, rows);

			*(tab + r) = newRow;
			*(cols + r) = argc;
			rows++;
		}
		else if (ccmp(op, "IBC") || ccmp(op, "IAC") ||
				 ccmp(op, "AFC") || ccmp(op, "ALC")) {
			int c;
			if (ccmp(op, "IBC") || ccmp(op, "IAC"))
				scanf("%d %d", &c, &argc);
			else
				scanf("%d", &argc);

			if (ccmp(op, "AFC"))
				c = 0;
			if (ccmp(op, "ALC"))
				c = 2147483647;

			int* input = malloc(argc * sizeof(*input));
			writeToArray(input, argc);

			int smaller = argc < rows ? argc : rows;

			if (ccmp(op, "IAC")) c++;
		
			int i;
			for (i = 0; i < smaller; i++) {
				*(tab + i) = realloc(*(tab + i), (*(cols + i) + 1) * sizeof(*(tab + i)));

				moveColumnsRight(*(tab + i), c, *(cols + i));
				int tmp_c = c;
				if (*(cols + i) < c) 
					tmp_c = *(cols + i);
				*(*(tab + i) + tmp_c) = *(input + i);
				*(cols + i) = *(cols + i) + 1;
			}
		
			if (argc > rows) {
				tab = realloc(tab, argc * sizeof(*tab));
				cols = realloc(cols, argc * sizeof(*cols));
				int i;
				for (i = rows; i < argc; i++) {
					*(cols + i) = 1;
					
					int* newRow = malloc(1 * sizeof(*newRow));
					*newRow = *(input + i);
					*(tab + i) = newRow;
				}
				rows = argc;
			}

			free(input);
		}
		else if (ccmp(op, "SWR")) {
			int r, s;
			scanf("%d %d", &r, &s);
			if (r > rows - 1 || s > rows - 1)
				continue;

			int* tmp = *(tab + r);
			*(tab + r) = *(tab + s);
			*(tab + s) = tmp;

			int tmp2 = *(cols + r);
			*(cols + r) = *(cols + s);
			*(cols + s) = tmp2;
		}
		else if (ccmp(op, "SWC")) {
			int c, d;
			scanf("%d %d", &c, &d);
			int bigger = c > d ? c : d;
			int i, swap;
			for (i = 0; i < rows; i++) {
				if (*(cols + i) < bigger + 1)
					continue;

				swap = *(*(tab + i) + c);
				*(*(tab + i) + c) = *(*(tab + i) + d);
				*(*(tab + i) + d) = swap;
			}
		}
		else if (ccmp(op, "DFR") || ccmp(op, "DLR") ||
				 ccmp(op, "RMR")) {
			int r;

			if (ccmp(op, "DFR"))
				r = 0;
			else if (ccmp(op, "DLR"))
				r = 2147483647;
			else if (ccmp(op, "RMR"))
				scanf("%d", &r);

			int tmp_r = r;
			if (rows < r) 
				tmp_r = rows - 1;
				
			free(*(tab + tmp_r));
			rows--;
			moveRowsUp(tab, tmp_r, rows);
			tab = realloc(tab, rows * sizeof(*tab));
			moveColumnsUp(cols, tmp_r, rows);
			cols = realloc(cols, rows * sizeof(*cols));
		}
		else if (ccmp(op, "PRT")) {
			printf("%d\n", rows);
			int i;
			for (i = 0; i < rows; i++) {
				printf("%d", *(cols + i));
				int j;
				for (j = 0; j < *(cols + i); j++) {
					printf(" %d", *(*(tab + i) + j));
				}
				printf("\n");
			}
		}
		else if (ccmp(op, "END")) {
			end = 1;
		}
		if (end)
			break;
	}

	int i;
	for (i = 0; i < rows; i++) {
		free(*(tab + i));
	}
	free(tab);
	free(cols);
	free(op);
	return 0;
}

// atBegBool = 1 => at beg
// atBegBool = 0 => at end
//void insertAtBegOrEnd(int** tab, unsigned short* cols, int atBegBool, unsigned short rows) {
//	int argc;
//	scanf("%d", &argc);
//
//	int* input = malloc(argc * sizeof(int));
//	writeToArray(input, argc);
//	int smaller = argc < rows ? argc : rows;
//
//	for (int i = 0; i < smaller; i++) {
//		*(tab + i) = realloc(*(tab + i), (*(cols + i) + 1) * sizeof(int*));
//		if (atBegBool == 1) {
//			moveColumnsRight(*(tab + i), 0, *(cols + i));
//		}
//		else {
//		}
//		*(cols + i) = *(cols + i) + 1;
//	}
//
//	if (argc > rows) {
//		tab = realloc(tab, argc * sizeof(int*));
//		cols = realloc(cols, argc * sizeof(short unsigned));
//		for (int i = rows; i < argc; i++) {
//			*(cols + i) = 1;
//			
//			int* newRow = malloc(1 * sizeof(int));
//			*newRow = *(input + i);
//			*(tab + i) = newRow;
//		}
//		rows = argc;
//	}
//
//	free(input);
//}



/*else if (ccmp(op, "AFC") || ccmp(op, "ALC")) {
	scanf("%d", &argc);
	int* input = malloc(argc * sizeof(int));
	writeToArray(input, argc);

	int smaller = argc < rows ? argc : rows;

	int i;
	for (i = 0; i < smaller; i++) {
		*(tab + i) = realloc(*(tab + i), (*(cols + i) + 1) * sizeof(int*));
		if (ccmp(op, "AFC")) {
			moveColumnsRight(*(tab + i), 0, *(cols + i));
			*(*(tab + i) + 0) = *(input + i);
		}
		else {
			*(*(tab + i) + *(cols + i)) = *(input + i);
		}
		*(cols + i) = *(cols + i) + 1;
	}

	if (argc > rows) {
		tab = realloc(tab, argc * sizeof(int*));
		cols = realloc(cols, argc * sizeof(short unsigned));
		int i;
		for (i = rows; i < argc; i++) {
			*(cols + i) = 1;
			
			int* newRow = malloc(1 * sizeof(int));
			*newRow = *(input + i);
			*(tab + i) = newRow;
		}
		rows = argc;
	}

	free(input);
}*/


/*if (ccmp(op, "AFR")) {
	scanf("%d", &argc);

	tab = realloc(tab, (rows + 1) * sizeof(int*));
	cols = realloc(cols, (rows + 1) * sizeof(short unsigned));

	// przesunięcie wszystkich wierszy w dół
	if (rows != 0)  {
		moveRowsDown(tab, 0, rows);
	//if (rows != 0) 
		moveColumnsDown(cols, 0, rows);
	}

	// wpisywanie danych do nowego wiersza
	int* newRow = malloc(argc * sizeof(int));
	writeToArray(newRow, argc);

	*(cols + 0) = argc;
	*(tab + 0) = newRow;

	rows++;
}
else if (ccmp(op, "ALR")) {
	scanf("%d", &argc);

	tab = realloc(tab, (rows + 1) * sizeof(int*));
	cols = realloc(cols, (rows + 1) * sizeof(short unsigned));

	int* newRow = malloc(argc * sizeof(int));
	writeToArray(newRow, argc);

	*(tab + rows) = newRow;
	*(cols + rows) = argc;

	rows++;
}*/
