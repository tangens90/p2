// Jakub Parapura

#include <iostream>

using std::cout;
using std::endl;
using std::cin;


struct IdSznura {
	char ch1, ch2, ch3;

	IdSznura() {}

	IdSznura(const char* id) {
		ch1 = *(id + 0);
		ch2 = *(id + 1);
		ch3 = *(id + 2);
	}

	int compare(IdSznura id) {
		if (id.ch1 == ch1 &&
			id.ch2 == ch2 &&
			id.ch3 == ch3)
			return 0;

		return -1;
	}

	void print() {
		cout << ch1 << ch2 << ch3;
	}
};

template <typename T>
struct Node {
	T data;
	Node<T>* next;

//	Node() : data(NULL), next(NULL) {}

	void print() {
		data.print();
	}
};

template <typename T>
struct List {
	Node<T>* head;

	List<T>() : head(NULL) {}

	// TODO dodawanie ma uwzględniać kolejność sznurów
	void push(T data) {
		if (head == NULL) {
			head = new Node<T>();
			head->data = data;
			head->next = NULL;
		}
		else {
			Node<T>* curr = head;
			while (curr->next != NULL) {
				curr = curr->next;	
			}
			// curr is the tail of the list
			Node<T>* last = new Node<T>();
			last->data = data;
			curr->next = last;
			last->next = NULL;
		}
	}

	Node<T>* findSznurById(IdSznura id) {
		Node<T>* curr = head;
		while (curr != NULL) {
			if (curr->data.id.compare(id) == 0) {
				return curr;
			}
			curr = curr->next;	
		}
		cout << "Nie ma sznura o podanym id!" << endl;
		return NULL;
	}

	Node<T>* findKoralikById(int id) {
		Node<T>* curr = head;
		while (curr != NULL) {
			if (curr->data.id == id) {
				return curr;
			}
			curr = curr->next;	
		}
		cout << "Nie ma koralika o podanym id!" << endl;
		return NULL;
	}

	void print() {
		Node<T>* node = head;
		while (node != NULL) {
			node->print();
			node = node->next;
		}
	}
	
	void printWiazania() {
		Node<T>* node = head;
		while (node != NULL) {
			cout << " "; 
			(*(node->data)).ojciec.print(); 
			cout << " " << (*(node->data)).id;
			node = node->next;
		}
	}
};

struct Koralik {
	int id;
	// TODO aktualizowac ojca po zmianie sznura
	IdSznura ojciec;
	List<Koralik*> in, out;

	Koralik() {}

	void linkMeTo(Koralik* k) {
		out.push(k);
		k->in.push(this);
	}

	void print() {
		// TODO wypisywanie wiązań
		// TODO czy ta spacja nie jest problemem jeśli
		// nie ma żadnych wiązań?
		cout << id;
		out.printWiazania();
		cout << endl;
	}
};

struct Sznur {
	IdSznura id;
	List<Koralik> koraliki;

 	Sznur() {}
 	Sznur(IdSznura cid) {
 		id.ch1 = cid.ch1; 
 		id.ch2 = cid.ch2; 
 		id.ch3 = cid.ch3; 
 	}

	void print() {
		id.print();
		cout << endl;
		koraliki.print();
	}
};

int main() {
	char op;
	bool end = false;

	List<Sznur> sznury;
	// TODO czy niezerowanie elementów poniżej nie powoduje
	// błędów ze wskaźnikami do dowiązań

	while (true) {
		cin >> op;
		Sznur s;
		IdSznura sn, sS, dS;
		int kr, sK, dK;
		Node<Sznur>* tmp_s;
//		Node<Koralik>* tmp_k;
		Koralik k;

		switch (op) {
			case 'S':
				cin >> sn.ch1 >> sn.ch2 >> sn.ch3;
				s.id = sn;
				sznury.push(s);	
				break;
			case 'B':
				cin >> kr;
				k.id = kr;
				cin >> sn.ch1 >> sn.ch2 >> sn.ch3;
				k.ojciec = sn;
				tmp_s = sznury.findSznurById(sn);
				tmp_s->data.koraliki.push(k);
//				tmp_s->data.koraliki.head->data.print();
//				tmp_s->data.id.print();
				break;
			case 'L':
				cin >> sK >> sS.ch1 >> sS.ch2 >> sS.ch3 >> dK >> dS.ch1 >> dS.ch2 >> dS.ch3;
				sznury.findSznurById(sS)->data.koraliki.findKoralikById(sK)->data.linkMeTo(
					&sznury.findSznurById(dS)->data.koraliki.findKoralikById(dK)->data);
				break;
			case 'P':
				sznury.print();
				break;
			case 'F':
				end = true;
				break;
		}

		if (end) break;
	}

	// TODO zwolnić pamięć
}
