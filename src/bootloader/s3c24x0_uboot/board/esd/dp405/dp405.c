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


/* fpga configuration data - not compressed, generated by bin2c */
const unsigned char fpgadata[] =
{
#include "fpgadata.c"
};
int filesize = sizeof(fpgadata);


int board_pre_init (void)
{
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
	mtebc (epcr, 0xa8400000); /* ebc always driven */

	return 0;
}


/* ------------------------------------------------------------------------- */

int misc_init_f (void)
{
	return 0;  /* dummy implementation */
}


int misc_init_r (void)
{
	/*
	 * Reset CPLD via GPIO13 (CS4) pin
	 */
	out32(GPIO0_OR, in32(GPIO0_OR) & ~(0x80000000 >> 13));
	udelay(1000); /* wait 1ms */
	out32(GPIO0_OR, in32(GPIO0_OR) | (0x80000000 >> 13));
	udelay(1000); /* wait 1ms */

	return (0);
}


/*
 * Check Board Identity:
 */

int checkboard (void)
{
	unsigned char str[64];
	int i = getenv_r ("serial#", str, sizeof(str));
	unsigned char trans[16] = {0x0,0x8,0x4,0xc,0x2,0xa,0x6,0xe,
				   0x1,0x9,0x5,0xd,0x3,0xb,0x7,0xf};
	unsigned char id1, id2;

	puts ("Board: ");

	if (i == -1) {
		puts ("### No HW ID - assuming DP405");
	} else {
		puts(str);
	}

	id1 = trans[(~(in32(GPIO0_IR) >> 5)) & 0x0000000f];
	id2 = trans[(~(in32(GPIO0_IR) >> 9)) & 0x0000000f];
	printf(" (ID=0x%1X%1X)\n", id1, id2);

	return 0;
}

/* ------------------------------------------------------------------------- */

long int initdram (int board_type)
{
	unsigned long val;

	mtdcr(memcfga, mem_mb0cf);
	val = mfdcr(memcfgd);

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
