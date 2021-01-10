
OSNAME = CustomOS

GNUEFI = ../gnu-efi
OVMFDIR = ../OVMFbin
LDS = kernel.ld
CC = g++
LD = ld

CFLAGS = -ffreestanding -fshort-wchar -I./include --std=c++2a 
LDFLAGS = -T $(LDS) -static -Bsymbolic -nostdlib

SRCDIR := src
OBJDIR := lib
BUILDDIR = bin
BOOTEFI := $(GNUEFI)/x86_64/bootloader/main.efi

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRC = $(call rwildcard,$(SRCDIR),*.cc)          
OBJS = $(patsubst $(SRCDIR)/%.cc, $(OBJDIR)/%.o, $(SRC))
DIRS = $(wildcard $(SRCDIR)/*)

kernel: $(OBJS) 
	@$(MAKE) -j1 link

$(OBJDIR)/%.o: $(SRCDIR)/%.cc
	@echo Compiling $^
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $^ -o $@

setup:
	@mkdir $(BUILDDIR)
	@mkdir $(SRCDIR)
	@mkdir $(OBJDIR)

link:
	@echo Linking
	$(LD) $(LDFLAGS) -o $(BUILDDIR)/kernel.elf $(OBJS)

clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(BUILDDIR)/CustomOS.img
	rm -f $(BUILDDIR)/kernel.elf

buildefi: 
	@cd ../gnu-efi && $(MAKE) bootloader && cd ../kernel

fullBuild: 
	@$(MAKE) clean 
	@$(MAKE) buildefi 
	@$(MAKE) kernel 
	@$(MAKE) buildimg

buildimg:
	dd if=/dev/zero of=$(BUILDDIR)/$(OSNAME).img bs=512 count=93750
	mformat -i $(BUILDDIR)/$(OSNAME).img -f 1440 ::
	mmd -i $(BUILDDIR)/$(OSNAME).img ::/EFI
	mmd -i $(BUILDDIR)/$(OSNAME).img ::/EFI/BOOT
	mcopy -i $(BUILDDIR)/$(OSNAME).img $(BOOTEFI) ::/EFI/BOOT
	mcopy -i $(BUILDDIR)/$(OSNAME).img startup.nsh ::
	mcopy -i $(BUILDDIR)/$(OSNAME).img $(BUILDDIR)/kernel.elf ::
	mcopy -i $(BUILDDIR)/$(OSNAME).img $(BUILDDIR)/zap-light16.psf ::

run:
	qemu-system-x86_64 -drive file=$(BUILDDIR)/$(OSNAME).img -m 4G -cpu qemu64 -drive if=pflash,format=raw,unit=0,file="$(OVMFDIR)/OVMF_CODE-pure-efi.fd",readonly=on -drive if=pflash,format=raw,unit=1,file="$(OVMFDIR)/OVMF_VARS-pure-efi.fd" -net none
