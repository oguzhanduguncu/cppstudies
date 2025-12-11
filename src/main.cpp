#include <iomanip>
#include <iostream>
#include <vector>
#include <thread>

#include "padded_struct.h"
#include "struct.h"
//Cache line : [ msb ... ][ cache line ID ][ offset bits (6 bits) ]
void roomIdentifier(room &sharedRoom) {
    for (long long int i = 0; i < 300'000'000; ++i) {
        sharedRoom.roomID++;
    }
};

void paddedRoomIdentifier(padded_room& sharedRoom) {
    for (long long int i = 0; i < 300'000'000; ++i) {
        sharedRoom.roomID++;
    }
};

int main() {
    std::vector<std::thread> threads;
    const unsigned int N = std::thread::hardware_concurrency();
    threads.reserve(N);

    std::vector<room> rooms(N);

    std::cout << "=== Layout: " << "normal structure" << " ===\n";
    std::cout << "index  address          line_id       offset_in_line\n";

    for (std::size_t i = 0; i < rooms.size(); ++i) {
        auto addr = reinterpret_cast<std::uintptr_t>(&rooms[i]);
        std::uintptr_t line_id = addr >> 6;      // 64 byte = 2^6
        std::uintptr_t offset  = addr & 0x3F;    // 0..63

        std::cout << std::setw(5) << i << "  "
                  << "0x" << std::hex << addr << std::hex << "  "
                  << std::setw(10) << line_id << "  "
                  << std::setw(14) << offset << "\n";
    }
    std::cout << "\n";


    auto start = std::chrono::high_resolution_clock::now();
    for (int i  = 0; i < N; ++i) {
        threads.emplace_back(roomIdentifier, std::ref(rooms[i]));
    }
    for (auto& t : threads) {
        t.join();
    }
    threads.clear();
    threads.reserve(N);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration<double>(end - start).count() << std::endl;

    std::vector<padded_room> paddedRooms(N);

    std::cout << "=== Layout: " << "padded structure" << " ===\n";
    std::cout << "index  address          line_id       offset_in_line\n";

    for (std::size_t i = 0; i < paddedRooms.size(); ++i) {
        auto addr = reinterpret_cast<std::uintptr_t>(&paddedRooms[i]);
        std::uintptr_t line_id = addr >> 6;      // 64 byte = 2^6
        std::uintptr_t offset  = addr & 0x3F;    // 0..63

        std::cout << std::setw(5) << i << "  "
                  << "0x" << std::hex << addr << std::hex << "  "
                  << std::setw(10) << line_id << "  "
                  << std::setw(14) << offset << "\n";
    }
    std::cout << "\n";

    auto paddedstart = std::chrono::high_resolution_clock::now();
    for (int i  = 0; i < N; ++i) {
        threads.emplace_back(paddedRoomIdentifier, std::ref(paddedRooms[i]));
    }
    for (auto& t : threads) {
        t.join();
    }
    auto paddedend = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration<double>(paddedend - paddedstart).count() << std::endl;

}