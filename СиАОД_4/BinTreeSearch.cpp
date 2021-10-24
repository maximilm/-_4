#include "BinTreeSearch.h"
void BinTreeSearch::insert(Knot** k, int key, long numInFile) {
	if ((*k) == nullptr)
	{
		(*k) = new Knot;
		(*k)->left = nullptr;
		(*k)->right = nullptr;
		(*k)->num = key;
		(*k)->numInFile = numInFile;
		return;
	}
	if (key > (*k)->num)
		insert(&((*k)->right), key, numInFile);
	else
		insert(&((*k)->left), key, numInFile);
}
void  BinTreeSearch::createTree(Knot** root) {
	ifstream bf("polisaBIN.dat", ios::in | ios::binary);
	Polis *p2 = new Polis;
	int numInFile = -1;
	bf.read((char*)p2, sizeof(Polis));
	while (numInFile != p2->getNumInFile())
	{
		numInFile = p2->getNumInFile();
		insert(root, p2->getNum(), p2->getNumInFile());
		bf.read((char*)p2, sizeof(Polis));
	}
	bf.close();
}
Knot** BinTreeSearch::getRoot() {
	return &root;
}
void  BinTreeSearch::printTree(Knot** key, int level) {
	if (*key != nullptr)
	{
		printTree(&((**key).right), level + 1);
		for (int i = 1; i <= level; i++)
			cout << "   ";
		cout << (**key).num << endl;
		printTree(&((**key).left), level + 1);
	}
}
void BinTreeSearch::knotDelete(Knot** k, int key) {
	Knot* del = find(*k, key);
	Knot* parent = searchParent(*getRoot(), del);
	if (parent == nullptr) {
		updateRoot();
		deletePolisInBinTxt((*del).numInFile);
		return;
	}
	if ((*del).right == nullptr && (*del).left == nullptr)
	{
		if ((*del).num < (*parent).num)
			(*parent).left = nullptr;
		else
			(*parent).right = nullptr;
	}
	if ((*del).right == nullptr)
	{
		if ((*del).num < (*parent).num)
			(*parent).left = (*del).left;
		else
			(*parent).right = (*del).left;
	}
	if ((*del).left == nullptr)
	{
		if ((*del).num < (*parent).num)
			(*parent).left = (*del).right;
		else
			(*parent).right = (*del).right;
	}
	if ((*del).right != nullptr && (*del).left != nullptr) {
		Knot* help;
		help = del->right;
		while (help->left != nullptr)
			help = help->left;
		Knot* parentHelp = searchParent(*getRoot(), help);
		if (parentHelp == del)
		{
			help->left = del->left;
			if (parent->left == del)
				parent->left = help;
			else
				parent->right = help;
		}
		else {
			parentHelp->left = nullptr;
			if (help->right != nullptr)
				parentHelp->left = help->right;
			help->right = del->right;
			help->left = del->left;
			if (parent->left == del)
				parent->left = help;
			else
				parent->right = help;
		}
	}
	deletePolisInBinTxt((*del).numInFile);
	return;
}
Knot* BinTreeSearch::find(Knot* root, int key)
{
	if (root != nullptr) {
		if ((*root).num == key)
			return root;
		else if (key > (*root).num)
			return find((*root).right, key);
		else
			return find((*root).left, key);
	}
	return nullptr;
}
Knot* BinTreeSearch::searchParent(Knot* root, Knot* key) {
	if (root == nullptr)
		return nullptr;
		if (root->left == key)
			return root;
		if (root->right == key)
			return root;
        if (key->num > (*root).num)
			return searchParent((*root).right, key);
		else
			return searchParent((*root).left, key);
}
void BinTreeSearch::updateRoot() {
	Knot* del = root;
	if ((*del).right == nullptr && (*del).left == nullptr)
	{
		root = nullptr;
		return;
	}
	if ((*del).right == nullptr)
	{
		root = root->left;
		return;
	}
	Knot* help;
	help = del->right;
	while (help->left != nullptr)
		help = help->left;
	Knot* parentHelp = searchParent(*getRoot(), help);
	if (parentHelp == del)
	{
		help->left = del->left;
		root = help;
	}
	else {
		if (help->right != nullptr)
			parentHelp->left = help->right;
		else
			parentHelp->left = nullptr;
		help->right = del->right;
		help->left = del->left;
		root = help;
	}
	return;
}