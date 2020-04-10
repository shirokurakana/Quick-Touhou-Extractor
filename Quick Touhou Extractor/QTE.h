#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR_LEN 1024
#define TRUE 1
#define FALSE 0
#define EXTENSION_AMOUNT 11
typedef int bool;

char dat_path[MAX_CHAR_LEN] = { 0 };

int GetDatName(char* dat_name);
void GetDirName(char* dat_name, char* dir_name);
int execmd(char* cmd, char* result);
void ExtractDat(char* dat_name, int game_ver);
void MoveDatFile(char* dir_name);
void ExtractAllAnm(char* dir_name);