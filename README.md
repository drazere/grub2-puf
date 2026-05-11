# GRUB PUF MODULE

Fetch your DRAM state at boot.

## How does it work?

The DRAM state cannot be copied by component manufacturers.
This project helps you to fetch that state to help you in your projects

## Usage
Run these in GRUB cmd.

### Load the Module
```javascript
insmod puf
```

### Execute
```javascript
puf_dump

```

### Get the Dram state in linux
```javascript
ls /sys/firmware/efi/efivars | grep CORTEX
```
WARNING: There is no security setup for this right now, it can be a security threat.

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
./bootstrap
./configure
```
```bash
make -j$(nproc)
```
##### (definately not forcing you to use nix)

## Testing
The Program has been tested on: <br />
Dell G15-5530 <br />
Dell Inspiron Inspiron 13 5300 <br />
Given that, Dell's BIOS is currently not wiping out the DRAM state at boot <br />
But some companies do wipe them, like HP.

## Security
Please do not be linient with security, the dram state can be used to easily identify devices if it is leaked.
