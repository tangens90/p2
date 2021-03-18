// Jakub Parapura

#include <iostream>

using namespace std;

struct IdSznura {
	char ch1, ch2, ch3;

	IdSznura() {}

	IdSznura(const char* id) {
		ch1 = *(id + 0);
		ch2 = *(id + 1);
		ch3 = *(id + 2);
	}

	void print() {
		cout << ch1 << ch2 << ch3;
	}
};

struct Sznur {
	IdSznura id;

 	Sznur() {}
 	Sznur(IdSznura cid) {
 		id.ch1 = cid.ch1; 
 		id.ch2 = cid.ch2; 
 		id.ch3 = cid.ch3; 
 	}
};

template <typename T>
struct Node {
	T data;
	Node<T>* next;

//	Node() : data(NULL), next(NULL) {}

	void print() {
		data.id.print();
	}
};

template <typename T>
struct List {
	Node<T>* head;

	List<T>() : head(NULL) {}

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

	void print() {
		Node<T>* node = head;
		while (node != NULL) {
			node->print();
			cout << endl;
			node = node->next;
		}
	}
};

int main() {
	char op;
	bool end = false;

	List<Sznur> sznury;
	// TODO czy niezerowanie elementów poniżej nie powoduje
	// błędów ze wskaźnikami do dowiązań
	Sznur s;
	IdSznura sn;

	while (true) {
		cin >> op;

		switch (op) {
			case 'S':
				cin >> sn.ch1 >> sn.ch2 >> sn.ch3;
				s.id = sn;
				sznury.push(s);	
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
