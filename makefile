build:
	@clang++ -m32 -ffreestanding -fno-exceptions -fno-rtti -fno-stack-protector -mno-red-zone -c -o output/kernel.o kernel/kernel.cpp
	@clang++ -m32 -ffreestanding -fno-exceptions -fno-rtti -fno-stack-protector -mno-red-zone -c -o output/lib.o kernel/lib.cpp
	@clang++ -m32 -ffreestanding -fno-exceptions -fno-rtti -fno-stack-protector -mno-red-zone -c -o output/pinit.o kernel/util/pinit/pinit.cpp
	@clang++ -m32 -ffreestanding -fno-exceptions -fno-rtti -fno-stack-protector -mno-red-zone -c -o output/psh.o kernel/util/psh/psh.cpp
	@ld -m elf_i386 -T kernel/linker.ld -o output/kernel.elf output/kernel.o output/lib.o output/pinit.o output/psh.o

all: build

clean:
	@rm output/kernel.o
	@rm output/lib.o
	@rm output/pinit.o
	@rm output/psh.o
	@rm output/kernel.elf
