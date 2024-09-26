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
            if(val == root->data) return tRoot; // value already present
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
        cout<< "deleted node " << val << endl;
        
        return tRoot;
    }
}btree;

class Traversals{
  public:
    bool search(Node* root, int key){
        while(root!=NULL){
            if(key==root->data) return 1; // key found
            else if(key<root->data) root = root->left; // key present in left subtree
            else root = root->right; // key present in right subtree
        }
        return 0; // key not found
    }
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
	    while(1){
	        char query;
    	    cin>>query;
    	    if(query=='D'){  // switch to the next test
    	        // clear the memory if any memory is occupied by the tree
    	        if(root!= NULL) deleteTree(root);
    	        break;
    	    }
    	    switch(query){
    	        case 'B':
    	            int n;
    	            cin>>n;
    	            while(n--){
    	                int val;
    	                cin>>val;
    	                if(val==0); // do nothing if the value is zero
    	                if(val>0) root = btree.insert(root, val); // insert on +ve value
    	                if(val<0) btree.deleteNode(root, val*-1); // delete on -ve value
    	            }
    	            break;
    	        case 'A':
    	            break;
    	        case 'I':
    	            break;
    	        case 'R':
    	            break;
    	        case 'F':
    	            int key;
    	            cin>>key;
    	            if(key<=0){
    	                cout<<"No\n";
    	                break;
    	            }
    	            if(traversals.search(root, key)){
    	                cout<<"Yes\n";
    	            }else{
    	                cout<<"No\n";
    	            }
    	            break;
    	        case 'L':
    	            break;
    	        case 'N':
    	            break;
    	        case 'Q':
    	            traversals.inorder(root);
    	            cout<<endl;
    	            break;
    	        case 'W':
    	            traversals.preorder(root);
    	            cout<<endl;
    	            break;
    	        case 'E':
    	            traversals.postorder(root);
    	            cout<<endl;
    	            break;
    	        case 'H':
    	            break;
    	        case 'M':
    	            break;
    	        case 'C':
    	            break;
    	        case 'Z':
    	            break;
    	        case 'Y':
    	            break;
    	        case 'K':
    	            deleteTree(root);
    	            root = NULL; // to avoid dangling pointer
    	            break;
    	    }
	    }
	}
	return 0;
}
