// Jakub Parapura

#include <iostream>

using std::cout;
using std::endl;
using std::cin;

struct Koralik {
	int id;

	Koralik() {}

	void print() {
		// TODO wypisywanie wiązań
		cout << id << endl;
	}
};

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

	void print() {
		Node<T>* node = head;
		while (node != NULL) {
			node->print();
			node = node->next;
		}
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
		IdSznura sn;
		int kr;
		Node<Sznur>* tmp_s;
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
				tmp_s = sznury.findSznurById(sn);
				tmp_s->data.koraliki.push(k);
//				tmp_s->data.koraliki.head->data.print();
//				tmp_s->data.id.print();
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
