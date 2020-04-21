#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR_LEN 1024
#define TRUE 1
#define FALSE 0
#define EXTENSION_AMOUNT 14
typedef int bool;

char dat_list[100][MAX_CHAR_LEN];		//不知道咋传递这玩意儿于是放这儿来了

void GetDirName(char* dat_name, char* dir_name);
int execmd(char* cmd, char* result);
void ExtractDat(char* dat_name, int game_ver);
void ExtractAll();
void MoveDatFile(char* dir_name);
void ExtractAllAnm(char* dir_name);