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
            if(val == root->data) return tRoot;
            if(val < root->data) root = root->left;
            else if(val > root->data) root = root->right;
        }
        node->parent = p;
        if(val < p->data) p->left = node;
        else if(val > p->data) p->right = node;
        return tRoot;
    }
    Node* deleteNode(Node* root, int val){
        Node* tRoot = root;
        
        //write the code to delete an element 
        
        return tRoot;
    }
}btree;

class Traversals{
  public:
    void inorder(Node* root){  // inorder traversal -> Left, Root, Right;
        if(root!=NULL){
            inorder(root->left);
            cout<<root->data<<' ';
            inorder(root->right);
        }
    }
    
    void preorder(Node* root){  // preorder traversal -> Root, Left, Right;
        if(root!=NULL){
            cout<<root->data<<' ';
            preorder(root->left);
            preorder(root->right);
        }
    }
    
    void postorder(Node* root){  // postorder traversal -> Left, Right, Root;
        if(root!=NULL){
            postorder(root->left);
            postorder(root->right);
            cout<<root->data<<' ';
        }
    }
}traversals;

// delete the tree
void deleteTree(Node* root){
    if(root==NULL) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
    return;
}

int main() {
	int test;
	cin>>test;
	while(test--){  // run the code snipet for the number of test cases
	    Node* root = NULL;
	    int n;
	    cin>>n;
    	while(n--){
    	    int val;
    	    cin>> val;
    	    root = btree.insert(root, val); 
    	}
    	char c;
    	cin>>c;
    	if(c=='D'){
    	    deleteTree(root);
    	    continue;
    	}
    	cout<<"Inorder : ";
    	traversals.inorder(root);
    	cout<<endl<<"Preorder : ";
    	traversals.preorder(root);
    	cout<<endl<< "Postorder : ";
    	traversals.postorder(root);
    	cout<<endl;
    	delete root;
	}
	return 0;
}
