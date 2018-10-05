/* Hidden stub code will pass a root argument to the function below. Complete the function to solve the challenge. Hint: you may want to write one or more helper functions.  

The Node struct is defined as follows:
	struct Node {
		int data;
		Node* left;
		Node* right;
	}
*/
    int findMax(Node *root) {
        Node *node = root;
        while (node->right) node = node->right;
        return node->data;
    }

    int findMin(Node *root) {
        Node *node = root;
        while (node->left) node = node->left;
        return node->data;
    }

#if 0
	bool checkBST(Node* root) {
        if (!root) return true;
        
        if (root->left) {
            if (findMax(root->left) >= root->data) return false;
            if (!checkBST(root->left)) return false;
        }
        if (root->right) {
            if (findMin(root->right) <= root->data) return false;
            if (!checkBST(root->right)) return false;
        }
        return true;
	}
#else
    #include <climits>

    bool check_range(Node *root, int min_val, int max_val) {
        if (!root) return true;
        if (root->data <= min_val || root->data >= max_val) return false;
        return check_range(root->left, min_val, root->data) 
            && check_range(root->right, root->data, max_val);                
    }

    bool checkBST(Node *root) {
        return check_range(root, INT_MIN, INT_MAX); 
    }
#endif
