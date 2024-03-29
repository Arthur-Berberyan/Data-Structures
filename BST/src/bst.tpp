#include "bst.hpp"

template <typename T>
BST<T>::~BST() noexcept {
    try {
        deleteTree(root);
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    
}


template <typename T>
void BST<T>::deleteTree(Node* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}


template <typename T>
void BST<T>::insert(T val) {
    if (!root) {
        root = new Node(val);
        return;
    }
    Node* tmp = root;
    Node* tmp2 = nullptr;
    while (tmp && tmp->data != val) {
        tmp2 = tmp;
        if (val < tmp->data) {
            tmp = tmp->left;
        } else {
            tmp = tmp->right;
        }
    }
    if (!tmp) {
        if (val < tmp2->data) {
            tmp2->left = new Node(val);
        } else {
            tmp2->right = new Node(val);
        }
    }
}

// Recursive insertion
// template <typename T>
// TreeNode<T>*  insert(TreeNode<T>* root, T val) {
//      if (!root) {
//         !root = new Node(val);
//         return root;
//     }
//     if (val < root->data) {
//         root->left = insert(root->left, val);
//     } else if (val > root) {
//         root->right = insert(root->right, val);
//     }
//     return root;
// }


template <typename T>
void BST<T>::remove(T val) {
    if (!root) {return;}
    Node* tmp1 = root;
    Node* tmp2 = nullptr;
    while (tmp1 && tmp1->data != val) {
        tmp2 = tmp1;
        if (val < tmp1->data) {
            tmp1 = tmp1->left;
        } else {
            tmp1 = tmp1->right;
        }
    }
    if (!tmp1) {
        return;
    }

    if (!tmp1->left && !tmp1->right) {
        if (tmp1 != root) {
            if (tmp2->data > val) {
                tmp2->left = nullptr;
            } else {
                tmp2->right = nullptr;
            }
        } else {
            root = nullptr;
        }
        delete tmp1;
    } else if (!tmp1->left) {
        Node* tmp3 = tmp1;
        tmp1 = tmp1->right;
        if(tmp3 != root) {
            if (tmp2->left == tmp3) {
                tmp2->left = tmp1;
            } else {
                tmp2->right = tmp1;
            }
        } else {
            root = tmp1;
        }
        delete tmp3;
    } else if (!tmp1->right) {
        Node* tmp3 = tmp1;
        tmp1 = tmp1->left;
        if (tmp3 != root) {
            if (tmp2->left == tmp3) {
                tmp2->left = tmp1;
            } else {
                tmp2->right = tmp1;
            }
        } else {
            root = tmp1;
        }
        delete tmp3;
    } else {
        Node* tmp3 = tmp1;
        Node* tmp4 = tmp1->right;
        while (tmp4->left) {
            tmp3 = tmp4;
            tmp4 = tmp4->left;
        }
        if (tmp3 != tmp1) {
            tmp3->left = tmp4->right;
            tmp4->right = tmp1->right;
        }
        tmp4->left = tmp1->left;
        if (tmp1 != root) {
            if (tmp2->left == tmp1) {
                tmp2->left = tmp4;
            } else {
                tmp2->right = tmp4;
            }
        } else {
            root = tmp4;
        }
        delete tmp1;
    }
}

//Rcursive deletion
// template <typename T>
// TreeNode<T>* remove(TreeNode<T>* root, T val) {
//     if (!root) {return root;}
//     if (val < root->data) {
//         root->left = remove(root->left, val);
//     } else if (val > root->data) {
//         root->right = remove(root->right, val);
//     } else {
//         if (!root->left) {
//             TreeNode<T>* tmp = root->right;
//             delete root;
//             root = tmp;
//         } else if (!root->right) {
//             TreeNode<T>* tmp = root->left;
//             delete root;
//             root = tmp;
//         } 
//         TreeNode<T>* min = root->right;
//         while (min->left) {
//             min = min->left;
//         }
//         root->data = min->data;
//         root->right = remove(root->left, min->data);
//     }
//     return root;
// }


template <typename T>
bool BST<T>::find(T val) {
    if (!root) {
        return false;
    }
    Node* tmp = root;
    while (tmp) {
        if (tmp->data == val) {
            return true;
        }
        if (val < tmp->data) {
            tmp = tmp->left;
        } else {
            tmp = tmp->right;
        }
    }
    return false;
}

// Recursive find
// template <typename T>
// bool find(TreeNode<T>* root, T val) {
//     if (!root) {
//         return false;
//     }
//     if (root->data == val) {
//             return true;
//     }
//     if (val < root->data) {
//         root->left = find(root->left, val);
//     } else {
//         tmp->right = find(root->right, val);
//     }
//     return false;
// }

template <typename T>
int BST<T>::height() {
    if (!root) {return -1;};
    Node* tmp = nullptr;
    std::queue<Node*> qu;
    int height = 0; 
    int size = 0;
    qu.push(root);
    while(!qu.empty()) {
        ++height;
        size = qu.size();
        for (int i = 0; i < size; ++i) {
            tmp = qu.front();
            qu.pop();
            if (tmp->left) {
                qu.push(tmp->left);
            }
            if (tmp->right) {
                qu.push(tmp->right);
            }
        }
    }
    return height;
}

//Recursive height
// template <typename T>
// int height(TreeNode<T>* root) {
//     if (!root) {return -1;};
//     int left = height(root->left;)
//     int right = height(root->right);
//     return std::max(left, right) + 1;
// }
template <typename T>
void BST<T>::inorder() {
    if (!root) {return;}
    Node* tmp = root;
    Node* tmp2 = nullptr;
    while (tmp) {
        if (!tmp->left) {
            std::cout << tmp->data;
            tmp = tmp->right;
        } else {
            tmp2 = tmp->left;
            while (tmp2->right && tmp2->right != tmp) {
                tmp2 = tmp2->right;
            }

            if (!tmp2->right) {
                tmp2->right = tmp;
                tmp = tmp->left;
            } else {
                std::cout << tmp2->right->data;
                tmp2->right = nullptr;
                tmp = tmp->right;
            }
        }
    }
}

//Recursive Inorder traversal
// template <typename T>
// void inorder(TreeNode<T>* root) {
//     if (!root) {return;}
//     inorder(root->left);
//     std::cout << root->data;
//     inorder(root->right);
// }

template <typename T>
void BST<T>::postorder() {
    if (!root) {return;}
    std::stack<Node*> st;
    Node* tmp1 = root;
    Node* tmp2 = nullptr;
    Node* tmp3 = nullptr;
    while (tmp1 || !st.empty()) {
        if (tmp1) {
            st.push(tmp1);
            tmp1 = tmp1->left;
        } else {
            tmp3 = st.top();
            if (tmp3->right && tmp2 != tmp3->right) {
                tmp1 = tmp3->right;
            } else {
                std::cout << tmp3->data;
                tmp2 = tmp3;
                st.pop();
            }
        }
    }
} 

//Recursive Postorder traversal
// template <typename T>
// void inorder(TreeNode<T>* root) {
//     if (!root) {return;}
//     inorder(root->left);
//     inorder(root->right);
//     std::cout << root->data;
// }

template <typename T>
void BST<T>::preorder() {
    if (!root) {return;}
    Node* tmp = root;
    Node* tmp2 = nullptr;
    while (tmp) {
        if (!tmp->left) {
            std::cout << tmp->data;
            tmp = tmp->right;
        } else {
            tmp2 = tmp->left;
            while (tmp2->right && tmp2->right != tmp) {
                tmp2 = tmp2->right;
            }
            if (!tmp2->right) {
                tmp2->right = tmp;
                std::cout << tmp->data;
                tmp = tmp->left;
            } else {
                tmp2->right = nullptr;
                tmp = tmp->right;
            }
        }
    }
}

//Recursive Preorder traversal
// template <typename T>
// void preorder(TreeNode<T>* root) {
//     if (!root) {return;}
//     std::cout << root->data;
//     inorder(root->left);
//     inorder(root->right);
// }

template <typename T>
void BST<T>::levelorder() {
    if (!root) {return;}
    Node* tmp = nullptr;
    std::queue<Node*> qu;
    qu.push(root);
    while(!qu.empty()) {
        tmp = qu.front();
        qu.pop();
        std::cout << tmp->data;
        if (tmp->left) {
            qu.push(tmp->left);
        }
        if (tmp->right) {
            qu.push(tmp->right);
        }
    }
}

template <typename T>
typename BST<T>::Node* BST<T>::getMax(Node* node) {
    while (node->right) {
        node = node->right;
    }
    return node;
}

template <typename T>
typename BST<T>::Node* BST<T>::getMin(Node* node) {
    while (node->left) {
        node = node->left;
    }
    return node;
}

template <typename T>
typename BST<T>::Node* BST<T>::predecessor(Node* node) {
    if (!node) return nullptr;
    if (node->left) {return getMax(node->left);}
    Node* pred = nullptr;
    Node* current = root;
    while (current != node) {
        if (current->data > node->data) {
            current = current->left;
        } else {
            pred = current;
            current = current->right;
        }
    }
    return pred;
}

template <typename T>
typename BST<T>::Node* BST<T>::successor(Node* node) {
    if (!node) return nullptr;
    if (node->right) {return getMin(node->right);}
    Node* succ = nullptr;
    Node* current = root;
    while (current != node) {
        if (current->data < node->data) {
            current = current->right;
        } else {
            succ = current;
            current = current->left;
        }
    }
    return succ;
}

template <typename T>
void BST<T>::printPredAndSucc(T val) {
    Node* tmp = root;
    while (tmp && tmp->data != val) {
        if (tmp->data > val) {
            tmp = tmp->left;
        } else {
            tmp = tmp->right;
        }
    }
    std::cout << predecessor(tmp)->data << std::endl;
    std::cout << successor(tmp)->data << std::endl;
}

