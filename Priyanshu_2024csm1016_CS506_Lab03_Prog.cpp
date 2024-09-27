#include <bits/stdc++.h>
using namespace std;

/*
    I have the same struct to create node for BST and AVL.
    In BST, I have not updated the height.
    In AVL, I have not updated the parent.
*/

struct Node{
    int data, height;
    Node* parent;
    Node* left;
    Node* right;
    
    Node(int val) : data(val){
        parent = left = right = NULL;
        height = 1;
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
        Node* insert(Node* root, int val){  //iterative insertion
            Node* tRoot = root;
            Node* node = new Node(val);  // create the node to be inserted
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
        Node* deleteNode(Node* root, int val){  // iterative deletion
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

class AVL{
    private:
        int height(Node* node){
            if(node==NULL) return 0;
            return node->height;
        }
        int getBalance(Node* node){
            if(node==NULL) return 0;
            return height(node->left) - height(node->right);
        }
        Node* getMin(Node* node){
            while(node && node->left){
                node->left;
            }
            return node;
        }
        Node* leftRotation(Node* node){
            // store the nodes which will be updated
            Node* temp1 = node->right;
            Node* temp2 = temp1->left;
            
            // apply rotation
            temp1->left = node;
            node->right = temp2;
            
            // update height of the nodes accordingly
            node->height = 1 + max(height(node->left), height(node->right));
            temp1->height = 1 + max(height(temp1->left), height(temp1->right));
            
            // retun updated root
            return temp1;
        }
        Node* rightRotation(Node* node){
            // store the nodes which will be updated
            Node* temp1 = node->left;
            Node* temp2 = temp1->right;
            
            // apply rotation
            temp1->right = node;
            node->left = temp2;
            
            // update the height of the nodes accordingly
            node->height = 1 + max(height(node->left), height(node->right));
            temp1->height = 1 + max(height(temp1->left), height(temp1->right));
            
            // return the updated root
            return temp1;
        }
        
    public:
        Node* insert(Node* root, int val){
            // if the tree is empty
            if(root==NULL) return new Node(val);
            
            // if the tree contains node, insert a new node like we inserted in BST
            if(val<root->data){
                root->left = insert(root->left, val);
            }
            else if(val>root->data){
                root->right = insert(root->right, val);
            }
            else{ // equal values not allowed
                return root;
            }
            
            // update height of the parent node
            root->height = 1 + max(height(root->left), height(root->right));
            
            // get the balance factor of the parent node
            int imbalance = getBalance(root);
            
            // let's consider cases of height imbalance - LL, LR, RL, RR
            
            // Left Left imbalance i.e. right rotation
            if(imbalance>1 && val<root->left->data){
                return rightRotation(root);
            }
            
            // Left Right imbalance i.e. left roation + right rotation
            if(imbalance>1 && val>root->left->data){
                root->left = leftRotation(root->left);
                return rightRotation(root);
            }
            
            // Right Right imbalance i.e left rotation
            if(imbalance<-1 && val>root->right->data){
                return leftRotation(root);
            }
            
            // Right Left imbalance i.e. right rotation + left rotation
            if(imbalance<-1 && val<root->right->data){
                root->right = rightRotation(root->right);
                return leftRotation(root);
            }
            
            return root;
        }
        Node* deleteNode(Node* root, int key){
            if(root==NULL) return root;
            
            if(key<root->data) root->left = deleteNode(root->left, key);
            else if(key>root->data) root->right = deleteNode(root->right, key);
            else{ // perform the delete operation
                // if node has 0 or 1 child
                if(root->left==NULL || root->right==NULL){
                    Node* temp = root->left ? root->left : root->right;
                    if(temp==NULL){ // no child
                        temp == root;
                        root = NULL;
                    }else{ // 1 child
                        *root = *temp;
                    }
                    delete temp; // free the memory allocated to the deleted node
                }else{ // both children present
                    Node* temp = getMin(root->right);
                    root->data = temp->data;
                    root->right = deleteNode(root->right, temp->data);
                }
            }
            
            if(root==NULL) return root;
            
            // update height of the parent node
            root->height = 1 + max(height(root->left), height(root->right));
            
            int balance = getBalance(root);
            
            // Left Left Case
            if (balance > 1 && 
                getBalance(root->left) >= 0)
                return rightRotation(root);
        
            // Left Right Case
            if (balance > 1 && 
                getBalance(root->left) < 0) {
                root->left = leftRotation(root->left);
                return rightRotation(root);
            }
        
            // Right Right Case
            if (balance < -1 && 
                getBalance(root->right) <= 0)
                return leftRotation(root);
        
            // Right Left Case
            if (balance < -1 && 
                getBalance(root->right) > 0) {
                root->right = rightRotation(root->right);
                return leftRotation(root);
            }
        
            return root;
        }
}avl;

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
    
    // Boundary traversing - clockwise
    void leaves(Node* root){
        if(root==NULL) return;
        leaves(root->right);
        if(root->left==NULL && root->right==NULL) cout<< root->data<<' ';
        leaves(root->left);
    }
    void boundaryRight(Node* root){
        if(root==NULL) return;
        if(root->right){
            cout<<root->data<<' ';
            boundaryRight(root->right);
        }else if(root->left){
            cout<<root->data<<' ';
            boundaryRight(root->left);
        }
    }
    void boundaryLeft(Node* root){
        if(root==NULL) return;
        if(root->left){
            boundaryLeft(root->left);
            cout<<root->data<<' ';
        }else if(root->right){
            boundaryLeft(root->right);
            cout<<root->right<<' ';
        }
    }
    void boundary(Node* root){
        if(root==NULL) return;
        
        cout<<root->data<<' ';  // print root
        
        boundaryRight(root->right); //print right boundary
        
        leaves(root->right); // print leaves of right subtree
        leaves(root->left); // print leaves of left subtree
        
        boundaryLeft(root->left); // print left boundary counter-clockwise
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

class Misc{
    private:
        int search(vector<int> in, int key, int n){
            for(int i=0; i<n; i++){
                if(in[i] == key) return i;
            }
            return -1;
        }
    public:
        void postorder(vector<int> in, vector<int> pre, int n){
            int root = search(in, pre[0], n);
            if (root < 0 || root >= n) return;
            vector<int> sub_pre(pre.begin() + 1, pre.end());
            vector<int> sub_in(in.begin()+root+1, in.end());
            vector<int> sub_pre1(pre.begin()+root+1, pre.end());
            if(root!=0) postorder(in, sub_pre, root);
            if(root!=n-1) postorder(sub_in, sub_pre1, n-root-1);
            cout<<pre[0]<<' ';
        }
        void preorder(vector<int> in, vector<int> post, int n){
            int root = search(in, post[n-1], n);
            if (root < 0 || root >= n) return;
            vector<int> sub_post(post.begin(), post.begin()+root);
            vector<int> sub_in(in.begin()+root+1, in.end());
            vector<int> sub_post1(post.begin()+root, post.end()-1);
            cout<<post[n-1]<<' ';
            if(root!=0) preorder(in, sub_post, root);
            if(root!=n-1) preorder(sub_in, sub_post1, n-root-1);
        }
        int findlca(Node* root, int k1, int k2){
            if(root==NULL) return -1;
            if(k1>root->data && k2>root->data) return findlca(root->right, k1, k2);
            else if(k1<root->data && k2<root->data) return findlca(root->left, k1, k2);
            return root->data;
        }
        int lca(Node* root, int val1, int val2){
            if(traversals.search(root, val1)==0 || traversals.search(root, val2)==0){
                return -1;
            }
            if(val1 == val2){
                return val1;
            }
            return findlca(root, val1, val2);
        }
}misc;

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
    	    int n;
    	    switch(query){
    	        case 'B':
    	            flag = 0;
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
    	            cin>>n;
    	            while(n--){
    	                int val;
    	                cin>>val;
    	                if(val==0);  // do nothing if the value is zero
    	                if(val>0) root = avl.insert(root, val);
    	                if(val<0) root = avl.deleteNode(root, val*-1);
    	            }
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
    	                root = avl.insert(root, val);
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
    	                root = avl.deleteNode(root, val);
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
    	            traversals.boundary(root);
    	            cout<<endl;
    	            break;
    	        case 'C':
    	            int k1, k2;
    	            cin>>k1>>k2;
    	            cout<< misc.lca(root, k1, k2) << endl;
    	            break;
    	        case 'Z':
    	        {
    	            cin>>n;
    	            vector<int> inorder;
    	            vector<int> preorder;
    	            int n1 = n;
    	            while(n1--){
    	                cin>>val;
    	                preorder.emplace_back(val);
    	            }
    	            n1=n;
    	            while(n1--){
    	                cin>>val;
    	                inorder.emplace_back(val);
    	            }
    	            misc.postorder(inorder, preorder, n);
    	            cout<<endl;
    	            break;
    	        }
    	        case 'Y':
    	        {
    	            cin>>n;
    	            vector<int> inorder;
    	            vector<int> postorder;
    	            int n1 = n;
    	            while(n1--){
    	                cin>>val;
    	                postorder.emplace_back(val);
    	            }
    	            n1=n;
    	            while(n1--){
    	                cin>>val;
    	                inorder.emplace_back(val);
    	            }
    	            misc.preorder(inorder, postorder, n);
    	            cout<<endl;
    	            break;
    	        }
    	        case 'K':
    	            deleteTree(root);
    	            root = NULL; // to avoid dangling pointer
    	            break;
    	    }
	    }
	}
	return 0;
}
