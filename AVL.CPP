#include<iostream>

#define SPACE 10

using namespace std;

class Node {
  public:
    int dato;
    Node * izq;
    Node * der;
    Node();
    Node(int v);
};
Node::Node() {
    dato = 0;
    izq = NULL;
    der = NULL;
}
Node::Node(int v) {
    dato = v;
    izq = NULL;
    der = NULL;
}
class AVLTree {
    public:
    Node * root;
    AVLTree();
    bool arbolVacio();
    int altura(Node * r);
    int getBalanceFactor(Node * n);
    Node* derRotacion(Node * y);
    Node* izqRotacion(Node * x);
    Node* insertar(Node * r, Node * new_node);
    Node* minDatoNode(Node * node);
    Node * deleteNode(Node * r, int v);
    void printArbol(Node * r, int space); 
    void printPreorder(Node * r);
    void printInorder(Node * r);
    void printPostorder(Node * r);
    Node * iterativeSearch(int v);
    Node * recursiveSearch(Node * r, int val);
};
AVLTree::AVLTree(){
    root = NULL;
}
bool AVLTree::arbolVacio() {
    if (root == NULL) {
        return true;
    } else 
        return false;
}
int AVLTree::altura(Node * r) {
    if (r == NULL)
        return -1;
    else {
        int izqAltura = altura(r -> izq);
        int derAltura = altura(r -> der);                                 
        if (izqAltura > derAltura)
            return (izqAltura + 1);
        else return (derAltura + 1);
    }
}
int AVLTree::getBalanceFactor(Node * n) {
    if (n == NULL)
        return -1;
    return altura(n -> izq) - altura(n -> der);
}
Node* AVLTree::derRotacion(Node * y) {
    Node * x = y -> izq;
    Node * T2 = x -> der;
    y -> izq = T2;
    return x;
}
Node* AVLTree::izqRotacion(Node * x) {
    Node * y = x -> der;
    Node * T2 = y -> izq;
    y -> izq = x;
    x -> der = T2;
    return y;
}
Node* AVLTree::insertar(Node * r, Node * new_node) {
    if (r == NULL) {
        r = new_node;
        cout << "dato insertado correctamente" << endl;
        return r;
    }
    if (new_node->dato < r->dato) {
        r -> izq = insertar(r -> izq, new_node);
    } else if (new_node -> dato > r -> dato) {
        r -> der = insertar(r -> der, new_node);
    } else {
        cout << "No se permite valores duplicados!" << endl;
        return r;
    }
    int bf = getBalanceFactor(r);
    if (bf > 1 && new_node -> dato < r -> izq -> dato)
        return derRotacion(r);
    if (bf < -1 && new_node -> dato > r -> der -> dato)
        return izqRotacion(r);
    if (bf > 1 && new_node -> dato > r -> izq -> dato) {
        r -> izq = izqRotacion(r -> izq);
        return derRotacion(r);
    }
    if (bf < -1 && new_node -> dato < r -> der -> dato) {
        r -> der = derRotacion(r -> der);
        return izqRotacion(r);
    }
    return r;
}
Node* AVLTree::minDatoNode(Node * node) {
    Node * actual = node;
    while (actual -> izq != NULL) {
        actual = actual -> izq;
    }
    return actual;
}
Node*AVLTree::deleteNode(Node * r, int v) {
    if (r == NULL) 
        return NULL;
    else if (v < r -> dato) {
        r -> izq = deleteNode(r -> izq, v);
    }
    else if (v > r -> dato) {
        r -> der = deleteNode(r -> der, v);
    }
    else {
        if (r -> izq == NULL) {
            Node * temp = r -> der;
            delete r;
            return temp;
        } else if (r -> der == NULL) {
            Node * temp = r -> izq;
            delete r;
            return temp;
        } else {
            Node * temp = minDatoNode(r -> der);
            r -> dato = temp -> dato;
            r -> der = deleteNode(r -> der, temp -> dato);
        }
    }

    int bf = getBalanceFactor(r);
    if (bf == 2 && getBalanceFactor(r -> izq) >= 0)
        return derRotacion(r);
    else if (bf == 2 && getBalanceFactor(r -> izq) == -1) {
        r -> izq = izqRotacion(r -> izq);
        return derRotacion(r);
    }	
    else if (bf == -2 && getBalanceFactor(r -> der) <= -0)
        return izqRotacion(r);
    
    else if (bf == -2 && getBalanceFactor(r -> der) == 1) {
        r -> der = derRotacion(r -> der);
        return izqRotacion(r);
    }
    return r;
}
void AVLTree::printArbol(Node * r, int space) {
    if (r == NULL) 
        return;
    space += SPACE; 
    printArbol(r->der, space); 
    cout << endl;
    for (int i = SPACE; i < space; i++) 
        cout << " "; 
    cout << r -> dato << "\n"; 
    printArbol(r -> izq, space); 
}
void AVLTree::printPreorder(Node * r){
    if (r == NULL)
        return;
    cout << r->dato << " ";
    printPreorder(r->izq);
    printPreorder(r->der);
}
void AVLTree::printInorder(Node * r){
    if (r == NULL)
        return;
    printInorder(r -> izq);
    cout << r -> dato << " ";
    printInorder(r -> der);
}
void AVLTree::printPostorder(Node * r) {
    if (r == NULL)
        return;
    printPostorder(r -> izq);
    printPostorder(r -> der);
    cout << r -> dato << " ";
}

Node* AVLTree::iterativeSearch(int v) {
    if (root == NULL) {
        return root;
    } else {
    Node * temp = root;
    while (temp != NULL) {
        if (v == temp -> dato) {
            return temp;
        } else if (v < temp -> dato) {
            temp = temp -> izq;
        } else {
            temp = temp -> der;
        }
    }
    return NULL;
    }
}
Node* AVLTree::recursiveSearch(Node * r, int val) {
    if (r == NULL || r -> dato == val)
        return r;
    else if (val < r -> dato)
        return recursiveSearch(r -> izq, val);
    else
        return recursiveSearch(r -> der, val);
}
int main() {
    AVLTree obj;
    int option, val;

    do{
        cout << "Que operacion desea realizar? " <<
        " Seleccione el numero de opcion. Ingrese 0 para salir." << endl;
        cout << "1. Insertar Nodo" << endl;
        cout << "2. Buscar Nodo" << endl;
        cout << "3. Eliminar Nodo" << endl;
        cout << "4. Imprimir/Traversal datos arbol AVL" << endl;
        cout << "5. Altura del arbol" << endl;
        cout << "6. Limpiar pantalla" << endl;
        cout << "0. Salir del programa" << endl;

        cin >> option;
        
        Node * new_node = new Node();

        switch (option) {
            case 0:
                break;
            case 1:
                cout << "Insertar AVL" << endl;
                cout << "Ingrese el dato del nodo del arbol para insertar en el arbol AVL: ";
                cin >> val;
                new_node -> dato = val;
                obj.root = obj.insertar(obj.root, new_node);
                cout << endl;
                break;
            case 2:
                cout << "Buscar" << endl;
                cout << "Ingrese el valor del nodo del arbol para buscar en el arbol AVL: ";
                cin >> val;
                new_node = obj.recursiveSearch(obj.root, val);
                if (new_node != NULL) {
                    cout << "Valor encontrado" << endl;
                } else {
                    cout << "Valor no encontrado" << endl;
                }
                break;
            case 3:
                cout << "Eliminar" << endl;
                cout << "Ingrese el valor del nodo del arbol para borrar en AVL: ";
                cin >> val;
                new_node = obj.recursiveSearch(obj.root, val);
                if (new_node != NULL) {
                    obj.root = obj.deleteNode(obj.root, val);
                    cout << "Valor eliminado" << endl;
                } else {
                    cout << "Valor no encontrado" << endl;
                }
                break;
            case 4:
                cout << "Imprimir: " << endl;
                obj.printArbol(obj.root, 5);
                cout << endl;
                break;
            case 5:
                cout << "Altura del arbol" << endl;
                cout << "Altura : " << obj.altura(obj.root) << endl;
                break;
            case 6:
                system("cls");
                break;
            default:
                cout << "Ingrese el numero de opcion adecuado " << endl;
        }

    } while (option != 0);

  return 0;
} 