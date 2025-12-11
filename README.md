**Cache line** : [ msb ... ][ cache line ID ][ offset bits (6 bits)]

📌 Layout: normal structure
| index | address        | line_id     | offset_in_line |
| ----: | -------------- | ----------- | -------------- |
|     0 | 0x55ec0ab62300 | 157b02ad88c | 0              |
|     1 | 0x55ec0ab62308 | 157b02ad88c | 8              |
|     2 | 0x55ec0ab62310 | 157b02ad88c | 16             |
|     3 | 0x55ec0ab62318 | 157b02ad88c | 24             |
|     4 | 0x55ec0ab62320 | 157b02ad88c | 32             |
|     5 | 0x55ec0ab62328 | 157b02ad88c | 40             |
|     6 | 0x55ec0ab62330 | 157b02ad88c | 48             |
|     7 | 0x55ec0ab62338 | 157b02ad88c | 56             |

Süre: 5.38799

📌 Layout: padded structure
| index | address        | line_id     | offset_in_line |
| ----: | -------------- | ----------- | -------------- |
|     0 | 0x55ec0ab63280 | 157b02ad8ca | 0              |
|     1 | 0x55ec0ab632c0 | 157b02ad8cb | 0              |
|     2 | 0x55ec0ab63300 | 157b02ad8cc | 0              |
|     3 | 0x55ec0ab63340 | 157b02ad8cd | 0              |
|     4 | 0x55ec0ab63380 | 157b02ad8ce | 0              |
|     5 | 0x55ec0ab633c0 | 157b02ad8cf | 0              |
|     6 | 0x55ec0ab63400 | 157b02ad8d0 | 0              |
|     7 | 0x55ec0ab63440 | 157b02ad8d1 | 0              |


Süre: 1.50059


MESI State Tablosu:

| State             | MESI Anlamı                                                          | MOESI Anlamı (AMD)                                                                               | MESIF Anlamı (Intel)                                                            |
| ----------------- | -------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------ | ------------------------------------------------------------------------------- |
| **M — Modified**  | Cache line yalnızca bu çekirdekte, RAM’den farklı, yazılmış durumda. | Aynı şekilde tek “dirty” kopya; write-back gerekir.                                              | Tek geçerli “dirty” kopya; çekirdek veri sahibidir.                             |
| **E — Exclusive** | Temiz ve yalnızca tek çekirdekte, henüz yazılmamış.                  | Temiz, tek çekirdekli kopya; yazmaya hazır.                                                      | Temiz, tek çekirdekte; ilk yazmada M durumuna geçer.                            |
| **S — Shared**    | Temiz, birden fazla çekirdekte; sadece okuma.                        | Temiz paylaşılmış kopya.                                                                         | Temiz, paylaşılmış kopya (Forwarder **değil**).                                 |
| **I — Invalid**   | Cache line geçersiz; başka çekirdeğin write'ı veya eviction sonrası. | Geçersiz cache line.                                                                             | Geçersiz cache line.                                                            |
| **O — Owned**     | ❌ MESI’de yok                                                        | “Dirty shared” durum: diğer çekirdeklere veri servis eden çekirdek. RAM henüz güncellenmemiştir. | ❌ MESIF’te yok                                                                  |
| **F — Forward**   | ❌ MESI’de yok                                                        | ❌ MOESI’de yok                                                                                   | Shared kopyalar arasında tek bir “forwarder” çekirdek diğerlerine veri dağıtır. |


False Sharing – MESI State Ping-Pong Senaryosu
----------------------------------------------

Başlangıç durumu:
- x ve y farklı değişkenlerdir fakat **aynı cache line içindedir**.
- Core0: x üzerinde çalışır
- Core1: y üzerinde çalışır

struct S {
    int x; // Core0 yazıyor
    int y; // Core1 yazıyor
}; // x ve y aynı cache line

Başlangıç:
Core0: I
Core1: I

1) Core0, x değişkenine write yapar:
- Cache line RAM’den Core0’a alınır
- Core0: I → M
- Core1: I

2) Core1, y değişkenine write yapar:
- Aynı cache line için Read-For-Ownership (RFO) gönderir
- Core0’daki cache line invalidate edilir: M → I
- Core1 cache line’ı alır ve yazar: I → M

Durum:
Core0: I
Core1: M
3) Core0 tekrar x yazmak ister:
- RFO yayınlar
- Core1’deki cache line invalidate edilir: M → I
- Core0 cache line’ı alır: I → M

Durum:
Core0: M
Core1: I

Bu süreç loop içinde tekrarlandığında:
- Cache line sürekli Core0 ↔ Core1 arasında taşınır
- Her write, karşı core’da **invalidate** üretir
- Buna **cache line ping-pong** denir
- Mantıksal paylaşım yoktur (farklı değişkenlerdir) fakat
  **donanımsal paylaşım vardır (aynı cache line)**

Sonuç:
- Ağır performans kaybı
- Yüksek coherence trafiği
- Pipeline stall ve latency artışı

Bu durum, değişkenlerin `alignas(64)` ile ayrı cache line’lara
yerleştirilmesiyle engellenebilir.
