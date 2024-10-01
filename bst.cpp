struct Node{
    int data, height;
    Node* left;
    Node* right;
    
    Node(int val) : data(val){
        left = right = NULL;
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
            if(root==NULL) return new Node(val);
            
            if(val<root->data) root->left = insert(root->left, val);
            else if(val>root->data) root->right = insert(root->right, val);
            
            return root;
        }
        Node* deleteNode(Node* root, int val){  // iterative deletion
            if(root==NULL) return root;
            
            if(val<root->data) root->left = deleteNode(root->left, val);
            else if(val>root->data) root->right = deleteNode(root->right, val);
            else{ // perform delete operation
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
            
            return root;
        }
};
