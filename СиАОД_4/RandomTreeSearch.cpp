#include "RandomTreeSearch.h"
int RandomTreeSearch::getSize(Knot* k) {
	if (k == nullptr)
		return 0;
	return k->size;
}
void RandomTreeSearch::fixSize(Knot* k) {
	k->size = getSize(k->left) + getSize(k->right) + 1;
}
Knot* RandomTreeSearch::rotateLeft(Knot* k) {
	Knot* help = k->right;
	if (help == nullptr)
		return k;
	k->right = help->left;
	help->left = k;
	help->size = k->size;
	fixSize(k);
	rotateCount++;
	return help;
}
Knot* RandomTreeSearch::rotateRight(Knot* k) {
	Knot* help = k->left;
	if (help == nullptr)
		return k;
	k->left = help->right;
	help->right = k;
	help->size = k->size;
	fixSize(k);
	rotateCount++;
	return help;
}
Knot* RandomTreeSearch::insertRoot(Knot* k, int key, long numInFile) {
	if (k == nullptr) {
		Knot* help = new Knot;
		help->left = nullptr;
		help->right = nullptr;
		help->num = key;
		help->numInFile = numInFile;
		return help;
	}
	if (key < k->num)
	{
		k->left = insertRoot(k->left, key,numInFile);
		return rotateRight(k);
	}
	else
	{
		k->right = insertRoot(k->right, key, numInFile);
		return rotateLeft(k);
	}
}
Knot* RandomTreeSearch::insert(Knot* k, int key, long numInFile) {
	if (k == nullptr) { 
		Knot* help = new Knot;
		help->left = nullptr;
		help->right = nullptr;
		help->num = key;
		help->numInFile = numInFile;
		return help;
	}
	if (rand() % (k->size + 1) == 0) {
		if (root == k)
		{
			root = insertRoot(k, key, numInFile);
			fixSize(root);
			return root;
		}
		return insertRoot(k, key, numInFile);
	}
	if (k->num > key)
		k->left = insert(k->left, key,numInFile);
	else
		k->right = insert(k->right, key, numInFile);

	return k;
}
void RandomTreeSearch::createTree() {
	srand(time(0));
	ifstream bf("polisaBIN.dat", ios::in | ios::binary);
	Polis* p2 = new Polis;
	int numInFile = 0;
	bf.read((char*)p2, sizeof(Polis));
	int num = atoi((p2->getNum()).c_str());
	root = insert(root,num, p2->getNumInFile());
	bf.read((char*)p2, sizeof(Polis));
	while (numInFile != p2->getNumInFile())
	{
		numInFile = p2->getNumInFile();
		num = atoi((p2->getNum()).c_str());
		insert(root,num, p2->getNumInFile());
		bf.read((char*)p2, sizeof(Polis));
	}
	cout << "Количество поворотов: " << rotateCount;
	bf.close();
}
Knot* RandomTreeSearch::getRoot() {
	return root;
}
void RandomTreeSearch::printTree(Knot* key, int level) {
	if (key != nullptr)
	{
		printTree(((*key).right), level + 1);
		for (int i = 1; i <= level; i++)
			cout << "   ";
		cout << (*key).num << endl;
		printTree(((*key).left), level + 1);
	}
}
Knot* RandomTreeSearch::join(Knot* small, Knot* big) {
	srand(time(0));
	if (!small) return big;
	if (!big) return small;
	if (rand() % (small->size + big->size) < small->size)
	{
		small->right = join(small->right, big);
		fixSize(small);
		return small;
	}
	else
	{
		big->left = join(small, big->left);
		fixSize(big);
		return big;
	}
}
Knot* RandomTreeSearch::knotDelete(Knot* k, int key) {
	if (!k) 
		return k;
	if (k->num == key)
	{
		Knot* q = join(k->left, k->right);
		delete k;
		return q;
	}
	else if (key < k->num)
		k->left = knotDelete(k->left, key);
	else
		k->right = knotDelete(k->right, key);
	return k;
}
Knot* RandomTreeSearch::find(Knot* root, int key) {
	if (root != nullptr) {
		srv++;
		if ((*root).num == key)
			return root;
		else {
			srv++;
			if (key > (*root).num)
				return find((*root).right, key);
			else
				return find((*root).left, key);
		}
	}
	return nullptr;
}
void RandomTreeSearch::setRoot(Knot* root) {
	this->root = root;
}