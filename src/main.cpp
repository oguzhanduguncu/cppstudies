#include <iostream>
#include <vector>
#include <thread>

#include "padded_struct.h"
#include "struct.h"

void roomIdentifier(room& sharedRoom) {
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