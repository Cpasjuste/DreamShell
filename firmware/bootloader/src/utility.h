//
// Created by cpasjuste on 28/01/2020.
//

#ifndef LOADER_UTILITY_H
#define LOADER_UTILITY_H

int file_exists(const char *fn);

int dir_exists(const char *dir);

int is_hacked_bios();

int is_custom_bios();

int is_no_syscalls();

int flash_get_region();

void descramble(uint8 *source, uint8 *dest, uint32 size);

#endif //LOADER_UTILITY_H
