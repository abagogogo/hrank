	bool checkBST(Node* root) {
		return checkBSTBound(root, -1, 10001);        
	}

    bool checkBSTBound(Node *root, int lowerLimit, int upperLimit) {        
        if (!root) {
            return true;
        }
        if (root->data >= upperLimit || root->data <= lowerLimit) {
            return false;
        }
                
        if (!checkBSTBound(root->left, lowerLimit, root->data)) {
            return false;
        }
        if (!checkBSTBound(root->right, root->data, upperLimit)) {
            return false;
        }
        return true;
    }
