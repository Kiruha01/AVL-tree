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

    void add(T item){
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
                        break;
                    }
                }
                else {
                    if (runner->left != nullptr)
                        runner = runner->left;
                    else {
                        runner->left = new Node(item, runner);
                        break;
                    }
                }

            }
        }
    }
    void remove(T item);

    bool contain(T item){
        if (find(item) != nullptr)
            return true;
        return false;
    }

private:
    struct Node{
    Node(T item, Node* parent){
        data = item;
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
    void small_right_tirn(Node* node);
    void big_left_turn(Node* node);
    void big_right_turn(Node* node);

    Node* head;
};

int main() {
    AVL<int> a = AVL<int>(3);
    a.add(3);
    a.add(1);
    a.add(7);
    a.add(5);
    a.add(2);
    a.add(13);
    a.add(9);
    a.add(4);
    a.print();
    std::cout << (a.contain(7) ? "Yes" : "No") << std::endl;
    std::cout << (a.contain(6) ? "Yes" : "No") << std::endl;
    std::cout << (a.contain(4) ? "Yes" : "No") << std::endl;
    std::cout << (a.contain(10) ? "Yes" : "No") << std::endl;

}
