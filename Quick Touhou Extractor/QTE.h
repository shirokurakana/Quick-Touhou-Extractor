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
int mode;	//图省事儿就放这里来了
//0：正常，1：缺少cv2conv.exe（此时可解包STG作），2：其他情况（QTE无法正常工作）

void ExtractSingleAnm(char* anm_name, char* dir_name);		//解包单个anm文件
void ExtractAllAnm(char* dir_name);							//批量解包anm文件
void GetAnmFile(char* dir_name);							//获取anm文件列表
void MoveDatFileFTG(int game_ver);							//移动dat解包出的文件（格斗作）
void ExtractDatFTG(char* dat_name, int game_ver);			//解包单个dat文件（格斗作）
void MoveDatFile(char* dir_name);							//移动单个dat解包出的文件(STG)
void ExtractDat(char* dat_name, int game_ver);				//解包单个dat文件(STG)
int CheckFTG(int game_ver);									//判断是否为格斗作
void ExtractAll();											//解包所有文件
int execmd(char* cmd, char* result);						//执行cmd命令并获取结果
int GetGameVersion(char dat_name[]);						//获取游戏版本
int GetDatList();											//获取dat文件名列表
void GetDirName(char* dat_name, char* dir_name);			//文件名转换为路径名
void CheckFiles();											//检查依赖完整性