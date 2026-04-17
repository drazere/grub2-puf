/* puf.c */
#include <grub/dl.h>
#include <grub/command.h>
#include <grub/misc.h>
#include <grub/mm.h>
#include <grub/term.h>

GRUB_MOD_LICENSE("GPLv3");

static grub_err_t
grub_puf_dump(grub_command_t cmd __attribute__((unused)),
              int argc __attribute__((unused)),
              char **argv __attribute__((unused)))
{
    grub_uint8_t *addr = (grub_uint8_t *)0x100000; // 1MB physical
    int i;

    grub_printf("PUF sample @ 0x100000:\n");

    for (i = 0; i < 64; i++)
        grub_printf("%02x", addr[i]);

    grub_printf("\n");

    return GRUB_ERR_NONE;
}

static grub_command_t cmd;

GRUB_MOD_INIT(puf)
{
    cmd = grub_register_command(
        "puf_dump",
        grub_puf_dump,
        0,
        "Dump early physical memory for PUF analysis");
}

GRUB_MOD_FINI(puf)
{
    grub_unregister_command(cmd);
}
