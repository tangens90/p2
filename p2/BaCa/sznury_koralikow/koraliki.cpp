// Jakub Parapura

#include <iostream>

using std::cout;
using std::endl;
using std::cin;

template <typename T> struct List;
struct Sznur;
struct Koralik;


struct IdSznura {
	char ch1, ch2, ch3;

	IdSznura() {}

	IdSznura(const char* id) {
		ch1 = *(id + 0);
		ch2 = *(id + 1);
		ch3 = *(id + 2);
	}

	bool operator==(const IdSznura s) {
		return this->ch1 == s.ch1 &&
			this->ch2 == s.ch2 &&
			this->ch3 == s.ch3;
	}

	bool operator!=(const IdSznura s) {
		return ch1 != s.ch1 ||
			   ch2 != s.ch2 ||
			   ch3 != s.ch3;
	}

	bool operator<(const IdSznura s) {
		if (ch1 != s.ch1)
			return ch1 < s.ch1;

		if (ch2 != s.ch2)
			return ch2 < s.ch2;

		return ch3 < s.ch3;
	}

	void print() {
		cout << ch1 << ch2 << ch3;
	}
};

struct Wiazanie {
	IdSznura sznur;
	int doKoralika;

	bool operator==(const Wiazanie w) {
		bool s = this->sznur.ch1 == w.sznur.ch1 &&
			this->sznur.ch2 == w.sznur.ch2 &&
			this->sznur.ch3 == w.sznur.ch3;
		return s && this->doKoralika == w.doKoralika;
	}
	
	bool operator!=(const Wiazanie w) {
		bool s = this->sznur.ch1 != w.sznur.ch1 || 
			this->sznur.ch2 != w.sznur.ch2 ||
			this->sznur.ch3 != w.sznur.ch3;
		return s && this->doKoralika != w.doKoralika;
	}

	bool operator<(const Wiazanie w) {
		if (sznur != w.sznur)
			return sznur < w.sznur;

		return doKoralika < w.doKoralika;
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
	// TODO nie zezwalać na duplikaty!
	// TODO czy działa porządek dla koralików jeśli sznur1 < sznur2 && koralik1 < koralik2
	void push(T data) {
		if (head == NULL) {
			head = new Node<T>();
			head->data = data;
			head->next = NULL;
		}
		else {
			Node<T>* curr = head;
			if (data < curr->data) {
				Node<T>* n = new Node<T>();
				n->data = data;
				n->next = head;
				head = n;
				return;
			}
			while (curr->next != NULL) {
				if (data < curr->next->data) {
					Node<T>* n = new Node<T>();
					n->data = data;
					Node<T>* tmp = curr->next;
					curr->next = n;
					n->next = tmp;
					return;
				}
				curr = curr->next;	
			}
			// curr is the tail of the list
			Node<T>* last = new Node<T>();
			last->data = data;
			curr->next = last;
			last->next = NULL;
		}
	}

	void pop(T data) {
		Node<T>* curr = head;
		if (curr->data == data) {
			// delete head node
			Node<T>* tmp = head;
			head = head->next;
			delete tmp;
		}
		else {
			while (curr->next->data != data) {
				curr = curr->next;
				if (curr->next == NULL)
					break;
			}

			if (curr->next == NULL)
				cout << "Nie ma Node do usunięcia o podanym wskaźniku!" << endl;
			else {
				Node<T>* tmp = curr->next;
				curr->next = tmp->next;
				delete tmp;
			}
		}
	}

//	void popKoralik(List<Sznur>* sznury, T data) {
//		Node<Sznur>* s = sznury->head;
//		while (s != NULL) {
//
//			s = s->next;
//		}
//		Node<Wiazanie>* curr = data.out.head;
//		while (curr != NULL) {
//			cout << curr->data.doKoralika << endl;
////			curr->data.sznur.print();
//			curr = curr->next;
//		}
//		pop(data);
//	}

	Node<T>* findSznurById(IdSznura id) {
		Node<T>* curr = head;
		while (curr != NULL) {
			if (curr->data.id == id) { 
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
			node->data.sznur.print();
			cout << " " << node->data.doKoralika;
			node = node->next;
		}
	}
};

struct Koralik {
	int id;
	// TODO aktualizowac ojca po zmianie sznura
	// podobno jednak tego nie trzeba robić?
	IdSznura ojciec;
	List<Wiazanie> out;

	Koralik() {}

	bool operator==(const Koralik k) {
		return this->id == k.id;
	}

	bool operator!=(const Koralik k) {
		return this->id != k.id;
	}

	bool operator<(const Koralik k) {
		return this->id < k.id;
	}

	void linkMeTo(Koralik* k) {
		Wiazanie w;
		w.sznur = k->ojciec;
		w.doKoralika = k->id;
		out.push(w);
	}

	void unLinkMeTo(Koralik* k) {
		Wiazanie w;
		w.sznur = k->ojciec;
		w.doKoralika = k->id;
		out.pop(w);
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

	bool operator<(const Sznur s) {
		return id < s.id;
	}

	void print() {
		id.print();
		cout << endl;
		koraliki.print();
	}
};

void popWiazania(List<Sznur>* sznury, int kr, IdSznura sn) {
	Node<Sznur>* curr = sznury->head;
	while (curr != NULL) {
		Node<Koralik>* k = curr->data.koraliki.head;
		while (k != NULL) {
			// TODO teraz patrzeć na wiązania!
			Node<Wiazanie>* w = k->data.out.head;
			while (w != NULL) {
				if (w->data.doKoralika == kr && w->data.sznur == sn) {
					k->data.out.pop(w->data);
				}
				w = w->next;
			}
			k = k->next;
		}
		curr = curr->next;
	}
}


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
			case 'U':
				cin >> sK >> sS.ch1 >> sS.ch2 >> sS.ch3 >> dK >> dS.ch1 >> dS.ch2 >> dS.ch3;
				sznury.findSznurById(sS)->data.koraliki.findKoralikById(sK)->data.unLinkMeTo(
					&sznury.findSznurById(dS)->data.koraliki.findKoralikById(dK)->data);
				break;
			case 'D':
				cin >> kr;
				k.id = kr;
				cin >> sn.ch1 >> sn.ch2 >> sn.ch3;
				popWiazania(&sznury, kr, sn);
				sznury.findSznurById(sn)->data.koraliki.pop(
					sznury.findSznurById(sn)->data.koraliki.findKoralikById(k.id)->data);
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
