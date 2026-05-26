# Arsitektur Proyek: Aplikasi Kamus Leksikografi (Trie & List)

**Tim Pengembang:** Kemal & Arsel  
**Bahasa Pemrograman:** C  
**Antarmuka:** Terminal / Command Line Interface (CLI)

---

## 📌 Deskripsi Proyek
Aplikasi terminal berbasis teks yang berfungsi ganda sebagai kamus pintar dan *sentence builder*. Aplikasi ini memanfaatkan struktur data tingkat lanjut untuk memberikan fitur *autocomplete* (*suggestion*), serta pencarian sinonim dan thesaurus dari kata yang dipilih.

**Catatan Revisi:** Fitur Huffman Code dihapus dari spesifikasi awal untuk memfokuskan pengerjaan pada optimasi *N-ary Tree* dan memori.

---

## ⚙️ Kebutuhan Sistem (Requirements)
1. **Leksikografi dengan Trie (N-ary Tree):** Digunakan untuk fitur *suggestion*. Jika pengguna mengetik minimal 3 huruf dan menekan `Enter`, program akan menampilkan daftar tebakan kata.
2. **Kamus Sinonim & Thesaurus:** Penyimpanan data relasi kata menggunakan struktur data *Linked List*. 
3. **Data Dummy:** Menggunakan data sinonim dan thesaurus yang di-*hardcode* di dalam program untuk keperluan *testing*.
4. **I/O Standar:** Menggunakan `scanf` bawaan C dan dieksekusi murni di terminal tanpa *library* OS eksternal (seperti `conio.h` atau `termios.h`).

---

## 🔄 Alur Program (State Machine)

1. **State 0 (Input):** Pengguna menginput kata/awalan kata (minimal 3 huruf) melalui `scanf`.
2. **State 1 (Suggestion):** Program menampilkan *List Suggestion* (opsi 1, 2, 3... atau 0 untuk lewat/tidak memilih).
    * Jika pengguna memilih angka, kata di nomor tersebut menjadi **Kata Aktif**.
    * Jika pengguna memilih 0, input asli pengguna yang menjadi **Kata Aktif**.
3. **State 2 (Menu Utama Kata):** Menampilkan opsi tindakan untuk Kata Aktif:
    * `[1]` Lihat Sinonim
    * `[2]` Lihat Thesaurus
    * `[3]` Lanjut input kata berikutnya (Kata Aktif disimpan ke dalam memori kalimat)
    * `[4]` Keluar dari program
4. **State 3 (Aksi Sinonim/Thesaurus):** * Menampilkan daftar kata. Pengguna dapat memilih nomor urutannya.
    * Jika pengguna memilih sebuah nomor, kata tersebut **menggantikan** Kata Aktif, lalu program kembali ke State 2.

---

## 🧱 Struktur Data (Abstract Data Types)

### 1. `nbTree` (First-Child Next-Sibling)
Digunakan sebagai mesin **Trie** untuk pencarian karakter.
* Setiap node menampung satu `char`.
* Menggunakan pointer `firstChild` untuk huruf berikutnya dalam satu kata.
* Menggunakan pointer `nextSibling` untuk alternatif huruf lain di posisi yang sama.
* Memiliki indikator `boolean isEndOfWord` untuk menandai huruf terakhir dari sebuah kata yang valid.
* Jika `isEndOfWord == true`, node tersebut memiliki *pointer* yang mengarah ke *Linked List* Sinonim dan Thesaurus.

### 2. `Linear Singly Linked List`
Digunakan untuk menampung data kamus (Sinonim & Thesaurus).
* Node menyimpan *string* kata.
* Operasi utamanya adalah penambahan kata (`Insert`) dan pencetakan layar (*traversing* List menggunakan *looping* murni untuk nampilin teks).

---

## 📁 Struktur File & Modularisasi (TO-DO List)

Proyek ini dipisah ke dalam beberapa file (*header* dan *source*) agar lebih terstruktur:

- [ ] **`boolean.h`**
  * Mendefinisikan tipe data boolean (`true` / `false`).
- [ ] **`dictionary.h` & `dictionary.c`**
  * Deklarasi `struct WordNode`.
  * Fungsi alokasi memori untuk *Linked List*.
  * Fungsi menambahkan kata ke dalam List.
  * Fungsi mencetak seluruh kata di dalam List (murni *looping* untuk *display* teks, bukan untuk perhitungan).
- [ ] **`nbtree.h` & `nbtree.c`**
  * Deklarasi `struct TrieNode` (dengan pointer N-ary dan pointer *dictionary*).
  * Fungsi alokasi node Trie.
  * Fungsi `InsertWordToTrie` (memasukkan kata secara rekursif/iteratif).
  * Fungsi `GetSuggestions` (menggunakan *Depth-First Search* dari ujung *prefix* 3 huruf).
- [ ] **`main.c`**
  * Fungsi untuk menginisialisasi data *dummy* secara *hardcode*.
  * *Looping* utama program (`while`) dan logika UI `switch-case` untuk mengatur transisi antar menu (State).