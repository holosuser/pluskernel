#include <cstdint>
#include "psh.hpp"
#include"../../lib.hpp"
#define MAX_INPUT 256

uint8_t inb(uint16_t port){
    uint8_t result;
    asm volatile ("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

char keyboard_get_char(){
    uint8_t scancode;
    while (!(inb(0x64) & 1));
    scancode = inb(0x60);
    static const char scancode_table[]={
        0, 27, '1','2','3','4','5','6','7','8','9','0','-','=', '\b',
        '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',
        0, 'a','s','d','f','g','h','j','k','l',';','\'','`',
        0, '\\','z','x','c','v','b','n','m',',','.','/', 0,
        '*', 0, ' '
    };

    if (scancode < sizeof(scancode_table)){
        return scancode_table[scancode];
    }
    return 0;
}

char getch(){
    return keyboard_get_char();
}

void putchar(char c){
    char str[2] = {c, 0};
    print(str);
}

bool streq(const char* a, const char* b){
    while (*a && *b){
        if (*a != *b) return false;
        a++;
        b++;
    }
    return *a == *b;
}


void handle_command(const char* cmd) {
    if (streq(cmd, "help")) {
        print("PSH:\n");
        print("help  - show help\n");
        print("clear - clear screen\n");
    }
    else if (streq(cmd, "clear")) {
        clearscreen();
    }
    else if (cmd[0] == '\0') {
    }
    else {
        print("Unknown: ");
        print(cmd);
        print("\n");
    }
}

void inshell() {
    char buffer[MAX_INPUT];
    int pos = 0;

    print("psh: ");

    while (true) {
        char c = getch();

        switch (c) {
            case '\n':
            case '\r':
                buffer[pos] = '\0';
                print("\n");
                handle_command(buffer);
                pos = 0;
                print("psh: ");
                break;

            case '\b':
                if (pos > 0) {
                    pos--;
                    print("\b \b");
                }
                break;

            default:
                if (c >= 32 && c <= 126) {
                    if (pos < MAX_INPUT - 1) {
                        buffer[pos++] = c;
                        putchar(c);
                    }
                }
                break;
        }
    }
}
