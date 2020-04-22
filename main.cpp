
#include <fstream>
#include <iostream>

using namespace std;

class Node {
    int info;
    Node *left, *right, *parent;
public:
    Node(){
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        info = 0;
    }
    Node(int val){
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        info = val;
    }

    Node * getParent(){return parent;}
    Node * getLeft(){return left;}
    Node * getRight(){return right;}
    int getKey(){return info;}
    void setParent(Node *n){parent = n;}
    void setLeft(Node *n){left = n;}
    void setRight(Node *n){right = n;}
    void setKey(int key){info = key;}
    bool isLeftChild(){return ((this->getParent())->getLeft()==this);}
};

class RB_Node{
    int info;
    RB_Node *left, *right, *parent;
    char color;
public:
    RB_Node(){
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        color = 'r';
    }
    RB_Node(int val){
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        info = val;
        color = 'r';
    }
    char getColor(){
        if(this!= nullptr)
        return color;
    }
    void setColor(char col){color=col;}
    RB_Node * getParent(){return parent;}
    RB_Node * getLeft(){return left;}
    RB_Node * getRight(){return right;}
    int getKey(){return info;}
    void setParent(RB_Node *n){parent = n;}
    RB_Node * getSibling() {
        if (this->getParent() == nullptr)
            return NULL;
        else if (this->isLeftChild())
            return (this->getParent())->getRight();
        else
            return (this->getParent())->getLeft();
    }
    void setLeft(RB_Node *n){left = n;}
    void setRight(RB_Node *n){right = n;}
    void setKey(int key){info = key;}
    bool isLeftChild(){
        if(this->getParent()!= nullptr)
        return ((this->getParent())->getLeft()==this);
        else return false;
    }
};
class Tree {
    int nr_noduri;
public:
    virtual void addNode(int key) = 0;
    virtual void removeKey(int key) = 0;

    Tree(){
        nr_noduri=0;
    }
    void plusNodes(){nr_noduri++;}
    void minusNodes(){nr_noduri--;}
    int getNodes(){return nr_noduri;}
};

class BST : public Tree {
    Node *root;
public:
    BST(){
        root = nullptr;
    }
    void operator = (const BST & copac)
    {
      Node *n=copac.getRoot();
      while()
    }
    void addSubTree(Node *n, BST cop){
        cop.addNode(n->getKey());
        if(n->getLeft()!= nullptr)
            displaySubTree(n->getLeft());

        if(n->getRight()!= nullptr)
            displaySubTree(n->getRight());
    }
    BST (const BST &copac2){
        this->addSubTree(this->getRoot(),copac2);
    }
    //cpy constructor
    //cin
    //cout
    //destructor

    friend istream &operator>>(istream &i, BST &cop);

    friend ostream &operator<<(istream &o, BST &cop);



    virtual void addNode(int key){
        Node *n = new Node;
        if(root == nullptr)
        {
            root = n;
            n->setKey(key);
            plusNodes();
        } else
        {
            Node *temp = root;
            int ok=1;
            while(ok)
            {
                if(key<temp->getKey())
                    if(temp->getLeft()== nullptr)
                    {
                        ok=0;
                        temp->setLeft(n);
                        n->setParent(temp);

                        n->setKey(key);
                        plusNodes();
                    }
                    else
                        temp=temp->getLeft();
                else if(key>temp->getKey())
                {
                    if(temp->getRight()== nullptr)
                    {
                        ok=0;
                        temp->setRight(n);
                        n->setParent(temp);

                        n->setKey(key);
                        plusNodes();
                    }
                    else
                        temp=temp->getRight();
                }
                else{ std::cout << "Key already in tree.\n";
                ok=0;}
            }
        }
    }
    virtual void removeKey(int key) {
        Node *temp = root;
        int ok=1;
        while(ok)
        {
            if(key<temp->getKey())
                if(temp->getLeft()!= nullptr)
                    temp=temp->getLeft();
                else
                {
                    std::cout << "key not in tree.\n";
                    return;
                }
            else if (key>temp->getKey())
                 if(temp->getRight()!= nullptr)
                     temp=temp->getRight();
                 else
                 {
                     std::cout << "key not in tree.\n";
                     return;
                 }
            else
                ok=0;
        }
        //nod fara copii
        if(temp->getLeft()== nullptr && temp->getRight()== nullptr)
        {
            if(temp!=root)
                if(temp->isLeftChild())
                    (temp->getParent())->setLeft(nullptr);
                else
                    (temp->getParent())->setRight(nullptr);
            else
                root= nullptr;
            delete temp;
            minusNodes();
        }
        //nod cu un copil stang
        else if(temp->getLeft()!= nullptr && temp->getRight()== nullptr)
        {
            if(temp!=root)
            {
                (temp->getLeft())->setParent(temp->getParent());
                if(temp->isLeftChild())
                    (temp->getParent())->setLeft(temp->getLeft());
                else
                    (temp->getParent())->setRight(temp->getLeft());
            } else
            {
                (temp->getLeft())->setParent(nullptr);
                root=temp->getLeft();
            }
            delete temp;
            minusNodes();
        }
        //nod cu un copil drept
        else if(temp->getLeft()== nullptr && temp->getRight()!= nullptr)
        {
            if(temp!=root)
            {
                (temp->getRight())->setParent(temp->getParent());
                if(temp->isLeftChild())
                    (temp->getParent())->setLeft(temp->getRight());
                else
                    (temp->getParent())->setRight(temp->getRight());
            } else
            {
                (temp->getRight())->setParent(nullptr);
                root=temp->getLeft();
            }
            delete temp;
            minusNodes();
        }
        //nod cu 2 copii
        else{
            Node *small = findSmallestKey(temp->getRight());
            int val = small->getKey();
            removeKey(val);
            temp->setKey(val);
        }
    }
    virtual int getHeight(Node *n){
        int x,y;
        if(n->getLeft()!= nullptr)
        x=getHeight(n->getLeft())+1;
        else
            x=1;
        if(n->getRight()!= nullptr)
        y=getHeight(n->getRight())+1;
        else y=1;
        return (x>y) ? x : y;
    }
    Node * findSmallestKey(Node *n) {
        Node *temp = n;
        while(temp->getLeft()!= nullptr)
            temp=temp->getLeft();
        return temp;
    }
    Node * getRoot(){return root;}
    void displaySubTree(Node *n){
        if(n->getLeft()!= nullptr)
        displaySubTree(n->getLeft());
        cout << n->getKey() << " ";
        if(n->getRight()!= nullptr)
        displaySubTree(n->getRight());
    }

};

istream &operator>>(istream &i, BST &cop){
    int val;
 i>>val;
 cop.addNode(val);
 return i;
}

ostream &operator<<(istream &o, BST &cop)
{
    cop.displaySubTree(cop.getRoot());
}
class RBT : Tree {
    RB_Node *root;
public:
    RBT(){
        root= nullptr;
    }
    virtual void addNode(int key){
        RB_Node * n = new RB_Node(key);
        if(root == nullptr)
        {
            root = n;
            plusNodes();
        } else
        {
            RB_Node *temp = root;
            int ok=1;
            while(ok)
            {
                if(key<temp->getKey())
                    if(temp->getLeft()== nullptr)
                    {
                        ok=0;
                        temp->setLeft(n);
                        n->setParent(temp);
                        plusNodes();
                        fixViolation(n);
                    }
                    else
                        temp=temp->getLeft();
                else if(key>temp->getKey())
                {
                    if(temp->getRight()== nullptr)
                    {
                        ok=0;
                        temp->setRight(n);
                        n->setParent(temp);
                        plusNodes();
                        fixViolation(n);
                    }
                    else
                        temp=temp->getRight();
                }
                else std::cout << "Key already in tree.\n";
                ok=0;
            }
        }


    }
    virtual void removeKey(int key){
        if(root== nullptr)
        {
            std::cout << "BRT empty.\n";
            return;
        }
        RB_Node *temp = root;
        int ok=1;
        while(ok)
        {
            if(key<temp->getKey())
                if(temp->getLeft()!= nullptr)
                    temp=temp->getLeft();
                else
                {
                    std::cout << "key not in tree.\n";
                    return;
                }
            else if (key>temp->getKey())
                if(temp->getRight()!= nullptr)
                    temp=temp->getRight();
                else
                {
                    std::cout << "key not in tree.\n";
                    return;
                }
            else
                ok=0;
        }
        RB_Node *replacer=findReplacer(temp);
        RB_Node *temp_parent=temp->getParent();
        bool doubleblack;
        if(replacer!= nullptr)
                doubleblack=(temp->getColor()=='b' && (replacer->getColor()=='b'));
        else
            doubleblack=temp->getColor()=='b';

        // nod cu 0 copii
        if(replacer== nullptr)
        {
            if(temp== root)
                root = nullptr;
            else{
                if(doubleblack)
                    fixDoubleBlack(temp);
                else{
                    if(temp->getSibling()!= nullptr)
                        (temp->getSibling())->setColor('r');
                }
                if(temp->isLeftChild())
                    temp->getParent()->setLeft(nullptr);
                else
                    temp->getParent()->setRight(nullptr);
            }
            delete temp;
        }
        //nod cu un copil
        else if(temp->getLeft()== nullptr || temp->getRight()== nullptr)
        {
            if(temp==root)
            {
                temp->setKey(replacer->getKey());
                temp->setLeft(nullptr);
                temp->setRight(nullptr);
                delete replacer;
            }
            else{
                if(temp->isLeftChild())
                {
                    temp_parent->setLeft(replacer);
                } else{
                    temp_parent->setRight(replacer);
                }
                delete temp;
                replacer->setParent(temp_parent);
                if(doubleblack){
                    fixDoubleBlack(replacer);
                } else
                    replacer->setColor('b');
            }

        }
        // nodul are 2 copii
        else{
            int swap;
            swap=temp->getKey();
            temp->setKey(replacer->getKey());
            replacer->setKey(swap);
            if(replacer->isLeftChild())
                replacer->getParent()->setLeft(nullptr);
            else
                replacer->getParent()->setRight(nullptr);


            delete replacer;
        }
    };
    void fixDoubleBlack(RB_Node *n) {
        if (n == root)
            return;

        RB_Node *sibling = n->getSibling();
        RB_Node *parent = n->getParent();

        if (sibling == nullptr)
            //recursie, nu avem frate
            fixDoubleBlack(parent);
        else {
            if (sibling->getColor() == 'r') {
                parent->setColor('r');
                sibling->setColor('b');
                if (sibling->isLeftChild()) {
                    rotateRight(parent);
                } else {
                    rotateLeft(parent);
                }
                fixDoubleBlack(n);
            } else if (sibling->getColor() == 'b') {

                if (sibling->getLeft()->getColor() == 'r' || sibling->getRight()->getColor() == 'r') {
                    if (sibling->getLeft() != nullptr && sibling->getLeft()->getColor() == 'r') {
                        if (sibling->isLeftChild()) {
                            //left left case
                            sibling->getLeft()->setColor(sibling->getColor());
                            sibling->setColor(parent->getColor());
                            rotateRight(parent);
                        } else {
                            //right left case
                            sibling->getLeft()->setColor(parent->getColor());
                            rotateRight(sibling);
                            rotateLeft(parent);
                        }
                    } else {
                        if (sibling->isLeftChild()) {
                            //left right case
                            sibling->getRight()->setColor(parent->getColor());
                            rotateLeft(sibling);
                            rotateRight(parent);
                        } else {
                            //right right case
                            sibling->getRight()->setColor(sibling->getColor());
                            sibling->setColor(parent->getColor());
                            rotateLeft(parent);
                        }
                    }
                    parent->setColor('b');
                } else {
                    sibling->setColor('r');
                    if (parent->getColor() == 'b')
                        fixDoubleBlack(parent);
                    else
                        parent->setColor('b');
                }
            }

        }
    }
    RB_Node * getRoot(){return root;}
    void rotateLeft(RB_Node *n){
        RB_Node *n_right= n->getRight();
        n->setRight(n_right->getLeft());

        if(n->getRight()!= nullptr)
            (n->getRight())->setParent(n);

        n_right->setParent(n->getParent());

        if(n->getParent()== nullptr)
            root=n_right;
        else if(n == (n->getParent())->getLeft())
            (n->getParent())->setLeft(n_right);
        else
            (n->getParent())->setRight(n_right);

        n_right->setLeft(n);
        n->setParent(n_right);
    }
    void rotateRight(RB_Node *n){
        RB_Node *n_left = n->getLeft();
        n->setLeft(n_left->getRight());

        if(n->getLeft() != nullptr)
            (n->getLeft())->setParent(n);

        n_left->setParent(n->getParent());

        if(n->getParent() == nullptr)
            root = n_left;
        else if(n->isLeftChild())
            (n->getParent())->setLeft(n_left);
        else
            (n->getParent()->setRight(n_left));
        n_left->setRight(n);
        n->setParent(n_left);
    }
    void fixViolation(RB_Node *n){
        RB_Node *n_parent= nullptr;
        RB_Node *n_grandparent= nullptr;

        while(n!=root && n->getColor()!='b' && n->getParent()->getColor()=='r' && (n->getParent()->getParent()!= nullptr))
        {
            n_parent=n->getParent();
            n_grandparent=n_parent->getParent();

            if(n_parent->isLeftChild())
            {

                RB_Node *n_uncle=n_grandparent->getRight();

                if(n_uncle != nullptr && n_uncle->getColor() == 'r')
                {
                    n_grandparent->setColor('r');
                    n_parent->setColor('b');
                    n_uncle->setColor('b');
                    n=n_grandparent;
                }
                else
                {
                    //left right case
                    if(!(n->isLeftChild()))
                    {
                        rotateLeft(n_parent);
                        n=n_parent;
                        n_parent=n->getParent();
                    }
                    //left left case
                    rotateRight(n_grandparent);
                    char temp;
                    temp=n_parent->getColor();
                    n_parent->setColor(n_grandparent->getColor());
                    n_grandparent->setColor(temp);
                    n=n_parent;
                }
            }
            else if( !(n_parent->isLeftChild()) )
            {
                RB_Node *n_uncle=n_grandparent->getRight();

                if(n_uncle != nullptr && n_uncle->getColor() == 'r')
                {
                    n_grandparent->setColor('r');
                    n_parent->setColor('b');
                    n_uncle->setColor('b');
                    n=n_grandparent;
                }
                //right left case
                if(n->isLeftChild())
                {
                    rotateRight(n_parent);
                    n=n_parent;
                    n_parent=n->getParent();
                }
                //right right case

                rotateLeft(n_grandparent);
                char temp;
                temp=n_parent->getColor();
                n_parent->setColor(n_grandparent->getColor());
                n_grandparent->setColor(temp);
                n=n_parent;
            }
        }
        root->setColor('b');
    }
    void displaySubTree(RB_Node *n){
        if(n== nullptr){
            cout << "BST gol.'\n";
            return;
            }
        if(n->getLeft()!= nullptr)
            displaySubTree(n->getLeft());
        std::cout << n->getKey() << n->getColor() << " ";
        if(n->getRight()!= nullptr)
            displaySubTree(n->getRight());
    }
    RB_Node * findSmallestKey(RB_Node *n) {
        RB_Node *temp = n;
        while(temp->getLeft()!= nullptr)
            temp=temp->getLeft();
        return temp;
    }
    RB_Node * findReplacer(RB_Node * n){
        if(n->getLeft()!= nullptr && n->getRight()!= nullptr)
            return findSmallestKey(n);
        if((n->getRight()==nullptr) && (n->getLeft()== nullptr))
            return nullptr;
        if(n->getLeft()!= nullptr)
            return n->getLeft();
        else
            return n->getRight();

    }
};


int main() {
    BST copac;
    int treekeys[16] ={50, 76, 21, 4, 32, 64, 15, 52 ,14, 100, 83, 2, 3, 70, 87, 80};
    for(int i=0;i<16;i++)
        copac.addNode(treekeys[i]);

    BST copac2;
    copac.displaySubTree(copac.getRoot());




    RBT copac_rosu;

    copac_rosu.displaySubTree(copac_rosu.getRoot());
    std::cout << '\n';
    copac_rosu.addNode(6);
    copac_rosu.displaySubTree(copac_rosu.getRoot());
    std::cout << '\n';
    copac_rosu.addNode(5);
    copac_rosu.displaySubTree(copac_rosu.getRoot());
    std::cout << '\n';
    copac_rosu.addNode(4);
    copac_rosu.displaySubTree(copac_rosu.getRoot());
    std::cout << '\n';
    copac_rosu.addNode(3);
    copac_rosu.displaySubTree(copac_rosu.getRoot());
    std::cout << '\n';
    copac_rosu.addNode(2);
    copac_rosu.displaySubTree(copac_rosu.getRoot());
    std::cout << '\n';
    copac_rosu.addNode(1);
    copac_rosu.displaySubTree(copac_rosu.getRoot());
    std::cout << '\n';
    copac_rosu.addNode(8);
    copac_rosu.displaySubTree(copac_rosu.getRoot());
    std::cout << '\n';
    copac_rosu.addNode(9);
    copac_rosu.displaySubTree(copac_rosu.getRoot());
    std::cout << '\n';
    RB_Node *n=copac_rosu.getRoot();
    copac_rosu.removeKey(7);
    copac_rosu.displaySubTree(copac_rosu.getRoot());
    std::cout << '\n';


    return 0;
}
