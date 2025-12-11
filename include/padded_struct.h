//
// Created by oguzh on 11.12.2025.
//

#ifndef PADDED_STRUCT_H
#define PADDED_STRUCT_H


struct alignas(64) padded_room {
    int roomID;
    int roomSize;
    char roomName[64-2*sizeof(int)];
};

#endif //PADDED_STRUCT_H
