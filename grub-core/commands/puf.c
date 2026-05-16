/* puf.c */

#include <grub/dl.h>
#include <grub/command.h>
#include <grub/misc.h>
#include <grub/mm.h>
#include <grub/term.h>
#include <grub/types.h>

GRUB_MOD_LICENSE("GPLv3");

/*
 * IMPORTANT:
 *
 * Add these kernel parameters:
 *
 * memmap=4M!4G nokaslr
 *
 * Example GRUB linux line:
 *
 * linux /boot/vmlinuz-linux root=/dev/nvme0n1p4 rw memmap=4M!4G nokaslr
 *
 * This reserves a persistent memory region starting at:
 *
 * 0x100000000 (4GB)
 */

#define CORTEX_MAILBOX_ADDR 0x100000000ULL
#define CORTEX_MAGIC        0x43525458 /* "CRTX" */

struct cortex_mailbox
{
    grub_uint32_t magic;
    grub_uint32_t version;

    grub_uint32_t data_size;

    grub_uint8_t puf_data[64];
};

static grub_err_t
grub_puf_dump(grub_command_t cmd __attribute__((unused)),
              int argc __attribute__((unused)),
              char **argv __attribute__((unused)))
{
    /*
     * Example DRAM sampling location
     */
    grub_uint8_t *dram_addr =
        (grub_uint8_t *)0x100000;

    /*
     * Mailbox pointer inside reserved persistent RAM
     */
    struct cortex_mailbox *mailbox =
        (struct cortex_mailbox *)(grub_addr_t)
            CORTEX_MAILBOX_ADDR;

    int i;

    grub_printf("Collecting DRAM PUF sample...\n");

    /*
     * Clear mailbox
     */
    grub_memset(mailbox, 0, sizeof(*mailbox));

    /*
     * Fill metadata
     */
    mailbox->magic = CORTEX_MAGIC;
    mailbox->version = 1;
    mailbox->data_size = 64;

    /*
     * Copy DRAM bytes
     */
    for (i = 0; i < 64; i++)
        mailbox->puf_data[i] = dram_addr[i];

    grub_printf("Cortex mailbox written.\n");

    grub_printf("Mailbox physical address: 0x%llx\n",
                (unsigned long long)
                CORTEX_MAILBOX_ADDR);

    grub_printf("First 16 bytes:\n");

    for (i = 0; i < 16; i++)
        grub_printf("%02x",
                    mailbox->puf_data[i]);

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
        "Dump DRAM PUF into Cortex reserved RAM mailbox");
}

GRUB_MOD_FINI(puf)
{
    grub_unregister_command(cmd);
}
