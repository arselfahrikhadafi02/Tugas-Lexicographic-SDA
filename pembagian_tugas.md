# Pembagian Tugas & Dependency Functions
**Proyek Kamus Leksikografi (Trie & List)**  
**Tim: Kemal & Arsel — Bahasa C**

---

## 1. Urutan Pengerjaan & Dependency

Kerjakan fungsi sesuai urutan di bawah. Jangan mulai nomor selanjutnya sebelum nomor sebelumnya selesai dan bisa dikompilasi.

| Urutan | File | Fungsi | Bergantung pada | Keterangan |
|--------|------|--------|-----------------|------------|
| 1 | `boolean.h` | (definisi tipe) | — | Tidak ada dependency |
| 2 | `dictionary.h` | `struct WordNode` | `boolean.h` | Hanya deklarasi struct |
| 3 | `dictionary.c` | `AlokasiWordNode` | `dictionary.h` | Fondasi linked list |
| 4 | `dictionary.c` | `InsertWord` | `AlokasiWordNode` | Pakai AlokasiWordNode |
| 5 | `dictionary.c` | `PrintWordList` | `InsertWord` | Traversal list untuk display |
| 6 | `dictionary.c` | `FindWordByIndex` | `InsertWord` | Ambil kata ke-n dari list |
| 7 | `nbtree.h` | `struct TrieNode` | `boolean.h`, `dictionary.h` | Deklarasi node trie |
| 8 | `nbtree.c` | `AlokasiTrieNode` | `nbtree.h` | Fondasi trie, selesaikan duluan |
| 9 | `nbtree.c` | `InsertWordToTrie` | `AlokasiTrieNode` | Sudah dibahas & diperbaiki |
| 10 | `nbtree.c` | `AddSynonymToTrie` | `InsertWordToTrie`, `InsertWord` | Butuh trie + linked list siap |
| 11 | `nbtree.c` | `AddThesaurusToTrie` | `InsertWordToTrie`, `InsertWord` | Sama seperti AddSynonym |
| 12 | `nbtree.c` | `DFS` (helper) | `AlokasiTrieNode` | Rekursif, helper privat |
| 13 | `nbtree.c` | `PrintSuggestions` | `DFS`, `InsertWordToTrie` | Gabungan navigasi + DFS |
| 14 | `main.c` | `InitData` | Semua fungsi trie + dict | Semua harus selesai dulu |
| 15 | `main.c` | `main()` + state machine | `InitData` + semua modul | Dikerjakan terakhir |

---

## 2. Bagian Kemal — `nbtree.c`

Bertanggung jawab atas seluruh modul Trie (`nbtree.h` dan `nbtree.c`).

| File | Fungsi | Keterangan | Dependency |
|------|--------|------------|------------|
| `nbtree.c` | `AlokasiTrieNode` | Sudah ada, tambah `return P` | `nbtree.h` |
| `nbtree.c` | `InsertWordToTrie` | Tulis ulang dari awal | `AlokasiTrieNode` |
| `nbtree.c` | `DFS` (helper) | Rekursif, helper privat (`static`) | `nbtree.h` |
| `nbtree.c` | `PrintSuggestions` | Fase 1 navigasi + Fase 2 DFS | `DFS`, `InsertWordToTrie` |
| `nbtree.c` | `AddSynonymToTrie` | Cari node kata, tambah ke list sinonim | `InsertWordToTrie`, `InsertWord` |
| `nbtree.c` | `AddThesaurusToTrie` | Sama seperti `AddSynonymToTrie` | `InsertWordToTrie`, `InsertWord` |

**Catatan untuk Kemal:**
- `AlokasiTrieNode`: tambahkan `return P` di akhir fungsi (bug saat ini).
- `InsertWordToTrie`: tulis ulang sepenuhnya — logika lama salah di inisialisasi `current` dan assignment `isEndWord`.
- `DFS` adalah `static` helper, cukup deklarasikan di atas `PrintSuggestions` tanpa expose ke header.
- `AddSynonymToTrie` dan `AddThesaurusToTrie` baru bisa dikerjakan setelah Arsel selesai `InsertWord`.

---

## 3. Bagian Arsel — `dictionary.c` & `main.c`

Bertanggung jawab atas modul Linked List (`dictionary.h` dan `dictionary.c`) dan seluruh `main.c`.

| File | Fungsi | Keterangan | Dependency |
|------|--------|------------|------------|
| `dictionary.c` | `AlokasiWordNode` | `malloc` + inisialisasi node | `dictionary.h` |
| `dictionary.c` | `InsertWord` | Tambah kata ke linked list | `AlokasiWordNode` |
| `dictionary.c` | `PrintWordList` | Traversal + cetak bernomor | `InsertWord` |
| `dictionary.c` | `FindWordByIndex` | Ambil kata ke-n dari list | `InsertWord` |
| `main.c` | `InitData` | Hardcode minimal untuk tes | Semua fungsi trie + dict |
| `main.c` | `main()` + state machine | Loop utama, `switch-case` state 0–3 | `InitData` + semua modul |

**Catatan untuk Arsel:**
- Kerjakan `dictionary.c` sepenuhnya dulu sebelum menyentuh `main.c`.
- `InsertWord`: boleh pilih insert di head (O(1)) atau tail (O(n)) sesuai preferensi tim.
- `FindWordByIndex`: dipakai di State 3 saat user memilih nomor sinonim/thesaurus.
- `InitData`: hardcode **minimal** (10–15 kata saja untuk keperluan tes). Buat sebagai fungsi `InitData(addressTrie *root)` agar nanti tinggal ganti isinya dengan loader file eksternal — tanpa ubah kode lain.
- Data dummy bersifat sementara. Setelah program berjalan lancar, isi `InitData` akan diganti dengan loader dari kamus eksternal tanpa perlu menyentuh fungsi lain.
- State machine: gunakan `switch-case` dengan variabel `int state` bernilai 0, 1, 2, atau 3 sesuai README.

---

## 4. Titik Integrasi

Dua titik di mana pekerjaan Kemal dan Arsel harus digabung sebelum lanjut:

| Titik integrasi | Kemal menyediakan | Arsel membutuhkan |
|-----------------|-------------------|-------------------|
| `AddSynonymToTrie` / `AddThesaurusToTrie` | `InsertWordToTrie` sudah berjalan | `InsertWord` sudah berjalan |
| `main()` state machine | `PrintSuggestions`, `AddSynonymToTrie`, `AddThesaurusToTrie` | `PrintWordList`, `FindWordByIndex`, `InitData` |

> Pastikan kompilasi bersama dilakukan setelah kedua modul selesai, sebelum mengerjakan `main.c`.

---

## 5. Catatan Arsitektur — Data Eksternal

Saat ini data kata menggunakan hardcode untuk keperluan tes. Ke depannya data akan diambil dari kamus eksternal. Agar migrasi mudah, **hanya `InitData` yang perlu diubah** — semua modul lain tidak perlu disentuh.

```c
/* Sekarang (hardcode untuk tes) */
void InitData(addressTrie *root) {
    InsertWordToTrie(root, "baca");
    AddSynonymToTrie(*root, "baca", "membaca");
    /* dst, minimal 10-15 kata */
}

/* Nanti (dari file eksternal, cukup ganti isi fungsi ini) */
void InitData(addressTrie *root) {
    LoadFromFile(root, "kamus.txt");
}
```
