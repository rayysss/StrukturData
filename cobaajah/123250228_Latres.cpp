#include <iostream>
using namespace std;

const int PANJANG_NAMA = 100;

struct nodeQueue {
    int nota;
    char nama[PANJANG_NAMA + 1];
    nodeQueue* next;
};

struct nodeStack {
    int nota;
    char nama[PANJANG_NAMA + 1];
    nodeStack* next;
};

struct nodeTree {
    int nota;
    char nama[PANJANG_NAMA + 1];
    nodeTree* kiri;
    nodeTree* kanan;
};

nodeQueue* frontQueue = nullptr;
nodeQueue* rearQueue = nullptr;
nodeStack* topStack = nullptr;
nodeTree* root = nullptr;

void salinTeks(char tujuan[], const char sumber[]) {
    int i = 0;
    while (sumber[i] != '\0' && i < PANJANG_NAMA) {
        tujuan[i] = sumber[i];
        i++;
    }
    tujuan[i] = '\0';
}

bool teksKosong(const char teks[]) {
    int i = 0;
    while (teks[i] != '\0') {
        if (teks[i] != ' ' && teks[i] != '\t' && teks[i] != '\r') return false;
        i++;
    }
    return true;
}

void bacaBaris(const char prompt[], char hasil[], int ukuran) {
    while (true) {
        cout << prompt;
        cin.getline(hasil, ukuran);
        if (!cin) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Input terlalu panjang atau tidak dapat dibaca. Coba lagi.\n";
        } else {
            return;
        }
    }
}

bool ubahKeAngkaPositif(const char teks[], int& hasil) {
    if (teks[0] == '\0') return false;
    long long nilai = 0;
    int i = 0;
    while (teks[i] != '\0') {
        if (teks[i] < '0' || teks[i] > '9') return false;
        nilai = nilai * 10 + (teks[i] - '0');
        if (nilai > 2147483647LL) return false;
        i++;
    }
    if (nilai <= 0) return false;
    hasil = static_cast<int>(nilai);
    return true;
}

int inputAngka(const char prompt[], int minimum, int maksimum) {
    char input[256];
    int nilai;
    while (true) {
        bacaBaris(prompt, input, 256);
        if (ubahKeAngkaPositif(input, nilai) && nilai >= minimum && nilai <= maksimum) return nilai;
        cout << "Input tidak valid! Masukkan angka " << minimum << " sampai " << maksimum << ".\n";
    }
}

bool inputKonfirmasi(const char prompt[]) {
    char jawaban[20];
    while (true) {
        bacaBaris(prompt, jawaban, 20);
        if (jawaban[0] == 'y' || jawaban[0] == 'Y') return true;
        if (jawaban[0] == 'n' || jawaban[0] == 'N') return false;
        cout << "Masukkan y untuk ya atau n untuk tidak.\n";
    }
}

bool adaDiQueue(int nota) {
    nodeQueue* current = frontQueue;
    while (current != nullptr) {
        if (current->nota == nota) return true;
        current = current->next;
    }
    return false;
}

bool adaDiStack(int nota) {
    nodeStack* current = topStack;
    while (current != nullptr) {
        if (current->nota == nota) return true;
        current = current->next;
    }
    return false;
}

nodeTree* cari_tree(nodeTree* akar, int nota) {
    if (akar == nullptr || akar->nota == nota) return akar;
    if (nota < akar->nota) return cari_tree(akar->kiri, nota);
    return cari_tree(akar->kanan, nota);
}

bool notaSudahDigunakan(int nota) {
    // Riwayat Stack tetap menyimpan nota yang sudah selesai, termasuk yang telah diambil.
    return adaDiQueue(nota) || adaDiStack(nota) || cari_tree(root, nota) != nullptr;
}

nodeTree* tambah_tree(nodeTree* akar, int nota, const char nama[]) {
    if (akar == nullptr) {
        nodeTree* baru = new nodeTree;
        baru->nota = nota;
        salinTeks(baru->nama, nama);
        baru->kiri = nullptr;
        baru->kanan = nullptr;
        return baru;
    }
    if (nota < akar->nota) akar->kiri = tambah_tree(akar->kiri, nota, nama);
    else if (nota > akar->nota) akar->kanan = tambah_tree(akar->kanan, nota, nama);
    return akar;
}

nodeTree* hapus_tree(nodeTree* akar, int nota) {
    if (akar == nullptr) return nullptr;

    if (nota < akar->nota) akar->kiri = hapus_tree(akar->kiri, nota);
    else if (nota > akar->nota) akar->kanan = hapus_tree(akar->kanan, nota);
    else {
        // Kasus 1: node tidak memiliki anak.
        if (akar->kiri == nullptr && akar->kanan == nullptr) {
            delete akar;
            return nullptr;
        }
        // Kasus 2: node hanya memiliki satu anak.
        if (akar->kiri == nullptr) {
            nodeTree* pengganti = akar->kanan;
            delete akar;
            return pengganti;
        }
        if (akar->kanan == nullptr) {
            nodeTree* pengganti = akar->kiri;
            delete akar;
            return pengganti;
        }
        // Kasus 3: dua anak. Gunakan successor terkecil dari subtree kanan.
        nodeTree* successor = akar->kanan;
        while (successor->kiri != nullptr) successor = successor->kiri;
        akar->nota = successor->nota;
        salinTeks(akar->nama, successor->nama);
        akar->kanan = hapus_tree(akar->kanan, successor->nota);
    }
    return akar;
}

void preorder(nodeTree* akar, int& no) {
    if (akar == nullptr) return;
    cout << no++ << ". [" << akar->nota << "] " << akar->nama << '\n';
    preorder(akar->kiri, no);
    preorder(akar->kanan, no);
}

void inorder(nodeTree* akar, int& no) {
    if (akar == nullptr) return;
    inorder(akar->kiri, no);
    cout << no++ << ". [" << akar->nota << "] " << akar->nama << '\n';
    inorder(akar->kanan, no);
}

void postorder(nodeTree* akar, int& no) {
    if (akar == nullptr) return;
    postorder(akar->kiri, no);
    postorder(akar->kanan, no);
    cout << no++ << ". [" << akar->nota << "] " << akar->nama << '\n';
}

int inputNota() {
    char input[256];
    int nota;
    while (true) {
        bacaBaris("Masukkan nomor nota: ", input, 256);
        if (ubahKeAngkaPositif(input, nota)) return nota;
        cout << "Nomor nota harus berupa angka lebih dari 0!\n";
    }
}

void tambah_cucian() {
    do {
        cout << "\n=== Tambah Cucian ===\n";
        int nota = inputNota();
        if (notaSudahDigunakan(nota)) {
            cout << "Nomor nota " << nota << " sudah pernah digunakan!\n";
        } else {
            char nama[PANJANG_NAMA + 1];
            do {
                bacaBaris("Masukkan nama cucian: ", nama, PANJANG_NAMA + 1);
                if (teksKosong(nama)) cout << "Nama cucian tidak boleh kosong!\n";
            } while (teksKosong(nama));

            nodeQueue* baru = new nodeQueue;
            baru->nota = nota;
            salinTeks(baru->nama, nama);
            baru->next = nullptr;
            if (frontQueue == nullptr) frontQueue = rearQueue = baru;
            else {
                rearQueue->next = baru;
                rearQueue = baru;
            }
            cout << "Berhasil memasukkan cucian!\n";
        }
    } while (inputKonfirmasi("Apakah ingin menambahkan cucian lagi? (y/n): "));
}

void lihat_antrean() {
    cout << "\n=== Cucian Dalam Antrean ===\n";
    if (frontQueue == nullptr) {
        cout << "Antrean kosong!\n";
        return;
    }
    nodeQueue* current = frontQueue;
    int no = 1;
    while (current != nullptr) {
        cout << no++ << ". [" << current->nota << "] " << current->nama << '\n';
        current = current->next;
    }
}

void proses_cucian() {
    if (frontQueue == nullptr) {
        cout << "Antrean kosong! Tidak ada cucian yang dapat diproses.\n";
        return;
    }

    // Salin data sebelum node antrean dihapus.
    int nota = frontQueue->nota;
    char nama[PANJANG_NAMA + 1];
    salinTeks(nama, frontQueue->nama);

    nodeQueue* nodeLama = frontQueue;
    frontQueue = frontQueue->next;
    if (frontQueue == nullptr) rearQueue = nullptr;
    delete nodeLama;

    // Push ke Stack: cucian terbaru berada di posisi paling atas.
    nodeStack* selesai = new nodeStack;
    selesai->nota = nota;
    salinTeks(selesai->nama, nama);
    selesai->next = topStack;
    topStack = selesai;

    // Masukkan juga ke BST sebagai cucian yang menunggu diambil.
    root = tambah_tree(root, nota, nama);
    cout << "Berhasil memproses cucian " << nama << " (nota " << nota << ")!\n";
}

void lihat_riwayat() {
    cout << "\n=== Cucian Yang Sudah Selesai ===\n";
    if (topStack == nullptr) {
        cout << "Belum ada cucian yang selesai diproses!\n";
        return;
    }
    nodeStack* current = topStack;
    int no = 1;
    while (current != nullptr) {
        cout << no++ << ". [" << current->nota << "] " << current->nama << '\n';
        current = current->next;
    }
}

void cari_cucian() {
    cout << "\n=== Cari Cucian Di Rak ===\n";
    if (root == nullptr) {
        cout << "Rak kosong!\n";
        return;
    }
    int nota = inputNota();
    nodeTree* hasil = cari_tree(root, nota);
    if (hasil == nullptr) cout << "Cucian dengan nota " << nota << " tidak ditemukan di rak!\n";
    else cout << "Ditemukan: [" << hasil->nota << "] " << hasil->nama << '\n';
}

void lihat_rak() {
    cout << "\n=== Isi Rak Cucian ===\n";
    if (root == nullptr) {
        cout << "Rak kosong!\n";
        return;
    }
    cout << "1. Pre-order\n2. In-order\n3. Post-order\n";
    int pilihan = inputAngka("Masukkan pilihan: ", 1, 3);
    int no = 1;
    if (pilihan == 1) {
        cout << "\nIsi Rak (Pre-order):\n";
        preorder(root, no);
    } else if (pilihan == 2) {
        cout << "\nIsi Rak (In-order):\n";
        inorder(root, no);
    } else {
        cout << "\nIsi Rak (Post-order):\n";
        postorder(root, no);
    }
}

void ambil_cucian() {
    cout << "\n=== Ambil Cucian ===\n";
    if (root == nullptr) {
        cout << "Rak kosong!\n";
        return;
    }
    int nota = inputNota();
    nodeTree* hasil = cari_tree(root, nota);
    if (hasil == nullptr) {
        cout << "Cucian dengan nota " << nota << " tidak ada di rak!\n";
        return;
    }
    char nama[PANJANG_NAMA + 1];
    salinTeks(nama, hasil->nama);
    root = hapus_tree(root, nota);
    // Stack tidak dihapus karena merupakan riwayat cucian selesai.
    cout << "Cucian " << nama << " telah diambil pelanggan!\n";
}

void hapusQueue() {
    while (frontQueue != nullptr) {
        nodeQueue* temp = frontQueue;
        frontQueue = frontQueue->next;
        delete temp;
    }
    rearQueue = nullptr;
}

void hapusStack() {
    while (topStack != nullptr) {
        nodeStack* temp = topStack;
        topStack = topStack->next;
        delete temp;
    }
}

void hapusSemuaTree(nodeTree* akar) {
    if (akar == nullptr) return;
    hapusSemuaTree(akar->kiri);
    hapusSemuaTree(akar->kanan);
    delete akar;
}

void tampilkanMenu() {
    cout << "\n====================================\n";
    cout << "       MANAJEMEN LAUNDRY RANI\n";
    cout << "====================================\n";
    cout << "1. Tambah Cucian\n";
    cout << "2. Lihat Cucian Dalam Antrean\n";
    cout << "3. Proses Cucian\n";
    cout << "4. Lihat Cucian Yang Sudah Selesai\n";
    cout << "5. Cari Cucian Di Rak\n";
    cout << "6. Lihat Isi Rak\n";
    cout << "7. Ambil Cucian\n";
    cout << "8. Keluar\n";
    cout << "====================================\n";
}

int main() {
    cout << "====================================\n";
    cout << "   SELAMAT DATANG DI LAUNDRY RANI\n";
    cout << "====================================\n";

    int pilihan;
    do {
        tampilkanMenu();
        pilihan = inputAngka("Masukkan pilihan Anda: ", 1, 8);
        switch (pilihan) {
            case 1: tambah_cucian(); break;
            case 2: lihat_antrean(); break;
            case 3: proses_cucian(); break;
            case 4: lihat_riwayat(); break;
            case 5: cari_cucian(); break;
            case 6: lihat_rak(); break;
            case 7: ambil_cucian(); break;
            case 8: cout << "Terima kasih telah menggunakan Manajemen Laundry Rani!\n"; break;
        }
    } while (pilihan != 8);

    hapusQueue();
    hapusStack();
    hapusSemuaTree(root);
    root = nullptr;
    return 0;
}
