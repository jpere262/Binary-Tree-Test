#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include "Main_Menu.h"
#include <mmstream.h>

using namespace std;

// Function to move console cursor
void gotoxy(int x, int y) {
	if (x >= 0 && y >= 0) {
		COORD kursor;
		kursor.X = x;
		kursor.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), kursor);
	}
}

// Creates class for node
class Node
{
public:
	// Holds value for node
	int num;
	// Right node child
	Node* right;
	// Left node child
	Node* left;

	// Constructors for node
	Node() { right = nullptr; left = nullptr; }
	Node(int c) { right = nullptr; left = nullptr;  num = c; }
};

// Creates class for binary tree
class BinaryTree
{
public:
	// Pre-order traversal
	void LNR(Node* N);
	// In-order traversal
	void LRN(Node* N);
	// Post-order traversal
	void NLR(Node* N);
	// Inserts node into binary tree
	Node* insertNode(Node* N, int INPUT);
	// Removes node from binary tree
	Node* removeNode(Node* N, int INPUT);
};

// Pre-order traversal
void BinaryTree::NLR(Node* N)
{
	cout << N->num << " ";
	if (N->left != nullptr)
		NLR(N->left);
	if (N->right != nullptr)
		NLR(N->right);
}

// In-order traversal
void BinaryTree::LNR(Node* N)
{
	if (N->left != nullptr)
		LNR(N->left);
	cout << N->num<<" ";
	if (N->right != nullptr)
		LNR(N->right);
}

// Post-order traversal
void BinaryTree::LRN(Node* N)
{
	if (N->left != nullptr)
		LRN(N->left);
	if (N->right != nullptr)
		LRN(N->right);
	cout << N->num<<" ";
}

// Inserts node into binary tree
Node* BinaryTree::insertNode(Node* N, int INPUT)
{
	// If no node exists, adds new node
	if (N == nullptr)
	{
		N = new Node(INPUT);
	}
	// If input is less than current node, move left
	else if (INPUT < N->num)
	{
		N->left = insertNode(N->left, INPUT);
	}
	// If input is equal or greater than current node, move right
	else
	{ 
		N->right = insertNode(N->right, INPUT);
	}
	return N;
}

// Removes node from binary tree
Node* BinaryTree::removeNode(Node* N, int INPUT)
{
	if (N == nullptr)
	{
		return N;
	}
	// Recurse through left if input is less than current node
	if (N->num > INPUT)
	{
		N->left = removeNode(N->left, INPUT);
	}
	// Recurse through right if input is greater than node
	else if (N->num < INPUT)
	{
		N->right = removeNode(N->right, INPUT);
	}
	else
	{
		// Does not remove value if it does not exist
		if (N->left == nullptr && N->right == nullptr)
		{
			return nullptr;
		}
		// If no left child exists, sets current node equal to right child
		else if (N->left == nullptr)
		{
			Node* tempNode = N->right;
			delete(N);
			return tempNode;
		}
		// If no right child exists, sets current node equal to left child
		else if (N->right == nullptr)
		{
			Node* tempNode = N->left;
			delete(N);
			return tempNode;
		}

		// Moves down the right path of selected node to be deleted and searches for the lowest value (left) in that path
		Node* current = N->right;
		while (current && current->left != nullptr)
		{
			// Sets current node to current left
			current = current->left;
		}

		Node* tempNode = current;

		// Sets current node number to temp node number
		N->num = tempNode->num;
		N->right = removeNode(N->right, tempNode->num);
	}
	return N;
}


// Definition for moveHorizontal
void moveHorizontal(int x1, int y1, int x2, int y2)
{
	int d = 0;

	// If moving down
	if (y1 < y2)
	{
		// Moves from left to right until x2 position is reached (for moving down then right)
		while (x1 + d <= x2)
		{
			// Displayscharacter
			gotoxy(x1 + d, y2);
			cout << char(205);
			// Moves character one position to the right
			d++;
		}
		// Shows final position of character
		gotoxy(x2, y2);
		cout << char(205);
	}
	// If moving up
	else if (y1 > y2)
	{
		// Moves from left to right until x2 postion is reached (for moving right then up)
		while (x1 + d <= x2)
		{
			// Displays character
			gotoxy(x1 + d, y1);
			cout << char(205);
			// Moves character one position to the right
			d++;
		}
		// Shows final position of character
		gotoxy(x2, y1);
		cout << char(205);
	}
}

// Definition for moveVertical
void moveVertical(int x1, int y1, int x2, int y2)
{
	// If moving down
	if (y1 < y2)
	{
		int d = 0;
		// Moves down until y2 postion is reached
		while (y1 + d <= y2)
		{
			// Displays character
			gotoxy(x1, y1 + d);
			cout << char(205);
			// Moves character one position to the right
			d++;
		}
		// Shows final position of character
		gotoxy(x1, y2);
		cout << char(205);
	}
}
void DisplayTree(Node* N, int xpos, int ypos, int width, int prevXPos, int prevYPos)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (N == nullptr)
		return;
	
	SetConsoleTextAttribute(hConsole, 12);

	gotoxy(xpos - 1, ypos-1+15);
	cout << char(201);
	// Top part of border
	gotoxy(xpos, ypos-1+15);
	for (int i = 0; i < 4; i++)
	{
		cout << char(205);
	}
	// Sides of border
	for (int i = 0; i < 1; i++)
	{
		gotoxy(xpos - 1, ypos + i+15);
		cout << char(186) << "    " << char(186) << endl;
	}
	// Bottom part of border
	gotoxy(xpos, ypos+1+15);
	for (int i = 0; i < 4; i++)
	{
		cout << char(205);
	}
	gotoxy(xpos - 1, ypos + 1+15);
	cout << char(200)<<endl;
	gotoxy(xpos+4, ypos-1+15);
	cout << char(187);
	gotoxy(xpos + 4, ypos + 1+15);
	cout << char(188);
	// Link if node is to the left of previous node
	if (xpos != prevXPos)
	{
		gotoxy(xpos + 2, ypos - 2+15);
		cout << char(186);
	}
	gotoxy(prevXPos + 1, prevYPos + 2+15);
	cout << char(186);
	// Link if node is to the right of previous node
	if (xpos < prevXPos)
	{
		int j = 2;
		for (int i = xpos; i < prevXPos; i++)
		{
			
			gotoxy(xpos + j, ypos - 3+15);
			cout << char(205);
			j++;
		}
	}
	if (xpos > prevXPos)
	{
		int j = 2;
		for (int i = xpos + 1; i >= prevXPos; i--)
		{
			gotoxy(xpos + 4 - j, ypos - 3+15);
			cout << char(205);
			j++;
		}
	}
	if (width < 1)
	{
		gotoxy(prevXPos + 1, prevYPos + 3+15);
		cout << char(186);
		gotoxy(prevXPos + 1, prevYPos + 4+15);
		cout << char(186);
	}
	// Displays node value
	gotoxy(xpos, ypos+15);
	SetConsoleTextAttribute(hConsole, 14);
	cout << N->num;
	SetConsoleTextAttribute(hConsole, 15);
	width = width / 2;
	// Recurses through all nodes in tree
	DisplayTree(N->right, xpos + width, ypos + 6, width, xpos, ypos);
	DisplayTree(N->left, xpos - width, ypos + 6, width, xpos, ypos);
}

// Counts number of leaf nodes in the tree
int CounterLeafNode(Node* N)
{
	if (N == nullptr)
		return 0;
	// Adds 1 to leaf node count if there are no children on current node
	if (N->left == nullptr && N->right == nullptr)
		return 1;
	else
		return CounterLeafNode(N->left) + CounterLeafNode(N->right);
}

// Counts total number of nodes in the tree
int CounterTotalNode(Node* N)
{
	if (N == nullptr)
		return 0;
	else
	{
		// Adds one recursively every time there is a node
		return  1 + CounterTotalNode(N->left) + CounterTotalNode(N->right);
	}
}

// Program to display graphical outputs of binary tree
void DisplayAllOutputs(Node* root, BinaryTree Tree1)
{
	system("cls");

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Displays title of program in ASCII
	SetConsoleTextAttribute(hConsole, 3);
	gotoxy(0, 0);
	cout << R"(
            $$$$$$$\  $$\                                               $$$$$$$$\                            
            $$  __$$\ \__|                                              \__$$  __|                           
            $$ |  $$ |$$\ $$$$$$$\   $$$$$$\   $$$$$$\  $$\   $$\          $$ | $$$$$$\   $$$$$$\   $$$$$$\  
            $$$$$$$\ |$$ |$$  __$$\  \____$$\ $$  __$$\ $$ |  $$ |         $$ |$$  __$$\ $$  __$$\ $$  __$$\ 
            $$  __$$\ $$ |$$ |  $$ | $$$$$$$ |$$ |  \__|$$ |  $$ |         $$ |$$ |  \__|$$$$$$$$ |$$$$$$$$ |
            $$ |  $$ |$$ |$$ |  $$ |$$  __$$ |$$ |      $$ |  $$ |         $$ |$$ |      $$   ____|$$   ____|
            $$$$$$$  |$$ |$$ |  $$ |\$$$$$$$ |$$ |      \$$$$$$$ |         $$ |$$ |      \$$$$$$$\ \$$$$$$$\ 
            \_______/ \__|\__|  \__| \_______|\__|       \____$$ |         \__|\__|       \_______| \_______|
                                                        $$\   $$ |                                           
                                                       \$$$$$$  |                                           
                                                        \______/                                                   

                       )" << endl;
	// Creates legend and border for additional information (LNR, LRN, NLR)
	SetConsoleTextAttribute(hConsole, 14);
	gotoxy(30, 13);
	for (int i = 0; i < 60; i++)
	{
		cout << char(196);
	}
	gotoxy(31, 15);
	SetConsoleTextAttribute(hConsole, 14);
	cout << "Additional Information:" << endl;
	gotoxy(31, 16);
	for (int i = 0; i < 23; i++)
	{
		cout << char(205);
	}
	gotoxy(31, 17);
	SetConsoleTextAttribute(hConsole, 02);
	cout << "LNR:";
	gotoxy(31, 18);
	SetConsoleTextAttribute(hConsole, 15);
	Tree1.LNR(root);
	gotoxy(31,20);
	SetConsoleTextAttribute(hConsole, 04);
	cout << "LRN:";
	gotoxy(31, 21);
	SetConsoleTextAttribute(hConsole, 15);
	Tree1.LRN(root);
	gotoxy(31, 23);
	SetConsoleTextAttribute(hConsole, 05);
	cout << "NLR:";
	gotoxy(31, 24);
	SetConsoleTextAttribute(hConsole, 15);
	Tree1.NLR(root);
	gotoxy(31, 26);
	cout << "Leaf Nodes: ";
	SetConsoleTextAttribute(hConsole, 11);
	cout<< CounterLeafNode(root);
	gotoxy(31, 27);
	SetConsoleTextAttribute(hConsole, 15);
	cout << "Total Nodes: ";
	SetConsoleTextAttribute(hConsole, 11);
	cout<< CounterTotalNode(root);
	gotoxy(31, 28);
	SetConsoleTextAttribute(hConsole, 15);
	cout << "Parent Nodes: ";
	SetConsoleTextAttribute(hConsole, 11);
	cout<< CounterTotalNode(root) - CounterLeafNode(root);
	gotoxy(31, 29);
	SetConsoleTextAttribute(hConsole, 15);
	cout << "Child Nodes: ";
	SetConsoleTextAttribute(hConsole, 11);
	cout<< CounterTotalNode(root) - 1;
	SetConsoleTextAttribute(hConsole, 15);

	DisplayTree(root, 60, 21, 40, 60, 21);

	SetConsoleTextAttribute(hConsole, 14);
	gotoxy(30, 33);
	for (int i = 0; i < 60; i++)
	{
		cout << char(196);
	}

	SetConsoleTextAttribute(hConsole, 15);
}

void main()
{
	// Play music in background while program is running, looped
	PlaySound(TEXT("music.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	
	// Main menu driver
	MainMenu();

	// Clear screen
	system("cls");

	int input;
	int input2;
	string command;
	
	BinaryTree Tree1;

	// Initalizes root to null
	Node* root = nullptr;

	// Opens input text file
	//ifstream inputFile("c:\\temp\\input.txt");
	ifstream inputFile("input.txt");

	// Reads through end of input text file
	while (!inputFile.eof())
	{
		// Reads input text
		inputFile >> input;
		if (input != -1)
		{
			// Inserts input into tree
			root = Tree1.insertNode(root, input);
		}
		// Stops reading if -1 is at the end
		if (input == -1)
		{
			break;
		}
	}

	// Displays outputs of binary tree
	DisplayAllOutputs(root, Tree1);
	
	while (1)
	{
		gotoxy(31, 31);
		cout << "Type ADD 'x' or REMOVE 'x'		Example: ADD 2";
		gotoxy(31, 32);
		cin >> command >> input2;
		
		// Adds user input into the binary tree
		if (command == "ADD" || command == "add")
		{
			root = Tree1.insertNode(root, input2);

			system("cls");

			DisplayAllOutputs(root, Tree1);
		}
		// Removes user input from binary tree, if it exists
		if (command == "REMOVE" || command == "remove")
		{
			root = Tree1.removeNode(root, input2);

			system("cls");

			DisplayAllOutputs(root, Tree1);
		}
	}
}