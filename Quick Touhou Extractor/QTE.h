#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR_LEN 1024
#define TRUE 1
#define FALSE 0
#define EXTENSION_AMOUNT 11
typedef int bool;

void get_dat_name(char* dat_name);
void get_dir_name(char* dat_name, char* dir_name);
int execmd(char* cmd, char* result);
void extract_dat(char* dat_name);
void move_dat_file(char* dir_name);
void extract_anm(char* dir_name);