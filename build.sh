#!/bin/bash

# you will probably need to run this file as sudo

# mount points for disk
ROOTFS_DIR="./mnt"
BOOT_DIR="${ROOTFS_DIR}/boot"
IMG_NAME="disk.img"

# respectfully lifted from https://github.com/RPi-Distro/pi-gen/blob/master/export-image/prerun.sh
BOOT_SIZE="$((256 * 1024 * 1024))"
ALIGN="$((4 * 1024 * 1024))"
BOOT_PART_START=$((ALIGN))
BOOT_PART_SIZE=$(((BOOT_SIZE + ALIGN - 1) / ALIGN * ALIGN))

# remove rootfs folder if it exists
rm -r "$ROOTFS_DIR"
mkdir -p "$ROOTFS_DIR"
mkdir -p "$BOOT_DIR"
rm "$IMG_NAME"

# make empty file
dd if=/dev/zero of="$IMG_NAME" bs=1M count=512

# give dos partition table
# parted -s "$IMG_NAME" mktable msdos
parted -s "$IMG_NAME" mklabel msdos
# make 256mb fat32 partition
parted -s "$IMG_NAME" unit B mkpart primary fat32 "${BOOT_PART_START}" "$((BOOT_PART_START + BOOT_PART_SIZE - 1))"
# get whatever parted generated (as always, lifted from link above)
PARTED_OUT=$(parted -sm "${IMG_NAME}" unit B print)
BOOT_OFFSET=$(echo "$PARTED_OUT" | grep -e '^1:' | cut -d':' -f 2 | tr -d B)
BOOT_LENGTH=$(echo "$PARTED_OUT" | grep -e '^1:' | cut -d':' -f 4 | tr -d B)
echo belike $BOOT_OFFSET $BOOT_LENGTH
# mount the "filesystem"
BOOT_DEV=$(losetup --show -f -o $BOOT_OFFSET --sizelimit $BOOT_LENGTH "$IMG_NAME")
# give fat32 filesystem to fat32 partition
mkdosfs -n boot -F 32 -v "$BOOT_DEV"
# mount filesystem, we can now write to it (probably only under root)
mount "$BOOT_DEV" "$BOOT_DIR" -t vfat

# build the files
make

# add files to disk
cp build/kernel8.img extra/* "$BOOT_DIR"

# unmount disk and clean up
umount $BOOT_DIR
losetup -d "$BOOT_DEV"

# done!