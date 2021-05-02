#include <iostream>

template <typename T>
class AVL{
public:
    AVL(){
        head = nullptr;
    }

    AVL(T item){
        head = new Node(item, nullptr);

    }

    void add(T item){
        if (this->head == nullptr){
            head = Node(item, nullptr);
        }
        else{
            Node* runner = head;
            while(true){
                if (runner->data < item) {
                    if (runner->right != nullptr)
                        runner = runner->right;
                    else {
                        runner->right = new Node(item, runner);
                        break;
                    }
                }
                else {
                    if (runner->left != nullptr)
                        runner = runner->left;
                    else {
                        runner->left = new Node(item, runner);
                    }
                }

            }
        }
    }
    void remove(T item);
    bool contain(T item);

private:
    struct Node{
    Node(T data, Node* parent){
        data = data;
        parent = parent;
        left = nullptr;
        right = nullptr;
    }

    T data;
    Node* left;
    Node* right;
    Node* parent;
    short diff;
};
    void small_left_turn(Node* node);
    void small_right_tirn(Node* node);
    void big_left_turn(Node* node);
    void big_right_turn(Node* node);

    Node* head;
};

int main() {

}
