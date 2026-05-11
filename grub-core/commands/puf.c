/* puf.c */

#include <grub/dl.h>
#include <grub/command.h>
#include <grub/misc.h>
#include <grub/mm.h>
#include <grub/term.h>

#include <grub/efi/efi.h>
#include <grub/efi/api.h>

GRUB_MOD_LICENSE("GPLv3");

static grub_guid_t cortex_guid =
{
    0x12345678,
    0x1234,
    0x5678,
    { 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x11, 0x22 }
};

static grub_err_t
grub_puf_dump(grub_command_t cmd __attribute__((unused)),
              int argc __attribute__((unused)),
              char **argv __attribute__((unused)))
{
    grub_uint8_t *addr = (grub_uint8_t *) 0x100000;
    grub_uint8_t sample[64];
    int i;

    for (i = 0; i < 64; i++)
        sample[i] = addr[i];

    grub_printf("Writing PUF sample to EFI variable...\n");

    grub_efi_status_t status = grub_efi_set_variable(
        "CORTEX_PUF",
        &cortex_guid,
        sample,
        sizeof(sample)
    );

    if (status != GRUB_EFI_SUCCESS)
    {
        grub_printf("EFI write failed: %lx\n", status);
        return GRUB_ERR_IO;
    }

    grub_printf("EFI variable written successfully.\n");
    return GRUB_ERR_NONE;
}

static grub_command_t cmd;

GRUB_MOD_INIT(puf)
{
    cmd = grub_register_command(
        "puf_dump",
        grub_puf_dump,
        0,
        "Dump DRAM PUF to EFI variable");
}

GRUB_MOD_FINI(puf)
{
    grub_unregister_command(cmd);
}
