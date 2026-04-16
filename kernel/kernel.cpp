// PLUSKernel 
#include<cstdint>
constexpr uint32_t MULTIBOOT_MAGIC=0x1BADB002;
constexpr uint32_t MULTIBOOT_FLAGS=0x00000003;
constexpr uint32_t MULTIBOOT_CHECKSUM =
    -(MULTIBOOT_MAGIC + MULTIBOOT_FLAGS);
__attribute__((section(".multiboot")))
__attribute__((used))
const struct MultibootHeader {
    uint32_t magic;
    uint32_t flags;
    uint32_t checksum;
} multiboot_header = {
    MULTIBOOT_MAGIC,
    MULTIBOOT_FLAGS,
    MULTIBOOT_CHECKSUM
};

volatile char* vimem=(volatile char*)0xB8000;
int cursor = 0;

void clearscreen(){
    for (int i = 0; i < 80 * 25; i++){
        vimem[i * 2]=' ';
        vimem[i * 2 + 1]=0x07;
    }
}

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

extern "C" void maink(){
    clearscreen();
    print("Pluskernel\n");
    while (1){}
}
