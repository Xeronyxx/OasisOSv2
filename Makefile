include_directories := -I src/header/drivers -I src/header/kernel -I src/header/std -I src/header/programs -I src/header/thread

kernel_source_files := $(shell find src/kernel -name *.c)
kernel_object_files := $(patsubst src/kernel/%.c, build/kernel/%.o, $(kernel_source_files))

x86_64_c_source_files := $(shell find src/x86_64 -name *.c)
x86_64_c_object_files := $(patsubst src/x86_64/%.c, build/x86_64/%.o, $(x86_64_c_source_files))

x86_64_asm_source_files := $(shell find src/x86_64 -name *.asm)
x86_64_asm_object_files := $(patsubst src/x86_64/%.asm, build/x86_64/%.o, $(x86_64_asm_source_files))

driver_source_files := $(shell find src/drivers -name *.c)
driver_object_files := $(patsubst src/drivers/%.c, build/drivers/%.o, $(driver_source_files))

std_source_files := $(shell find src/std -name *.c)
std_object_files := $(patsubst src/std/%.c, build/std/%.o, $(std_source_files))

programs_source_files := $(shell find src/programs -name *.c)
programs_object_files := $(patsubst src/programs/%.c, build/programs/%.o, $(programs_source_files))

x86_64_object_files := $(x86_64_c_object_files) $(x86_64_asm_object_files)

driver_header_files := $(shell find src/header/drivers -name *.h)
std_header_files := $(shell find src/header/std -name *.h)
programs_header_files := $(shell find src/header/programs -name *.h)

$(kernel_object_files): build/kernel/%.o : src/kernel/%.c
	mkdir -p $(dir $@) && \
	x86_64-elf-gcc -c $(include_directories) -ffreestanding $< -o $@

$(x86_64_c_object_files): build/x86_64/%.o : src/x86_64/%.c
	mkdir -p $(dir $@) && \
	x86_64-elf-gcc -c $(include_directories) -ffreestanding $< -o $@

$(x86_64_asm_object_files): build/x86_64/%.o : src/x86_64/%.asm
	mkdir -p $(dir $@) && \
	nasm -f elf64 $< -o $@

$(driver_object_files): build/drivers/%.o : src/drivers/%.c $(driver_header_files)
	mkdir -p $(dir $@) && \
	x86_64-elf-gcc -c $(include_directories) -ffreestanding $< -o $@

$(std_object_files): build/std/%.o : src/std/%.c $(std_header_files)
	mkdir -p $(dir $@) && \
	x86_64-elf-gcc -c $(include_directories) -ffreestanding $< -o $@

$(programs_object_files): build/programs/%.o : src/programs/%.c $(programs_header_files)
	mkdir -p $(dir $@) && \
	x86_64-elf-gcc -c $(include_directories) -ffreestanding $< -o $@

kernel_object_files += $(driver_object_files) $(std_object_files) $(programs_object_files)

.PHONY: build-x86_64
build-x86_64: $(kernel_object_files) $(x86_64_object_files)
	mkdir -p dist/x86_64 && \
	x86_64-elf-ld -n -o dist/x86_64/kernel.bin -T targets/x86_64/linker.ld $(kernel_object_files) $(x86_64_object_files) && \
	cp dist/x86_64/kernel.bin targets/x86_64/iso/boot/kernel.bin && \
	grub-mkrescue /usr/lib/grub/i386-pc -o dist/x86_64/kernel.iso targets/x86_64/iso

run:
	qemu-system-x86_64 -cdrom dist/x86_64/kernel.iso