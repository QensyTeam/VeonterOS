#!/bin/sh
set -e

export PATH="$HOME/opt/cross/bin:$PATH"  # Добавляем эту команду для обновления переменной PATH

. ./clean.sh
. ./iso.sh
qemu-system-$(./target-triplet-to-arch.sh $HOST) -cdrom Veonter.iso
