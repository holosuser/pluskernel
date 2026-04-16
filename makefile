build:
	@clang++ -m32 -ffreestanding -fno-exceptions -fno-rtti -fno-stack-protector -mno-red-zone -c -o output/kernel.o kernel/kernel.cpp
	@ld -m elf_i386 -T kernel/linker.ld -o output/kernel.elf output/kernel.o

all: build

clean:
	@rm output/kernel.o
