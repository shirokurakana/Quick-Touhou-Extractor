#define _CRT_SECURE_NO_WARNINGS
#include "QTE.h"


//�ƶ�dat��������ļ�

void move_dat_file(char* dir_name) {
	char cmd[MAX_CHAR_LEN] = { 0 };
	char *extension[10] = {			//һ��Ҫ�ƶ��ĺ�׺
	".anm",".rpy",".ecl",".jpg",".end",".sht",".wav",".std",".mid",".png"
	};
	for (int i = 0; i < 10; i++) {
		sprintf(cmd, "MOVE *%s %s", extension[i], dir_name);
		system(cmd);
	}
	FILE *fp = fopen("dat_file_list.txt", "rt");
	char line[MAX_CHAR_LEN] = { 0 };
	char root[MAX_CHAR_LEN] = { 0 };
	//int f = 0;
	printf("�����ƶ����ˣ��������ǵ����ļ��ƶ�\n");
	system("pause");
	while (!feof(fp)) {
		fscanf(fp, "%s", &line);
		/*

		for (int i = 0; i < MAX_CHAR_LEN && line[i] !='\0'; i++)																		//����Ƿ����Ŀ¼
			if (line[i] == '/') {				//�ļ�·���е�б��ת��Ϊ��б��
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
			for (int i = 0; i < 10; i++) {
				if (strstr(line, extension[i]) != NULL) {
					need_move = FALSE;
					break;
				}
			}
			if (need_move) {
				sprintf(cmd, "MOVE %s %s", line, dir_name);
				system(cmd);
			}
		}

	}
	fclose(fp);
	printf("Extract dat file succeed.\n");
	system("pause");

}

//���dat
void extract_dat(char* dat_name) {
	char dir_name[MAX_CHAR_LEN] = { 0 };
	char cmd[MAX_CHAR_LEN] = { 0 };
	strcpy(dir_name, dat_name);
	dir_name[4] = '_';
	sprintf(cmd, "mkdir %s", dir_name);
	system(cmd);
	sprintf(cmd, "thdat.exe -x d %s > dat_file_list.txt", dat_name);
	system(cmd);
	move_dat_file(dir_name);
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
	int head = 0;
	printf("result=");
	execmd("dir /s/b th??.dat", result);
	printf(result);
	for (int i = 0; i < MAX_CHAR_LEN && result[i] != '\0'; i++)
		if (result[i] == '\\') head = i;
	for (int i = 0; i < 8; i++) {
		head++;
		dat_name[i] = result[head];
	}
	printf("dat_name=%s", dat_name);
	if (dat_name[0] != 't') {					//�Ҳ���thxx.dat�ļ�
		printf("FILE NOT FOUND!\n");
		system("pause");
		exit(0);
	}
	else printf("\n");
	system("pause");
}

int main() {
	char dat_name[MAX_CHAR_LEN] = { 0 };
	get_dat_name(dat_name);
	extract_dat(dat_name);
	printf("û\n");
	system("pause");

	return 0;
}