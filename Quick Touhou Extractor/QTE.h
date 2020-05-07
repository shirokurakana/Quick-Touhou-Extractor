#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR_LEN 1024
#define TRUE 1
#define FALSE 0
#define EXTENSION_AMOUNT 14
typedef int bool;

char dat_list[100][MAX_CHAR_LEN];		//��֪��զ��������������Ƿ��������
int mode;	//ͼʡ�¶��ͷ���������
//0��������1��ȱ��cv2conv.exe����ʱ�ɽ��STG������2�����������QTE�޷�����������

void ExtractSingleAnm(char* anm_name, char* dir_name);		//�������anm�ļ�
void ExtractAllAnm(char* dir_name);							//�������anm�ļ�
void GetAnmFile(char* dir_name);							//��ȡanm�ļ��б�
void MoveDatFileFTG(int game_ver);							//�ƶ�dat��������ļ���������
void ExtractDatFTG(char* dat_name, int game_ver);			//�������dat�ļ���������
void MoveDatFile(char* dir_name);							//�ƶ�����dat��������ļ�(STG)
void ExtractDat(char* dat_name, int game_ver);				//�������dat�ļ�(STG)
int CheckFTG(int game_ver);									//�ж��Ƿ�Ϊ����
void ExtractAll();											//��������ļ�
int execmd(char* cmd, char* result);						//ִ��cmd�����ȡ���
int GetGameVersion(char dat_name[]);						//��ȡ��Ϸ�汾
int GetDatList();											//��ȡdat�ļ����б�
void GetDirName(char* dat_name, char* dir_name);			//�ļ���ת��Ϊ·����
void CheckFiles();											//�������������