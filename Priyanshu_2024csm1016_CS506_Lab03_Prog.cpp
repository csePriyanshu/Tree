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
    private:
        Node* getMin(Node* node){
            while(node && node->left){
                node->left;
            }
            return node;
        }
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
            
            //search for the target node in the tree
            while(root!=NULL){
                if(val==root->data) break;
                else if(val<root->data) root = root->left;
                else root = root->right;
            }
            
            // target is not present in the tree
            if(root == NULL) return tRoot;
            
            Node* parent = root->parent;
            
            // if the target node has 0 child
            if(root->left==NULL && root->right==NULL){
                if(parent==NULL){ // the target node is the root node
                    tRoot = NULL;
                } 
                else{
                    if(root->data<parent->data){
                        parent->left = NULL;
                    }
                    else if(root->data>parent->data){
                        parent->right = NULL;
                    }
                }
                delete root;
                return tRoot;
            }
            
            // if the target node has only left child
            if(root->right==NULL){
                if(parent==NULL){
                    tRoot = root->left;
                }
                else{
                    if(root->data<parent->data){
                        parent->left = root->left;
                    }
                    else if(root->data>parent->data){
                        parent->right = root->left;
                    }
                }
                delete root;
                return tRoot;
            }
            
            // if the target node has only right child
            if(root->left==NULL){
                if(parent==NULL){
                    tRoot = root->right;
                }
                else{
                    if(root->data<parent->data){
                        parent->left = root->right;
                    }
                    else if(root->data>parent->data){
                        parent->right = root->right;
                    }
                }
                delete root;
                return tRoot;
            }
            
            // if the target node has both children
            if(root->left!=NULL && root->right!=NULL){
                Node* successor = getMin(root->right);
                
                root->data = successor->data;
                if(successor->data>successor->parent->data){
                    successor->parent->right = NULL;
                }
                else if(successor->data<successor->parent->data){
                    successor->parent->left = NULL;
                }
                if(successor->right){
                    successor->right->parent = successor->parent;
                }
                delete successor;
                return tRoot;
            }
            
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

class TreeMetrics{
    public:
        int getHeight(Node* root){
            if(root==NULL){
                return -1;
            }
            
            int lHeight = getHeight(root->left);
            int rHeight = getHeight(root->right);
            
            return max(lHeight, rHeight) + 1;
        }
        int getLeafNodes(Node* root){
            if(root==NULL){
                return 0;
            }
            if(root->left==NULL && root->right==NULL){
                return 1;
            }
            
            return getLeafNodes(root->left) + getLeafNodes(root->right);
        }
        int getTotalNodes(Node* root){
            if(root==NULL) return 0;
            
            int l = getTotalNodes(root->left);
            int r = getTotalNodes(root->right);
            
            return 1+l+r;
        }
}metrics;

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
	    bool flag; // to switch between AVL(1) and BST(0) trees
	    while(1){
	        char query;
    	    cin>>query;
    	    if(query=='D'){  // switch to the next test
    	        // clear the memory if any memory is occupied by the tree
    	        if(root!= NULL){
    	            deleteTree(root);
    	            root = NULL; // to avoid dangling pointer
    	        }
    	        break;
    	    }
    	    int val;
    	    switch(query){
    	        case 'B':
    	            flag = 0;
    	            int n;
    	            cin>>n;
    	            while(n--){
    	                int val;
    	                cin>>val;
    	                if(val==0); // do nothing if the value is zero
    	                if(val>0) root = btree.insert(root, val); // insert on +ve value
    	                if(val<0) root = btree.deleteNode(root, val*-1); // delete on -ve value
    	            }
    	            break;
    	        case 'A':
    	            flag = 1;
    	            break;
    	        case 'I':
    	            cin>>val;
    	            if(val<=0) break;
    	            // the tree is empty, add the element as the first node of a BST
    	            if(root==NULL){
    	                root = btree.insert(root, val);
    	                break;
    	            }
    	            //tree is not empty
    	            if(flag){
    	                //insert in AVL
    	            }
    	            else{
    	                //insert in BST
    	                root = btree.insert(root, val);
    	            }
    	            break;
    	        case 'R':
    	            cin>>val;
    	            if(val<=0) break;
    	            if(flag){ // working on AVL tree
    	                // delete code here...
    	            }
    	            else{
    	                root = btree.deleteNode(root, val);
    	            }
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
    	            cout<< metrics.getLeafNodes(root) << endl;
    	            break;
    	        case 'N':
    	            cout << metrics.getTotalNodes(root) << endl;
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
    	            cout<< metrics.getHeight(root) << endl;
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
