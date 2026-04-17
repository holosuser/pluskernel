#include "lib.hpp"
volatile char* vimem=(volatile char*)0xB8000;
int cursor=0;

void print(const char* str) {
    while (*str){
        if (*str == '\n') {
            cursor+=(80 - (cursor % 80));
        } else {
            vimem[cursor * 2]=*str;
            vimem[cursor * 2 + 1]=0x07;
            cursor++;
        }
        str++;
    }
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
}
