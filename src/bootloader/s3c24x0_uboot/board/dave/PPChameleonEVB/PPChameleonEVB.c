/*
 * (C) Copyright 2001-2003
 * Stefan Roese, esd gmbh germany, stefan.roese@esd-electronics.com
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <asm/processor.h>
#include <command.h>
#include <malloc.h>

/* ------------------------------------------------------------------------- */

#if 0
#define FPGA_DEBUG
#endif

/* fpga configuration data - gzip compressed and generated by bin2c */
const unsigned char fpgadata[] =
{
#include "fpgadata.c"
};

/*
 * include common fpga code (for esd boards)
 */
#include "../common/fpga.c"


/* Prototypes */
int gunzip(void *, int, unsigned char *, int *);


int board_pre_init (void)
{
	out32(GPIO0_OR, CFG_NAND0_CE);                 /* set initial outputs     */
	out32(GPIO0_OR, CFG_NAND1_CE);                 /* set initial outputs     */

	/*
	 * IRQ 0-15  405GP internally generated; active high; level sensitive
	 * IRQ 16    405GP internally generated; active low; level sensitive
	 * IRQ 17-24 RESERVED
	 * IRQ 25 (EXT IRQ 0) CAN0; active low; level sensitive
	 * IRQ 26 (EXT IRQ 1) SER0 ; active low; level sensitive
	 * IRQ 27 (EXT IRQ 2) SER1; active low; level sensitive
	 * IRQ 28 (EXT IRQ 3) FPGA 0; active low; level sensitive
	 * IRQ 29 (EXT IRQ 4) FPGA 1; active low; level sensitive
	 * IRQ 30 (EXT IRQ 5) PCI INTA; active low; level sensitive
	 * IRQ 31 (EXT IRQ 6) COMPACT FLASH; active high; level sensitive
	 */
	mtdcr(uicsr, 0xFFFFFFFF);       /* clear all ints */
	mtdcr(uicer, 0x00000000);       /* disable all ints */
	mtdcr(uiccr, 0x00000000);       /* set all to be non-critical*/
	mtdcr(uicpr, 0xFFFFFF80);       /* set int polarities */
	mtdcr(uictr, 0x10000000);       /* set int trigger levels */
	mtdcr(uicvcr, 0x00000001);      /* set vect base=0,INT0 highest priority*/
	mtdcr(uicsr, 0xFFFFFFFF);       /* clear all ints */

	/*
	 * EBC Configuration Register: set ready timeout to 512 ebc-clks -> ca. 15 us
	 */
#if 1 /* test-only */
	mtebc (epcr, 0xa8400000); /* ebc always driven */
#else
	mtebc (epcr, 0x28400000); /* ebc in high-z */
#endif

	return 0;
}


/* ------------------------------------------------------------------------- */

int misc_init_f (void)
{
	return 0;  /* dummy implementation */
}


int misc_init_r (void)
{
#if 0 /* test-only */
	DECLARE_GLOBAL_DATA_PTR;
#if 0
	volatile unsigned short *fpga_mode =
		(unsigned short *)((ulong)CFG_FPGA_BASE_ADDR + CFG_FPGA_CTRL);
	volatile unsigned char *duart0_mcr =
		(unsigned char *)((ulong)DUART0_BA + 4);
	volatile unsigned char *duart1_mcr =
		(unsigned char *)((ulong)DUART1_BA + 4);

	bd_t *bd = gd->bd;
	char *	tmp;                    /* Temporary char pointer      */
	unsigned char *dst;
	ulong len = sizeof(fpgadata);
	int status;
	int index;
	int i;
	unsigned long cntrl0Reg;

	dst = malloc(CFG_FPGA_MAX_SIZE);
	if (gunzip (dst, CFG_FPGA_MAX_SIZE, (uchar *)fpgadata, (int *)&len) != 0) {
		printf ("GUNZIP ERROR - must RESET board to recover\n");
		do_reset (NULL, 0, 0, NULL);
	}

	status = fpga_boot(dst, len);
	if (status != 0) {
		printf("\nFPGA: Booting failed ");
		switch (status) {
		case ERROR_FPGA_PRG_INIT_LOW:
			printf("(Timeout: INIT not low after asserting PROGRAM*)\n ");
			break;
		case ERROR_FPGA_PRG_INIT_HIGH:
			printf("(Timeout: INIT not high after deasserting PROGRAM*)\n ");
			break;
		case ERROR_FPGA_PRG_DONE:
			printf("(Timeout: DONE not high after programming FPGA)\n ");
			break;
		}

		/* display infos on fpgaimage */
		index = 15;
		for (i=0; i<4; i++) {
			len = dst[index];
			printf("FPGA: %s\n", &(dst[index+1]));
			index += len+3;
		}
		putc ('\n');
		/* delayed reboot */
		for (i=20; i>0; i--) {
			printf("Rebooting in %2d seconds \r",i);
			for (index=0;index<1000;index++)
				udelay(1000);
		}
		putc ('\n');
		do_reset(NULL, 0, 0, NULL);
	}

	puts("FPGA:  ");

	/* display infos on fpgaimage */
	index = 15;
	for (i=0; i<4; i++) {
		len = dst[index];
		printf("%s ", &(dst[index+1]));
		index += len+3;
	}
	putc ('\n');

	free(dst);

	/*
	 * Reset FPGA via FPGA_DATA pin
	 */
	SET_FPGA(FPGA_PRG | FPGA_CLK);
	udelay(1000); /* wait 1ms */
	SET_FPGA(FPGA_PRG | FPGA_CLK | FPGA_DATA);
	udelay(1000); /* wait 1ms */

#endif

#if 0
	/*
	 * Enable power on PS/2 interface
	 */
	*fpga_mode |= CFG_FPGA_CTRL_PS2_RESET;

	/*
	 * Enable interrupts in exar duart mcr[3]
	 */
	*duart0_mcr = 0x08;
	*duart1_mcr = 0x08;
#endif
#endif

	return (0);
}


/*
 * Check Board Identity:
 */

int checkboard (void)
{
	unsigned char str[64];
	int i = getenv_r ("serial#", str, sizeof(str));

	puts ("Board: ");

	if (i == -1) {
		puts ("### No HW ID - assuming PPChameleonEVB");
	} else {
		puts(str);
	}

	putc ('\n');

	return 0;
}

/* ------------------------------------------------------------------------- */

long int initdram (int board_type)
{
	unsigned long val;

	mtdcr(memcfga, mem_mb0cf);
	val = mfdcr(memcfgd);

#if 0 /* test-only */
	for (;;) {
		NAND_DISABLE_CE(1);
		udelay(100);
		NAND_ENABLE_CE(1);
		udelay(100);
	}
#endif
#if 0
	printf("\nmb0cf=%x\n", val); /* test-only */
	printf("strap=%x\n", mfdcr(strap)); /* test-only */
#endif

	return (4*1024*1024 << ((val & 0x000e0000) >> 17));
}

/* ------------------------------------------------------------------------- */

int testdram (void)
{
	/* TODO: XXX XXX XXX */
	printf ("test: 16 MB - ok\n");

	return (0);
}

/* ------------------------------------------------------------------------- */

#if (CONFIG_COMMANDS & CFG_CMD_NAND)
extern ulong
nand_probe(ulong physadr);

void
nand_init(void)
{
	ulong totlen = 0;

#if (CONFIG_PPCHAMELEON_MODULE_MODEL == CONFIG_PPCHAMELEON_MODULE_ME) || \
    (CONFIG_PPCHAMELEON_MODULE_MODEL == CONFIG_PPCHAMELEON_MODULE_HI)
	debug ("Probing at 0x%.8x\n", CFG_NAND0_BASE);
	totlen += nand_probe (CFG_NAND0_BASE);
#endif	/* CONFIG_PPCHAMELEON_MODULE_ME, CONFIG_PPCHAMELEON_MODULE_HI */

	debug ("Probing at 0x%.8x\n", CFG_NAND1_BASE);
	totlen += nand_probe (CFG_NAND1_BASE);

	printf ("%4lu MB\n", totlen >>20);
}
#endif
