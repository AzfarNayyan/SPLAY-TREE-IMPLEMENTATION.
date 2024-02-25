//AZFAR NAYYAN 
//BSE-3C
//22L-7886 
//DS ASSIGNMENT 04



#include<iostream>
#include<vector>
#include<Windows.h>

using namespace std;


template<class T>
class SpecialBST
{

private:

	struct Node
	{
		T data;
		Node* right;
		Node* left;
		Node* parent;
	public:
		Node()
		{
			left = right = parent = nullptr;
		}
		Node(T e)
		{
			data = e;
			left = right = parent = nullptr;
		}
	};

	Node* root;

	void leftRotate(Node* node) 
	{
		Node* child = node->right;
		node->right = child->left;

		if (child->left != nullptr)
		{
			child->left->parent = node;
		}
		child->parent = node->parent;
		if (node->parent == nullptr)
		{
			this->root = child;
		}
		else if (node == node->parent->left)
		{
			node->parent->left = child;
		}
		else 
		{
			node->parent->right = child;
		}

		child->left = node;
		node->parent = child;
	}

	void rightRotate(Node* node) 
	{
		Node* child = node->left;
		node->left = child->right;

		if (child->right != nullptr) 
		{
			child->right->parent = node;
		}
		child->parent = node->parent;
		if (node->parent == nullptr) 
		{
			this->root = child;
		}
		else if (node == node->parent->right) 
		{
			node->parent->right = child;
		}
		else 
		{
			node->parent->left = child;
		}

		child->right = node;
		node->parent = child;
	}

	void SPLAY_NODE_TO_ROOT(Node* node) 
	{
		if (!node) return;

		while (node->parent)
		{
			if (!node->parent->parent)
			{
				if (node == node->parent->left)//ZIG ROTATION CASE.
				{
					rightRotate(node->parent);  
				}
				else //ZAG ROTATION CASE.
				{
					leftRotate(node->parent);   
				}
			}
			else if (node == node->parent->left && node->parent == node->parent->parent->left) //ZIG-ZIG ROTATION CASE.
			{
				rightRotate(node->parent->parent);  
				rightRotate(node->parent);
			}
			else if (node == node->parent->right && node->parent == node->parent->parent->right) //ZAG-ZAG ROTATION CASE.
			{
				leftRotate(node->parent->parent);   
				leftRotate(node->parent);
			}
			else if (node == node->parent->right && node->parent == node->parent->parent->left) //ZIG-ZAG ROTATION CASE.
			{
				leftRotate(node->parent);   
				rightRotate(node->parent);
			}
			else //ZAG-ZIG ROTATION CASE.
			{
				rightRotate(node->parent);  
				leftRotate(node->parent);
			}
		}
	}

	void deleteR(Node*& node, T e);

	void getPredecessor(Node* node,T& e)
	{
		while (node->right != NULL)
			node = node->right;

		e = node->data;
	}

	void deleteNode(Node*& node)
	{
		T e;
		Node* temp = node;
	
		if (node->left == NULL) 
		{
			node = node->right;
			SPLAY_NODE_TO_ROOT(temp->parent);
			delete temp;
		}
		else if (node->right == NULL) 
		{
			node = node->left;
			SPLAY_NODE_TO_ROOT(temp->parent);
			delete temp;
		}
		else
		{
			getPredecessor(node->left, e);
			node->data = e;
			deleteR(node->left,e);
		}
	}

	void getValuesInVECTOR(vector<T>& v,Node* node)
	{
		if (node)
		{
			getValuesInVECTOR(v, node->left);
			v.push_back(node->data);
			getValuesInVECTOR(v, node->right);
		}
	}

	void getLevelValues(Node* node, int i, vector<T>& v)
	{
		if (node == NULL)
			return;

		if (i == 1)
		{
			v.push_back(node->data);
		}
		else if (i > 1) 
		{
			getLevelValues(node->left, i - 1, v);
			getLevelValues(node->right, i - 1, v);
		}
	}

	void inOrderR(Node* node)
	{
		if (node)
		{
			inOrderR(node->left);
			cout << node->data << " ";
			inOrderR(node->right);
		}
	}
	void preOrderR(Node* node)
	{
		if (node)
		{
			cout << node->data << " ";
			inOrderR(node->left);
			inOrderR(node->right);
		}
	}
	void postOrderR(Node* node)
	{
		if (node)
		{
			inOrderR(node->left);
			inOrderR(node->right);
			cout << node->data << " ";
		}
	}
	void destroy(Node* node)
	{
		if (node == nullptr) return;

		destroy(node->left);
		destroy(node->right);

		delete node;
	}

	int size(Node* node)
	{
		if (node == NULL)
			return 0;
		else
			return(size(node->left) + 1 + size(node->right));
	}
	int height(Node* node)
	{
		if (node == NULL)
			return 0;
		else 
		{
			int lheight = height(node->left);
			int rheight = height(node->right);

			if (lheight > rheight)
				return (lheight + 1);
			else
				return (rheight + 1);
		}
	}


public:
	SpecialBST()              // 1. DEFAULT CONSTRUCTOR.
	{ 
		root = nullptr;
	} 
	void insert(T e)              // 2. INSERTION WITH SPLAYING.
	{
		Node* node = new Node(e);
		
		Node* parent = nullptr;
		Node* child = this->root;

		while (child != nullptr) 
		{
			parent = child;
			if (node->data < child->data) 
			{
				child = child->left;
			}
			else if (node->data == child->data)
			{
				cout << "DUPLICATION!" << endl;
				return;
			}
			else 
			{
				child = child->right;
			}
		}

		node->parent = parent;

		if (parent == nullptr) 
		{
			root = node;
		}
		else if (node->data < parent->data) 
		{
			parent->left = node;
		}
		else
		{
			parent->right = node;
		}

		SPLAY_NODE_TO_ROOT(node);
	}
	bool search(T e)       // 3. SEARCHING WITH SPLAYING.
	{  
		Node* temp_node = root;
		Node* prev_node = nullptr;
		bool flag = false;

		while (temp_node && !flag) 
		{
			if (temp_node->data == e)
			{
				flag = true;
				break;
			}
			else if (temp_node->data > e)
			{
				prev_node = temp_node;
				temp_node = temp_node->left;
			}
			else
			{
				prev_node = temp_node;
				temp_node = temp_node->right;
			}

		}

		if (temp_node == nullptr)
		{
			SPLAY_NODE_TO_ROOT(prev_node);
			return flag;
		}

		SPLAY_NODE_TO_ROOT(temp_node);
		return flag;
	}
	void Delete(T e)        // 4. DELETING WITH SPLAYING.
	{
		if (search(e) == true)
		{
			deleteR(root, e);
			cout << "KEY DELETED !!" << endl;
		}
		else
			cout << "KEY NOT FOUND TO DELETE !!" << endl;
	}

	vector<T> getValuesInOrder()   // 6. GET VALUES IN ORDER IN VECTOR.
	{
		vector<T> temp = {};
		getValuesInVECTOR(temp, root);
		return temp;
	}

	vector<T> getValuesLevelOrder()    // 5. GET VALUES LEVEL ORDER IN VECTOR.
	{ 
		vector<T> v = {};

		int h = height(root);
		for (int i = 1; i <= h; i++)
		{
			getLevelValues(root, i, v);
		}

		return v;
	}



	void inOrderPrint()
	{
		cout << "THE IN-ORDER PRINT IS: ";
		inOrderR(root);
		cout << endl;
	}
	void preOrderPrint()
	{
		cout << "THE PRE-ORDER PRINT IS: ";
		preOrderR(root);
		cout << endl;
	}
	void postOrderPrint()
	{
		cout << "THE POST-ORDER PRINT IS: ";
		postOrderR(root);
		cout << endl;
	}

	void ROOT()
	{
		cout << "root: " << root->data << "." << endl;
	}

	~SpecialBST()  // 7. DESTRUCTOR.
	{
		destroy(root);
	}
};
template<class T>
void SpecialBST<T>::deleteR(Node*& node, T e)
{
	if (e > node->data)
		deleteR(node->right,e);
	else if (e < node->data)
		deleteR(node->left,e);
	else
		deleteNode(node);
}




int main()
{
	//SpecialBST<int> BST;

	//BST.insert(50);
	//BST.insert(40);
	//BST.insert(60);
	//BST.insert(20);
	//BST.ROOT();
	//BST.insert(30);
	//BST.insert(10);
	//BST.insert(80);
	//BST.insert(70);
	//BST.ROOT();
	//BST.insert(100);
	//BST.insert(90);
	//BST.ROOT();

	//BST.inOrderPrint();

	//BST.search(110);
	//BST.ROOT();
	//BST.inOrderPrint();

	//BST.Delete(110);
	//BST.ROOT();
	//BST.inOrderPrint();


	//cout << " IN ORDER ===========" << endl;

	//vector<int> vec = BST.getValuesInOrder();

	//for (int i = 0; i < vec.size(); i++)
	//{
	//	cout << vec.at(i) << " ";
	//}
	//cout << endl;

	//cout << " LEVEL ORDER ===========" << endl;

	//vector<int> v = BST.getValuesLevelOrder();

	//for (int i = 0; i < v.size(); i++)
	//{
	//	cout << v.at(i) << " ";
	//}
	//cout << endl;



	SpecialBST<int> specialBST;

	int choice, value;
	int sleeptime = 1500;

	while (true)
	{

		cout << "1. Insert." << endl;
		cout << "2. Search." << endl;
		cout << "3. Delete." << endl;
		cout << "4. Level Order Print." << endl;
		cout << "5. In Order Print." << endl;
		cout << "6. Exit." << endl;

		cout << "Enter your choice: ";
		cin >> choice;

		if (choice == 1) 
		{
			cout << "Enter value to insert: ";
			cin >> value;

			specialBST.insert(value);
			specialBST.ROOT();
			specialBST.inOrderPrint();

			cout << "Value " << value << " inserted." << endl;
			Sleep(sleeptime);
			system("CLS");
		}
		else if (choice == 2) 
		{
			cout << "Enter value to search: ";
			cin >> value;

			if (specialBST.search(value)) 
			{
				cout << "Value " << value << " found in the tree." << endl;
				specialBST.ROOT();
				specialBST.inOrderPrint();
			}
			else 
			{
				cout << "Value " << value << " not found in the tree.\n";
				specialBST.ROOT();
				specialBST.inOrderPrint();
			}

			Sleep(sleeptime);
			system("CLS");
		}
		else if (choice == 3) 
		{
			cout << "Enter value to delete: ";
			cin >> value;
			specialBST.Delete(value);
			specialBST.ROOT();
			specialBST.inOrderPrint();

			Sleep(sleeptime);
			system("CLS");
		}
		else if (choice == 4) 
		{
			vector<int> levelOrder = specialBST.getValuesLevelOrder();

			cout << "LEVEL ORDER PRINT BY VECTOR: ";
			for (int i = 0; i < levelOrder.size(); i++)
			{
				cout << levelOrder.at(i) << " ";
			}
			cout << endl;

			Sleep(1000);
			system("CLS");
		}
		else if (choice == 5) 
		{
			vector<int> inorder = specialBST.getValuesInOrder();

			cout << "IN ORDER PRINT BY VECTOR: ";
			for (int i = 0; i < inorder.size(); i++)
			{
				cout << inorder.at(i) << " ";
			}
			cout << endl;

			Sleep(1000);
			system("CLS");
		}
		else if (choice == 6) 
		{
			cout << "Exiting program." << endl;
			break;
		}
		else 
		{
			cout << "Invalid choice. Please enter a valid option." << endl;

			Sleep(1000);
			system("CLS");
		}
	}


	system("pause>0");
	return 0;

	//ds 04
}