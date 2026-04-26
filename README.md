# GRUB PUF MODULE

Fetch your DRAM state at boot.

## How does it work?

The DRAM state cannot be copied by component manufacturers.
This project helps you to fetch that state to help you in your projects

## Usage

### load the module
```javascript
insmod puf
```
### execute
```javascript
puf_dump

```

## Installation

### Put the puf.mod in the following location
```bash
/boot/grub/x86_64-efi/puf.mod
```

## Building
### On nix
#### Everything is already setup
```bash
nix-shell
```
```bash
make -j$(nproc)
```
##### (definately not forcing you to use nix)

## Security
Please do not be linient with security, the dram state can be used to easily identify devices if it is leaked.
a system is in development to securely transfer the state to linux os.

