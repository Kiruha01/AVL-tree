#include <iostream>

template <typename T>
class AVL{
public:
    AVL(){
        head = nullptr;
    }

    explicit AVL(T item){
        head = new Node(item, nullptr);

    }

    void print(){
        print(head);
    }

    void add(T item);
    void remove(T item);
    bool contain(T item);

private:
    struct Node{
    Node(T item, Node* prnt){
        data = item;
        parent = prnt;
        left = nullptr;
        right = nullptr;
        diff = 0;
    }

    T data;
    Node* left;
    Node* right;
    Node* parent;
    short diff;
};

    void print(Node* node){
        if (node->left != nullptr)
            print(node->left);
        std::cout << node->data << ' ';
        if (node->right != nullptr)
            print(node->right);
    }

    Node* find(T item){
        Node* runner = head;
        while (runner != nullptr && runner->data != item){
            if (item < runner->data){
                runner = runner->left;
            }
            else {
                runner = runner->right;
            }
        }
        return runner;
    }

    void small_left_turn(Node* node);
    void small_right_turn(Node* node);
    void big_left_turn(Node* node);
    void big_right_turn(Node* node);

    Node* head;
};

template<typename T>
void AVL<T>::add(T item) {
    if (this->head == nullptr){
        head = new Node(item, nullptr);
    }
    else{
        Node* runner = head;
        while(true){
            if (runner->data < item) {
                if (runner->right != nullptr)
                    runner = runner->right;
                else {
                    runner->right = new Node(item, runner);
                    runner = runner->right;
                    break;
                }
            }
            else {
                if (runner->left != nullptr)
                    runner = runner->left;
                else {
                    runner->left = new Node(item, runner);
                    runner = runner->left;
                    break;
                }
            }

        }
        // recalculation diff
        while (true){
            if (runner->parent == nullptr)
                break;
            if (runner->parent->left == runner){
                runner->parent->diff += 1;
                runner = runner->parent;
            }
            else{
                runner->parent->diff -= 1;
                runner = runner->parent;
            }
            //TODO: turn
            if (runner->diff == 0) {
                break;
            }
        }
    }
}

template<typename T>
void AVL<T>::remove(T item) {
    Node* to_remove = find(item);
    if (to_remove == nullptr)
        return;

    Node* new_node = to_remove->right;
    Node* runner; // с этой ноды мы начинаем пересчет diff
    if (new_node == nullptr){
        if (to_remove->parent->left == to_remove) {
            to_remove->parent->left = to_remove->left;
            to_remove->left->parent = to_remove->parent;
            to_remove->parent->diff -= 1;
        }
        else {
            to_remove->parent->right = to_remove->left;
            to_remove->left->parent = to_remove->parent;
            to_remove->parent->diff += 1;
        }
        runner = to_remove->parent;
    }
    else {
        while (new_node->left != nullptr)
            new_node = new_node->left;
        new_node->diff = to_remove->diff;

        new_node->parent->diff -= 1;
        // connect children to new_node
        new_node->parent->left = new_node->right;
        new_node->right = to_remove->right;
        new_node->left = to_remove->left;

        runner = new_node->parent;

        // connect new_node to parent
        new_node->parent = to_remove->parent;
        if (to_remove->parent == nullptr)
            head = new_node;
        else if (to_remove->parent->left == to_remove)
            to_remove->parent->left = new_node;
        else
            to_remove->parent->right = new_node;
    }
    // recalculation diff
    while (runner->parent != nullptr){
        if (runner->parent->diff == 1 || runner->parent->diff == -1) {
            break;
        }
        if (runner->parent->left == runner)
        {
            runner->parent->diff -= 1;
        }
        else{
            runner->parent->diff += 1;
        }
        runner = runner->parent;
        // TODO: turn
    }
}

template<typename T>
bool AVL<T>::contain(T item) {
    if (find(item) != nullptr)
        return true;
    return false;
}

template<typename T>
void AVL<T>::small_left_turn(AVL::Node *node) {
    Node* b = node->right;
    node->right = b->left;
    node->right->parent = node;
    b->left = node;
    b->parent = node->parent;
    node->parent = b;
    if (b->parent->left == node)
        b->parent->left = b;
    else
        b->parent->right = b;
}

template<typename T>
void AVL<T>::small_right_turn(AVL::Node *node) {
    Node* b = node->right;
    node->left = b->right;
    node->left->parent = node;
    b->right = node;
    b->parent = node->parent;
    node->parent = b;
    if (b->parent->left == node)
        b->parent->left = b;
    else
        b->parent->right = b;

}

template<typename T>
void AVL<T>::big_left_turn(AVL::Node *node) {
    Node* b = node->right;
    Node* c = b->left;

    node->right = c->left;
    node->right->parent = node;

    b->left = c->right;
    b->left->parent = b;

    c->parent = node->parent;
    if (node->parent->left == node)
        node->parent->left = c;
    else
        node->parent->right = c;
    c->left = node;
    node->parent = c;
    c->right = b;
    b->parent = c;
}

template<typename T>
void AVL<T>::big_right_turn(AVL::Node *node) {
    Node* b = node->left;
    Node* c = b->right;

    node->left = c->right;
    node->left->parent = node;

    b->right = c->left;
    b->right->parent = b;

    c->parent = node->parent;
    if (node->parent->left == node)
        node->parent->left = c;
    else
        node->parent->right = c;
    c->right = node;
    node->parent = c;
    c->left = b;
    b->parent = c;
}

int main() {
    AVL<int> a = AVL<int>();
    a.add(2);
    a.add(1);
    a.add(7);
    a.add(8);
    a.add(4);
    a.add(3);
    a.add(5);
    a.add(6);
    a.print();
    a.remove(2);
//    std::cout << (a.contain(7) ? "Yes" : "No") << std::endl;
//    a.remove(2);
//    std::cout << (a.contain(7) ? "Yes" : "No") << std::endl;
//    std::cout << (a.contain(6) ? "Yes" : "No") << std::endl;
//    std::cout << (a.contain(4) ? "Yes" : "No") << std::endl;
//    a.remove(4);
//    std::cout << (a.contain(4) ? "Yes" : "No") << std::endl;
//    std::cout << (a.contain(10) ? "Yes" : "No") << std::endl;

}
