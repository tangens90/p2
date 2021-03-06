// Jakub Parapura

#include <cstdlib>

//#include <iostream>
//using namespace std;

typedef unsigned int cint;

#define Fruit FRUIT_CLASS
#define Branch BRANCH_CLASS
#define Tree WOOD_CLASS
#define Garden GARDEN_CLASS

#define cloneTree cloneWood
#define cutTree cutWood
#define extractTree extractWood
#define getTreePointer getWoodPointer
#define getTreesTotal getWoodsTotal
#define harvestTree harvestWood
#define plantTree plantWood
#define getTreesTotal getWoodsTotal
#define harvestTree harvestWood
#define plantTree plantWood
#define growthTree growthWood
#define fadeTree fadeWood

class Garden;
class Tree;
class Branch;
class Fruit;

// TODO sprawdzić czy nigdzie nie ma (unsigned) inta innego niż cint


class Fruit {
private:
	cint weight;
	cint length; // długość na jakiej owoc rośnie
	Branch* branch;

	Fruit* next;
	
public:
	Fruit();
	Fruit(cint, Branch*);
	Fruit(const Fruit&, Branch*);
	~Fruit();

	cint getLength(void) const;
	cint getWeight(void) const;
	void growthFruit(void);
	void fadeFruit(void);
	void pluckFruit(void);
	Branch* getBranchPointer(void);

	Fruit* getNext(void) const;
	void setNext(Fruit*);
	void updateGlobalWeight(cint, bool);
	void updateGlobalFruitAmt(cint, bool);
	void setBranchPointer(Branch*);
};


class Branch {
private:
	cint fruitAmt;
	cint weightAmt;
	cint height;
	cint length;
	Tree* tree;

	Fruit* first;
	Fruit* last;
	Branch* next;

public:
	Branch();
	Branch(const Branch&);
	Branch(const Branch&, Tree*);
	Branch(cint, Tree*);
	~Branch();

	cint getFruitsTotal(void) const;
	cint getWeightsTotal(void) const;
	cint getHeight(void) const;
	cint getLength(void) const;
	void growthBranch(void);
	void fadeBranch(void);
	void harvestBranch(cint);
	void cutBranch(cint);
	Fruit* getFruitPointer(cint);
	Tree* getTreePointer(void);

	void setWeight(cint);
	void setHeight(cint);
	void setTreePointer(Tree*);
	void setFruitAmt(cint);
	void updateGlobalBranchAmt(cint, bool);
	Branch* getNext(void) const;
	void setNext(Branch*);
};


class Tree {
private:
	cint id;
	cint height;
	cint fruitAmt;
	cint branchAmt;
	cint weight;
	Garden* garden;

	Branch* first;
	Branch* last;
	Tree* next;
	Tree* prev;

public:
	Tree();
	Tree(cint, Garden*);
	Tree(const Tree&, Garden*);
	Tree(const Tree&);
	~Tree();

	void setNumber(cint);
	void setGardenPointer(Garden*);
	Tree* getNext(void) const;
	Tree* getPrev(void) const;
	Branch* getFirst(void) const;
	void setWeight(cint);
	void setFruitAmt(cint);
	void setNext(Tree*);
	void setPrev(Tree*);
	void setBranchAmt(cint);
	void updateGlobalTreesAmt(cint, bool);

	cint getBranchesTotal(void) const;
	cint getFruitsTotal(void) const;
	cint getWeightsTotal(void) const;
	cint getNumber(void) const;
	cint getHeight(void) const;
	void growthTree(void);
	void fadeTree(void);
	void harvestTree(cint);
	void cutTree(cint);
	void cloneBranch(Branch*);
	Garden* getGardenPointer(void);
	Branch* getBranchPointer(cint);
};

class Garden {
private:
	cint treesAmt;
	cint branchesAmt;
	cint fruitAmt;
	cint weightAmt;

	Tree* first;
	Tree* last;

	cint potentialGaps;

public:
	Garden();
	~Garden();

	cint getTreesTotal(void) const;
	cint getBranchesTotal(void) const;
	cint getFruitsTotal(void) const;
	cint getWeightsTotal(void) const;
	void plantTree(void);
	void extractTree(cint);
	void growthGarden(void);
	void fadeGarden(void);
	void harvestGarden(cint);
	void cloneTree(cint);
	Tree* getTreePointer(cint);

	void setTreesAmt(cint);
	void setBranchAmt(cint);
	void setWeight(cint);
	void setFruitAmt(cint);
};


// ================ START FRUIT ================

Fruit::Fruit() {
	this->weight = 0;
	this->length = 0;
	this->branch = NULL;
	this->next = NULL;
	updateGlobalFruitAmt(1, true);
}

Fruit::~Fruit() {
	updateGlobalWeight(weight, false);
	updateGlobalFruitAmt(1, false);
	weight = 0;
	length = 0;
	branch = NULL;
	next = NULL;
}

Fruit::Fruit(cint len, Branch* b) {
	weight = 0;
	length = len;
	branch = b;
	next = NULL;
	updateGlobalFruitAmt(1, true);
}

Fruit::Fruit(const Fruit& f, Branch* b) {
	weight = 0;
	length = f.length;
	next = f.next;
	branch = b;

	updateGlobalFruitAmt(1, true);
	updateGlobalWeight(f.weight, true);
}

cint Fruit::getLength(void) const {
	return length;
}

cint Fruit::getWeight(void) const {
	return weight;
}

void Fruit::growthFruit(void) {
	updateGlobalWeight(1, true);
}

void Fruit::fadeFruit(void) {
	// if w zasadzie sprawdza czy weight != 0
	if (weight > 0) {
		updateGlobalWeight(1, false);
	}
}

void Fruit::pluckFruit(void) {
	updateGlobalWeight(weight, false);
}

Branch* Fruit::getBranchPointer(void) {
	return branch;
}

Fruit* Fruit::getNext(void) const {
	return next;
}

void Fruit::setNext(Fruit* f) {
	next = f;
}

void Fruit::updateGlobalWeight(cint n, bool add) {
	if (add) weight += n;
	else weight -= n;
	Branch* branch = getBranchPointer();
		
	if (branch == NULL) {
		return;
	}
	if (add) branch->setWeight(branch->getWeightsTotal() + n);
	else	 branch->setWeight(branch->getWeightsTotal() - n);

	Tree* tree = branch->getTreePointer();
	if (tree == NULL)
		return;
	if (add) tree->setWeight(tree->getWeightsTotal() + n);
	else 	 tree->setWeight(tree->getWeightsTotal() - n);

	Garden* garden = tree->getGardenPointer();
	if (garden == NULL)
		return;
	
	if (add) garden->setWeight(garden->getWeightsTotal() + n);
	else     garden->setWeight(garden->getWeightsTotal() - n);

}

void Fruit::updateGlobalFruitAmt(cint n, bool add) {
	Branch* branch = getBranchPointer();
	if (branch == NULL) {
		return;
	}
	if (add) branch->setFruitAmt(branch->getFruitsTotal() + n);
	else	 branch->setFruitAmt(branch->getFruitsTotal() - n);

	Tree* tree = branch->getTreePointer();
	if (tree == NULL) {
		return;
	}
	if (add) tree->setFruitAmt(tree->getFruitsTotal() + n);
	else 	 tree->setFruitAmt(tree->getFruitsTotal() - n);

	Garden* garden = tree->getGardenPointer();
	if (garden == NULL)
		return;
	
	if (add) garden->setFruitAmt(garden->getFruitsTotal() + n);
	else     garden->setFruitAmt(garden->getFruitsTotal() - n);
}

void Fruit::setBranchPointer(Branch* b) {
	branch = b;
}

// ================ END FRUIT ================


// ================ START BRANCH ================


Branch::Branch() {
	fruitAmt = 0;
	weightAmt = 0;
	length = 0;
	height = 0;
	tree = NULL;
	first = NULL;
	last = NULL;
	next = NULL;
	updateGlobalBranchAmt(1, true);
}

Branch::Branch(cint h, Tree* t) {
	fruitAmt = 0;
	weightAmt = 0;
	length = 0;
	height = h;
	tree = t;
	first = NULL;
	last = NULL;
	next = NULL;
	updateGlobalBranchAmt(1, true);
}

Branch::Branch(const Branch& b) {
	// TODO każdą zmianę zrobić też niżej!!!!!
	weightAmt = 0;
	fruitAmt = 0;
	length = b.length;
	height = b.height;
	tree = b.tree;
	first = NULL;
	last = NULL;
	next = b.getNext();
	// nie musimy tutaj aktualizować ilości owoców, bo konstruktor owocu zwiększa globalnie fruitAmt
	updateGlobalBranchAmt(1, true);

	if (b.fruitAmt > 0) {
		first = new Fruit(*b.first, this);
		first->setBranchPointer(this);
		last = first;

		Fruit* it = first;
		Fruit* itB = b.first->getNext();

		while (itB != NULL) {
			it->setNext(new Fruit(*itB, this));

			it = it->getNext();
			itB = itB->getNext();

			it->setBranchPointer(this);

			last = it;
		}

		last->setNext(NULL);
	}
}


Branch::Branch(const Branch& b, Tree* parent) {
	// TODO każdą zmianę zrobić też wyżej!!!!!
	weightAmt = 0;
	fruitAmt = 0;
	length = b.length;
	height = b.height;
	tree = parent;
	first = NULL;
	last = NULL;
	next = b.getNext();
	// nie musimy tutaj aktualizować ilości owoców, bo konstruktor owocu zwiększa globalnie fruitAmt
	updateGlobalBranchAmt(1, true);

	if (b.fruitAmt > 0) {
		// ten cyrk z fruitAmt jest potrzebny, bo fruitAmt ma zostać globalnie wypełnione przez mechanizm globalnego zwiększania wartości fruitAmt w konstruktorze Fruit
		fruitAmt = 0;
		first = new Fruit(*b.first, this);
		first->setBranchPointer(this);
		last = first;

		Fruit* it = first;
		Fruit* itB = b.first->getNext();

		while (itB != NULL) {
			it->setNext(new Fruit(*itB, this));

			it = it->getNext();
			itB = itB->getNext();

			it->setBranchPointer(this);

			last = it;
		}

		last->setNext(NULL);
	}
}

Branch::~Branch() {
	Fruit* it = first;
	Fruit* tmp;
	while (it != NULL) {
		tmp = it;
		it = it->getNext();
		delete tmp;
	}
	updateGlobalBranchAmt(1, false);
	first = NULL;
	fruitAmt = 0;
	weightAmt = 0;
	length = 0;
	height = 0;
	tree = NULL;
	last = NULL;
}

void Branch::setFruitAmt(cint n) {
	fruitAmt = n;
}

void Branch::setTreePointer(Tree* t) {
	tree = t;
}

void Branch::setHeight(cint h) {
	height = h;
}

cint Branch::getFruitsTotal(void) const {
	return fruitAmt;
}


cint Branch::getWeightsTotal(void) const {
	return weightAmt;
}

cint Branch::getHeight(void) const {
	return height;
}

cint Branch::getLength(void) const {
	return length;
}

void Branch::growthBranch(void) {
	length++;
	for (Fruit* it = first; it != NULL; it = it->getNext()) {
		it->growthFruit();
	}
	if (length > 0 && length % 2 == 0) {
		if (fruitAmt > 0) {
			last->setNext(new Fruit(length, this));
			last = last->getNext();
		}
		else {
			Fruit* f = new Fruit(length, this);
			last = f;
			first = f;
		}
		last->setNext(NULL);
	}
}

void Branch::fadeBranch(void) {
	if (length == 0)
		return;
	
	length--;
	if (fruitAmt == 0)
		return;
	
	if (last->getLength() > length) {
		Fruit* it = first;
		if (it == last)
			first = last = NULL;
		else {
			while (it->getNext() != last) {
				it->fadeFruit();
				it = it->getNext();
			}
			it->fadeFruit();

			last = it;
			it = it->getNext();
			last->setNext(NULL);
		}

		delete it;
	}
	else {
		for (Fruit* it = first; it != NULL; it = it->getNext()) {
			it->fadeFruit();
		}
	}
}

void Branch::harvestBranch(cint n) {
	for (Fruit* it = first; it != NULL; it = it->getNext()) {
		if (it->getWeight() >= n) {
			it->pluckFruit();
		}
	}
}

Fruit* Branch::getFruitPointer(cint n) {
	if (n == 0 || n % 2 != 0 || n > length)
		return NULL;

	for (Fruit* it = first; it != NULL; it = it->getNext()) {
		if (it->getLength() == n)
			return it;
	}
	return NULL;
}

Tree* Branch::getTreePointer(void) {
	return tree;
}

void Branch::cutBranch(cint l) {
	length = l;
	if (fruitAmt == 0)
		return;
	
	if (last->getLength() <= length)
		return;

	Fruit* it = first;
	while (it != NULL) {
		if (it->getLength() > length) {
			break;
		}
		last = it;
		it = it->getNext();
	}

	if (it == first)
		first = last = NULL; // nie ma wycieku, bo it != NULL
	
	Fruit* tmp;
	while (it != NULL) {
		tmp = it;
		it = it->getNext();
		delete tmp;
	}

	if (last != NULL) {
		last->setNext(NULL);
	}
}

void Branch::setWeight(cint n) {
	weightAmt = n;
}

void Branch::updateGlobalBranchAmt(cint n, bool add) {
	Tree* tree = getTreePointer();
	if (tree == NULL)
		return;

	if (add) tree->setBranchAmt(tree->getBranchesTotal() + n);
	else     tree->setBranchAmt(tree->getBranchesTotal() - n);

	Garden* garden = tree->getGardenPointer();
	if (garden == NULL)
		return;

	if (add) garden->setBranchAmt(garden->getBranchesTotal() + n);
	else     garden->setBranchAmt(garden->getBranchesTotal() - n);
}

Branch* Branch::getNext() const {
	return next;
}

void Branch::setNext(Branch* b) {
	next = b;
}

// ================ END BRANCH ================


// ================ START TREE ================


Tree::Tree() {
	id = 0;
	height = 0;
	fruitAmt = 0;
	branchAmt = 0;
	weight = 0;
	garden = NULL;
	first = NULL;
	last = NULL;
	next = NULL;
	prev = NULL;
	updateGlobalTreesAmt(1, true);
}

Tree::Tree(cint id, Garden* g) {
	this->id = id;
	height = 0;
	fruitAmt = 0;
	branchAmt = 0;
	weight = 0;
	garden = g;
	first = NULL;
	last = NULL;
	next = NULL;
	prev = NULL;
	updateGlobalTreesAmt(1, true);
}

Tree::Tree(const Tree& t) {
	// TODO każda zmiana również niżej!!!!
	id = t.id;
	height = t.height;
	fruitAmt = 0;
	weight = 0;
	garden = t.garden;
	first = NULL;
	last = NULL;
	next = t.getNext();
	prev = t.getPrev();
	updateGlobalTreesAmt(1, true);

	branchAmt = t.branchAmt;
	if (branchAmt > 0) {
		branchAmt = 0;
		first = new Branch(*t.first, this);
		last = first;

		Branch* it = first;
		Branch* itB = t.first->getNext();
	
		while (itB != NULL) {
			it->setNext(new Branch(*itB, this));

			it = it->getNext();
			itB = itB->getNext();

			last = it;
		}

		last->setNext(NULL);
	}
}

Tree::Tree(const Tree& t, Garden* g) {
	// TODO każda zmiana również wyżej!!!!
	id = t.id;
	height = t.height;
	fruitAmt = 0;
	weight = 0;
	garden = g;
	first = NULL;
	last = NULL;
	next = t.getNext();
	prev = t.getPrev();
	updateGlobalTreesAmt(1, true);

	branchAmt = t.branchAmt;
	if (branchAmt > 0) {
		branchAmt = 0;
		first = new Branch(*t.first, this);
		last = first;

		Branch* it = first;
		Branch* itB = t.first->getNext();
	
		while (itB != NULL) {
			it->setNext(new Branch(*itB, this));

			it = it->getNext();
			itB = itB->getNext();

			last = it;
		}

		last->setNext(NULL);
	}
}

Tree::~Tree() {
	Branch* it = first;
	Branch* tmp;
	while (it != NULL) {
		tmp = it;
		it = it->getNext();
		delete tmp;
	}
	updateGlobalTreesAmt(1, false);
}

void Tree::setNumber(cint n) {
	id = n;
}

void Tree::setWeight(cint n) {
	weight = n;
}

Tree* Tree::getNext(void) const {
	return next;
}

Tree* Tree::getPrev(void) const {
	return prev;
}

Branch* Tree::getFirst(void) const {
	return first;
}

void Tree::setFruitAmt(cint n) {
	fruitAmt = n;
}

void Tree::setNext(Tree* n) {
	next = n;
}

void Tree::setPrev(Tree* n) {
	prev = n;
}

void Tree::setBranchAmt(cint n) {
	branchAmt = n;
}

void Tree::updateGlobalTreesAmt(cint n, bool add) {
	Garden* garden = getGardenPointer();
	if (garden == NULL)
		return;
	if (add) garden->setTreesAmt(garden->getTreesTotal() + n);
	else	 garden->setTreesAmt(garden->getTreesTotal() - n);
}

cint Tree::getBranchesTotal(void) const {
	return branchAmt;
}

cint Tree::getFruitsTotal(void) const {
	return fruitAmt;
}

cint Tree::getWeightsTotal(void) const {
	return weight;
}

cint Tree::getNumber(void) const {
	return id;
}

cint Tree::getHeight(void) const {
	return height;
}

void Tree::growthTree(void) {
	height++;
	for (Branch* it = first; it != NULL; it = it->getNext()) {
		it->growthBranch();
	}

	if (height > 0 && height % 3 == 0) {
		if (branchAmt > 0) {
			last->setNext(new Branch(height, this));
			last = last->getNext();
		}
		else {
			Branch* b = new Branch(height, this);
			last = first = b;
		}
		last->setNext(NULL);
	}
}

void Tree::fadeTree(void) {
	if (height == 0)
		return;

	height--;

	if (last != NULL && last->getHeight() > height) {
		Branch* it = first;
		while (it != NULL) {
			if (it->getHeight() > height) {
				break;
			}
			last = it;
			it->fadeBranch();
			it = it->getNext();
		}
		if (it == last) {
			last = first = NULL;
		}

		Branch* tmp;
		while (it != NULL) {
			tmp = it;
			it = it->getNext();
			delete tmp;
		}
		if (last != NULL) {
			last->setNext(NULL);
		}
	}
	else {
		for (Branch* it = first; it != NULL; it = it->getNext()) {
			it->fadeBranch();
		}
	}
}

void Tree::harvestTree(cint n) {
	for (Branch* it = first; it != NULL; it = it->getNext()) {
		it->harvestBranch(n);
	}
}

void Tree::cutTree(cint h) {
	height = h;
	if (branchAmt == 0)
		return;

	if (last->getHeight() > height) {
		Branch* it = first;
		while (it != NULL) {
			if (it->getHeight() > height) {
				break;
			}
			last = it;
			it = it->getNext();
		}
		if (it == first) {
			first = last = NULL;
		}

		Branch* tmp;
		while (it != NULL) {
			tmp = it;
			it = it->getNext();
			delete tmp;
		}
		if (last != NULL) {
			last->setNext(NULL);
		}
	}
}

void Tree::cloneBranch(Branch* b) {
	if (b == NULL || branchAmt == 0) 
		return;
	
	Branch* it = first;
	Branch* true_prev = NULL;
	while (it != NULL) {
		if (it->getLength() == 0) {
			break;
		}
		true_prev = it;
		it = it->getNext();
	}
	if (it != NULL) {
		cint h = it->getHeight();
		Branch* true_next = it->getNext();
		delete it;
		it = new Branch(*b, this);
		if (true_prev != NULL) {
			true_prev->setNext(it);
		}
		it->setHeight(h);
		it->setTreePointer(this);
		it->setNext(true_next);
	}
}

Garden* Tree::getGardenPointer() {
	return garden;
}

Branch* Tree::getBranchPointer(cint n) {
	if (n == 0 || n % 3 != 0 || n > height)
		return NULL;

	for (Branch* it = first; it != NULL; it = it->getNext()) {
		if (it->getHeight() == n) {
			return it;
		}
	}
	
	return NULL;
}

// ================ END TREE ================


// ================ START GARDEN ================

Garden::Garden() {
	treesAmt = 0;
	branchesAmt = 0;
	fruitAmt = 0;
	weightAmt = 0;
	first = NULL;
	last = NULL;
	potentialGaps = 0;
}

Garden::~Garden() {
	Tree* it = first;
	Tree* tmp;
	while (it != NULL) {
		tmp = it;
		it = it->getNext();
		delete tmp;
	}
}

void Garden::setTreesAmt(cint n) {
	treesAmt = n;
}

void Garden::setBranchAmt(cint n) {
	branchesAmt = n;
}

void Garden::setWeight(cint n) {
	weightAmt = n;
}

void Garden::setFruitAmt(cint n) {
	fruitAmt = n;
}

cint Garden::getTreesTotal() const {
	return treesAmt;
}

cint Garden::getBranchesTotal() const {
	return branchesAmt;
}

cint Garden::getFruitsTotal() const {
	return fruitAmt;
}

cint Garden::getWeightsTotal() const {
	return weightAmt;
}

void Garden::plantTree(void) {
	if (treesAmt == 0) {
		first = last = new Tree(0, this);
		last->setNext(NULL);
	}
	else {
		if (potentialGaps == 0) {
			last->setNext(new Tree(last->getNumber() + 1, this));
			last->getNext()->setPrev(last);
			last = last->getNext();
			last->setNext(NULL);
		}
		else {
			if (first->getNumber() > 0) {
				Tree* tmp = new Tree(0, this);
				tmp->setPrev(NULL);
				tmp->setNext(first);
				first->setPrev(tmp);
				first = tmp;
				potentialGaps--;
			}
			else {
				Tree* it = first;
				while (it->getNext() != NULL) {
					if (it->getNumber() + 1 < it->getNext()->getNumber()) {
						break;
					}
					it = it->getNext();
				}

				Tree* tmp = it->getNext();
				it->setNext(new Tree(it->getNumber() + 1, this));

				if (tmp != NULL) {
					tmp->setPrev(it->getNext());
				}
				if (it->getNext() != NULL) {
					it->getNext()->setNext(tmp);
					it->getNext()->setPrev(it);
				}

				if (it == last) {
					last = it->getNext();
					potentialGaps = 0;
				}
				else if (potentialGaps > 0) {
					potentialGaps--;
				}
			}
		}
	}
}

void Garden::growthGarden(void) {
	for (Tree* it = first; it != NULL; it = it->getNext()) {
		it->growthTree();
	}
}

void Garden::extractTree(cint n) {
	if (treesAmt == 0)
		return;

	if (n == last->getNumber()) {
		Tree* tmp = last;
		if (first == last) {
			first = last = NULL;
		}
		else {
			last = last->getPrev();
			last->setNext(NULL);
		}

		delete tmp;
	}
	else if (n < last->getNumber()) {
		Tree* it = first;
		Tree* prev = NULL;

		while (it->getNext() != NULL) {
			if (it->getNumber() == n) {
				break;
			}
			prev = it;
			it = it->getNext();
		}

		if (it->getNumber() == n) {
			if (it == first && it == last) {
				first = last = NULL;
				potentialGaps = 0;
			}
			else if (it == first) {
				first = first->getNext();
				first->setPrev(NULL);
				potentialGaps++;
			}
			else if (it == last) {
				last = prev;
				last->setNext(NULL);
			}
			else {
				prev->setNext(it->getNext());
				it->getNext()->setPrev(prev);
				potentialGaps++;
			}

			delete it;
		}
	}
}

void Garden::fadeGarden(void) {
	for (Tree* it = first; it != NULL; it = it->getNext()) {
		it->fadeTree();
	}
}

void Garden::harvestGarden(cint n) {
	for (Tree* it = first; it != NULL; it = it->getNext()) {
		it->harvestTree(n);
	}
}

Tree* Garden::getTreePointer(cint n) {
	if (treesAmt == 0) {
		return NULL;
	}

	if (n > last->getNumber()) {
		return NULL;
	}

	if (n == last->getNumber()) {
		return last;
	}
	for (Tree* it = first; it != NULL; it = it->getNext()) {
		if (it->getNumber() == n) {
			return it;
		}
	}
	return NULL;
}

void Garden::cloneTree(cint x) {
	if (treesAmt == 0)
		return;

	if (x > last->getNumber())
		return;

	Tree* it = first;
	Tree* it2 = last;
	// znaleziony element do skopiowania
	Tree* X = NULL;
	// miejsce za którym wstawiamy
	// chyba że beforeData == true, wtedy wstawiamy przed
	Tree* A = NULL;
	
	bool beforeData = false;
	if (potentialGaps == 0)
		A = last;
	else if (first->getNumber() > 0) {
		beforeData = true;
		A = first;
	}

	if (last->getNumber() == x)
		X = last;

	while (it != NULL && it2 != NULL && (X == NULL || A == NULL)) {
		if (X == NULL && it->getNumber() == x) {
			X = it;
		}
		else if (X == NULL && it2->getNumber() == x) {
			X = it2;
		}
		else if (X == NULL && it->getNumber() >= it2->getNumber()) {
			break;
		}

		if (A == NULL && it == last) {
			A = it;
		}
		else if (A == NULL) {
			if (it->getNumber() + 1 < it->getNext()->getNumber()) {
				A = it;
			}
		}

		it = it->getNext();
		it2 = it2->getPrev();
	}

	if (X != NULL) {
		if (beforeData) {
			A = new Tree(*X, this);
			A->setNext(first);
			A->setPrev(NULL);
			first->setPrev(A);
			A->setNumber(0);
			first = A;
			potentialGaps--;
		}
		else {
			Tree* tmp = A->getNext();
			A->setNext(new Tree(*X, this));
			A->getNext()->setPrev(A);
			A->getNext()->setNumber(A->getNumber() + 1);
			if (tmp != NULL) {
				tmp->setPrev(A->getNext());
			}
			else {
				last = A->getNext();
			}
			A->getNext()->setNext(tmp);

			if (A == last) {
				potentialGaps = 0;
			}
			else if (potentialGaps > 0) {
				potentialGaps--;
			}
		}
	}
}

// ================ END GARDEN ================
