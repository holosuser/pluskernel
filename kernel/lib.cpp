#include <cstdint>
#include "lib.hpp"
volatile char* vimem=(volatile char*)0xB8000;
int cursor=0;

void outb(uint16_t port, uint8_t value){
    asm volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

void updatecursor() {
    uint16_t pos = cursor;

    outb(0x3D4, 14);
    outb(0x3D5, pos >> 8);

    outb(0x3D4, 15);
    outb(0x3D5, pos);
}

void print(const char* str) {
    while (*str){
        if (*str == '\n') {
            cursor+=(80 - (cursor % 80));
        }
        else if (*str == '\b') {
            if (cursor > 0) {
                cursor--;
                vimem[cursor * 2] = ' ';
                vimem[cursor * 2 + 1] = 0x07;
            }
        }
        else {
            vimem[cursor * 2]=*str;
            vimem[cursor * 2 + 1]=0x07;
            cursor++;
        }
        str++;
    }
    updatecursor();
}

void startlogo(){
    print("        888    d8P  8888888888 8888888b.  888b    888 8888888888 888      \n");
    print("        888   d8P   888        888   Y88b 8888b   888 888        888      \n");
    print("        888  d8P    888        888    888 88888b  888 888        888      \n");
    print("  888   888d88K     8888888    888   d88P 888Y88b 888 8888888    888      \n");
    print("8888888 8888888b    888        8888888P8  888 Y88b888 888        888      \n");
    print("  888   888  Y88b   888        888 T88b   888  Y88888 888        888      \n");
    print("        888   Y88b  888        888  T88b  888   Y8888 888        888      \n");
    print("        888    Y88b 8888888888 888   T88b 888    Y888 8888888888 88888888 \n"); 
}

void clearscreen(){
    for (int i = 0; i < 80 * 25; i++){
        vimem[i * 2]=' ';
        vimem[i * 2 + 1]=0x07;
    }
    cursor=0;
    updatecursor();
}
