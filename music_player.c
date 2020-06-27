#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_NUM 50	//노래 최대 50곡


typedef struct
{
	char singer[30];
	char title[30];
	int count[30];

} Song;

Song song[MAX_NUM];
Song playlist_song[MAX_NUM];
char playlist[10][20];


void intro();	//사용법 설명

void song_list(Song* ptr, int* num);	//노래 리스트 알파벳순 출력
void print_playlist(Song* ptr, int* num);	//플레이리스트 목록 출력

int select_play(Song* ptr, int* num);	//사용자가 입력한 노래 검색 후 재생
int entire_play(Song* ptr, int* num);	//리스트의 전체 노래를 재생

void add_playlist(int* num, char* ptr);	//플레이리스트 추가
void add_song(Song* ptr, int* num, char *filename);	//플레이리스트에 노래 추가

int delete_playlist(Song* ptr, int* num);	//플레이리스트 삭제
int delete_song(Song* ptr, int* num);	//플레이리스트의 노래 삭제

int included(char s1[40], char s2[40]);	//포함되었는지 검색



int main(void) {
	FILE* fr = NULL;
	fr = fopen("song_data.txt", "r");
	
	if (fr == NULL) {
		fprintf(stderr, "노래 파일을 읽을 수 없습니다.");
		return -1;                //파일을 쓸 수 없을 때(-1의 반환은 비정상적 종료 의미)
	}

	//전체노래 갯수 세기
	int number = 0;
	char c = NULL;
	while ((c = fgetc(fr)) != EOF)
		if (c == '\n') number++;
	printf("%d\n", number);



	fseek(fr, 0, SEEK_SET);	//파일포인터 처음으로
	for (int i = 0; i < number; i++) {
		fscanf(fr, "%s %s %s\n", &song[i].title, &song[i].singer, &song[i].count);
		printf("%20s %20s %20s\n", song[i].title, song[i].singer, song[i].count);

		//printf("%s\n", user[i].phone2);
	}
	fclose(fr);

	//플레이리스트 받아오기
	FILE* frp = NULL;
	frp = fopen("playlist.txt", "r+");

	if (frp == NULL) {
		fprintf(stderr, "플레이리스트 파일을 읽을 수 없습니다.");
		return -1;                //파일을 쓸 수 없을 때(-1의 반환은 비정상적 종료 의미)
	}

	//전체플레이리스트 갯수 세기
	int playlist_number = 0;
	char ch = NULL;
	while ((ch = fgetc(frp)) != EOF)
		if (ch == '\n') playlist_number++;
	printf("%d\n", playlist_number);


	fseek(frp, 0, SEEK_SET);	//파일포인터 처음으로
	for (int i = 0; i < playlist_number; i++) {
		fgets(playlist[i],20,frp);
		printf("%s",playlist[i]);
	}

	//song_list(song, &number);
	add_playlist(playlist, &playlist_number);
	//add_song(song1, &number, "jinyplay.txt");

	fclose(frp);

	return 0;
}


void intro() {
	printf("Welcome to Music Play Console App");
	//내용 추가하자
}

void song_list(Song* ptr, int* num) {
	int i, j;
	Song temp;

	for (i = 0; i < *num - 1; i++) {
		for (j = 0; j < *num - i - 1; j++) {
			if (strcmp(ptr[j].title, ptr[j + 1].title) > 0) {
				temp = ptr[j];
				ptr[j] = ptr[j + 1];
				ptr[j + 1] = temp;
			}
		}
	}

	for (int i = 0; i < *num; i++) {
		printf("%d. %s %s %s\n", i + 1, ptr[i].title, ptr[i].singer, ptr[i].count);

	}
}

void add_playlist(char* ptr,int* num) {
	char* filename[50];
	printf("Input playlist name you want to add.\nname : ");
	scanf("%s", filename);
	char* playlist_name[50];
	strcpy(playlist_name,filename);
	strcat(filename, ".txt");
	FILE* fw = NULL;
	fw = fopen(filename, "w");
	fclose(fw);


	if (*num < 10) {
		FILE* fp = NULL;
		fp = fopen("playlist.txt", "r+");   //입력 스트림 형성
		if (fp == NULL) {
			fprintf(stderr, "can not read file.\n");

			return -1;                //파일을 쓸 수 없을 때(-1의 반환은 비정상적 종료 의미)

		}

		fseek(fp, 0, SEEK_END);
		fputs(playlist_name, fp);
		fputs("\n", fp);
		(*num)++;

		fclose(fp);
		printf("added successfully.\n\n");
		return 0;
	}

	//유저 정보가 꽉 차면

	else
		printf("no storage.\n\n");

}

	




void print_playlist(Song* ptr, int* num) {
	//시스템함수 txt 파일만 불러오기 (song_data 제외)
}



