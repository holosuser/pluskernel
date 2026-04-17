#include<cstdint>
#include"lib.hpp"
#include"util/pinit/pinit.hpp"
//multiboot header
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

extern "C" void maink(){
    init();
    while (1){}
}
