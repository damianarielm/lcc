TARGET = nachosfuse
NACHOS_DIR = ../../filesys
NACHOS_NAME = nachos
DISK_NAME = DISK
MOUNT_POINT = mnt

NACHOS_PATH = $(NACHOS_DIR)/$(NACHOS_NAME)
DISK_PATH = $(NACHOS_DIR)/$(DISK_NAME)
DEFINES = -DNACHOS="\"$(NACHOS_PATH)\""

.PHONY: all clean mount umount

all: $(TARGET)

clean:
	[ -h "$(DISK_NAME)" ] && $(RM) "$(DISK_NAME)"
	rmdir "$(MOUNT_POINT)" 2>/dev/null || true
	$(RM) $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $< -o $@ $(DEFINES) $$(pkg-config fuse --cflags --libs)

mount: $(TARGET)
	ln -s "$(DISK_PATH)" "$(DISK_NAME)" 2>/dev/null || true
	mkdir "$(MOUNT_POINT)" 2>/dev/null || true
	./$< -f "$(MOUNT_POINT)"

umount:
	fusermount -u "$(MOUNT_POINT)"
