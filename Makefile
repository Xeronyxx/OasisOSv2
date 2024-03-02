include_directories := -I src/intf/drivers -I src/intf/kernel -I src/intf/std

kernel_source_files := $(shell find src/implementation/kernel -name *.c)
kernel_object_files := $(patsubst src/implementation/kernel/%.c, build/kernel/%.o, $(kernel_source_files))

x86_64_c_source_files := $(shell find src/implementation/x86_64 -name *.c)
x86_64_c_object_files := $(patsubst src/implementation/x86_64/%.c, build/x86_64/%.o, $(x86_64_c_source_files))

x86_64_asm_source_files := $(shell find src/implementation/x86_64 -name *.asm)
x86_64_asm_object_files := $(patsubst src/implementation/x86_64/%.asm, build/x86_64/%.o, $(x86_64_asm_source_files))

driver_source_files := $(shell find src/implementation/drivers -name *.c)
driver_object_files := $(patsubst src/implementation/drivers/%.c, build/drivers/%.o, $(driver_source_files))

std_source_files := $(shell find src/implementation/std -name *.c)
std_object_files := $(patsubst src/implementation/std/%.c, build/std/%.o, $(std_source_files))

x86_64_object_files := $(x86_64_c_object_files) $(x86_64_asm_object_files)

driver_header_files := $(shell find src/intf/drivers -name *.h)
std_header_files := $(shell find src/intf/std -name *.h)

$(kernel_object_files): build/kernel/%.o : src/implementation/kernel/%.c
	mkdir -p $(dir $@) && \
	x86_64-elf-gcc -c $(include_directories) -ffreestanding $< -o $@

$(x86_64_c_object_files): build/x86_64/%.o : src/implementation/x86_64/%.c
	mkdir -p $(dir $@) && \
	x86_64-elf-gcc -c $(include_directories) -ffreestanding $< -o $@

$(x86_64_asm_object_files): build/x86_64/%.o : src/implementation/x86_64/%.asm
	mkdir -p $(dir $@) && \
	nasm -f elf64 $< -o $@

$(driver_object_files): build/drivers/%.o : src/implementation/drivers/%.c $(driver_header_files)
	mkdir -p $(dir $@) && \
	x86_64-elf-gcc -c $(include_directories) -ffreestanding $< -o $@

$(std_object_files): build/std/%.o : src/implementation/std/%.c $(std_header_files)
	mkdir -p $(dir $@) && \
	x86_64-elf-gcc -c $(include_directories) -ffreestanding $< -o $@

kernel_object_files += $(driver_object_files) $(std_object_files)

.PHONY: build-x86_64
build-x86_64: $(kernel_object_files) $(x86_64_object_files)
	mkdir -p dist/x86_64 && \
	x86_64-elf-ld -n -o dist/x86_64/kernel.bin -T targets/x86_64/linker.ld $(kernel_object_files) $(x86_64_object_files) && \
	cp dist/x86_64/kernel.bin targets/x86_64/iso/boot/kernel.bin && \
	grub-mkrescue /usr/lib/grub/i386-pc -o dist/x86_64/kernel.iso targets/x86_64/iso

run:
	qemu-system-x86_64 dist/x86_64/kernel.iso
