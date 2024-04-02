#include <iostream>
#include <ctime>
using namespace std;
// Dua header <iostream> dan <ctime> digunakan dalam program untuk melakukan input-output dasar dan menghasilkan angka acak.
// using namespace std; digunakan agar kode dapat menggunakan simbol-simbol dari namespace std tanpa menuliskan std:: di depannya.


// Struktur data untuk menyimpan informasi produk
struct Product {
    string type;        // Tipe produk (contoh: baju, celana, sepatu, dsb)
    string name;        // Nama produk
    string color;       // Warna produk
    string size;        // Ukuran produk
    int price;          // Harga produk dalam rupiah
    int code;           // Kode barang
    int stock;          // Stok produk
    bool isDiscounted;  // Status apakah produk sedang diskon
};
//struktur 'produk' dipakai untuk menyimpan info penjualan diatas


// Kelas untuk node linked list
class Node {
public:
    Product data;
    Node* next;

    Node(const Product& product) : data(product), next(nullptr) {}
};
// 'node' dipakai untuk menampilkan setiap elemen dalam linked list
// setiap node memiliki data seperti 'product' dan pointer 'next' agar menuju ke node berikutnya


// Kelas untuk linked list produk
class ProductList {
private:
    Node* head;

public:
    ProductList() : head(nullptr) {}
// 'productlist'dipakai untuk mengelola linked list produk
// fungsinya untuk menambahkan produk baru, menampilkan semua produk dll


    // Fungsi untuk menambahkan produk baru
    void addProduct(const Product& product) {
        Node* newNode = new Node(product);
        newNode->next = head;
        head = newNode;
    }
// 'addproduct' fungsinya membuat node baru menggunakan data yang akan ditambahkan
// mengubungkan node baru ke linked list


    // Fungsi untuk menampilkan semua produk
    void displayAllProducts() {
        if (!head) {
            cout << "Tidak ada produk yang tersedia." << endl;
            return;
        }
        Node* temp = head;
        while (temp) {
            displayProduct(temp->data);
            temp = temp->next;
        }
    }
    // fungsi 'displayAllProducts' untuk menampilkan semua produk yang tersedia


    // Fungsi untuk mencari produk berdasarkan kode barang
    void searchProductByCode(int code) {
        if (!head) {
            cout << "Tidak ada produk yang tersedia." << endl;
            return;
        }
        Node* temp = head;
        bool found = false;
        while (temp) {
            if (temp->data.code == code) {
                displayProduct(temp->data);
                found = true;
                break;
            }
            temp = temp->next;
        }
        if (!found) {
            cout << "Produk dengan kode " << code << " tidak ditemukan." << endl;
        }
    }
    // fungsi 'searchProductByCode' mencari produk berdasarkan kode


    // Fungsi untuk membeli produk berdasarkan kode barang
    void buyProductByCode(int code) {
        if (!head) {
            cout << "Tidak ada produk yang tersedia." << endl;
            return;
        }
        Node* temp = head;
        while (temp) {
            if (temp->data.code == code) {
                if (temp->data.stock > 0) {
                    cout << "Anda telah membeli " << temp->data.name << " seharga Rp. ";
                    if (temp->data.isDiscounted) {
                        int discountedPrice = temp->data.price * 0.5; // Diskon 50%
                        cout << discountedPrice << " (harga diskon 50%)" << endl;
                    } else {
                        cout << temp->data.price << endl;
                    }
                    cout << "Harga Asli: Rp. " << temp->data.price << endl;
                    temp->data.stock--;
                    cout << "Detail Barang yang Dibeli:\n";
                    displayProduct(temp->data); // Tampilkan detail barang yang dibeli
                } else {
                    cout << "Maaf, produk " << temp->data.name << " sedang tidak tersedia." << endl;
                }
                return;
            }
            temp = temp->next;
        }
        cout << "Produk dengan kode " << code << " tidak ditemukan." << endl;
    }

    // Fungsi untuk mengecek barang yang sedang diskon
    void checkDiscountedProducts() {
        if (!head) {
            cout << "Tidak ada produk yang tersedia." << endl;
            return;
        }
        Node* temp = head;
        while (temp) {
            if (temp->data.isDiscounted) {
                displayProduct(temp->data);
            }
            temp = temp->next;
        }
    }

    // Fungsi untuk menampilkan detail produk
    void displayProduct(const Product& product) {
        cout << "Tipe: " << product.type << endl;
        cout << "Nama: " << product.name << endl;
        cout << "Warna: " << product.color << endl;
        cout << "Ukuran: " << product.size << endl;
        cout << "Harga: Rp. " << product.price << endl;
        cout << "Kode Barang: " << product.code << endl;
        cout << "Stok: " << product.stock << endl;
        cout << (product.isDiscounted ? "Produk sedang diskon (50% off)." : "Produk tidak sedang diskon.") << endl;
        cout << endl;
    }

    // Getter untuk kepala linked list
    Node* getHead() {
        return head;
    }
};

// Fungsi untuk menghasilkan warna acak
string generateRandomColor() {
    string colors[] = {"Merah", "Kuning", "Hijau", "Pink", "Navy"};
    return colors[rand() % (sizeof(colors) / sizeof(colors[0]))];
}

// Fungsi untuk menghasilkan kode barang acak
int generateRandomCode() {
    return rand() % 1000 + 1; // Kode barang antara 1 hingga 1000
}

// Fungsi untuk membuat produk acak
void createRandomProducts(ProductList& productList, int numProducts) {
    srand(time(nullptr)); // Untuk menghasilkan angka acak yang berbeda setiap kali program dijalankan
    for (int i = 0; i < numProducts; ++i) {
        Product product;
        product.type = "Baju";
        product.name = "Produk " + to_string(i + 1);
        product.color = generateRandomColor();
        product.size = "XL";
        product.price = rand() % 500000 + 50000; // Harga antara Rp. 50.000 hingga Rp. 550.000
        product.code = generateRandomCode();
        product.stock = rand() % 50 + 1; // Stok antara 1 hingga 50
        product.isDiscounted = rand() % 2 == 0; // Produk memiliki kemungkinan diskon 50%
        productList.addProduct(product);
    }
}

int main() {
    cout << "N-Style - Jualan Aksesoris Perlengkapan Anak Muda" << endl;

    ProductList productList;

    // Membuat produk acak
    createRandomProducts(productList, 20);

    int choice;
    do {
        cout << "\nMenu Program:\n";
        cout << "1. Tampilkan Semua Produk\n";
        cout << "2. Cari Produk (Masukkan Kode Barang)\n";
        cout << "3. Beli Produk (Masukkan Kode Barang)\n";
        cout << "4. Cek Barang Diskon\n";
        cout << "5. Keluar\n";
        cout << "Pilih menu: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Daftar Semua Produk:" << endl;
                productList.displayAllProducts();
                break;
            case 2: {
                int code;
                cout << "Masukkan Kode Barang: ";
                cin >> code;
                productList.searchProductByCode(code);
                break;
            }
            case 3: {
                int code;
                cout << "Masukkan Kode Barang untuk Membeli: ";
                cin >> code;
                productList.buyProductByCode(code);
                break;
            }
            case 4:
                cout << "Daftar Produk Diskon:" << endl;
                productList.checkDiscountedProducts();
                break;
            case 5:
                cout << "Terima kasih telah menggunakan N-Style." << endl;
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } while (choice != 5);

    return 0;
}
