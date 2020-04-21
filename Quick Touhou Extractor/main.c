#define _CRT_SECURE_NO_WARNINGS
#include "QTE.h"

//�������anm�ļ�
void ExtractSingleAnm(char* anm_name, char* dir_name) {

}

//�������anm�ļ�
void ExtractAllAnm(char* dir_name) {
	char result[MAX_CHAR_LEN] = { 0 };
	
}

//�õ�anm�ļ��б�
void GetAnmFile(char* dir_name) {
	char cmd[MAX_CHAR_LEN] = { 0 };
	sprintf(cmd, "mkdir %s\\ANM", dir_name);
	system(cmd);
	sprintf(cmd, "dir /s/b %s\\*.anm > %s\\ANM\\anm_file_list.txt", dir_name, dir_name);
	system(cmd);
	printf("Get anm file list succeed.\n");
	system("pause");
}

//�ƶ�dat��������ļ���������
void MoveFTGDatFile(char* dir_name) {
	/*
		for (int i = 0; i < MAX_CHAR_LEN && line[i] !='\0'; i++)																		//����Ƿ����Ŀ¼
			if (line[i] == '/') {				//�ļ�·���е�ȫ��б��ת��Ϊ��б��
				line[i] = '\\';
				f = 1;
			}
		if (f) {																							//������Ŀ¼��ֱ���ƶ���Ŀ¼
			int i = 0;
			while (line[i] != '\\') {
				root[i] = line[i];
				i++;
			}
			break;
		}
		else {
			sprintf(cmd, "MOVE %s %s\\thdat\\%s_dat\\", line, thtkpath, name);
			system(cmd);
		}
	}
	fclose(fp);
	if (f) {
		sprintf(cmd, "md %s\\thdat\\%s_dat\\%s\\", thtkpath, name, root);
		system(cmd);
		sprintf(cmd, "XCOPY %s %s\\thdat\\%s_dat\\%s\\ /e", root, thtkpath, name, root);
		system(cmd);
		printf("����������...");
		sprintf(cmd, "RMDIR %s /s /q", root);																//������
		system(cmd);
		*/
}

//���dat�ļ���������
void ExtractFTGDat(char* dat_name, int game_ver) {

}

//�ƶ�dat��������ļ�(STG)
void MoveDatFile(char* dir_name) {
	char cmd[MAX_CHAR_LEN] = { 0 };
	//�������ƶ��ٵ����ƶ������Ч��
	//�����ƶ�
	char *extension[EXTENSION_AMOUNT] = {
	".anm",".rpy",".ecl",".jpg",".end",".sht",".wav",".std",".mid",".png",".msg",
	".ant",".ect",".mst"		//����¼���������壩
	};
	for (int i = 0; i < EXTENSION_AMOUNT; i++) {
		sprintf(cmd, "MOVE *%s %s", extension[i], dir_name);
		system(cmd);
	}
	//�����ƶ�
	FILE *fp = fopen("dat_file_list.txt", "rt");
	char line[MAX_CHAR_LEN] = { 0 };
	char root[MAX_CHAR_LEN] = { 0 };
	while (!feof(fp)) {
		fgets(line, MAX_CHAR_LEN, fp);
		if (line[0] != 'D') {
			bool need_move = TRUE;
			for (int i = 0; i < EXTENSION_AMOUNT; i++) {
				if (strstr(line, extension[i])) {
					need_move = FALSE;
					break;
				}
			}
			if (need_move) {
				char *find;
				if (find = strchr(line, '\n')) *find = '\0';		//ȥ��fgets��ȡ���Ļ��з�
				sprintf(cmd, "MOVE %s %s", line, dir_name);
				system(cmd);
			}
		}
	}
	fclose(fp);
	system("cls");
}

//���dat�ļ�(STG)
void ExtractDat(char* dat_name, int game_ver) {
	char dir_name[MAX_CHAR_LEN] = { 0 };
	char cmd[MAX_CHAR_LEN] = { 0 };
	GetDirName(dat_name, dir_name);
	sprintf(cmd, "mkdir %s", dir_name);
	system(cmd);
	sprintf(cmd, "thdat.exe -x %d %s > dat_file_list.txt", game_ver, dat_name);
	system(cmd);
	MoveDatFile(dir_name);
	system("del dat_file_list.txt");
	sprintf(cmd, "del %s", dat_name);
	system(cmd);
	//printf("Extract dat file succeed.\n");
	//system("pause");
}

//�ж��Ƿ�Ϊ����
int checkFTG(int game_ver) {
	if (game_ver == 103 || game_ver == 123) return 1;
	else return 0;
}

//��������ļ�
void ExtractAll() {
	int num = 0;
	while (strlen(dat_list[num])){
		int game_ver = GetGameVersion(dat_list[num]);
		if(checkFTG(game_ver)) ExtractFTGDat(dat_list[num], game_ver);
		else ExtractDat(dat_list[num], game_ver);
		++num;
	}
}

//ִ��cmd�����ȡ���
int execmd(char* cmd, char* result) {
	char buffer[128];
	FILE* pipe = _popen(cmd, "r");
	if (!pipe)
		return -1;
	while (!feof(pipe)) {
		if (fgets(buffer, 128, pipe)) {
			strcat(result, buffer);
		}
	}
	_pclose(pipe);
	return 0;
}

//��ȡ��Ϸ�汾
int GetGameVersion(char dat_name[]) {
	if (strcmp(dat_name, "�tħ�_CM.DAT") == 0) return 6;
	else if (strcmp(dat_name, "�tħ�_ED.DAT") == 0) return 6;
	else if (strcmp(dat_name, "�tħ�_IN.DAT") == 0) return 6;
	else if (strcmp(dat_name, "�tħ�_MD.DAT") == 0) return 6;
	else if (strcmp(dat_name, "�tħ�_ST.DAT") == 0) return 6;
	else if (strcmp(dat_name, "�tħ�_TL.DAT") == 0) return 6;
	else if (strcmp(dat_name, "�g����CM.DAT") == 0) return 6;
	else if (strcmp(dat_name, "�g����ED.DAT") == 0) return 6;
	else if (strcmp(dat_name, "�g����IN.DAT") == 0) return 6;
	else if (strcmp(dat_name, "�g����MD.DAT") == 0) return 6;
	else if (strcmp(dat_name, "�g����ST.DAT") == 0) return 6;
	else if (strcmp(dat_name, "�g����TL.DAT") == 0) return 6;
	else if (strcmp(dat_name, "th07.dat") == 0) return 7;
	else if (strcmp(dat_name, "th08.dat") == 0) return 8;
	else if (strcmp(dat_name, "th09.dat") == 0) return 9;
	else if (strcmp(dat_name, "th095.dat") == 0) return 95;
	else if (strcmp(dat_name, "th095c.dat") == 0) return 95;
	else if (strcmp(dat_name, "th10.dat") == 0) return 10;
	else if (strcmp(dat_name, "th10c.dat") == 0) return 10;
	else if (strcmp(dat_name, "alcostg.dat") == 0) return 103;
	else if (strcmp(dat_name, "th11.dat") == 0) return 11;
	else if (strcmp(dat_name, "th11c.dat") == 0) return 11;
	else if (strcmp(dat_name, "th12.dat") == 0) return 12;
	else if (strcmp(dat_name, "th12c.dat") == 0) return 12;
	else if (strcmp(dat_name, "th125.dat") == 0) return 125;
	else if (strcmp(dat_name, "th125c.dat") == 0) return 125;
	else if (strcmp(dat_name, "th128.dat") == 0) return 128;
	else if (strcmp(dat_name, "th128c.dat") == 0) return 128;
	else if (strcmp(dat_name, "th13.dat") == 0) return 13;
	else if (strcmp(dat_name, "th13c.dat") == 0) return 13;
	else if (strcmp(dat_name, "th14.dat") == 0) return 14;
	else if (strcmp(dat_name, "th14c.dat") == 0) return 14;
	else if (strcmp(dat_name, "th143.dat") == 0) return 143;
	else if (strcmp(dat_name, "th143c.dat") == 0) return 143;
	else if (strcmp(dat_name, "th15.dat") == 0) return 15;
	else if (strcmp(dat_name, "th15c.dat") == 0) return 15;
	else if (strcmp(dat_name, "th16.dat") == 0) return 16;
	else if (strcmp(dat_name, "th16c.dat") == 0) return 16;
	else if (strcmp(dat_name, "th165.dat") == 0) return 165;
	else if (strcmp(dat_name, "th165c.dat") == 0) return 165;
	else if (strcmp(dat_name, "th17.dat") == 0) return 17;
	else if (strcmp(dat_name, "th17c.dat") == 0) return 17;		//���ʰ溺��
	else return 0;
}

//��ȡdat�ļ����б�
int GetDatList() {
	char result[MAX_CHAR_LEN] = { 0 };
	execmd("dir /a:-d /b /o /p /w *.dat", result);		//��ȡdat�ļ��б�
	char *find;
	if (find = strchr(result, '.') == NULL) return 0;		//û���ҵ�dat�ļ�
	int num = 0;
	while (find = strchr(result, '\n')) {
		char temp[MAX_CHAR_LEN] = { 0 };
		*find++ = '\0';
		strcpy(temp, result);
		if (GetGameVersion(temp)) {
			strcpy(dat_list[num], temp);
			++num;
			printf("%s\n", temp);
		}
		strcpy(result, find);
	}
	system("pause");
	if (strlen(dat_list[0])) return 1;		//������һ��֧�ֵ�dat�ļ�
	else return 0;							//�ҵ���dat�ļ�������֧��
}

//�ļ���ת��Ϊ·����
void GetDirName(char* dat_name, char* dir_name) {
	int game_ver = GetGameVersion(dat_name);
	if (game_ver == 6) {
		strcpy(dir_name, "th06_dat");
		return;
	}
	strcpy(dir_name, dat_name);
	char *find;
	if (find = strrchr(dir_name, '.')) *find = '_';
}

int main() {
	if (!GetDatList()) {
		system("pause");
		exit(0);
	}
	ExtractAll();
	//GetDirName(dat_name, dir_name);
	//GetAnmFile(dir_name);
	//ExtractAllAnm(dir_name);
	return 0;
}