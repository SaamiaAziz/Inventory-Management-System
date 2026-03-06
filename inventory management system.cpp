#include <iostream>//for input output
#include <string>//for text 
#include <iomanip>//formating input output
#include <fstream>  // For file operations
#include <sstream>  // For string stream operations
#include <cstdlib>  // For atoi and atof functions

using namespace std;

// ANSI Escape Codes for coloring the output
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"

// Structure for storing item details
struct InventoryItem {
    int itemID;
    string itemName;
    int quantity;
    double price;

    InventoryItem(int id, string name, int qty, double pr)
        : itemID(id), itemName(name), quantity(qty), price(pr) {}
};

// Node structure for Linked List
struct Node {
    InventoryItem item;
    Node* next;

    Node(int id, string name, int qty, double pr)
        : item(id, name, qty, pr), next(NULL) {}
};

// Linked List class to manage inventory
class LinkedListInventory {
private:
    Node* head;

public:
    LinkedListInventory() : head(NULL) {}

    // Add item to the list
    void addItem(int id, const string& name, int qty, double pr) {
        Node* newNode = new Node(id, name, qty, pr);
        newNode->next = head;
        head = newNode;
        cout << GREEN << "Item added successfully to Linked List!" << RESET << "\n";
    }

    // Update item in the list
    void updateItem(int id, int newQty, double newPrice) {
        Node* current = head;
        while (current != NULL) {
            if (current->item.itemID == id) {
                current->item.quantity = newQty;
                current->item.price = newPrice;
                cout << GREEN << "Item updated successfully in Linked List!" << RESET << "\n";
                return;
            }
            current = current->next;
        }
        cout << RED << "Item with ID " << id << " not found in Linked List!" << RESET << "\n";
    }

    // View all items in the list
    void viewInventory() {
        if (head == NULL) {
            cout << RED << "No items in inventory (Linked List)!" << RESET << "\n";
            return;
        }
        cout << BLUE << "Inventory List (Linked List):" << RESET << "\n";
        cout << "ID\tName\t\tQuantity\tPrice\n";
        cout << "-----------------------------------------\n";
        Node* current = head;
        while (current != NULL) {
            cout << current->item.itemID << "\t" << current->item.itemName << "\t\t"
                 << current->item.quantity << "\t\t" << fixed << setprecision(2) << current->item.price << "\n";
            current = current->next;
        }
    }

    // Delete item from the list
    void deleteItem(int id) {
        Node* current = head;
        Node* prev = NULL;
        while (current != NULL && current->item.itemID != id) {
            prev = current;
            current = current->next;
        }

        if (current == NULL) {
            cout << RED << "Item not found in Linked List." << RESET << "\n";
            return;
        }

        if (prev == NULL) {
            head = current->next;
        } else {
            prev->next = current->next;
        }
        delete current;
        cout << GREEN << "Item deleted from Linked List!" << RESET << "\n";
    }

    // Search item by ID
    void searchItem(int id) {
        Node* current = head;
        bool found = false;
        cout << BLUE << "Search Results:" << RESET << "\n";
        cout << "-----------------------------------------\n";
        cout << "ID\tName\t\tQuantity\tPrice\n";
        cout << "-----------------------------------------\n";
        
        while (current != NULL) {
            if (current->item.itemID == id) {
                cout << current->item.itemID << "\t" << current->item.itemName << "\t\t"
                     << current->item.quantity << "\t\t" << fixed << setprecision(2) << current->item.price << "\n";
                found = true;
                break;
            }
            current = current->next;
        }

        if (!found) {
            cout << RED << "Item with ID " << id << " not found in Linked List!" << RESET << "\n";
        }
    }

    // Save inventory to file
    void saveToFile(const string& filename) {
        ofstream file(filename.c_str()); // Use c_str() for compatibility
        if (!file) {
            cout << RED << "Failed to open file for writing." << RESET << "\n";
            return;
        }
        Node* current = head;
        while (current != NULL) {
            file << current->item.itemID << ","
                 << current->item.itemName << ","
                 << current->item.quantity << ","
                 << current->item.price << "\n";
            current = current->next;
        }
        file.close();
        cout << GREEN << "Inventory saved to file." << RESET << "\n";
    }

    // Load inventory from file
    void loadFromFile(const string& filename) {
        ifstream file(filename.c_str()); // Use c_str() for compatibility
        if (!file.is_open()) {
            cout << RED << "Failed to open the file." << RESET << "\n";
            return;
        }

        int id, qty;
        double price;
        string name;
        string line;

        cout << "\n" << BLUE << "Inventory Table:" << RESET << "\n";
        cout << "-----------------------------------------\n";
        cout << "ID\tName\t\tQuantity\tPrice\n";
        cout << "-----------------------------------------\n";

        while (getline(file, line)) {
            stringstream ss(line);
            string token;
            getline(ss, token, ',');
            id = atoi(token.c_str()); // Use atoi for compatibility
            getline(ss, token, ',');
            name = token;
            getline(ss, token, ',');
            qty = atoi(token.c_str()); // Use atoi for compatibility
            getline(ss, token, ',');
            price = atof(token.c_str()); // Use atof for compatibility

            addItem(id, name, qty, price);

            // Print in tabular format
            cout << id << "\t" << name << "\t\t" << qty << "\t\t" << fixed << setprecision(2) << price << "\n";
        }
        file.close();
        cout << "-----------------------------------------\n";
        cout << GREEN << "Inventory loaded from file." << RESET << "\n";
    }
};

// Function to display menu
void showMenu() {
    cout << "\n" << YELLOW << "Inventory Management System" << RESET << "\n";
    cout << "1. Add Item (Linked List)\n";
    cout << "2. Update Item (Linked List)\n";
    cout << "3. View Inventory (Linked List)\n";
    cout << "4. Delete Item (Linked List)\n";
    cout << "5. Search Item (Linked List)\n"; 
    cout << "6. Save Inventory to File\n";  // Save to file option
    cout << "7. Load Inventory from File\n";  // Load from file option
    cout << "8. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    LinkedListInventory linkedListSystem;
    string filename = "inventory.txt";  // File name where inventory will be saved/loaded

    // Load inventory from file when the program starts
    linkedListSystem.loadFromFile(filename);

    int choice;
    while (true) {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                // Add item to Linked List
                int id, qty;
                string name;
                double price;
                cout << "Enter item ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter item name: ";
                getline(cin, name);
                cout << "Enter quantity: ";
                cin >> qty;
                cout << "Enter price: ";
                cin >> price;
                linkedListSystem.addItem(id, name, qty, price);
                break;
            }
            case 2: {
                // Update item in Linked List
                int id, qty;
                double price;
                cout << "Enter item ID to update: ";
                cin >> id;
                cout << "Enter new quantity: ";
                cin >> qty;
                cout << "Enter new price: ";
                cin >> price;
                linkedListSystem.updateItem(id, qty, price);
                break;
            }
            case 3: {
                // View inventory in Linked List
                linkedListSystem.viewInventory();
                break;
            }
            case 4: {
                // Delete item from Linked List
                int id;
                cout << "Enter item ID to delete: ";
                cin >> id;
                linkedListSystem.deleteItem(id);
                break;
            }
            case 5: {
                // Search item in Linked List
                int id;
                cout << "Enter item ID to search: ";
                cin >> id;
                linkedListSystem.searchItem(id);
                break;
            }
            case 6: {
                // Save inventory to file
                linkedListSystem.saveToFile(filename);
                break;
            }
            case 7: {
                // Load inventory from file
                linkedListSystem.loadFromFile(filename);
                break;
            }
            case 8: {
                cout << GREEN << "Exiting the system." << RESET << "\n";
                return 0;
            }
            default:
                cout << RED << "Invalid choice. Please try again." << RESET << "\n";
        }
    }
    return 0;
}
