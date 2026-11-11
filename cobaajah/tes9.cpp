#include<iostream>
using namespace std;

struct node{
    node* left;
    node* right;
    int data;
};

node* createNode(int value){
    node* newNode = new node();
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->data = value;
    return newNode;
}

// alur : left -> root -> right
void inorder(node* root){
        if (root == nullptr){
            return;
        }
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
}

// alur : root -> left -> right
void preorder(node* root){
        if (root == nullptr){
            return;
        }
        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
}

// alur : left -> right -> root
void postorder(node* root){
        if (root == nullptr){
            return;
        }
        postorder(root->left);
        postorder(root->right);
        cout << root->data << " ";
}

int jumlahNode(node* root){
    if (root == nullptr){
        return 0;
    }
    return 1 + jumlahNode(root->left) + jumlahNode(root->right);
}

bool searchNode(node* root, int value){
    if (root == nullptr){
        return false;
    }
    if (root->data == value){
        return true;
    }
    return searchNode(root->left, value) || searchNode(root->right, value);
}

void clearnode(node* root){
    if (root == nullptr){
        return;
    }
    clearnode(root->left);
    clearnode(root->right);
    delete root;
    root = nullptr;
}

int main(){
    node* root = nullptr;

    // cabang sebelah kiri
    root = createNode(50);
    root->left = createNode(80);
    root->left->left = createNode(10);
    root->left->right = createNode(70);
    root->left->right->left = createNode(30);

    // cabang sebelah kanan
    root->right = createNode(20);
    root->right->right = createNode(90);

    cout << "Coba transversal";
    cout << "\nAlur : left -> root -> right";
    cout << "\nInorder: ";
    inorder(root);

    cout << "\nAlur : root -> left -> right";
    cout << "\nPreorder: ";
    preorder(root);

    cout << "\nAlur : left -> right -> root";
    cout << "\nPostorder: ";
    postorder(root);

    cout << "\nJumlah node: " << jumlahNode(root) << endl;
    
    cout << "Cari node 90: " << (searchNode(root, 90) ? "Ditemukan" : "Tidak ditemukan") << endl;
}
