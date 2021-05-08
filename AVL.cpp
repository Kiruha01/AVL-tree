#include <iostream>
#include "fstream"

template <typename T>
class AVL{
public:
    AVL(){
        head = nullptr;
    }

    explicit AVL(T item){
        head = new Node(item, nullptr);
    }

    void add(T item);
    void remove(T item);
    bool contain(T item);

    T get_head(){
        if (head == nullptr)
            return 0;
        else
            return head->data;
    }

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

    bool do_rotation(Node* node);

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
            }
            else
                runner->parent->diff -= 1;
            runner = runner->parent;
            if (do_rotation(runner))
                runner = runner->parent;
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
            if (to_remove->left != nullptr)
                to_remove->left->parent = to_remove->parent;
            to_remove->parent->diff -= 1;
        }
        else {
            to_remove->parent->right = to_remove->left;
            if (to_remove->left != nullptr)
                to_remove->left->parent = to_remove->parent;
            to_remove->parent->diff += 1;
        }
        runner = to_remove->parent;
        delete to_remove;
        if (do_rotation(runner))
            runner = runner->parent;
        if (runner->diff == -1 || runner->diff == 1)
            return;
    }
    else {
        while (new_node->left != nullptr)
            new_node = new_node->left;
        if (new_node->parent == to_remove){
            new_node->parent = to_remove->parent;
            if (to_remove->parent->left == to_remove)
                to_remove->parent->left = new_node;
            else
                to_remove->parent->right = new_node;
            new_node->left = to_remove->left;
            if (to_remove->left != nullptr)
                to_remove->left->parent = new_node;
            new_node->diff = to_remove->diff + 1;
            runner = new_node;
            delete to_remove;
            if (do_rotation(runner))
                runner = runner->parent;
            if (new_node->diff == 1 || new_node->diff == -1) {
                return;
            }
        }
        else {
            new_node->diff = to_remove->diff;

            new_node->parent->diff -= 1;
            // connect children to new_node
            new_node->parent->left = new_node->right;
            // TODO: try inline function to set child
            if (new_node->right != nullptr)
                new_node->right->parent = new_node->parent;
            new_node->right = to_remove->right;
            if (to_remove->right != nullptr)
                to_remove->right->parent = new_node;
            new_node->left = to_remove->left;
            if (to_remove->left != nullptr)
                to_remove->left->parent = new_node;

            runner = new_node->parent;

            // connect new_node to parent
            new_node->parent = to_remove->parent;
            if (to_remove->parent == nullptr)
                head = new_node;
            else if (to_remove->parent->left == to_remove)
                to_remove->parent->left = new_node;
            else
                to_remove->parent->right = new_node;
            delete to_remove;
            if (runner->diff == -1 || runner->diff == 1)
                return;
        }
    }
    // recalculation diff
    while (runner->parent != nullptr){

        if (runner->parent->left == runner)
        {
            runner->parent->diff -= 1;
        }
        else{
            runner->parent->diff += 1;
        }
        runner = runner->parent;
        if (do_rotation(runner)){
            runner = runner->parent;
        }
        if (runner->diff == 1 || runner->diff == -1) {
            break;
        }
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
    if (node->right != nullptr)
        node->right->parent = node;
    b->left = node;
    b->parent = node->parent;
    node->parent = b;
    if (b->parent != nullptr) {
        if (b->parent->left == node)
            b->parent->left = b;
        else
            b->parent->right = b;
    }
    else
        head = b;

    // change diff
    if (b->diff == -1){
        node->diff = 0;
        b->diff = 0;
    }
    else if (b->diff == 0){
        node->diff = -1;
        b->diff = +1;
    }
}

template<typename T>
void AVL<T>::small_right_turn(AVL::Node *node) {
    Node* b = node->left;
    node->left = b->right;
    if (node->left != nullptr)
        node->left->parent = node;
    b->right = node;
    b->parent = node->parent;
    node->parent = b;
    if (b->parent != nullptr) {
        if (b->parent->left == node)
            b->parent->left = b;
        else
            b->parent->right = b;
    }
    else
        head = b;
    // change diff
    if (b->diff == 1){
        node->diff = 0;
        b->diff = 0;
    }
    else if (b->diff == 0){
        b->diff = -1;
        node->diff = 1;
    }
}

template<typename T>
void AVL<T>::big_right_turn(AVL::Node *node) {
    Node* b = node->left;
    Node* c = b->right;

    node->left = c->right;
    if (node->left != nullptr)
        node->left->parent = node;

    b->right = c->left;
    if (b->right != nullptr)
        b->right->parent = b;

    c->parent = node->parent;
    if (node->parent != nullptr) {
        if (node->parent->left == node)
            node->parent->left = c;
        else
            node->parent->right = c;
    }
    else
        head = c;
    c->right = node;
    node->parent = c;
    c->left = b;
    b->parent = c;

    // change diff
    if (c->diff == 1){
        node->diff = -1;
        b->diff = 0;
    }
    else if (c->diff == 0){
        node->diff = 0;
        b->diff = 0;
    }
    else if (c->diff == -1){
        node->diff = 0;
        b->diff = 1;
    }
    c->diff = 0;
}

template<typename T>
void AVL<T>::big_left_turn(AVL::Node *node) {
    Node* b = node->right;
    Node* c = b->left;

    node->right = c->left;
    if (node->right != nullptr)
        node->right->parent = node;

    b->left = c->right;
    if (b->left != nullptr)
        b->left->parent = b;

    c->parent = node->parent;
    if (node->parent != nullptr) {
        if (node->parent->left == node)
            node->parent->left = c;
        else
            node->parent->right = c;
    }
    else{
        head = c;
    }
    c->left = node;
    node->parent = c;
    c->right = b;
    b->parent = c;

    // change diff
    if (c->diff == 1){
        node->diff = 0;
        b->diff = -1;
    }
    else if (c->diff == 0){
        node->diff = 0;
        b->diff = 0;
    }
    else if (c->diff == -1){
        node->diff = 1;
        b->diff = 0;
    }
    c->diff = 0;
}


template<typename T>
// "true" if rotation was done, "false" otherwise
bool AVL<T>::do_rotation(AVL::Node *node) {
    if (node->diff == 2){
        if (node->left->diff == 1 || node->left->diff == 0){
            small_right_turn(node);
            return true;
        }
        else if (node->left->diff == -1){
            big_right_turn(node);
            return true;
        }
    }
    else if (node->diff == -2){
        if (node->right->diff == -1 || node->right->diff == 0){
            small_left_turn(node);
            return true;
        }
        else if (node->right->diff == 1){
            big_left_turn(node);
            return true;
        }
    }
    return false;
}

int main() {
    std::fstream filein, fileout;
    filein.open("input.txt", std::ios_base::in);
    fileout.open("output.txt", std::ios_base::out);

    AVL<int> tree = AVL<int>();

    if (fileout.is_open() && filein.is_open()) {
        while (!filein.eof()) {
            std::string c;
            char* end;
            filein >> c;
            switch (c[0]) {
                case '+':
                    filein >> c;
                    tree.add(std::strtol(c.c_str(), &end, 10));
                    fileout << tree.get_head() << std::endl;
                    break;
                case '-':
                    filein >> c;
                    tree.remove(std::strtol(c.c_str(), &end, 10));
                    fileout << tree.get_head() << std::endl;
                    break;
                case '?':
                    filein >> c;
                    if (tree.contain(std::strtol(c.c_str(), &end, 10)))
                        fileout << "true" << std::endl;
                    else
                        fileout << "false" << std::endl;
                    break;
                default:
                    break;
            }
        }
        fileout.close();
        filein.close();
    }
    return 0;
}
