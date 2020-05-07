#define _CRT_SECURE_NO_WARNINGS
#include "QTE.h"

//解包单个anm文件
void ExtractSingleAnm(char* anm_name, char* dir_name) {

}

//批量解包anm文件
void ExtractAllAnm(char* dir_name) {
	char result[MAX_CHAR_LEN] = { 0 };
	
}

//获取anm文件列表
void GetAnmFile(char* dir_name) {
	char cmd[MAX_CHAR_LEN] = { 0 };
	sprintf(cmd, "mkdir %s\\ANM", dir_name);
	system(cmd);
	sprintf(cmd, "dir /s/b %s\\*.anm > %s\\ANM\\anm_file_list.txt", dir_name, dir_name);
	system(cmd);
	printf("Get anm file list succeed.\n");
	system("pause");
}

//移动dat解包出的文件（格斗作）
void MoveDatFileFTG(int game_ver) {
	char cmd[MAX_CHAR_LEN] = { 0 };
	if (game_ver == 105) {
		system("mkdir th105_dat");
		system("move data th105_dat");
	}
	else if (game_ver == 123) {
		system("mkdir th123_dat");
		system("move data th123_dat");
	}
}

//解包单个dat文件（格斗作）
void ExtractDatFTG(char* dat_name, int game_ver) {
	char dir_name[MAX_CHAR_LEN] = { 0 };
	char cmd[MAX_CHAR_LEN] = { 0 };
	sprintf(cmd, "thdat.exe -x %d %s", game_ver, dat_name);
	system(cmd);
}

//移动单个dat解包出的文件(STG)
void MoveDatFile(char* dir_name) {
	char cmd[MAX_CHAR_LEN] = { 0 };
	//先批量移动再单个移动，提高效率
	//批量移动
	char *extension[EXTENSION_AMOUNT] = {
	".anm",".rpy",".ecl",".jpg",".end",".sht",".wav",".std",".mid",".png",".msg",
	".ant",".ect",".mst"		//风神录汉化（繁体）
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

//解包单个dat文件(STG)
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
	//sprintf(cmd, "del %s", dat_name);
	//system(cmd);
}

//判断是否为格斗作
int CheckFTG(int game_ver) {
	if (game_ver == 103 || game_ver == 123) return 1;
	else return 0;
}

//解包所有文件
void ExtractAll() {
	int num = 0;
	int th105_flag = 0;
	int th123_flag = 0;
	while (strlen(dat_list[num])){
		int game_ver = GetGameVersion(dat_list[num]);
		if (game_ver == 105) {
			ExtractDatFTG(dat_list[num], game_ver);
			th105_flag = 1;
		}
		else if (game_ver == 123) {
			if (th105_flag) {
				MoveDatFileFTG(105);
				th105_flag = 0;
			}
			ExtractDatFTG(dat_list[num], game_ver);
			th123_flag = 1;
		}
		else ExtractDat(dat_list[num], game_ver);
		++num;
	}
	//多个格斗作dat文件解压后，文件将全部位于data目录下
	//所以等循环结束后再移动
	//但由于绯想天和非想天则的目录都是dat，会合并
	//所以如果已经解包绯想天，需要先移动，再解包非想天则
	if (th105_flag) MoveDatFileFTG(105);
	if (th123_flag) MoveDatFileFTG(123);
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

//获取游戏版本
int GetGameVersion(char dat_name[]) {
	//水平有限只想到这种愚蠢的方法
	if (mode == 0) {
		if (strcmp(dat_name, "th105a.dat") == 0) return 105;
		else if (strcmp(dat_name, "th105b.dat") == 0) return 105;
		else if (strcmp(dat_name, "th105c.dat") == 0) return 105;
		else if (strcmp(dat_name, "th123a.dat") == 0) return 123;
		else if (strcmp(dat_name, "th123b.dat") == 0) return 123;
		else if (strcmp(dat_name, "th123c.dat") == 0) return 123;
	}
	if (strcmp(dat_name, "紅魔郷CM.DAT") == 0) return 6;
	else if (strcmp(dat_name, "紅魔郷ED.DAT") == 0) return 6;
	else if (strcmp(dat_name, "紅魔郷IN.DAT") == 0) return 6;
	else if (strcmp(dat_name, "紅魔郷MD.DAT") == 0) return 6;
	else if (strcmp(dat_name, "紅魔郷ST.DAT") == 0) return 6;
	else if (strcmp(dat_name, "紅魔郷TL.DAT") == 0) return 6;
	else if (strcmp(dat_name, "峠杺嫿CM.DAT") == 0) return 6;
	else if (strcmp(dat_name, "峠杺嫿ED.DAT") == 0) return 6;
	else if (strcmp(dat_name, "峠杺嫿IN.DAT") == 0) return 6;
	else if (strcmp(dat_name, "峠杺嫿MD.DAT") == 0) return 6;
	else if (strcmp(dat_name, "峠杺嫿ST.DAT") == 0) return 6;
	else if (strcmp(dat_name, "峠杺嫿TL.DAT") == 0) return 6;
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
	else if (strcmp(dat_name, "th17c.dat") == 0) return 17;		//尝鲜版汉化
	else return 0;
}

//获取dat文件名列表
int GetDatList() {
	char result[MAX_CHAR_LEN] = { 0 };
	printf("List of .dat file:\n\n");
	execmd("dir /a:-d /b /o /p /w *.dat", result);		//获取dat文件列表
	char *find;
	if (find = strchr(result, '.') == NULL) return 0;		//没有找到dat文件
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
	printf("\n");
	system("pause");
	if (strlen(dat_list[0])) return 1;		//至少有一个支持的dat文件
	else return 0;							//找到了dat文件，但不支持
}

//文件名转换为路径名
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

//检查依赖完整性
void CheckFiles() {
	char thdat_info[MAX_CHAR_LEN] = { 0 };
	char thdat_file[MAX_CHAR_LEN] = { 0 };
	char thanm_info[MAX_CHAR_LEN] = { 0 };
	char thanm_file[MAX_CHAR_LEN] = { 0 };
	char thtk_dll_file[MAX_CHAR_LEN] = { 0 };
	char thtk_lib_file[MAX_CHAR_LEN] = { 0 };
	char cv2conv_file[MAX_CHAR_LEN] = { 0 };
	char *thdat_ver, *thanm_ver;
	
	//检查thdat版本
	printf("thdat version: ");
	execmd("dir /a:-d /b /o /p /w thdat.exe", thdat_file);
	if (strcmp(thdat_file, "thdat.exe\n") == 0) {
		execmd("thdat.exe -V", thdat_info);
		if (thdat_ver = strstr(thdat_info, "Touhou Toolkit release")) {
			printf(thdat_ver += 23);
		}
		else {
			printf("NOT FOUND (or using antiquated version)");
		}
	}
	else {
		mode = 2;
	}
	//检查thanm版本
	printf("thanm version: ");
	execmd("dir /a:-d /b /o /p /w thanm.exe", thanm_file);
	if (strcmp(thanm_file, "thanm.exe\n") == 0) {
		execmd("thanm.exe -V", thanm_info);
		if (thanm_ver = strstr(thanm_info, "Touhou Toolkit release")) {
			printf(thanm_ver += 23);
		}
		else {
			printf("NOT FOUND (or using antiquated version)");
		}
	}
	else {
		mode = 2;
	}
	//检查是否存在thtk.dll
	printf("thtk.dll: ");
	execmd("dir /a:-d /b /o /p /w thtk.dll", thtk_dll_file);
	if (strcmp(thtk_dll_file, "thtk.dll\n") == 0) {
		printf("YES\n");
	}
	else {
		mode = 2;
	}
	//检查是否存在thtk.lib
	printf("thtk.lib: ");
	execmd("dir /a:-d /b /o /p /w thtk.dll", thtk_lib_file);
	if (strcmp(thtk_lib_file, "thtk.dll\n") == 0) {
		printf("YES\n");
	}
	else {
		mode = 2;
	}
	//检查是否存在cv2conv.exe
	printf("cv2conv.exe (for FTG): ");
	execmd("dir /a:-d /b /o /p /w cv2conv.exe", cv2conv_file);
	if (strcmp(cv2conv_file, "cv2conv.exe\n") == 0) {
		printf("YES\n");
	}
	else {
		if (mode == 0) mode = 1;
		else mode = 2;
	}
	if (mode == 2) {
		printf("\n[ERROR] NECESSARY FILE MISSING !\n\n");
		system("pause");
		exit(0);
	}
	else if (mode == 1) {
		printf("\n[WARNING] CAN NOT EXTRACT FTG DATA !\n\n");
	}
	if (!GetDatList()) {
		system("pause");
		exit(0);
	}
}

int main() {
	CheckFiles();
	ExtractAll();
	//GetDirName(dat_name, dir_name);
	//GetAnmFile(dir_name);
	//ExtractAllAnm(dir_name);
	return 0;
}