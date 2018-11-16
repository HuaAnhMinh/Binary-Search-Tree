#include <iostream>
#include <vector>
using namespace std;

struct NODE {
    int key;
    NODE* left;
    NODE* right;

    NODE(int key) : key(key), left(nullptr), right(nullptr) { }
};

class BinarySearchTree {
private:
    NODE* root;

    NODE* CreateNewNode(int key) {
        return new NODE(key);
    }

    // chèn một nút mới vào cây:
    // nếu node đang rỗng thì chèn nút mới vào ngay vị trí đó
    // nếu key nhỏ hơn key chứa trong node thì chắc chắn phải chèn sang vị trí nhánh trái
    // nếu key lớn hơn key chứa trong node thì chắc chắn phải chèn sang vị trí nhánh phải
    // do đây là unordered binary search tree nên dữ liệu các node sẽ là duy nhất, không có trường hợp
    // có 2 node chứa cùng 1 số.
    NODE* _Insert(NODE* node, int key) {
        if (!node) {
            return CreateNewNode(key);
        }
        else if (key < node->key) {
            node->left = _Insert(node->left, key);
        }
        else if (key > node->key) {
            node->right = _Insert(node->right, key);
        }
        return node;
    }

    void DeleteTree(NODE* node) {
        if (!node) {
            return;
        }
        DeleteTree(node->left);
        DeleteTree(node->right);
        delete node;
    }

    void InorderTraversal(NODE* node) {
        if (node->left) {
            InorderTraversal(node->left);
        }
        cout << node->key << " ";
        if (node->right) {
            InorderTraversal(node->right);
        }
    }

    void PreorderTraversal(NODE* node) {
        cout << node->key << " ";
        if (node->left) {
            PreorderTraversal(node->left);
        }
        if (node->right) {
            PreorderTraversal(node->right);
        }
    }

    void PostorderTraversal(NODE* node) {
        if (node->left) {
            PostorderTraversal(node->left);
        }
        if (node->right) {
            PostorderTraversal(node->right);
        }
        cout << node->key << " ";
    }

    NODE* _Search(NODE* node, int key) {
        if (key == node->key || !node) {
            return node;
        }
        else if (key < node->key) {
            return _Search(node->left, key);
        }
        else if (key > node->key) {
            return _Search(node->right, key);
        }
    }

    NODE* _DeleteNode(NODE* & node, int x) {
        if (!node) {
            return node;
        }
        if (x < node->key) {
            node->left = _DeleteNode(node->left, x);
        }
        else if (x > node->key) {
            node->right = _DeleteNode(node->right, x);
        }
        else {
            if (!node->left) {
                NODE* temp = node->right;
                delete node;
                return temp;
            }
            else if (!node->right) {
                NODE* temp = node->left;
                delete node;
                return temp;
            }
            NODE* temp = _MinValueNodeFromRight(node->right);
            node->key = temp->key;
            node->right = _DeleteNode(node->right, temp->key);
        }
        return node;
    }

    NODE* _MinValueNodeFromRight(NODE* node) {
        NODE* current = node;
        while (current->left) {
            current = current->left;
        }
        return current;
    }

    int _Size(NODE* node) {
        if (!node) {
            return 0;
        }
        return _Size(node->left) + 1 + _Size(node->right);
    }

public:
    BinarySearchTree() : root(nullptr) { }

    BinarySearchTree(const BinarySearchTree & source) = delete;

    BinarySearchTree(BinarySearchTree && source) = delete;

    BinarySearchTree & operator=(const BinarySearchTree & source) = delete;

    void Insert(int key) {
        root = _Insert(root, key);
    }

    void Traversal(int type) {
        if (type == 0) {
            InorderTraversal(root);
        }
        else if (type == 1) {
            PreorderTraversal(root);
        }
        else if (type == 2) {
            PostorderTraversal(root);
        }
    }

    NODE* Search(int key) {
        return _Search(root, key);
    }

    NODE* MinValueNodeFromRight() {
        if (root) {
            return _MinValueNodeFromRight(root->right);
        }
        return root;
    }

    void DeleteNode(int key) {
        root = _DeleteNode(root, key);
    }

    int Size() {
        return _Size(root);
    }

    ~BinarySearchTree() {
        DeleteTree(root);
        root = nullptr; // this line is redundant...
    }
};

int main() {
    BinarySearchTree tree;
    int num, choose;

    /*while (true) {
        cout << "Enter number or not (0: no, other: yes): ";
        cin >> choose;
        if (choose == 0) {
            break;
        }
        cout << "Enter a number: ";
        cin >> num;
        tree.Insert(num);
    }*/

    vector<int> test = { 10, 8, 15, 6, 9, 4, 5, 7, 12, 17 };
    for (auto & i : test) {
        tree.Insert(i);
    }

    cout << "Choose type of traversal to print tree (0: inorder, 1: preorder, 2: postorder): ";
    cin >> choose;

    tree.Traversal(choose);
    cout << endl;

    NODE* findNode = tree.Search(9);
    cout << findNode->key << endl;

    tree.DeleteNode(5);

    tree.Traversal(choose);
    cout << endl;

    tree.DeleteNode(15);

    tree.Traversal(choose);
    cout << endl;

    tree.DeleteNode(8);
    
    tree.Traversal(choose);
    cout << endl;

    return EXIT_SUCCESS;
}