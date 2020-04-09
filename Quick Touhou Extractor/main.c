#define _CRT_SECURE_NO_WARNINGS
#include "QTE.h"

//�������anm
void extract_anm(char* dir_name) {
	char result[MAX_CHAR_LEN] = { 0 };
	char cmd[MAX_CHAR_LEN] = { 0 };
	sprintf(cmd, "mkdir %s\\ANM", dir_name);
	system(cmd);
	sprintf(cmd, "dir /s/b %s\\*.anm > %s\\ANM\\anm_file_list.txt", dir_name, dir_name);
	system(cmd);
	printf("Get anm file list succeed.\n");
	system("pause");
}

//�ƶ�dat��������ļ�
void move_dat_file(char* dir_name) {
	char cmd[MAX_CHAR_LEN] = { 0 };
	//�������ƶ��ٵ����ƶ������Ч��
	//�����ƶ�
	char *extension[EXTENSION_AMOUNT] = {
	".anm",".rpy",".ecl",".jpg",".end",".sht",".wav",".std",".mid",".png",".msg"
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
		//�����ĸ���dat���
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

//���dat�ļ�
void extract_dat(char* dat_name) {
	char dir_name[MAX_CHAR_LEN] = { 0 };
	char cmd[MAX_CHAR_LEN] = { 0 };
	get_dir_name(dat_name, dir_name);
	sprintf(cmd, "mkdir %s", dir_name);
	system(cmd);
	sprintf(cmd, "thdat.exe -x d %s > dat_file_list.txt", dat_name);
	system(cmd);
	move_dat_file(dir_name);
	printf("Extract dat file succeed.\n");
	system("pause");
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

//��ȡ�ļ���
void get_dat_name(char* dat_name) {
	char result[MAX_CHAR_LEN] = { 0 };
	printf("result=");
	execmd("dir /s/b th??.dat", result);
	printf(result);
	char *find;
	find = strrchr(result, '\\');
	strcpy(dat_name, ++find);
	if (find = strchr(dat_name, '\n')) *find = '\0';
	printf("dat_name=%s", dat_name);
	if (dat_name[0] != 't') {					//�Ҳ���thxx.dat�ļ�
		printf("FILE NOT FOUND!\n");
		system("pause");
		exit(0);
	}
	else printf("\n");
	system("pause");
}

void get_dir_name(char* dat_name, char* dir_name) {
	strcpy(dir_name, dat_name);
	char *find;
	if (find = strchr(dir_name, '.')) *find = '_';
}

int main() {
	char dat_name[MAX_CHAR_LEN] = { 0 };
	char dir_name[MAX_CHAR_LEN] = { 0 };
	get_dat_name(dat_name);
	extract_dat(dat_name);
	get_dir_name(dat_name, dir_name);
	extract_anm(dir_name);
	return 0;
}