// Jakub Parapura

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO czy w IBR r może być ujemny?

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
		//printf("aaaaa\n");
		// swap
		int tmp = *(tab + i);
		*(tab + i) = *(tab + start);
		*(tab + start) = tmp;
	}
}

void moveColumnsDown(unsigned short* tab, int start, int end) {
	//moveColumnsRight(tab, start, end);
	int i;
	for (i = start; i < end; i++) {
		// swap
		int tmp = *(tab + i);
		*(tab + i) = *(tab + end);
		*(tab + end) = tmp;
	}
}

void moveColumnsUp(unsigned short* tab, int start, int end) {
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

void moveColsLeftMult(int* row, int start, int amt, short unsigned int* cols, int index) {
	int to_place = start;
	int end = start + amt - 1;
	//printf("d: %d %d %d\n", start, amt, *len);
	int i;
	for (i = start + amt; i < *(cols + index); i++) {
		*(row + to_place) = *(row + i);
		to_place++;
	}
	if (start <= *(cols + index) - 1) {
		if (end <= *(cols + index) - 1) {
			(*(cols + index)) -= amt;
		}
		else {
			(*(cols + index)) = start;
		}
//		if (to_place - 1 <= *(cols + index))
//			(*(cols + index)) -= to_place - 1 - start + 1;
//		else
//			*(cols + index) = start;
	}
	//*(cols + index) = *(cols + index) - start;
	//*deleted = len - start;
	//*len = *len - start;
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

/*void removeEmptyRows(int** tab, unsigned short* cols, unsigned short* rows) {
	int tmp_rows = *rows;
	int last_empty = 0;
	int i;
	for (i = 0; i < *rows; i++) {
		if (*(cols + i) == 0) {
			tmp_rows--;
			//printf("pusty %d\n", i);
		}
		else {
			if (i != last_empty) {
				*(tab + last_empty) = *(tab + i);
				*(cols + last_empty) = *(cols + i);
			}
			last_empty++;
		}
	}
	tab = realloc(tab, tmp_rows * sizeof(*tab));
	cols = realloc(cols, tmp_rows * sizeof(*cols));
	*rows = tmp_rows;
}*/

int main() {
	unsigned short rows = 0;
	unsigned short* cols = NULL;
	int** tab = NULL;
	char* op = malloc(4 * sizeof(char));
	int end = 0;
	int argc;

	while (1) {
		scanf("%s", op);
		*(op + 3) = '\0';
	 	if (ccmp(op, "IBR") || ccmp(op, "IAR") ||
				 ccmp(op, "AFR") || ccmp(op, "ALR")) {
			int r;
			if (ccmp(op, "IBR") || ccmp(op, "IAR"))
				scanf("%d %d", &r, &argc);
			else
				scanf("%d", &argc);

			if (argc == 0)
				continue;

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
				r = rows - 1;
			else if (ccmp(op, "RMR"))
				scanf("%d", &r);

			if (rows == 0)
				continue;

			if (r > rows - 1)
				continue;
				
			free(*(tab + r));
			rows--;
			moveRowsUp(tab, r, rows);
			tab = realloc(tab, rows * sizeof(*tab));
			moveColumnsUp(cols, r, rows);
			cols = realloc(cols, rows * sizeof(*cols));
		}
		else if (ccmp(op, "DFC") || ccmp(op, "DLC") || ccmp(op, "RMC")) {
			int c, org_c;
			
			if (ccmp(op, "DFC"))
				org_c = 0;
			else if (ccmp(op, "DLC"))
				org_c = 2147483647;
			else if (ccmp(op, "RMC"))
				scanf("%d", &org_c);

			if (rows == 0)
				continue;

			int i;
			for (i = 0; i < rows; i++) {
				//moveColumnsRight(*(tab + i), *(cols + i), c);
				//printf("%d\n", c);
				c = org_c;
				if (*(cols + i) < c && ccmp(op, "DLC")) 
					c = *(cols + i);
				else if (*(cols + i) <= c && ccmp(op, "RMC"))
					continue;
				moveColumnsLeft(*(tab + i), c, *(cols + i) - 1);
				*(tab + i) = realloc(*(tab + i), (*(cols + i) - 1) * sizeof(*(tab + i)));
				*(cols + i) = *(cols + i) - 1;
			}
			//removeEmptyRows(tab, cols, &rows);
			// TODO przenieść to poniżej do osobnej funkcji
			int tmp_rows = rows;
			int last_empty = 0;
			//int i;
			for (i = 0; i < rows; i++) {
				if (*(cols + i) == 0) {
					tmp_rows--;
					//printf("pusty %d\n", i);
				}
				else {
					if (i != last_empty) {
						*(tab + last_empty) = *(tab + i);
						*(cols + last_empty) = *(cols + i);
					}
					last_empty++;
				}
			}
			tab = realloc(tab, tmp_rows * sizeof(*tab));
			cols = realloc(cols, tmp_rows * sizeof(*cols));
			rows = tmp_rows;
		}
		else if (ccmp(op, "RMB")) {
			int r, h, c, w;
			scanf("%d %d %d %d", &r, &h, &c, &w);

			int i;
			for (i = r; i < r + h; i++) {
				if (i > rows - 1)
					break;
				moveColsLeftMult(*(tab + i), c, w, cols, i);
			}
			
			//removeEmptyRows(tab, cols, &rows);
			// TODO przenieść to poniżej do osobnej funkcji
			int tmp_rows = rows;
			int tmp_rows = rows;
			int last_empty = 0;
			//int i;
			for (i = 0; i < rows; i++) {
				if (*(cols + i) == 0) {
					tmp_rows--;
					//printf("pusty %d\n", i);
				}
				else {
					if (i != last_empty) {
						*(tab + last_empty) = *(tab + i);
						*(cols + last_empty) = *(cols + i);
					}
					last_empty++;
				}
			}
			tab = realloc(tab, tmp_rows * sizeof(*tab));
			cols = realloc(cols, tmp_rows * sizeof(*cols));
			rows = tmp_rows;

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
			int i;
			for (i = 0; i < rows; i++) {
				free(*(tab + i));
			}
			if (rows != 0) {
				free(tab);
				free(cols);
			}
			free(op);
		}
		if (end)
			break;
	}

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
