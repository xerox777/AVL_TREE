#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <stdlib.h>
#include "avl.h"
#include <fstream>
#include <sstream>
#include <time.h>
#include <vector>
#include <string>
using namespace std;

ifstream dictionary;

void userdisplay(avlTree* input);
void sortdict (vector<string>& input);
avlTree* ReadIn (int index);

Node* minof(Node* find);
int main(int argc, char* argv[]) {
	if(argc < 2) {
		cout << "Usage : ./a.out 'filename'\n";
		exit(0);
	}
	avlTree* me = new avlTree();	
        string file = argv[1];
	dictionary.open(argv[1]);
	string line;
	string oneword;
	me = ReadIn(0);
	userdisplay(me);
	return 0;
}

Node* minof(Node* find) {
	if(find == NULL)
		return NULL;
	else if (find->left == NULL)
		return find;
	else
		return minof(find->left);
}

Node* avlTree::deleteNode(Node* &temp, string key) {
	if(temp == NULL)
		return temp;
	if(key < temp->data)
		//temp->left =
		return deleteNode(temp->left, key);
	else if (key > temp->data)
		//temp->right = 
		return deleteNode(temp->right, key);
	else { //key == temp->data
		if (temp->left != NULL && temp->right != NULL) { //2 child
			Node* min = minof(temp->right);
			temp->data = min->data;
			temp->linenumber = min->linenumber;
			deleteNode(temp->right, temp->data);
		} else if (temp->left == NULL && temp->right == NULL){
			//delete temp;
			temp = NULL;
		} else {		//one child
			Node* remove = temp;
			if (temp->left == NULL) {
				//vector<int> tempn = temp->linenumber;
				temp->data = remove->right->data;
				temp->linenumber = remove->right->linenumber;
				//temp->linenumber = tempn;
				remove->right = NULL;
				//delete remove->right;
				//return temp;
			} else {
				//vector<int> tempn = temp->linenumber;
				temp->data = remove->left->data;
				temp->linenumber = remove->left->linenumber;
				remove->left = NULL;
				//delete remove->left;
				//return temp;
			}
			//delete(remove);
			//remove = NULL;
				
		}
	}
	//temp = balance(temp);
	return temp; 
}

avlTree* ReadIn (int index) { 	// ROOT NODE IS HALF WAY MARK OF VECTOR
	double finish_time;
	double start_time = clock();
	avlTree* out = new avlTree();
	string line;
	string oneword;
	int wordnum = 0;
	while (getline(dictionary, line)) {
		stringstream stream(line);
		index++;
		while (stream >> oneword) {
		 string nopunct;
		 int i = 0;
		 while(i < oneword.size()){
		   if(oneword.at(i) == '.' || oneword.at(i) == ',')
		   	break;
		   nopunct += oneword[i];
		   i++;
		 }
		 root = out->insert(root,nopunct, index);
		 //root->size++;
		 wordnum++;
		}	
	}
	finish_time = clock();
	double time = (finish_time - start_time) / CLOCKS_PER_SEC;
	cout << "Total number of words: " << wordnum << "\t\t\n";
	int val = out->size(root);
	cout << "Total number of distinct words: " << val  << "\n";
	cout << "Time taken to build index using BST is: " << time << "\n";
	cout << "ROOT " << root->data << "\n";
	return out;
}

void userdisplay(avlTree* input) {
		ofstream output;
		cout << "Options: (1) display index, (2) search, (3) save index, (4) quit\n";
		int option = 0;
		while(cin >> option && option != 4) {
		if(option == 1) {
			cout << "Binary Search Tree Index:\n-------------------------\n";
			input->DFS(1, output);
		}
		if (option == 2) {
			cout << "Search word? ";
			string word;
			cin >> word;
			Node* out = input->usersearch(root, word);
			vector<int> temp = out->linenumber;
			int num = 0;
			cout << "Line number<BST>: ";
			while(num < temp.size()){
				if(num<1)
					cout << temp[num]; 
				else if (num <= temp.size() && num > 0)
					cout << ", " << temp[num];
				num++;
			}
			cout << "\n";
		}
		if (option == 3) {
			cout << "output will be saved as output.txt\n";
			output.open("output.txt");
			output << "Binary Search Tree Index:\n-------------------------\n";
			input->DFS(0, output);
			output.close();
		}
		if (option == 5) {
			cout << "Enter value to delete from AVL tree: \n";
			string key;
			cin >> key;
			//root = 	
			input->deleteNode(root, key);
			root = input->balance(root);

		}
		cout << "Options: (1) display index, (2) search, (3) save index, (4) quit\n";
	}
}

int avlTree::height(Node *temp) {
    int h = 0;
    if (temp != NULL)
    {
        int l_height = height (temp->left);
        int r_height = height (temp->right);
        int max_height = max (l_height, r_height);
        h = max_height + 1;
    }
    return h;
}

int avlTree::diff(Node* temp)

{
	
    int l_height = height (temp->left);
    int r_height = height (temp->right);
    int b_factor= l_height - r_height;
    return b_factor;
}
Node *avlTree::insert(Node* root, string value, int line)
{
    if (root == NULL)
    {
        root = new Node();
        root->data = value;
        root->left = NULL;
        root->right = NULL;
	//root->size++;
	root->linenumber.push_back(line);
        return root;
    }
    else if (value < root->data)
    {
	//root->size++;
        root->left = insert(root->left, value, line);
        root = balance (root);
    }
    else if (value > root->data)
    {
//	root->size++;
        root->right = insert(root->right, value, line);
        root = balance (root);
    }	
    else if (value == root->data){
	root->linenumber.push_back(line);
    }
    root->size = root->size + 1;
    return root;
}
Node* avlTree::usersearch(Node* flux, string find) {
	if(!search(flux, find)) {
		return NULL;
	}
	if(flux->data==find)
		return flux;
	if(flux->data<find)
		return usersearch(flux->right, find);
	if(flux->data>find)
		return usersearch(flux->left, find);
	return NULL;
}

bool avlTree::search(Node* target, string key) {
	if(target == NULL)
		return false;
	if (target->data == key) 
		return true;
	if(key>target->data) 
		return search(target->right, key);
	if(key<target->data) 
		return search(target->left, key);
	return false;
}
Node *avlTree::balance(Node *temp)
{
    int bal_factor = diff (temp);
    if (bal_factor > 1)
    {
        if (diff (temp->left) > 0)
            temp = LL_rotation (temp);
        else
            temp = LR_rotation (temp);
    }
    else if (bal_factor < -1)
    {
        if (diff (temp->right) > 0)
            temp = RL_rotation (temp);
        else
            temp = RR_rotation (temp);
    }
    return temp;
}

void avlTree::inorder(Node *tree)
{
    if (tree == NULL)
        return;
    inorder (tree->left);
    cout<<tree->data<<"  ";
    inorder (tree->right);
}

Node *avlTree::RR_rotation(Node *parent)
{
    Node *temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}

/*

 * Left- Left Rotation

 */

Node *avlTree::LL_rotation(Node *parent)
{
    Node *temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}

 

/*

 * Left - Right Rotation

 */

Node *avlTree::LR_rotation(Node *parent)
{
    Node *temp;
    temp = parent->left;
    parent->left = RR_rotation (temp);
    return LL_rotation (parent);
}

 

/*

 * Right- Left Rotation

 */
Node *avlTree::RL_rotation(Node *parent)
{
    Node *temp;
    temp = parent->right;
    parent->right = LL_rotation (temp);
    return RR_rotation (parent);
}

void avlTree::privDFS(Node* inme, ostream & outs) {
	vector<int> line = inme->linenumber;
	if(inme->left!=NULL) privDFS(inme->left, outs);
		int num = 0;
		if(num<1)
			outs <<" "<< inme->data <<"\t";
		while(num < line.size()) {
			if(num<1)
				outs << line[num];
			if(num>0)
				outs << ", " << line[num];
			num++;
		}
		outs << "\n";
	if(inme->right!=NULL) privDFS(inme->right, outs);
}

void avlTree::DFS(int flag, ofstream & output) {
	if (root != NULL && flag == 1) 
		privDFS(root, cout);
	if (root != NULL && flag == 0) 
		privDFS(root, output);

	else return;
}
int avlTree::size(Node* me) {
	if (me == NULL) {
		return 0;
	} else {
		return 1 + size(me->left) + size(me->right);
	}
}
