#include <bits/stdc++.h>

using namespace std;

class Node {
    public:
        int data;
        Node *left;
        Node *right;
        Node(int d) {
            data = d;
            left = right = nullptr;
        }
};

class Solution {
    public:
        Node *insert(Node *root, int data) {
            if (!root) return new Node(data);
            Node *cur;
            if (data <= root->data) {
                root->left = insert(root->left, data);
            } else {
                root->right = insert(root->right, data);
            }
            return root;
        }

        void levelOrder(Node *root) {
            if (!root) return;
            
            queue<Node *> q;
            q.push(root);
            
            while(!q.empty()) {
                Node *n = q.front(); q.pop();
                cout << n->data << " ";
                if (n->left) q.push(n->left);
                if (n->right) q.push(n->right);
            }
        }
};

int main(void) {
    Solution s;
}
