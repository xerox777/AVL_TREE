#include <string>
#include <vector>
using namespace std;

struct Node
{
    string data = "";
    int size = 1;
    vector<int> linenumber;
    struct Node *left;
    struct Node *right;
    
    int status = 0; // 0 for unused, 1 for inserted/active, -1 for deleted
}*root;
/*

 * Class Declaration

 */

class avlTree
{
    private:
     void privDFS(Node* inme, ostream & outs);
	
    public:
        int height(Node *temp);
        int diff(Node *temp);
        Node *RR_rotation(Node *parent);
        Node *LL_rotation(Node *parent);
        Node *LR_rotation(Node *parent);
        Node *RL_rotation(Node *parent);
        Node* balance(Node *temp);
	bool search(Node* flux, string find);
        Node* insert(Node *root, string value, int line);
        void display(Node *ptr, int level);
        void inorder(Node *tree);
        void preorder(Node *tree);
        void postorder(Node *tree);
	Node* usersearch(Node* flux , string find);
	void DFS(int flag, ofstream & output);
	int size(Node* me);
	Node* deleteNode(Node* &temp, string key);
        avlTree()
        {
            root = NULL;
        }
};

