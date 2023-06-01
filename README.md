# assembly_bootloader
A tiny x86 assembly bootloader

## Build
```bash
nasm -f bin boot.asm -o boot.com
```

## Run
```bash
bochs -f bochsrc.txt
```
