#include <iostream>
#include <string>
#include <fstream>
#include <functional>

// Customer class containing information and member functions
class Customer {
public:
  // Public member functions
  Customer();
  ~Customer();
  void readInfoFromConsole();
  void readInfoFromFile(const std::string& filePath);
  std::string getName() const;
  std::string toString() const;

private:
  // Private member variables
  std::string name;
  std::string id;
  std::string address;
  std::string phone;
  int membershipLevel;
  double amountSpent;
};

// Node class representing a node in the linked list
class Node {
public:
  // Public member variables
  Customer customer;
  Node* next;

  // Constructor
  Node(const Customer& customer);
};

// Global variable for the head of the linked list
Node* head = nullptr;

// Utility functions
bool compareByName(const Customer& c1, const Customer& c2) {
  return c1.getName() < c2.getName();
}

bool compareByLevel(const Customer& c1, const Customer& c2) {
  return c1.getMembershipLevel() < c2.getMembershipLevel();
}

Node* findNodeById(const std::string& id) {
  Node* current = head;
  while (current) {
    if (current->customer.getId() == id) {
      return current;
    }
    current = current->next;
  }
  return nullptr;
}

void insertNode(const Customer& customer, std::function<bool(Customer, Customer)> compareFun) {
  Node* newNode = new Node(customer);
  Node* prev = nullptr;
  Node* current = head;

  // Find insertion position based on comparison function
  while (current && compareFun(customer, current->customer)) {
    prev = current;
    current = current->next;
  }

  // Insert new node
  if (prev) {
    newNode->next = current;
    prev->next = newNode;
  } else {
    newNode->next = head;
    head = newNode;
  }
}

void deleteNode(Node* node) {
  if (head == node) {
    head = head->next;
  } else {
    Node* prev = head;
    while (prev && prev->next != node) {
      prev = prev->next;
    }
    if (prev) {
      prev->next = node->next;
    }
  }
  delete node;
}

void sortList(Node** headPtr, std::function<bool(Customer, Customer)> compareFun, bool ascending) {
  // Implement a sorting algorithm based on your will dud
  
  // rmber modify the linked list pointed to by headPtr

  // ... Sorting algorithm implementation ...

  cout << "Customer list sorted " << (ascending ? "ascendingly" : "descendingly") << " by " <<
    "membership level" << endl;
}

// Main program functions
void insertCustomer(bool interactive, const std::string& filePath) {
  Customer customer;

  if (interactive) {
    customer.readInfoFromConsole();
  } else {
    customer.readInfoFromFile(filePath);
  }

  insertNode(customer, compareByName);
  cout << "Customer " << customer.getName() << " successfully inserted!" << endl;
}

void deleteCustomer(const std::string& id) {
  cout << "Confirm deletion of customer ID " << id << "? (y/n): ";
  char ch;
  cin >> ch;

  if (tolower(ch) == 'y') {
    Node* node = findNodeById(id);
    if (node) {
      deleteNode(node);
      cout << "Customer with ID " << id << " successfully deleted!" << endl;
    } else {
      cout << "Customer with ID " << id << " not found!" << endl;
    }
  } else {
    cout << "Deletion cancelled." << endl;
  }
}

void sortCustomers(bool sortByLevel = false, bool ascending = true) {
  if (sortByLevel) {
    sortList(&head, compareByLevel, ascending);
  } else {
    sortList(&head, compareByName, ascending);
  }

  cout
