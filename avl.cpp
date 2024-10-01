struct Node{
    int data, height;
    Node* left;
    Node* right;
    
    Node(int val) : data(val){
        left = right = NULL;
        height = 1;
    }
};

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
};
