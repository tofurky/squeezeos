/*
 * (C) Copyright 2002
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
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

/*
 * Boot support
 */
#include <common.h>
#include <command.h>
#include <s_record.h>
#include <jffs2/load_kernel.h>
#include <net.h>

#if (CONFIG_COMMANDS & CFG_CMD_JFFS2)
static int part_num=0;

#ifndef CFG_JFFS_CUSTOM_PART

static struct part_info part;

struct part_info*
jffs2_part_info(int part_num)
{
	extern flash_info_t flash_info[];	/* info for FLASH chips */
	int i;

	if(part_num==0){

		if(part.usr_priv==(void*)1)
			return &part;

		memset(&part, 0, sizeof(part));

#if defined(CFG_JFFS2_FIRST_SECTOR)
		part.offset = (unsigned char *) flash_info[CFG_JFFS2_FIRST_BANK].start[CFG_JFFS2_FIRST_SECTOR];
#else
		part.offset = (unsigned char *) flash_info[CFG_JFFS2_FIRST_BANK].start[0];
#endif

		/* Figure out flash partition size */
		for (i = CFG_JFFS2_FIRST_BANK; i < CFG_JFFS2_NUM_BANKS+CFG_JFFS2_FIRST_BANK; i++)
			part.size += flash_info[i].size;

#if defined(CFG_JFFS2_FIRST_SECTOR) && (CFG_JFFS2_FIRST_SECTOR > 0)
		part.size -=
			flash_info[CFG_JFFS2_FIRST_BANK].start[CFG_JFFS2_FIRST_SECTOR] -
			flash_info[CFG_JFFS2_FIRST_BANK].start[0];
#endif

		/* unused in current jffs2 loader */
		part.erasesize = 0;

		/* Mark the struct as ready */
		part.usr_priv=(void*)1;

		return &part;
	}
	return 0;
}
#endif /* ifndef CFG_JFFS_CUSTOM_PART */
int
do_jffs2_fsload(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
    struct part_info* jffs2_part_info(int);
    int jffs2_1pass_load(char *, struct part_info *,const char *);

	char *filename = "uImage";
	ulong offset = CFG_LOAD_ADDR;
	int size;
	struct part_info *part;

	if (argc == 2) {
		filename = argv[1];
	}
	if (argc == 3) {
		offset = simple_strtoul(argv[1], NULL, 16);
		filename = argv[2];
	}

	if (0 != (part=jffs2_part_info(part_num))){

		printf("### JFFS2 loading '%s' to 0x%lx\n", filename, offset);
		size = jffs2_1pass_load((char *)offset, part, filename);

		if (size > 0) {
			char buf[10];
			printf("### JFFS2 load complete: %d bytes loaded to 0x%lx\n",
				size, offset);
			sprintf(buf, "%x", size);
			setenv("filesize", buf);
		} else {
			printf("### JFFS2 LOAD ERROR<%x> for %s!\n", size, filename);
		}

		return !(size > 0);
	}
	printf("Active partition not valid\n");
	return 0;
}

int
do_jffs2_ls(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
   struct part_info* jffs2_part_info(int);
   int jffs2_1pass_ls(struct part_info *,char *);

   char *filename = "/";
	int ret;
	struct part_info *part;

	if (argc == 2)
		filename = argv[1];

	if (0 != (part=jffs2_part_info(part_num))){

		ret = jffs2_1pass_ls(jffs2_part_info(part_num), filename);

		return (ret == 1);
	}
	printf("Active partition not valid\n");
	return 0;
}

int
do_jffs2_fsinfo(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
   struct part_info* jffs2_part_info(int);
   int jffs2_1pass_info(struct part_info *);

	int ret;
	struct part_info *part;

	if (0 != (part=jffs2_part_info(part_num))){

		ret = jffs2_1pass_info(jffs2_part_info(part_num));

		return (ret == 1);
	}
	printf("Active partition not valid\n");
	return 0;
}

int
do_jffs2_chpart(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	int tmp_part;
   struct part_info* jffs2_part_info(int);

   if (argc >= 2) {
		tmp_part = simple_strtoul(argv[1], NULL, 16);
	}else{
		printf("Need partition number in argument list\n");
		return 0;

	}

	if (jffs2_part_info(tmp_part)){
		printf("Partition changed to %d\n",tmp_part);
		part_num=tmp_part;
		return 0;
	}

	printf("Partition %d is not valid partiton\n",tmp_part);
	return 0;

}

/***************************************************/

U_BOOT_CMD(
	fsload,	3,	0,	do_jffs2_fsload,
	"fsload  - load binary file from a filesystem image\n",
	"[ off ] [ filename ]\n"
	"    - load binary file from flash bank\n"
	"      with offset 'off'\n"
);

U_BOOT_CMD(
	fsinfo,	1,	1,	do_jffs2_fsinfo,
	"fsinfo  - print information about filesystems\n",
	"    - print information about filesystems\n"
);

U_BOOT_CMD(
	ls,	2,	1,	do_jffs2_ls,
	"ls      - list files in a directory (default /)\n",
	"[ directory ]\n"
	"    - list files in a directory.\n"
);

U_BOOT_CMD(
	chpart,	2,	0,	do_jffs2_chpart,
	"chpart  - change active partition\n",
	"    - change active partition\n"
);

#endif /* CFG_CMD_JFFS2 */
