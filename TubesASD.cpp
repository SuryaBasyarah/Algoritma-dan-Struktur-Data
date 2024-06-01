#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cctype>

using namespace std;

string categoryName, subCategoryName, ItemName;
int ItemPrice;
int ItemStock;

struct Node {
    string name;
    int price;
    int stock;
    Node* leftChild;
    Node* rightSibling;

    explicit Node(const string& name) {
        this->name = name;
        this->price = -1;
        this->stock = -1;
        this->leftChild = nullptr;
        this->rightSibling = nullptr;
    }

    Node(const string& name, int price, int stock) {
        this->name = name;
        this->price = price;
        this->stock = stock;
        this->leftChild = nullptr;
        this->rightSibling = nullptr;
    }

    bool isItem() const {
        return this->price >= 0 || this->stock >= 0;
    }
};

//====PROMOTIONS===
struct PromotionNode
{
    bool Status;
    struct StartDate
    {
        int day, month, year;
    } StartDate;

    struct EndDate
    {
        int day, month, year;
    } EndDate;

    int PromotionType;
    string PaymentMethod;
    int MinimumPayment;
    string Product;
    string Benefit;
    PromotionNode *next;
};
PromotionNode *head = nullptr;
int numberOfPromotions = 0;

// enum dan struct untuk event
enum Type { Item, Event };

struct TreeNodeEvent {
    string eventName;
    Node* menuItem;
    vector<TreeNodeEvent*> Children;
    Type type;
};

// MENU UTAMA
Node* AddCategoryAndSub(Node* parent, const string& name);
Node* AddItem(Node* parent, const string& name, int price, int stock);
Node* FindNode(Node* root, const string& name);
void DeleteSubTree(Node* node);
Node* DeleteNode(Node* root, const string& name);
void EditNode(Node* root, const string& name, const string& newName, int newPrice = -1, int newStock = -1);
void DisplayTree(Node* root, int depth = 0);
void FillMenu(Node* root, const vector<tuple<string, vector<pair<string, vector<tuple<string, int, int>>>>>>& menuData);
Node* AddCategoryTerminal(Node* root);
Node* AddSubCategoryTerminal(Node* root);
Node* AddItemTerminal(Node* root);
void DeleteCategoryTerminal(Node* root);
void DeleteSubCategoryTerminal(Node* root);
void DeleteItemTerminal(Node* root);
void EditCategoryTerminal(Node* root);
void EditSubCategoryTerminal(Node* root);
void EditItemTerminal(Node* root);
void SearchAvailable(Node* root);
void InsertAll(Node* root);

// PROMOSI
void AddPromotion(bool status,
                  int startDate_day, int startDate_month, int startDate_year,
                  int endDate_day, int endDate_month, int endDate_year,
                  int promotiontype, string paymentmethod, int minimumpayment, string benefit, string product);
void EditPromotion(int selectedpromotion, bool status,
                   int startDate_day, int startDate_month, int startDate_year,
                   int endDate_day, int endDate_month, int endDate_year,
                   int promotiontype, string paymentmethod, int minimumpayment, string benefit, string product);
void DeletePromotion(int selectedpromotion);
void DisplayPromotions();
void ApplyPromotion(int CurrentDate, int CurrentMonth, int CurrentYear, int TotalPrice, string PaymentMethod, string product);

// EVENT
TreeNodeEvent* FindEventItem(TreeNodeEvent* root, const string& itemName);
TreeNodeEvent* FindEvent(TreeNodeEvent* root, const string& eventName);
TreeNodeEvent* AddEvent(TreeNodeEvent* root, const string& eventName);
TreeNodeEvent* AddEventItem(TreeNodeEvent* root, Node* mainMenu, const string& parentEventName, const string& itemName);
void DisplayEventTree(TreeNodeEvent* root, int depth = 0);
bool DeleteEvent(TreeNodeEvent* root, const string& eventName);
bool DeleteEventItem(TreeNodeEvent* root, const string& parentEventName, const string& itemName);
bool RenameEvent(TreeNodeEvent* root, const string& oldName, const string& newName);
bool MoveEventItem(TreeNodeEvent* root, const string& sourceEventName, const string& destinationEventName, const string& itemName);

int main() {
    system("cls");
    string name;
    Node* root = new Node("Menu");
    TreeNodeEvent* eventroot = new TreeNodeEvent{"Event", nullptr, {}, Type::Event};
    InsertAll(root);

    // AddCategoryAndSub(root, "TEST");

    // --- TEST ADD CATEGORY ---
    // menambahkan category langsung di parameter maupun terminal
    // AddCategoryTerminal(root);

    // --- TEST ADD SUB CAT ---
    // menambahkan sub cat by terminal
    // AddSubCategoryTerminal(root);
    // AddSubCategoryTerminal(root);
    // AddSubCategoryTerminal(root);


    // --- TEST ADD ITEM ---
    // menambahkan item by terminal dengan menginput nama, harga, stock
    // AddItemTerminal(root);

    // --- TEST DELETE ---
    // menghapus category, subcategory, dan item by terminal dengan menginputkan nama-nama yang diperlukan
    // DeleteCategoryTerminal(root);
    // DeleteSubCategoryTerminal(root);
    // DeleteItemTerminal(root);
    
    // --- TEST EDIT ---
    // mengedit nama category dan subcategory, dan mengedit item yang terdiri dari nama, harga, dan stock.
    // Jika hanya ingin mengubah sebagian value, value yang tidak ingin diubah diinputkan dengan value sebelumnya
    // EditCategoryTerminal(root);
    EditSubCategoryTerminal(root);
    // EditItemTerminal(root);

    // --- TEST SEARCH ---
    // mengecek apakah category, subcategory, atau item tersedia atau tidak
    // SearchAvailable(root);

    DisplayTree(root);

    // // ---TEST ADD PROMO---
    // // Menambahkan beberapa promosi untuk diuji
    // AddPromotion(true, 1, 1, 2022, 31, 12, 2022, 2, "Gopay", 50000, "Discount", "Pulsa");
    // AddPromotion(true, 1, 13, 2022, 1, 1, 2023, 1, "Go", 50000, "Discount", "Pul");
    // AddPromotion(true, 1, 1, 2022, 31, 12, 2022, 3, "Gopay", 50000, "Discount", "Pul");
    // AddPromotion(true, 1, 12, 2022, 1, 1, 2023, 1, "Go", 50000, "Discount", "Pul");
    // // DisplayPromotions();
    // cout << endl;

    // // --- TEST AVAIL PROMOTION ---
    // // Menguji fungsi ApplyPromotion dengan berbagai skenario untuk melihat apakah promosi yang sesuai diterapkan dengan benar.
    // ApplyPromotion(23, 1, 2022, 100000, "Gopay", "Pul");
    // ApplyPromotion(20, 1, 2022, 100000, "Gopay", "Pul");
    // cout << endl;

    // // // --- TEST EDIT PROMO ---
    // // Mengedit promosi yang sudah ada untuk memperbarui informasi promosi.
    // EditPromotion(4, false, 12, 1, 2022, 31, 12, 2022, 1, "Gopay", 50000, "Discount", "Pulsa");
    // EditPromotion(2, false, 12, 1, 2022, 31, 12, 2022, 2, "Gopay", 50000, "Free Item", "Pulsa");
    // DisplayPromotions();
    // cout << endl;

    // // --- TEST DELETE PROMO ---
    // //  Menghapus promosi yang sudah tidak berlaku atau tidak diperlukan lagi.
    // DeletePromotion(4);
    // DeletePromotion(2);
    // DisplayPromotions();


    // --- TEST ADD EVENT ---
    // menambahkan event ke dalam tree event.
    AddEvent(eventroot, "Lunch");
    AddEvent(eventroot, "Breakfast");
    AddEvent(eventroot, "");
    AddEvent(eventroot, "Dinner");
    // DisplayEventTree(eventroot);

    // --- TEST ADD EVENT ITEM ---
    // menambahkan item ke dalam event yang dituju.
    AddEventItem(eventroot, root, "Breakfast", "Burger");
    AddEventItem(eventroot, root, "Breakfast", "");
    // AddEventItem(eventroot, root, "Breakfast", "Sandwich");
    // AddEventItem(eventroot, root, "Breakfast", "Bun");
    AddEventItem(eventroot, root, "Dinner", "Apple juice");
    AddEventItem(eventroot, root, "Breakfast", "BOURBON");
    // DisplayEventTree(eventroot);
    // DeleteItemTerminal(root);

    // --- TEST DELETE EVENT ---
    // menghapus event beserta isinya.
    // DeleteEventItem(eventroot, "Breakfast", "Bun");
    // DeleteEvent(eventroot, "lunasdach");

    // --- TEST DELETE EVENT ITEM ---
    // menghapus item tertentu di dalam event.
    // DeleteEventItem(eventroot, "Breakfast", "burger");
    // DeleteEventItem(eventroot, "Breakfast", "Burger");

    // --- TEST RENAME EVENT ---
    // mengganti nama event
    // RenameEvent(eventroot, "Dinner", "Breakfast");

    // --- TEST MOVE EVENT ITEM ---
    // memindahkan item ke event lain
    // MoveEventItem(eventroot, "Breakfast", "Dinner", "Burger");
    // DisplayEventTree(eventroot);

    return 0;
}

//Fungsi menambahkan node kategori dan subkategori pada tree
Node* AddCategoryAndSub(Node* parent, const string& name) {
    if (!parent || name.empty() || all_of(name.begin(), name.end(), ::isspace)) {
        cout << "Nama tidak boleh kosong atau hanya berisi spasi." << endl;
        return nullptr;
    }

    //Jika item sudah tersedia
    Node* current = parent->leftChild;
    while (current) {
        if (current->name == name) {
            cout << "gagal ditambahkan " << name << " sudah ada" << endl;
            return current;
        }
        current = current->rightSibling;
    }

    //Jika item belum tersedia
    if (parent->leftChild == nullptr) {
        parent->leftChild = new Node(name);
        return parent->leftChild;
    } else {
        Node* sibling = parent->leftChild;
        while (sibling->rightSibling) {
            sibling = sibling->rightSibling;
        }
        sibling->rightSibling = new Node(name);
        return sibling->rightSibling;
    }

}

//Fungsi menambahkan node item pada tree
Node* AddItem(Node* parent, const string& name, int price, int stock) {
    if (!parent || name.empty() || all_of(name.begin(), name.end(), ::isspace)) {
        cout << "Nama tidak boleh kosong atau hanya berisi spasi." << endl;
        return nullptr;
    }

    // Check if the item already exists
    Node* current = parent->leftChild;
    while (current) {
        if (current->name == name) {
            cout << "gagal ditambahkan " << name << " sudah ada" << endl;
            return current;
        }
        current = current->rightSibling;
    }

    // If the item does not exist, add a new one
    if (parent->leftChild == nullptr) {
        parent->leftChild = new Node(name, price, stock);
        return parent->leftChild;
    } else {
        Node* sibling = parent->leftChild;
        while (sibling->rightSibling) {
            sibling = sibling->rightSibling;
        }
        sibling->rightSibling = new Node(name, price, stock);
        return sibling->rightSibling;
    }
}

// Fungsi untuk mencari kategori atau item dengan nama tertentu
Node* FindNode(Node* root, const string& name) {
    if (!root) return nullptr;

    if (root->name == name) return root;

    Node* foundNode = FindNode(root->leftChild, name);
    if (foundNode) return foundNode;

    // Iterate through right siblings
    Node* sibling = root->rightSibling;
    while (sibling) {
        foundNode = FindNode(sibling, name);
        if (foundNode) return foundNode;
        sibling = sibling->rightSibling;
    }

    return nullptr;
}

//Fungsi rekursif untuk delete node
void DeleteSubTree(Node* node) {
    if (!node) return;

    DeleteSubTree(node->leftChild);
    Node* rightSibling = node->rightSibling;
    delete node;

    if (rightSibling) {
        DeleteSubTree(rightSibling);
    }
}

//Untuk menghapus node pada tree
Node* DeleteNode(Node* root, const string& name) {
    if (!root) return nullptr;
    //jika node tersebut root
    if (root->name == name) {
        Node* newRoot = root->rightSibling;
        DeleteSubTree(root);
        return newRoot;
    }

    //Jika node target tersebut di rightsibling
    if (root->leftChild) {
        Node* sibling = root->leftChild;
        Node* prevSibling = nullptr;
        while (sibling && sibling->rightSibling) {
            if (sibling->rightSibling->name == name) {
                DeleteSubTree(sibling->rightSibling);
                sibling->rightSibling = sibling->rightSibling->rightSibling;
                return root;
            }
            prevSibling = sibling;
            sibling = sibling->rightSibling;
        }
    }

    //pencarian rekursif
    root->leftChild = DeleteNode(root->leftChild, name);
    root->rightSibling = DeleteNode(root->rightSibling, name);

    return root;
}

// Fungsi untuk mengganti isi dari kategori atau item pada tree
// program dibawah dapat mengedit semuanya termasuk harga dan stock
void EditNode(Node* root, const string& name, const string& newName, int newPrice, int newStock) {
    if (newName.empty() || all_of(newName.begin(), newName.end(), ::isspace)) {
        cout << "Nama tidak boleh kosong atau hanya berisi spasi." << endl;
        return;
    }

    Node* node = FindNode(root, name);
    if (!node) {
        cout << "Node tidak ditemukan" << endl;
        return;
    }

    //jika new name sudah ada di tree
    while (node) {
        if (node->name == newName) {
            cout << "gagal ditambahkan " << newName << " sudah ada" << endl;
            return;
        }
        node = node->rightSibling;
    }
    cout << "Item " << ItemName <<" diedit!" <<endl;
    node = FindNode(root, name);

    //Edit item jika node berupa item
    if (node->isItem()) {
        node->name = newName;
        node->price = newPrice;
        node->stock = newStock;
    //jika node bukan item
    } else {
        node->name = newName;
    }
}

// Fungsi untuk menampilkan tree
void DisplayTree(Node* root, int depth) {
    if (!root) return;

    string indent(depth * 2, ' '); // Membuat indentasi
    if(root->stock == -1 && root->price == -1){
       cout << indent << root->name << endl; 
    } else if (root->stock == 0) {
        cout << indent << root->name << " (Stock habis)" << endl;
    } else if (root->price == 0) {
        cout << indent << root->name << ", Gratis" ", " << root->stock << endl;
    }else {
        cout << indent << root->name << ", " << root->price << ", " << root-> stock << endl; // Menampilkan nama kategori atau item
    }

    if (root->leftChild) {
        DisplayTree(root->leftChild, depth + 1);
    }

    if (root->rightSibling) {
        DisplayTree(root->rightSibling, depth);
    }
}

// Fungsi untuk mengisi tree dengan data
void FillMenu(Node* root, const vector<tuple<string, vector<pair<string, vector<tuple<string, int, int>>>>>>& menuData) {
    for (const auto& categoryData : menuData) {
        // Extracting values from categoryData tuple
        const string& categoryName = get<0>(categoryData);
        const vector<pair<string, vector<tuple<string, int, int>>>>& subCategories = get<1>(categoryData);

        // Creating a Node* for the category
        Node* categoryNode = AddCategoryAndSub(root, categoryName);

        for (const auto& subCategoryData : subCategories) {
            // Extracting values from subCategoryData tuple
            const string& subCategoryName = subCategoryData.first;
            const vector<tuple<string, int, int>>& items = subCategoryData.second;

            // Creating a Node* for the subcategory
            Node* subCategoryNode = AddCategoryAndSub(categoryNode, subCategoryName);

            for (const auto& itemData : items) {
                // Extracting values from itemData tuple
                const string& itemName = get<0>(itemData);
                int itemPrice = get<1>(itemData);
                int itemStock = get<2>(itemData);

                // Creating a Node* for the item
                AddItem(subCategoryNode, itemName, itemPrice, itemStock);
            }
        }
    }
}

//====Fungsi-fungsi implementasi untuk dijalankan pada terminal===
Node* AddCategoryTerminal(Node* root) {
    cout << "Masukkan Kategori: ";
    getline(cin, categoryName);
    if (categoryName.empty() || all_of(categoryName.begin(), categoryName.end(), ::isspace)) {
        cout << "Nama tidak boleh kosong atau hanya berisi spasi." << endl;
        return nullptr;
    }

    return AddCategoryAndSub(root, categoryName);
}

Node* AddSubCategoryTerminal(Node* root) {
    if (!root || root->leftChild == nullptr) {
        cout << "Kategori kosong\n";
        return nullptr;
    } 
        cout << "Kategori dari sub kategori yang akan ditambahkan : ";
        getline(cin, categoryName);
        Node* categoryNode = FindNode(root, categoryName);

        if (categoryNode) {
            cout << "Masukkan sub Kategori : ";
            getline(cin, subCategoryName);
            if (subCategoryName.empty() || all_of(subCategoryName.begin(), subCategoryName.end(), ::isspace)) {
                cout << "Nama tidak boleh kosong atau hanya berisi spasi." << endl;
                return nullptr;
            }
            cout << "Sub Kategori " << subCategoryName <<" ditambahkan!" <<endl;
            return AddCategoryAndSub(categoryNode, subCategoryName);
        } else {
            cout << "Kategori tidak ditemukan.\n";
            return nullptr;
        }
}

Node* AddItemTerminal(Node* root){
    if (!root || root->leftChild == nullptr) {
        cout << "Kategori kosong\n";
        return nullptr;
    } else if (!root || root->leftChild->leftChild == nullptr){
        cout << "Sub Kategori kosong\n";
        return nullptr;
    }

    cout << "Kategori dari item yang akan ditambahkan : ";
    getline(cin, categoryName);
    Node* categoryNode = FindNode(root, categoryName);

    if (categoryNode) {
        cout << "Sub Kategori yang akan ditambahkan : ";
        getline(cin, subCategoryName);
        Node* subCategoryNode = FindNode(categoryNode, subCategoryName);
        
        if (subCategoryNode) {
        cout << "Masukkan Nama Item : ";
        getline(cin, ItemName);
        if (ItemName.empty() || all_of(ItemName.begin(), ItemName.end(), ::isspace)) {
            cout << "Nama tidak boleh kosong atau hanya berisi spasi." << endl;
            return nullptr;
        }
        cout << "Masukkan Harga Item : ";
        cin >> ItemPrice;
        cout << "Masukkan Stok Item : ";
        cin >> ItemStock;
        cout << "Item " << ItemName <<" ditambahkan!" <<endl;
        return AddItem(subCategoryNode, ItemName, ItemPrice, ItemStock);
        
        } else {
            cout << "Sub Kategori Tidak ditemukan.\n";
            return nullptr;
        }
    } else {
        cout << "Kategori tidak ditemukan.\n";
        return nullptr;
    }
}

void DeleteCategoryTerminal(Node* root){
    cout << "Masukkan Kategori yang ingin dihapus: ";
    getline(cin, categoryName);
    Node* categoryNode = FindNode(root, categoryName);
    
    if (categoryNode)
        DeleteNode(root, categoryName);
    else
        cout << "Kategori tidak ditemukan.\n";
}

void DeleteSubCategoryTerminal(Node* root){
    if (!root || root->leftChild == nullptr) {
        cout << "Kategori kosong\n";
        return;
    } else if (!root || root->leftChild->leftChild == nullptr){
        cout << "Sub Kategori kosong\n";
        return;
    }

    cout << "Kategori dari sub kategori yang akan dihapus : ";
    getline(cin, categoryName);
    Node* categoryNode = FindNode(root, categoryName);

    if (categoryNode) {
        cout << "Masukkan sub Kategori : ";
        getline(cin, subCategoryName);
        DeleteNode(categoryNode, subCategoryName);
        cout << "Sub Kategori " << subCategoryName <<" dihapus!" <<endl;
        return;
    } else {
        cout << "Kategori tidak ditemukan.\n";
    }
}

void DeleteItemTerminal(Node* root){
    if (!root || root->leftChild == nullptr) {
        cout << "Kategori kosong\n";
        return;
    } else if (!root || root->leftChild->leftChild == nullptr){
        cout << "Sub Kategori kosong\n";
        return;
    } else if (!root || root->leftChild->leftChild->leftChild == nullptr) {
        cout << "Item kosong\n";
        return;
    }

    cout << "Kategori yang item nya akan dikurangi : ";
    getline(cin, categoryName);
    Node* categoryNode = FindNode(root, categoryName);

    if (categoryNode) {
        cout << "Sub Kategori yang item nya akan dikurangi : ";
        getline(cin, subCategoryName);
        Node* subCategoryNode = FindNode(categoryNode, subCategoryName);
        
        if (subCategoryNode) {
        cout << "Masukkan Nama Item : ";
        getline(cin, ItemName);
        DeleteNode(subCategoryNode, ItemName);
        cout << "Item " << ItemName <<" dihapus!" <<endl;
        return;
        } else {
            cout << "Sub Kategori Tidak ditemukan.\n";
        }
    } else {
        cout << "Kategori tidak ditemukan.\n";
    }
}

void EditCategoryTerminal(Node* root){
    string newcategoryName;
    cout << "Masukkan Kategori yang akan diedit: ";
    getline(cin, categoryName);
    cout << "Masukkan nama Kategori baru: ";
    getline(cin, newcategoryName);
    if (newcategoryName.empty() || all_of(newcategoryName.begin(), newcategoryName.end(), ::isspace)) {
        cout << "Nama tidak boleh kosong atau hanya berisi spasi." << endl;
        return;
    }
    Node* categoryNode = FindNode(root, newcategoryName);
    if (categoryNode) {
            cout << "gagal ditambahkan " << newcategoryName << " sudah ada" << endl;
            return;
    }
    else
        EditNode(root, categoryName, newcategoryName);
}

void EditSubCategoryTerminal(Node* root){
    string newSubcategoryName;

    if (!root || root->leftChild == nullptr) {
        cout << "Kategori kosong\n";
        return;
    } else if (!root || root->leftChild->leftChild == nullptr){
        cout << "Sub Kategori kosong\n";
        return;
    }

    cout << "Kategori yang sub kategori nya akan diedit : ";
    getline(cin, categoryName);
    Node* categoryNode = FindNode(root, categoryName);

    if (categoryNode) {
        cout << "Masukkan Sub Kategori: ";
        getline(cin, subCategoryName);
        cout << "Masukkan nama Sub Kategori baru: ";
        getline(cin, newSubcategoryName);
        if (newSubcategoryName.empty() || all_of(newSubcategoryName.begin(), newSubcategoryName.end(), ::isspace)) {
            cout << "Nama tidak boleh kosong atau hanya berisi spasi." << endl;
            return;
        }
        Node* subCategoryNode = FindNode(root, newSubcategoryName);
        if (subCategoryNode) {
            cout << "gagal ditambahkan " << newSubcategoryName << " sudah ada" << endl;
            return;
        } else {
            EditNode(root, subCategoryName, newSubcategoryName);
            // cout << "Sub Kategori " << subCategoryName <<" diedit!" <<endl;
            return;
        }
        
    } else {
        cout << "Kategori tidak ditemukan.\n";
    }
}

// program berikut hanya dapat mengedit nama dari item by terminal
void EditItemTerminal(Node* root){
    string newitemName;
    float newPrice;
    int newStock;
    
    if (!root || root->leftChild == nullptr) {
        cout << "Kategori kosong\n";
        return;
    } else if (!root || root->leftChild->leftChild == nullptr){
        cout << "Sub Kategori kosong\n";
        return;
    } else if (!root || root->leftChild->leftChild->leftChild == nullptr) {
        cout << "Item kosong\n";
        return;
    }

    cout << "Kategori yang item nya akan diedit : ";
    getline(cin, categoryName);
    Node* categoryNode = FindNode(root, categoryName);

    if (categoryNode) {
        cout << "Sub Kategori yang item nya akan diedit : ";
        getline(cin, subCategoryName);
        Node* subCategoryNode = FindNode(categoryNode, subCategoryName);
        
        if (subCategoryNode) {
        cout << "Masukkan Item: ";
        getline(cin, ItemName);
        cout << "Masukkan nama Item baru: ";
        getline(cin, newitemName);
        if (newitemName.empty() || all_of(newitemName.begin(), newitemName.end(), ::isspace)) {
            cout << "Nama tidak boleh kosong atau hanya berisi spasi." << endl;
            return;
        }
        cout << "Masukkan harga Item baru: ";
        cin >> newPrice;
        cout << "Masukkan stok Item baru: ";
        cin >> newStock;
        Node* itemNode = FindNode(subCategoryNode, newitemName);
            if (itemNode) {
                cout << "Item dengan nama " << newitemName << " sudah ada.\n";
            } else {
                EditNode(root, ItemName, newitemName, newPrice, newStock);
                // cout << "Item " << ItemName <<" diedit!" <<endl;
                return;
            }
            
        } else {
            cout << "Sub Kategori Tidak ditemukan.\n";
        }
    } else {
        cout << "Kategori tidak ditemukan.\n";
    } 
}

void SearchAvailable(Node* root){
    string target;
    cout << "Masukkan Item yang ingin dicari : ";
    getline (cin, target);
    Node* node = FindNode(root, target);
    if (node){
        cout << "Item tersedia \n";
    } else {
        cout << "Item tidak tersedia " << endl;
    }

}

//isi dari tree yang telah disediakan
void InsertAll(Node* root) {
    vector<tuple<string, vector<pair<string, vector<tuple<string, int, int>>>>>> menuData = {
        {"Roti dan kue", {
            {"Viennoiseries", {
                {"Croissant", 20000, 10},
                {"Pain au Chocolat", 15000, 5},
                {"Brioche", 24000, 7}
            }},
            {"Pastry", {
                {"Eclair", 12000, 10},
                {"Mille-feuille", 13000, 6},
                {"Tarte Tatin", 18000, 4},
                {"Tarlet", 15000, 8}
            }},
            {"Bread", {
                {"Baguette", 7000, 15},
                {"Sourdough", 9500, 10},
                {"Brioche Long", 6000, 7}
            }},
            {"Bun", {
                {"Bagel", 3000, 8},
                {"Burger", 4000, 12},
                {"Hotdog", 4500, 14}
            }}
        }},
        {"Minuman", {
            {"Juice", {
                {"Apple Juice", 4500, 20},
                {"Orange Juice", 6000, 20},
                {"Strawberry Juice", 6500, 15}
            }},
            {"Teh", {
                {"Earl Grey", 9000, 30},
                {"Chamomile", 8500, 30},
                {"English Breakfast", 7000, 35},
                {"Darjeeling", 6000, 32},
                {"Oolong", 5000, 30},
                {"Matcha", 6500, 35},
                {"Jasmine", 4500, 40}
            }},
            {"Kopi", {
                {"Long black", 16000, 25},
                {"Cappuccino", 18000, 25},
                {"Latte", 19000, 25},
                {"Espresso", 17000, 27},
                {"Machiato", 18500, 29},
                {"Piccolo", 16000, 23}
            }}
        }},
        {"Makanan Utama", {
            {"Salad", {
                {"Caesar Salad", 23000, 8},
                {"Caprese Salad", 34000, 6},
                {"Waldrof Salad", 52000, 9},
                {"Nicoise Salad", 47000, 6}
            }},
            {"Sup", {
                {"Pumpkin soup", 34000, 10},
                {"Mushroom soup", 38000, 10},
                {"Corn Soup", 42000, 9}
            }},
            {"Pasta", {
                {"Gnocchi", 45000, 5},
                {"Aglio Olio", 67000, 7},
                {"Lasagna", 49000, 8},
                {"Fettucine", 53000, 5},
                {"Carbonara", 63000, 8}
            }},
            {"Sandwich", {
                {"Club Sandwich", 34000, 8},
                {"Tune Sandwich", 39000, 6}
            }}
        }}
    };
     // Fill the menu tree with the data
    FillMenu(root, menuData);
}

void AddPromotion(bool status,
                  int startDate_day, int startDate_month, int startDate_year,
                  int endDate_day, int endDate_month, int endDate_year,
                  int promotiontype, string paymentmethod, int minimumpayment, string benefit, string product)
{
    if (endDate_year < startDate_year || (endDate_year == startDate_year && endDate_month < startDate_month) || (endDate_year == startDate_year && endDate_month == startDate_month && endDate_day < startDate_day))
    {
        cout << "Error: End date cannot be earlier than start date!" << endl;
        return;
    }

    if (startDate_day < 1 || startDate_day > 31 || startDate_month < 1 || startDate_month > 12 ||
        endDate_day < 1 || endDate_day > 31 || endDate_month < 1 || endDate_month > 12)
    {
        cout << "Error: Invalid date!" << endl;
        return;
    }

    if (promotiontype != 1 && promotiontype != 2)
    {
        cout << "Error: Invalid promotion type! Please enter either 1 for Discount or 2 for Free Item." << endl;
        return;
    }

    PromotionNode *newNode = new PromotionNode;
    newNode->Status = status;
    newNode->StartDate.day = startDate_day;
    newNode->StartDate.month = startDate_month;
    newNode->StartDate.year = startDate_year;
    newNode->EndDate.day = endDate_day;
    newNode->EndDate.month = endDate_month;
    newNode->EndDate.year = endDate_year;
    newNode->PromotionType = promotiontype;
    newNode->PaymentMethod = paymentmethod;
    newNode->MinimumPayment = minimumpayment;
    newNode->Product = product;
    newNode->Benefit = benefit;
    newNode->next = nullptr;

    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        PromotionNode *temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    cout << endl
         << "Promotion added." << endl;
    numberOfPromotions++;
}
// Fungsi ini digunakan untuk menambahkan sebuah promosi baru ke dalam daftar promosi.
// Parameter:
// - status: status promosi (aktif atau tidak)
// - startDate_day, startDate_month, startDate_year: tanggal mulai promosi
// - endDate_day, endDate_month, endDate_year: tanggal berakhir promosi
// - promotiontype: jenis promosi (1 untuk Diskon, 2 untuk Barang Gratis)
// - paymentmethod: metode pembayaran yang berlaku untuk promosi
// - minimumpayment: jumlah pembayaran minimum yang diperlukan untuk memenuhi syarat promosi
// - benefit: manfaat yang diberikan oleh promosi
// - product: produk yang tercakup dalam promosi

void EditPromotion(int selectedpromotion, bool status,
                   int startDate_day, int startDate_month, int startDate_year,
                   int endDate_day, int endDate_month, int endDate_year,
                   int promotiontype, string paymentmethod, int minimumpayment, string benefit, string product)
{
    PromotionNode *current = head;
    int index = 1;

    while (current != nullptr && index < selectedpromotion)
    {
        current = current->next;
        index++;
    }

    if (current == nullptr)
    {
        cout << "Error: No promotions exist yet!" << endl;
        return;
    }

    if (endDate_year < startDate_year || (endDate_year == startDate_year && endDate_month < startDate_month) || (endDate_year == startDate_year && endDate_month == startDate_month && endDate_day < startDate_day))
    {
        cout << "Error: End date is earlier than start date!" << endl;
        return;
    }

    if (startDate_day < 1 || startDate_day > 31 || startDate_month < 1 || startDate_month > 12 ||
        endDate_day < 1 || endDate_day > 31 || endDate_month < 1 || endDate_month > 12)
    {
        cout << "Error: Invalid date!" << endl;
        return;
    }

    if (promotiontype != 1 && promotiontype != 2)
    {
        cout << "Error: Invalid promotion type! Please enter either 1 for Discount or 2 for Free Item." << endl;
        return;
    }

    current->Status = status;
    current->StartDate.day = startDate_day;
    current->StartDate.month = startDate_month;
    current->StartDate.year = startDate_year;
    current->EndDate.day = endDate_day;
    current->EndDate.month = endDate_month;
    current->EndDate.year = endDate_year;
    current->PromotionType = promotiontype;
    current->PaymentMethod = paymentmethod;
    current->MinimumPayment = minimumpayment;
    current->Product = product;
    current->Benefit = benefit;

    cout << "Promotion edited." << endl;
}
// Fungsi ini digunakan untuk mengedit promosi yang sudah ada dalam daftar promosi.
// Parameter:
// - selectedpromotion: nomor promosi yang akan diedit
// - status: status baru promosi (aktif atau tidak)
// - startDate_day, startDate_month, startDate_year: tanggal mulai baru promosi
// - endDate_day, endDate_month, endDate_year: tanggal berakhir baru promosi
// - promotiontype: jenis promosi baru (1 untuk Diskon, 2 untuk Barang Gratis)
// - paymentmethod: metode pembayaran baru yang berlaku untuk promosi
// - minimumpayment: jumlah pembayaran minimum baru yang diperlukan untuk memenuhi syarat promosi
// - benefit: manfaat baru yang diberikan oleh promosi
// - product: produk baru yang tercakup dalam promosi

void DeletePromotion(int selectedpromotion)
{
    if (selectedpromotion <= 0 || selectedpromotion > numberOfPromotions)
        return;

    PromotionNode *current = head;
    PromotionNode *previous = nullptr;
    int index = 1;

    while (current != nullptr && index < selectedpromotion)
    {
        previous = current;
        current = current->next;
        index++;
    }

    if (current == nullptr)
        return;

    if (previous == nullptr)
    {
        head = current->next;
    }
    else
    {
        previous->next = current->next;
    }

    delete current;

    cout << "Promotion " << selectedpromotion << " deleted." << endl;
    numberOfPromotions--; // update jumlah promosi yang tersedia
}
// Fungsi ini digunakan untuk menghapus promosi dari daftar promosi berdasarkan nomor promosi.
// Parameter:
// - selectedpromotion: nomor promosi yang akan dihapus

void DisplayPromotions()
{
    PromotionNode *current = head;
    int index = 1;

    while (current != nullptr)
    {
        cout << "------------------------" << endl;
        cout << "Promotion " << index << ":" << endl;
        cout << "Promotion Type: ";
        switch (current->PromotionType)
        {
        case 1:
            cout << "Discount" << endl;
            break;

        case 2:
            cout << "Free Item" << endl;
            break;

        default:
            break;
        }
        cout << "Status: " << (current->Status ? "Active" : "Inactive") << endl;
        cout << "Start Date: " << current->StartDate.day << "/" << current->StartDate.month << "/" << current->StartDate.year << endl;
        cout << "End Date: " << current->EndDate.day << "/" << current->EndDate.month << "/" << current->EndDate.year << endl;
        cout << "Terms and Condition: " << endl;
        cout << "1. Payment method: " << current->PaymentMethod << endl;
        cout << "2. Minimum payment: " << current->MinimumPayment << endl;
        cout << "3. Product: " << current->Product << endl;
        cout << "Benefit: " << current->Benefit << endl;
        cout << "------------------------" << endl;
        cout << endl;

        current = current->next;
        index++;
    }
}
// Fungsi ini digunakan untuk menampilkan semua promosi yang tersedia beserta detailnya.

void ApplyPromotion(int CurrentDate, int CurrentMonth, int CurrentYear, int TotalPrice, string PaymentMethod, string product)
{
    PromotionNode *current = head;

    while (current != nullptr)
    {
        if (current->Status &&
            current->StartDate.year <= CurrentYear && current->StartDate.month <= CurrentMonth && current->StartDate.day <= CurrentDate &&
            current->EndDate.year >= CurrentYear && current->EndDate.month >= CurrentMonth && current->EndDate.day >= CurrentDate &&
            current->MinimumPayment < TotalPrice && current->PaymentMethod == PaymentMethod && current->Product == product)
        {
            cout << "You got a discount!" << endl;
            cout << "Your benefit: " << current->Benefit << endl;
            return;
        }
        current = current->next;
    }
    cout << "------------------------" << endl;
    cout << "No discount applied." << endl;
    cout << "------------------------" << endl;
}
// Fungsi ini digunakan untuk menerapkan promosi berdasarkan tanggal, total harga, metode pembayaran, dan produk yang dipilih.
// Fungsi ini akan mencari promosi yang sesuai dengan kriteria tertentu, seperti tanggal berlaku, metode pembayaran, dan produk.
// Jika promosi yang sesuai ditemukan, maka manfaat promosi akan diberikan.


// program FindEventItem dan FindItem adalah pengecekan untuk menghindari duplikasi
TreeNodeEvent* FindEventItem(TreeNodeEvent* root, const string& itemName) {
    auto it = find_if(root->Children.begin(), root->Children.end(), [&](TreeNodeEvent* child) {
        return child->eventName == itemName && child->type == Type::Item;
    });

    return it != root->Children.end() ? *it : nullptr;
}

TreeNodeEvent* FindEvent(TreeNodeEvent* root, const string& eventName) {
    auto it = find_if(root->Children.begin(), root->Children.end(), [&](TreeNodeEvent* child) {
        return child->eventName == eventName && child->type == Type::Event;
    });

    return it != root->Children.end() ? *it : nullptr;
}

// digunakan untuk menambahkan kategori event (breakfast, lunch, dll)
TreeNodeEvent* AddEvent(TreeNodeEvent* root, const string& eventName) {
    TreeNodeEvent* parentEvent = nullptr;
    if (eventName.empty() || all_of(eventName.begin(), eventName.end(), ::isspace)) {
        cout << "Nama tidak boleh kosong atau hanya berisi spasi." << endl;
        return nullptr;
    }
    // pengecekan apakah event sudah ada, jika ada akan return
    TreeNodeEvent* existingEvent = FindEvent(root, eventName);
    if (existingEvent) {
        cout << "Error: Event '" << eventName << "' already exists." << endl;
        return nullptr;
    }

    // menambahkan event baru
    TreeNodeEvent* newEvent = new TreeNodeEvent{eventName, nullptr, {}, Type::Event};
    if (parentEvent) {
        parentEvent->Children.push_back(newEvent);
    } else {
        root->Children.push_back(newEvent);
    }

    cout << "Event '" << eventName << "' added." << endl;
    return newEvent;
}

// untuk menambahkan item ke dalam kategori event yang ingin dituju
TreeNodeEvent* AddEventItem(TreeNodeEvent* root, Node* mainMenu, const string& parentEventName, const string& itemName) {
    // parent (event) yang dituju
    TreeNodeEvent* parentEvent = nullptr;
    for (TreeNodeEvent* child : root->Children) {
        if (child->eventName == parentEventName && child->type == Type::Event) {
            parentEvent = child;
            break;
        }
    }

    if (parentEvent) {
        // pengecekan apakah item sudah ada di event tersebut
        TreeNodeEvent* existingItem = FindEventItem(parentEvent, itemName);
        if (existingItem) {
            cout << "Error: Item '" << itemName << "' already exists in the event." << endl;
            return nullptr;
        }

        // pengecekan apakah item yang ingin ditambahkan ada pada menu utama
        Node* menuItem = FindNode(mainMenu, itemName);
        if (menuItem) {
            // ngecek apakah item yang ditambah tersebut adalah 'item' dan bukan category/subcategory
            if (menuItem->leftChild) {
                cout << "Error: '" << itemName << "' is not an item." << endl;
                return nullptr;
            }

            // item berhasil ditambah
            TreeNodeEvent* newEventItem = new TreeNodeEvent{itemName, menuItem, {}, Type::Item};
            parentEvent->Children.push_back(newEventItem);

            cout << "Item added to the event." << endl;
            return newEventItem;
        } else {
            cout << "Error: Item '" << itemName << "' doesn't exist in the main menu." << endl;
            return nullptr;
        }
    } else {
        cout << "Error: Parent event '" << parentEventName << "' not found." << endl;
        return nullptr;
    }
}

// menampilkan tree event
void DisplayEventTree(TreeNodeEvent* root, int depth) {
    if (!root) return;

    string indent(depth * 2, ' '); 
    cout << indent << root->eventName << endl;

    for (TreeNodeEvent* child : root->Children) {
        if (child->type == Type::Item) {
            // display nama + stock dan harga (jika ada)
            Node* menuItem = child->menuItem;
            if (menuItem) {
                if(menuItem->stock == -1 && menuItem->price == -1)
                    cout << indent + "   " << menuItem->name << endl;
                else if (menuItem->stock == 0)
                    cout << indent + "   " << menuItem->name << " (Stock Habis)" << endl;
                else if (menuItem->price == 0)
                    cout << indent + "   " << menuItem->name << ", Gratis" << ", " << menuItem->stock << endl;
                else            
                    cout << indent + "   " << menuItem->name << ", " << menuItem->price << ", " << menuItem->stock << endl;            
            }
        } else {
            DisplayEventTree(child, depth + 1);
        }
    }
}

// menghapus event beserta isinya
bool DeleteEvent(TreeNodeEvent* root, const string& eventName) {
    // mencari event yang akan dihapus
    for (auto it = root->Children.begin(); it != root->Children.end(); ++it) {
        if ((*it)->eventName == eventName && (*it)->type == Type::Event) {
            root->Children.erase(it);
            cout << "Event '" << eventName << "' deleted." << endl;
            return true;
        }
    }

    cout << "Error: Event '" << eventName << "' not found." << endl;
    return false;
}

// menghapus item yang ada di dalam event
bool DeleteEventItem(TreeNodeEvent* root, const string& parentEventName, const string& itemName) {
    TreeNodeEvent* parentEvent = nullptr;
    // mencari event dari event item yang akan dihapus
    for (TreeNodeEvent* child : root->Children) {
        if (child->eventName == parentEventName && child->type == Type::Event) {
            parentEvent = child;
            break;
        }
    }
    // menghapus event item jika event ditemukan
    if (parentEvent) {
        for (auto it = parentEvent->Children.begin(); it != parentEvent->Children.end(); ++it) {
            if ((*it)->eventName == itemName && (*it)->type == Type::Item) {
                parentEvent->Children.erase(it);
                cout << "Item '" << itemName << "' deleted from event." << endl;
                return true;
            }
        }

        cout << "Error: Item '" << itemName << "' not found in event." << endl;
        return false;
    } else {
        cout << "Error: Parent event '" << parentEventName << "' not found." << endl;
        return false;
    }
}

// rename event
bool RenameEvent(TreeNodeEvent* root, const string& oldName, const string& newName) {
    TreeNodeEvent* existingEvent = FindEvent(root, newName);
    if (newName.empty() || all_of(newName.begin(), newName.end(), ::isspace)) {
        cout << "Nama tidak boleh kosong atau hanya berisi spasi." << endl;
        return false;
    }
    // mengecek apakah sudah ada event dengan nama yang sama
    if (existingEvent) {
        cout << "Error: Event '" << newName << "' already exists." << endl;
        return false;
    }

    // pencarian event dan rename event
    for (TreeNodeEvent* child : root->Children) {
        if (child->eventName == oldName && child->type == Type::Event) {
            child->eventName = newName;
            cout << "Event '" << oldName << "' renamed to '" << newName << "'." << endl;
            return true;
        }
    }

    cout << "Error: Event '" << oldName << "' not found." << endl;
    return false;
}

// mindahin parent event item
bool MoveEventItem(TreeNodeEvent* root, const string& sourceEventName, const string& destinationEventName, const string& itemName) {
    TreeNodeEvent* sourceEvent = nullptr;
    TreeNodeEvent* destinationEvent = nullptr;

    // cek event asal
    for (TreeNodeEvent* child : root->Children) {
        if (child->eventName == sourceEventName && child->type == Type::Event) {
            sourceEvent = child;
            break;
        }
    }

    // cek event tujuan
    for (TreeNodeEvent* child : root->Children) {
        if (child->eventName == destinationEventName && child->type == Type::Event) {
            destinationEvent = child;
            break;
        }
    }

    // jika kedua event ada, akan menjalankan kode di bawah
    if (sourceEvent && destinationEvent) {
        // cek apakah item yang ingin dipindah ada di event asal
        auto it = find_if(sourceEvent->Children.begin(), sourceEvent->Children.end(),
                          [&](TreeNodeEvent* item) { return item->eventName == itemName && item->type == Type::Item; });

        if (it != sourceEvent->Children.end()) {
            // pengecekan apakah item yang ingin dipindah sudah ada di event tujuan
            auto existingItem = find_if(destinationEvent->Children.begin(), destinationEvent->Children.end(),
                                         [&](TreeNodeEvent* item) { return item->eventName == itemName && item->type == Type::Item; });

            if (existingItem == destinationEvent->Children.end()) {
                destinationEvent->Children.push_back(*it);
                sourceEvent->Children.erase(it);

                cout << "Item '" << itemName << "' moved from '" << sourceEventName << "' to '" << destinationEventName << "'." << endl;
                return true;
            } else {
                cout << "Error: Item '" << itemName << "' already exists in destination event." << endl;
                return false;
            }
        } else {
            cout << "Error: Item '" << itemName << "' not found in source event." << endl;
            return false;
        }
    } else {
        cout << "Error: Source or destination event not found." << endl;
        return false;
    }
}

