#include "initdata.h"

void InitData(addressTrie *root) {
    InsertWordToTrie(root, "baca");
    InsertWordToTrie(root, "bacaan");
    InsertWordToTrie(root, "bacan");
    InsertWordToTrie(root, "baru");
    InsertWordToTrie(root, "barat");
    InsertWordToTrie(root, "barang");
    InsertWordToTrie(root, "cari");
    InsertWordToTrie(root, "cepat");
    InsertWordToTrie(root, "cerita");
    InsertWordToTrie(root, "dalam");
    InsertWordToTrie(root, "damai");
    InsertWordToTrie(root, "dapat");
    InsertWordToTrie(root, "dapur");
    InsertWordToTrie(root, "ekor");
    InsertWordToTrie(root, "emas");
    InsertWordToTrie(root, "enak");
    InsertWordToTrie(root, "fajar");
    InsertWordToTrie(root, "fakta");
    InsertWordToTrie(root, "fasilitas");
    InsertWordToTrie(root, "gajah");
    InsertWordToTrie(root, "gala");
    InsertWordToTrie(root, "garis");
    InsertWordToTrie(root, "hati");
    InsertWordToTrie(root, "hujan");
    InsertWordToTrie(root, "hutan");
    InsertWordToTrie(root, "ikan");
    InsertWordToTrie(root, "ikut");
    InsertWordToTrie(root, "ilmu");
    InsertWordToTrie(root, "jari");
    InsertWordToTrie(root, "jalan");
    InsertWordToTrie(root, "jasa");
    InsertWordToTrie(root, "kaca");
    InsertWordToTrie(root, "kabar");
    InsertWordToTrie(root, "kacamata");
    InsertWordToTrie(root, "laba");
    InsertWordToTrie(root, "labu");
    InsertWordToTrie(root, "laci");
    InsertWordToTrie(root, "makan");
    InsertWordToTrie(root, "malam");
    InsertWordToTrie(root, "manis");
    InsertWordToTrie(root, "nasi");
    InsertWordToTrie(root, "nasi goreng");
    InsertWordToTrie(root, "nasi uduk");
    InsertWordToTrie(root, "orang");
    InsertWordToTrie(root, "otak");
    InsertWordToTrie(root, "padi");
    InsertWordToTrie(root, "pagar");
    InsertWordToTrie(root, "pakai");
    InsertWordToTrie(root, "palu");
    InsertWordToTrie(root, "qurban");
    InsertWordToTrie(root, "rasa");
    InsertWordToTrie(root, "rata");
    InsertWordToTrie(root, "rumah");
    InsertWordToTrie(root, "sapi");
    InsertWordToTrie(root, "sapu");
    InsertWordToTrie(root, "satu");
    InsertWordToTrie(root, "tahu");
    InsertWordToTrie(root, "taman");
    InsertWordToTrie(root, "tanah");
    InsertWordToTrie(root, "tangan");
    InsertWordToTrie(root, "uang");
    InsertWordToTrie(root, "ular");
    InsertWordToTrie(root, "umur");
    InsertWordToTrie(root, "vaksin");
    InsertWordToTrie(root, "waktu");
    InsertWordToTrie(root, "warna");
    InsertWordToTrie(root, "wisata");
    InsertWordToTrie(root, "xenon");
    InsertWordToTrie(root, "yakin");
    InsertWordToTrie(root, "zebra");

    AddSynonymToTrie(*root, "baca", "membaca");
    AddSynonymToTrie(*root, "baca", "menelaah");
    AddSynonymToTrie(*root, "baca", "mengeja");

    AddSynonymToTrie(*root, "cepat", "kilat");
    AddSynonymToTrie(*root, "cepat", "laju");

    AddSynonymToTrie(*root, "makan", "mengonsumsi");
    AddSynonymToTrie(*root, "makan", "menyantap");

    AddThesaurusToTrie(*root, "baca", "literasi");
    AddThesaurusToTrie(*root, "baca", "perpustakaan");
    AddThesaurusToTrie(*root, "baca", "buku");

    AddThesaurusToTrie(*root, "cepat", "kecepatan");
    AddThesaurusToTrie(*root, "cepat", "laju");

}