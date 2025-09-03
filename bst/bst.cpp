#include <iostream>

template<typename T>
class Node {
    private:


    public:
        T value;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;

        Node(T val): value(val), left(nullptr), right(nullptr) {}

        ~Node() {
        }

        void print() {
            std::cout << "val: " << value << std::endl;

            if (left) {
                left->print();
            }
            if (right) {
                right->print();
            }
        }


};

template<typename T>
class BST {
    private:
        std::shared_ptr<Node<T>> actualRoot;
        std::weak_ptr<Node<T> > root;

    public:

        void print() {

            auto r = root.lock();
            if (r) {
                r->print();
            }
        }

        bool contains(T value) {
            auto r = root.lock();
            if (!r) {
                return false;
            }

            return contains(value, r);
        }

        bool contains(T value, std::shared_ptr<Node<T> > n) {
            if (!n) {
                return false;
            }

            if (n->value == value) {
                return true;
            }

            if (value < n->value) {
                return contains(value, n->left);
            }

            return contains(value, n->right);
        }

        void insert(T value) {

            auto r = root.lock();
            if (!r) {
                std::cout << "no root; making now" << std::endl;
                actualRoot = std::make_shared<Node<T> >(value);

                root = actualRoot;

                return;
            }

            auto parent = getParent(value, r);
            if (parent == nullptr) {
                return; // Already have this value.
            }

            if (value < parent->value) {
                parent->left = std::make_shared<Node<T> >(value);
                return;
            }

            parent->right = std::make_shared<Node<T> >(value);
        }

        std::shared_ptr<Node<T> > getParent(T value, std::shared_ptr<Node<T> > start) {

            if (value == start->value) {
                return nullptr;
            }

            if (value < start->value) {

                if (start->left == nullptr) {
                    return start;
                }

                return getParent(value, start->left);
            }

            if (start->right == nullptr) {
                return start;
            }

            return getParent(value, start->right);
        }

        std::shared_ptr<Node<T> > remove(T value) {

            auto r = root.lock();
            if (!r) {
                return nullptr;
            }

            return remove(value, r);
        }

        std::shared_ptr<Node<T> > remove(T value, std::shared_ptr<Node<T> > n) {

            if (!n) return nullptr;
            
            if (n->value == value) {
                if (!n->left && !n->right) {
                    return nullptr;
                }

                if (!n->right) {
                    auto tmp = n->left;
                    return tmp;
                }

                if (!n->left) {
                    auto tmp = n->right;
                    return tmp;
                }

                std::cout << "Subtree: " << n->value << std::endl;

                // Otherwise we have left and right both in the tree.
                auto minN = min(n->right);
                if (!minN) {
                    std::cout << "returning nullptr for subtree" << std::endl;
                    return nullptr;
                }
                n->value = minN->value;
                n->right = remove(minN->value, n->right);
                return n;
            }

            if (value < n->value) {
                n->left = remove(value, n->left);
                return n;
            }

            n->right = remove(value, n->right);
            return n;                
        }

        T min() {

            auto r = root.lock();
            if (!r) {
                return T();
            }

            std::shared_ptr<Node<T> > minNode = min(r);
            if (!minNode) {
                return T();
            }

            return minNode->value;
        }

        std::shared_ptr<Node<T> > min(std::shared_ptr<Node<T> > n) {
            if (!n) {
                return nullptr;
            }

            if (!n->left) {
                return n;
            }

            return min(n->left);
        }

        T max() {
            return max(root);
        }

        T max(std::shared_ptr<Node<T> > n) {
            if (!n) {
                return T();;
            }

            if (!n->right) {
                return n->value;
            }

            return max(n->right);
        }
};


int main() {
    BST<int> b;

    b.insert(10);
    b.insert(12);
    b.insert(2);
    b.insert(25);
    b.insert(7);
    b.insert(1);
    b.insert(3);
    b.insert(13);
    b.insert(11);

    b.print();

    b.remove(12);
    b.print();
}