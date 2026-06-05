# Product Requirements Document (PRD)
## Aplikasi Kamus Leksikografi Berbasis Trie

| | |
|---|---|
| **Nama Proyek** | Aplikasi Kamus Leksikografi (Trie & List) |
| **Tim** | Kemal & Arsel |
| **Bahasa** | C |
| **Antarmuka** | Terminal / CLI |
| **Versi Dokumen** | 1.0 |
| **Status** | In Development |

---

## 1. Latar Belakang

Proyek ini dibuat sebagai implementasi struktur data tingkat lanjut dalam bentuk aplikasi yang fungsional. Aplikasi berfungsi sebagai kamus pintar berbasis terminal yang memanfaatkan **N-ary Tree (Trie)** untuk fitur *autocomplete* dan **Linked List** untuk penyimpanan relasi kata (sinonim & thesaurus).

Sumber data saat ini menggunakan data *hardcode* untuk keperluan pengujian. Setelah program berjalan lancar, sumber data akan dialihkan ke kamus eksternal tanpa mengubah arsitektur program.

---

## 2. Tujuan

- Mengimplementasikan struktur data Trie (First-Child Next-Sibling) untuk fitur *autocomplete* berbasis prefix.
- Mengimplementasikan Linked List untuk menyimpan dan menampilkan relasi kata (sinonim & thesaurus).
- Membangun antarmuka CLI yang mengikuti alur *state machine* yang jelas dan dapat diprediksi.
- Merancang arsitektur yang mudah dimigrasikan ke sumber data eksternal di masa mendatang.

---

## 3. Pengguna

Aplikasi ini digunakan langsung oleh pengembang (Kemal & Arsel) dan dosen/asesor dalam konteks pengujian dan penilaian mata kuliah struktur data. Pengguna diasumsikan familiar dengan antarmuka terminal.

---

## 4. Fitur & Kebutuhan Fungsional

### 4.1 Autocomplete / Suggestion (State 0 → State 1)

**Deskripsi:** Pengguna mengetik awalan kata (minimal 3 huruf). Program menampilkan daftar kata yang berawalan sama berdasarkan data di Trie.

**Kebutuhan:**
- Input diterima melalui `scanf` standar C.
- Program hanya memproses input jika panjang karakter ≥ 3.
- Hasil suggestion ditampilkan bernomor urut mulai dari `[1]`.
- Selalu tersedia opsi `[0]` untuk melewati suggestion dan menggunakan input asli.
- Jika tidak ada suggestion, program menampilkan pesan informatif dan input asli dijadikan Kata Aktif.

**Contoh output:**
```
Input: "bac"
Saran kata:
  [1] baca
  [2] bacaan
  [3] bacan
  [0] Lewati (pakai "bac")
Pilih nomor:
```

---

### 4.2 Menu Utama Kata (State 2)

**Deskripsi:** Setelah Kata Aktif ditentukan, program menampilkan menu tindakan.

**Kebutuhan:**
- Menampilkan Kata Aktif saat ini dengan jelas.
- Menyediakan empat pilihan aksi:
  - `[1]` Lihat Sinonim
  - `[2]` Lihat Thesaurus
  - `[3]` Simpan kata ke kalimat dan lanjut input berikutnya
  - `[4]` Keluar dari program
- Input selain 1–4 menampilkan pesan error dan mengulang menu.

**Contoh output:**
```
Kata aktif: "baca"
  [1] Lihat Sinonim
  [2] Lihat Thesaurus
  [3] Simpan & lanjut input
  [4] Keluar
Pilih aksi:
```

---

### 4.3 Sinonim & Thesaurus (State 3)

**Deskripsi:** Menampilkan daftar kata relasi dari Kata Aktif. Pengguna dapat memilih salah satu untuk menggantikan Kata Aktif.

**Kebutuhan:**
- Daftar ditampilkan bernomor urut mulai dari `[1]`.
- Selalu tersedia opsi `[0]` untuk kembali ke State 2 tanpa mengganti Kata Aktif.
- Jika pengguna memilih nomor valid, kata tersebut menjadi Kata Aktif baru dan program kembali ke State 2.
- Jika tidak ada data sinonim/thesaurus untuk kata tersebut, program menampilkan pesan informatif.

**Contoh output:**
```
Sinonim untuk "baca":
  [1] membaca
  [2] menelaah
  [3] mengeja
  [0] Kembali
Pilih nomor:
```

---

### 4.4 Sentence Builder

**Deskripsi:** Pengguna dapat menyimpan Kata Aktif ke dalam memori kalimat, lalu melanjutkan input kata berikutnya.

**Kebutuhan:**
- Pilihan `[3]` di State 2 menyimpan Kata Aktif ke buffer kalimat dan kembali ke State 0.
- Kalimat yang terbentuk ditampilkan saat program keluar (pilihan `[4]`).
- Urutan kata dalam kalimat mengikuti urutan penambahan.

**Contoh output saat keluar:**
```
Kalimat yang terbentuk:
"anak itu suka membaca buku"
```

---

## 5. Kebutuhan Non-Fungsional

| Kebutuhan | Spesifikasi |
|---|---|
| Bahasa | C standar (C89/C99) |
| I/O | `scanf` dan `printf` bawaan C, tanpa library OS eksternal |
| Library terlarang | `conio.h`, `termios.h`, atau library platform-spesifik lainnya |
| Manajemen memori | Semua alokasi menggunakan `malloc`, semua node diinisialisasi sebelum digunakan |
| Portabilitas | Dapat dikompilasi di Linux/Windows menggunakan GCC tanpa flag tambahan |
| Modularisasi | Kode dipisah ke dalam file header (`.h`) dan implementasi (`.c`) per modul |

---

## 6. Arsitektur & Struktur Data

### 6.1 Modul

| File | Tanggung Jawab |
|---|---|
| `boolean.h` | Definisi tipe `boolean`, `true`, `false` |
| `dictionary.h` | Deklarasi `struct WordNode` dan makro aksesor |
| `dictionary.c` | Implementasi operasi Linked List |
| `nbtree.h` | Deklarasi `struct TrieNode` dan makro aksesor |
| `nbtree.c` | Implementasi operasi Trie |
| `main.c` | Inisialisasi data, loop utama, state machine |

### 6.2 Struktur Data Utama

**Trie Node (First-Child Next-Sibling):**
```c
typedef struct tTrieNode {
    char        info;
    boolean     isEndWord;
    addressWord synonims;    /* pointer ke Linked List sinonim */
    addressWord thesaurus;   /* pointer ke Linked List thesaurus */
    addressTrie firstChild;
    addressTrie nextSibling;
} TrieNode;
```

**Word Node (Singly Linked List):**
```c
typedef struct tWordNode {
    char        word[100];
    addressWord next;
} WordNode;
```

### 6.3 Alur State Machine

```
[State 0] Input prefix (≥3 huruf)
     ↓
[State 1] Tampilkan suggestion → pilih → Kata Aktif ditentukan
     ↓
[State 2] Menu aksi Kata Aktif
     ├─[1]→ [State 3] Lihat Sinonim   → pilih → Kata Aktif diganti → kembali State 2
     ├─[2]→ [State 3] Lihat Thesaurus → pilih → Kata Aktif diganti → kembali State 2
     ├─[3]→ Simpan ke kalimat → kembali State 0
     └─[4]→ Tampilkan kalimat → Keluar
```

---

## 7. Sumber Data

### 7.1 Fase Saat Ini (Testing)

Data kata, sinonim, dan thesaurus di-*hardcode* di dalam fungsi `InitData()` pada `main.c`. Jumlah data minimal (10–15 kata) cukup untuk memverifikasi semua fitur berjalan benar.

### 7.2 Fase Selanjutnya (Produksi)

Setelah program diverifikasi, isi fungsi `InitData()` akan diganti dengan loader dari file kamus eksternal. **Tidak ada perubahan pada modul lain** — hanya isi `InitData()` yang berubah.

```c
/* Fase testing */
void InitData(addressTrie *root) {
    InsertWordToTrie(root, "baca");
    AddSynonymToTrie(*root, "baca", "membaca");
    /* ... */
}

/* Fase produksi — hanya fungsi ini yang diganti */
void InitData(addressTrie *root) {
    LoadFromFile(root, "kamus.txt");
}
```

Format file eksternal dan mekanisme parsing akan ditentukan pada fase berikutnya.

---

## 8. Batasan & Asumsi

- Input pengguna diasumsikan hanya berisi huruf alfabet (a–z), tanpa angka atau karakter khusus.
- Panjang kata maksimum 99 karakter (sesuai ukuran array `word[100]`).
- Panjang kalimat tidak dibatasi secara eksplisit, tetapi dibatasi oleh memori sistem.
- Program tidak perlu menyimpan state antar sesi (tidak ada persistensi data ke disk pada fase ini).
- Tidak ada fitur *undo* untuk kata yang sudah disimpan ke kalimat.

---

## 9. Kriteria Selesai (Definition of Done)

Sebuah fitur dianggap selesai jika memenuhi seluruh kriteria berikut:

- [ ] Fungsi dapat dikompilasi tanpa *warning* dengan `gcc -Wall`.
- [ ] Fungsi berperilaku sesuai spesifikasi di semua skenario normal.
- [ ] Fungsi menangani edge case: input `NULL`, string kosong, kata tidak ditemukan di Trie.
- [ ] Tidak ada *memory leak* untuk operasi alokasi yang dilakukan fungsi tersebut.
- [ ] Kode mengikuti konvensi penamaan dan makro aksesor yang sudah didefinisikan di header.

---

## 10. Risiko & Mitigasi

| Risiko | Dampak | Mitigasi |
|---|---|---|
| Bug di `InsertWordToTrie` menyebabkan data tidak tersimpan | Tinggi | Perbaikan sudah diidentifikasi, tulis ulang dari awal |
| `AlokasiTrieNode` tidak ada `return P` | Tinggi | Segera perbaiki sebelum fungsi lain diimplementasi |
| Integrasi trie + linked list gagal di `AddSynonymToTrie` | Sedang | Pastikan `InsertWord` selesai sebelum Kemal mengerjakan fungsi ini |
| Migrasi ke data eksternal membutuhkan refactor besar | Rendah | Arsitektur `InitData` sudah dirancang untuk isolasi perubahan |
