#include <bits/stdc++.h>
using namespace std;

struct Node{
    int data;
    Node* parent;
    Node* left;
    Node* right;
    
    Node(int val, Node* p) : data(val), parent(p){
        left = right = NULL;
    }
};

class BST{
  public:
    Node* insert(Node* root, int val){
        Node* tRoot = root;
        Node* node = new Node(val, NULL);  // create the node to be inserted
        if(root == NULL) return node;  // the tree is empty
        Node* p = root;  // stores the parent for the new node
        while(root!=NULL){
            p = root; // update parent for the new node
            if(val == root->data) return root;
            if(val < root->data) root = root->left;
            else if(val > root->data) root = root->right;
        }
        node->parent = p;
        if(val < p->data) p->left = node;
        else if(val > p->data) p->right = node;
        return tRoot;
    }
    
    void inorder(Node* root){  // inorder traversal -> Left, Root, Right;
        if(root!=NULL){
            inorder(root->left);
            cout<<root->data<<' ';
            inorder(root->right);
        }
    }
};

int main() {
	Node* root = NULL;
	BST btree;
	int n =6;
	while(n--){
	    int val;
	    cin>> val;
	    root = btree.insert(root, val); 
	}
	btree.inorder(root);
	delete root;
	return 0;
}
