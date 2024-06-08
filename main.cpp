#include <iostream>
#include <fstream>

using namespace std;

// Define a class named 'grocery' to manage grocery store operations
class grocery {
private:
    int product_id; // Unique identifier for each product
    float price;    // Price of the product
    float discount; // Discount percentage for the product
    string product_name; // Name of the product

public:
    grocery() {} // Constructor

    // Function prototypes
    void menu();        // Main menu for the program
    void manager();     // Manager's menu
    void customer();    // Customer's menu
    void add();         // Add a new product
    void edit();        // Edit an existing product
    void remove();      // Remove a product
    void list();        // List all available products
    void receipt();     // Generate a receipt for customer's purchase
};

// Function to display the main menu and handle user's choice
void grocery::menu() {
    int choice;
    string username;
    string password;

    // Display main menu options
    cout << "\n________________________________________\n";
    cout << "|               Main Menu              |\n";
    cout << "________________________________________\n";
    cout << "| 1) Manager                           |\n";
    cout << "| 2) Customer                          |\n";
    cout << "| 3) Exit                              |\n";
    cout << "________________________________________\n";
    cout << "\nPlease select an option -";
    cin >> choice;

    // Process user's choice
    switch (choice) {
        case 1: {
            // Manager login
            cout << "\nPlease Enter Your Credentials: -\n";
            cout << "Username -";
            cin >> username;
            cout << "Password -";
            cin >> password;

            if (username == "username" && password == "password") {
                cout << "\nLogin Successful!\n";
                manager(); // Proceed to manager's menu
            } else {
                cout << "\nInvalid Credentials!\n";
                menu(); // Return to main menu
            }
            break;
        }
        case 2: {
            // Customer menu
            customer();
            break;
        }
        case 3: {
            exit(0); // Exit the program
        }
        default: {
            cout << "\nPlease choose from the given options!\n";
            menu(); // Return to main menu for invalid choices
            break;
        }
    }
}

// Function to handle manager's operations
void grocery::manager() {
    int choice;

    // Display manager's menu options
    while (true) {
        cout << "\n________________________________________\n";
        cout << "|                Manager               |\n";
        cout << "________________________________________\n";
        cout << "| 1) Add Product                       |\n";
        cout << "| 2) Edit Product                      |\n";
        cout << "| 3) Remove Product                    |\n";
        cout << "| 4) Go back to the Main Menu          |\n";
        cout << "________________________________________\n";
        cout << "\nPlease select an option -";
        cin >> choice;

        // Process manager's choice
        switch(choice) {
            case 1: {
                add(); // Add a new product
                break;
            }
            case 2: {
                edit(); // Edit an existing product
                break;
            }
            case 3: {
                remove(); // Remove a product
                break;
            }
            case 4: {
                menu(); // Go back to the main menu
                break;
            }
            default: {
                cout << "\nPlease choose from the given options!\n";
                break;
            }
        }
    }
}

// Function to handle customer's operations
void grocery::customer() {
    int choice;

    // Display customer menu options
    while (true) {
        cout << "\n________________________________________\n";
        cout << "|               Customer               |\n";
        cout << "________________________________________\n";
        cout << "| 1) Buy Product                       |\n";
        cout << "| 2) Go back to the Main Menu          |\n";
        cout << "________________________________________\n";
        cout << "\nPlease select an option -";
        cin >> choice;

        // Process customer's choice
        switch (choice) {
            case 1: {
                receipt(); // Generate a receipt for purchase
                break;
            }
            case 2: {
                menu(); // Go back to the main menu
                break;
            }
            default: {
                cout << "\nPlease choose from the given options!\n";
                break;
            }
        }
    }
}

// Function to add a new product
void grocery::add() {
    m:
    fstream data;
    int token=0;
    int c;
    string n;
    float p;
    float d;

    // Prompt user to enter product details
    cout << "\n________________________________________\n";
    cout << "|           Add a New Product          |\n";
    cout << "________________________________________\n";
    cout << "1) Product ID -";
    cin >> product_id;
    cout << "2) Product Name -";
    cin >> product_name;
    cout << "3) Price -";
    cin >> price;
    cout << "4) Discount -";
    cin >> discount;

    // Open products file
    data.open("products.txt", ios::app | ios::in);

    // If file doesn't exist, create it and add product details
    if (!data) {
        data.open("products.txt", ios::app | ios::out);
        data << product_id << " " << product_name << " " << price << " " << discount << "\n";
        data.close();
    }
    else {
        // If file exists, check for duplicate product IDs
        data >> c >> n >> p >> d;
        while (!data.eof()) {
            if (c == product_id) {
                token++;
            }
            data >> c >> n >> p >> d;
        }
        data.close();
    }

    // If duplicate product ID found, prompt user to re-enter details
    if (token == 1) {
        goto m;
    }
    else {
        // Otherwise, add product details to the file
        data.open("products.txt", ios::app | ios::out);
        data << " " << product_id << " " << product_name << " " << price << " " << discount << "\n";
        data.close();
    }
    cout << "\nProduct Added Successfully!\n";
}

// Function to edit an existing product
void grocery::edit() {
    fstream data, data1;
    int token = 0;
    int product_key;
    int c;
    string n;
    float p;
    float d;

    // Prompt user to enter product ID for editing
    cout << "\n________________________________________\n";
    cout << "|             Edit a Product           |\n";
    cout << "________________________________________\n";
    cout << "Product ID -";
    cin >> product_key;

    // Open products file
    data.open("products.txt", ios::in);

    // If file doesn't exist, display error message
    if (!data) {
        cout << "\nFile doesn't exist!\n";
    }
    else {
        // Open temporary file for writing edited data
        data1.open("products1.txt", ios::app | ios::out);
        data >> product_id >> product_name >> price >> discount;

        // Loop through file to find product to be edited
        while (!data.eof()) {
            if (product_key == product_id) {
                // Prompt user to enter new product details
                cout << "\nNew Product Code -";
                cin >> c;
                cout << "New Product Name -";
                cin >> n;
                cout << "New Price -";
                cin >> p;
                cout << "New Discount -";
                cin >> d;
                // Write edited data to temporary file
                data1 << " " << c << " " << n << " " << p << " " << d << "\n";
                cout << "\nProduct Edited!\n";
                token++;
            }
            else {
                // Copy existing data to temporary file
                data1 << " " << product_id << " " << product_name << " " << price << " " << discount << "\n";
            }
            data >> product_id >> product_name >> price >> discount;
        }
        // Close file streams
        data.close();
        data1.close();

        // Replace original file with edited data
        ::remove("products.txt");
        rename("products1.txt", "products.txt");

        // If product not found, display error message
        if (token == 0) {
            cout << "\nNo Product Records Found!\n";
        }
    }
}

// Function to remove a product from the inventory
void grocery::remove() {
    fstream data, data1;
    int token = 0;
    int product_key;

    // Prompt user to enter product ID for removal
    cout << "\n________________________________________\n";
    cout << "|           Remove a Product           |\n";
    cout << "________________________________________\n";
    cout << "Product ID - ";
    cin >> product_key;

    // Open products file
    data.open("products.txt", ios::in);

    // If file doesn't exist, display error message
    if (!data) {
        cout << "File doesn't exist!";
    }
    else {
        // Open temporary file for writing updated data
        data1.open("products1.txt", ios::app | ios::out);
        data >> product_id >> product_name >> price >> discount;

        // Loop through file to find product to be removed
        while (!data.eof()) {
            if (product_key == product_id) {
                cout << "\nProduct Removed successfully!\n";
                token++;
            }
            else {
                // Copy existing data to temporary file
                data1 << " " << product_id << " " << product_name << " " << price << " " << discount << "\n";
            }
            data >> product_id >> product_name >> price >> discount;
        }
        // Close file streams
        data.close();
        data1.close();

        // Replace original file with updated data
        ::remove("products.txt");
        rename("products1.txt", "products.txt");

        // If product not found, display error message
        if (token == 0) {
            cout << "\nNo Product Records Found!\n";
        }
    }
}

// Function to list all available products
void grocery::list() {
    fstream data;
    data.open("products.txt", ios::in);
    cout << "\n\n";
    cout << "Product ID\tProduct Name\tPrice";
    cout << "\n\n";
    data >> product_id >> product_name >> price >> discount;

    // Loop through file to display product details
    while (!data.eof()) {
        cout << product_id << "\t\t" << product_name << "\t\t" << "$" << price << "\n";
        data >> product_id >> product_name >> price >> discount;
    }
    data.close();
}

// Function to generate a receipt for customer's purchase
void grocery::receipt() {
    m:
    fstream data;
    int arrc[100];
    int arrq[100];
    char choice;
    float amount = 0;
    float total = 0;
    float net = 0;
    int c = 0;
    int j = 0;

    // Display available products for purchase
    cout << "\n________________________________________\n";
    cout << "|             ALL PRODUCTS             |\n";
    cout << "________________________________________";
    data.open("products.txt", ios::in);

    // If file doesn't exist, display error message
    if (!data) {
        cout << "\n Empty database";
    } else {
        data.close();
    }

    list(); // Display available products
    cout << "\n________________________________________\n";
    cout << "|       Please place your Order        |\n";
    cout << "________________________________________\n";

    // Prompt user to enter product codes and quantities
    do {
        cout << "\nEnter Product code -";
        cin >> arrc[j];
        cout << "\nEnter the product quantity -";
        cin >> arrq[j];
        // Check for duplicate product codes
        for (int i = 0; i < j; i++) {
            if (arrc[i] == arrc[j]) {
                cout << "\n\n Duplicate product code. Please try again!";
                goto m;
            }
        }
        // Prompt user for further orders
        cout << "\nDo you want to Purchase another Product? If 'Yes', then Press Y/y else Press N/n for 'No' :";
        cin >> choice;
        j++;
    }
    while (choice == 'y' || choice == 'Y');

    // Display receipt header
    cout << "\n________________________________________________________________\n";
    cout << "|                           RECEIPT                            |\n";
    cout << "________________________________________________________________\n";
    cout << "\nP_ID    P_Name  Qty     Price   Amount  Net Total with Discounts\n";

    // Loop through selected products to calculate total amount
    for (int i = 0; i < j; i++) {
        data.open("products.txt", ios::in);
        data >> product_id >> product_name >> price >> discount;
        while (!data.eof()) {
            if (product_id == arrc[i]) {
                // Calculate amount and net total for each product
                amount = price * arrq[i];
                net = amount - (amount * discount) / 100;
                total += net;
                // Display product details in receipt
                cout << "\n" << product_id << "\t" << product_name << "\t" << arrq[i] << "\t" << "$"  << price << "\t" << "$" << amount << "\t" << "$"  << net;
            }
            data >> product_id >> product_name >> price >> discount;
        }
        data.close();
    }
    // Display total amount to be paid by customer
    cout << "\n\nTotal Amount to be Paid: $" << total << endl;
}

// Main function
int main() {
    grocery shop;
    shop.menu(); // Start program by displaying main menu
    return 0;
}