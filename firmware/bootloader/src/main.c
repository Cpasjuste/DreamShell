/**
 * DreamShell boot loader
 * Main
 * (c)2011-2016 SWAT <http://www.dc-swat.ru>
 */

#include "main.h"
#include "fs.h"
#include "utility.h"
#include "drawing.h"
#include "menu_new.h"

KOS_INIT_FLAGS(INIT_DEFAULT/* | INIT_NET*/);
extern uint8 romdisk[];

const char title[28] = "DreamShell boot loader v"VERSION;

#define EMU
//#define BIOS_MODE

#ifdef BIOS_MODE
//int is_no_syscalls() {
//	return (*(uint16 *)0x8c000100) != 0x2f06;
//}


static int setup_syscalls() {

    file_t fd;
    size_t fd_size;
    int (*sc)(int, int, int, int);

    dbglog(DBG_INFO, "Loading and setup syscalls...\n");

    fd = fs_open(RES_PATH"/syscalls.bin", O_RDONLY);

    if(fd != FILEHND_INVALID) {

        fd_size = fs_total(fd);
        dbgio_dev_select("null");
        dcache_flush_range(0x8c000000, fd_size);
        icache_flush_range(0x8c000000, fd_size);

        if(fs_read(fd, (uint8*)0x8c000000, fd_size) < 0) {

            fs_close(fd);
            dbgio_dev_select("fb");
            dbglog(DBG_ERROR, "Error at loading syscalls\n");
            return -1;

        } else {

            fs_close(fd);
            dcache_flush_range(0x8c000000, fd_size);
            icache_flush_range(0x8c000000, fd_size);

            dbgio_dev_select("fb");
            *((uint32 *)&sc) = *((uint32 *)0x8c0000b0);

            if(sc(0, 0, 0, 0)) {
                dbglog(DBG_ERROR, "Error in sysinfo syscall\n");
                return -1;
            }

            dbglog(DBG_INFO, "Syscalls successfully installed\n");
            return 0;
        }
    } else {
        dbglog(DBG_ERROR, "Can't open file with syscalls\n");
    }

    return -1;
}
#endif

int start_pressed = 0;

static void start_callback(void) {
    if (!start_pressed) {
        dbglog(DBG_INFO, "Enter the boot menu...\n");
        start_pressed = 1;
    }
}

static void dcload_callback(void) {

    if (fs_romdisk_mount(RES_PATH, (const uint8 *) romdisk, 0) != 0) {
        dbgio_dev_select("fb");
        dbglog(DBG_INFO, "error: could not mount romdisk\n");
        return;
    }

    file_t f = fs_open(RES_PATH"/dcload.bin", O_RDONLY);
    if (f == FILEHND_INVALID) {
        dbgio_dev_select("fb");
        dbglog(DBG_INFO, "error: could not find dcload.bin\n");
        return;
    }

    void *bin = fs_mmap(f);
    arch_exec(bin, fs_total(f));
}

static void show_boot_message(void) {
    dbglog(DBG_INFO, "         %s\n", title);
    dbglog(DBG_INFO, "  !!! Press START to enter the boot menu !!!\n\n");
}

int main(int argc, char **argv) {

    cont_btn_callback(0, CONT_START, (cont_btn_callback_t) start_callback);
    cont_btn_callback(0, CONT_A | CONT_B, (cont_btn_callback_t) start_callback);

    if (vid_check_cable() == CT_VGA) {
        vid_set_mode(DM_640x480_VGA, PM_RGB565);
    } else if (flash_get_region() == FLASHROM_REGION_EUROPE) {
        vid_set_mode(DM_640x480_PAL_IL, PM_RGB565);
    } else {
        vid_set_mode(DM_640x480_NTSC_IL, PM_RGB565);
    }

    menu_run();

#if 0
#ifndef EMU

#ifdef BIOS_MODE

    if(!fs_romdisk_mount(RES_PATH, (const uint8 *)romdisk, 0)) {

        dbgio_dev_select("fb");
        show_boot_message();

        if(is_custom_bios()/* && is_no_syscalls()*/) {
            setup_syscalls();
//			cdrom_init();
//			fs_iso9660_init();
        }

    } else {
        dbgio_dev_select("fb");
        show_boot_message();
    }

    InitIDE();
    InitSDCard();

#else

    int ird = 1;
    dbgio_dev_select("fb");
    show_boot_message();

    if (!InitIDE()) {
        ird = 0;
    }

    if (!InitSDCard()) {
        ird = 0;
    }

    if (ird && is_custom_bios()) {
        InitRomdisk();
    }
#endif

    dbgio_disable();

#else
    dbgio_dev_select("scif");
    show_boot_message();
#endif

    if (!start_pressed) {
        //menu_init();
        //loading_core(1);
    }

    pvr_init(&params);

#ifdef BIOS_MODE
    fs_romdisk_unmount(RES_PATH);
#else
    if (!fs_romdisk_mount(RES_PATH, (const uint8 *) romdisk, 0)) {
        fs_romdisk_unmount(RES_PATH);
    }
#endif

    if (!start_pressed)
        init_menu_txr();
    else
        menu_init();

    pvr_set_bg_color(192.0 / 255.0, 192.0 / 255.0, 192.0 / 255.0);

    while (1) {
        pvr_wait_ready();
        pvr_scene_begin();
        pvr_list_begin(PVR_LIST_TR_POLY);
        menu_frame();
        pvr_list_finish();
        pvr_scene_finish();
    }
#endif
    return 0;
}
