#define _CRT_SECURE_NO_WARNINGS
#include "QTE.h"

//解包单个anm文件
void ExtractSingleAnm(char* anm_name, char* dir_name) {

}

//批量解包anm文件
void ExtractAllAnm(char* dir_name) {
	char result[MAX_CHAR_LEN] = { 0 };
	
}

//得到anm文件列表
void GetAnmFile(char* dir_name) {
	char cmd[MAX_CHAR_LEN] = { 0 };
	sprintf(cmd, "mkdir %s\\ANM", dir_name);
	system(cmd);
	sprintf(cmd, "dir /s/b %s\\*.anm > %s\\ANM\\anm_file_list.txt", dir_name, dir_name);
	system(cmd);
	printf("Get anm file list succeed.\n");
	system("pause");
}

//移动dat解包出的文件
void MoveDatFile(char* dir_name) {
	char cmd[MAX_CHAR_LEN] = { 0 };
	//先批量移动再单个移动，提高效率
	//批量移动
	char *extension[EXTENSION_AMOUNT] = {
	".anm",".rpy",".ecl",".jpg",".end",".sht",".wav",".std",".mid",".png",".msg"
	};
	for (int i = 0; i < EXTENSION_AMOUNT; i++) {
		sprintf(cmd, "MOVE *%s %s", extension[i], dir_name);
		system(cmd);
	}
	//单个移动
	FILE *fp = fopen("dat_file_list.txt", "rt");
	char line[MAX_CHAR_LEN] = { 0 };
	char root[MAX_CHAR_LEN] = { 0 };
	while (!feof(fp)) {
		fgets(line, MAX_CHAR_LEN, fp);
		//待定的格斗作dat解包
		/*
		for (int i = 0; i < MAX_CHAR_LEN && line[i] !='\0'; i++)																		//检测是否带有目录
			if (line[i] == '/') {				//文件路径中的全部斜杠转换为反斜杠
				line[i] = '\\';
				f = 1;
			}
		if (f) {																							//若带有目录，直接移动根目录
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
		printf("正在清理缓存...");
		sprintf(cmd, "RMDIR %s /s /q", root);																//清理缓存
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
				if (find = strchr(line, '\n')) *find = '\0';		//去掉fgets获取到的换行符
				sprintf(cmd, "MOVE %s %s", line, dir_name);
				system(cmd);
			}
		}

	}
	fclose(fp);
	system("cls");
}

//解包dat文件
void ExtractDat(char* dat_name, int game_ver) {
	char dir_name[MAX_CHAR_LEN] = { 0 };
	char cmd[MAX_CHAR_LEN] = { 0 };
	GetDirName(dat_name, dir_name);
	sprintf(cmd, "mkdir %s", dir_name);
	system(cmd);
	if (!game_ver) {				//未指定游戏版本
		sprintf(cmd, "thdat.exe -x d %s > dat_file_list.txt", dat_name);
	}
	else{
		sprintf(cmd, "thdat.exe -x %d %s > dat_file_list.txt", game_ver, dat_name);
	}
	system(cmd);
	MoveDatFile(dir_name);
	if (dat_path[0] != '\0') {					//若在其他路径，则移回去
		sprintf(cmd, "xcopy /e /y %s %s\\%s\\", dir_name, dat_path, dir_name);
		system(cmd);
		sprintf(cmd, "xcopy /y dat_file_list.txt %s\\", dat_path);
		system(cmd);
	}
	printf("Extract dat file succeed.\n");
	system("pause");
}

//执行cmd命令并获取结果
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

//获取dat文件名
int GetDatName(char* dat_name) {
	char result[MAX_CHAR_LEN] = { 0 };
	execmd("dir /s/b th??.dat", result);
	char *find;
	if (find = strrchr(result, '\\')) {
		strcpy(dat_name, ++find);
		if (find = strchr(dat_name, '\n')) *find = '\0';
		//printf("result=%s", result);
		printf("dat_name=%s\n", dat_name);
		system("pause");
		return 1;
	}
	return 0;
}

int GetDatFull(char* dat_name) {
	char dat_full[MAX_CHAR_LEN] = { 0 };
	char cmd[MAX_CHAR_LEN] = { 0 };
	int version = 0;
	gets(dat_full);
	char *find;
	if (find = strrchr(dat_full, '>')) {			//指定了游戏版本
		*find = '\0';
		version = atoi(++find);
	}
	sprintf(cmd, "xcopy /y %s \"%%cd%%\" > NUL", dat_full);
	system(cmd);
	find = strrchr(dat_full, '\\');
	*find = '\0';
	strcpy(dat_name, ++find);
	printf("dat_name=%s\n", dat_name);
	strcpy(dat_path, dat_full);
	printf("dat_path=%s\n", dat_path);
	return version;
}

//文件名转换为路径名
void GetDirName(char* dat_name, char* dir_name) {
	strcpy(dir_name, dat_name);
	char *find;
	if (find = strrchr(dir_name, '.')) *find = '_';
}

int main() {
	int game_ver = 0;
	char dat_name[MAX_CHAR_LEN] = { 0 };
	char dir_name[MAX_CHAR_LEN] = { 0 };
	char cmd[MAX_CHAR_LEN] = { 0 };
	if (!GetDatName(dat_name)) {
		system("cls");
		game_ver = GetDatFull(dat_name);
		printf("game_ver=%d\n", game_ver);
		system("pause");
	}
	ExtractDat(dat_name, game_ver);
	//GetDirName(dat_name, dir_name);
	//GetAnmFile(dir_name);
	//ExtractAllAnm(dir_name);
	return 0;
}