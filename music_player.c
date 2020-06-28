#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_NUM 50	//노래 최대 50곡
#define LIST_NUM 10


typedef struct
{
	char title[30];
	char singer[30];
	int count[30];

} Song;

Song song[MAX_NUM];
Song playlist_song[MAX_NUM];
Song playlist[LIST_NUM];


void intro();	//사용법 설명

//플레이리스트 관련 함수
void print_playlist(Song *ptr,int *num);	//플레이리스트 목록 출력
void add_playlist(Song* ptr,int *num);	//플레이리스트 추가
int delete_playlist(Song* ptr, int *num);	//플레이리스트 삭제

//노래 관련 함수
void song_list(Song* ptr, int* num);	//노래 리스트 알파벳순 출력
void add_song(Song* ptr);	//플레이리스트에 노래 추가
int delete_song(Song* ptr);	//플레이리스트의 노래 삭제

//재생 함수
int select_play(Song* ptr);	//사용자가 입력한 노래 검색 후 재생
int entire_play(Song* ptr, int* num);	//리스트의 전체 노래를 재생






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
		fscanf(frp,"%s\n",playlist[i].title);
	}
	fclose(frp);

	//song_list(song, &number);
	//add_playlist(playlist, &playlist_number);
	//add_song(playlist_song, &number);
	//delete_song(playlist_song);
	print_playlist(playlist, &playlist_number);
	select_play(playlist_song);
	//delete_playlist(playlist, &playlist_number);

	

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

void add_playlist(Song* ptr,int* num) {
	char* filename[50];
	printf("Input playlist name you want to add.\nname : ");
	scanf("%s", filename);
	char* playlist_name[50];
	strcpy(playlist_name,filename);
	strcat(filename, ".txt");
	FILE* fw = NULL;
	fw = fopen(filename, "w");
	fclose(fw);


	if (*num < LIST_NUM) {	//플레이리스트의 갯수는 최대 10개로 제한한다. 
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
	for (int i = 0; i < *num; i++) {
		printf("%s\n", ptr[i].title);
	}
}

//플레이리스트를 삭제하는 함수
int delete_playlist(Song* ptr, int* num) {
	char name[30];
	int i,j;

	FILE* fp = NULL;
	fp = fopen("playlist.txt", "w");   //입력 스트림 형성
	if (fp == NULL) {
		fprintf(stderr, "can not read file.\n");
		return -1;                //파일을 쓸 수 없을 때(-1의 반환은 비정상적 종료 의미)
	}

	//데이터가 있을 때만 지울 수 있음.
	if (*num > 0) {
		printf("Input Name you want to delete. : ");
		scanf("%s", name);

		int searchIndex[40] = { 0 };
		j = 0;
		//   i : start from 0 to MAX_NUM
		for (i = 0; i < LIST_NUM; i++) {
			// compare whether name and ptr array's current value is same
			if (strcmp(name, ptr[i].title)==0) {
				//  if same printf the value and
				printf("%d. %s\n", j + 1, ptr[i].title);
				// regist currnet index:i to searchIndex array
				searchIndex[j] = i;
				j++;
			}
		}


		printf("what do you wanna delete?\n");

		//   user will select number wanna delete
		int selected = -1;
		scanf("%d", &selected);
		if (selected == -1) {
			// throw error
		}

		//   after selecting, copy and overwrite value after user selected index
		for (j = searchIndex[selected - 1]; j < LIST_NUM; j++) {
			strcpy(ptr[j].title, ptr[j + 1].title);
			
		}
		// cuz one of value was Deleted and overwrited so the last value should to go away far far far from herrreee
		*ptr[LIST_NUM].title = NULL;
		
		(*num)--;


		//파일 쓰기
		for (i = 0; i < *num; i++) {
			fprintf(fp, "%s\n", ptr[i].title);
		}

		fclose(fp);

		return 0;
		printf("Can Not Found \n\n");


	}


	//저장된 유저 정보가 없다면

	else {
		printf("No Data \n\n");
		return 0;

	}

}



void add_song(Song* ptr) {
	char* filename[50];
	printf("Input playlist name you want to add song.\nname : ");
	scanf("%s", filename);
	char* playlist_name[50];
	strcpy(playlist_name, filename);
	strcat(filename, ".txt");
	

	FILE* fw = NULL;
	fw = fopen(filename, "r+");   //입력 스트림 형성
	if (fw == NULL) {
		fprintf(stderr, "can not read file.\n");

		return -1;                //파일을 쓸 수 없을 때(-1의 반환은 비정상적 종료 의미)

	}

	//전체노래 갯수 세기
	int song_num = 0;
	char chh = NULL;
	while ((chh = fgetc(fw)) != EOF)
		if (chh == '\n') song_num++;
	printf("%d\n", song_num);


	fseek(fw, 0, SEEK_SET);	//파일포인터 처음으로
	for (int i = 0; i < song_num; i++) {
		fscanf(fw, "%s %s %s\n", &ptr[i].title, &ptr[i].singer, &ptr[i].count);
		printf("%20s %20s %20s\n", ptr[i].title, ptr[i].singer, ptr[i].count);

		//printf("%s\n", user[i].phone2);
	}

	


	if (song_num < MAX_NUM) {	 
		
		printf("Input song name and singer");
		scanf("\n%s %s", ptr[song_num].title, ptr[song_num].singer);




		fseek(fw, 0, SEEK_END);
		fputs(ptr[song_num].title, fw);
		fputs(" ", fw);
		fputs(ptr[song_num].singer, fw);
		fputs("\n", fw);
		(song_num)++;

		fclose(fw);
		printf("added successfully.\n\n");
		return 0;
	}

	//유저 정보가 꽉 차면

	else
		printf("no storage.\n\n");

}



int delete_song(Song* ptr) {
	char* filename[50];
	printf("Input playlist name you want to add song.\nname : ");
	scanf("%s", filename);
	char* playlist_name[50];
	strcpy(playlist_name, filename);
	strcat(filename, ".txt");


	FILE* fr = NULL;
	fr = fopen(filename, "r");   //입력 스트림 형성
	if (fr == NULL) {
		fprintf(stderr, "can not read file.\n");

		return -1;                //파일을 쓸 수 없을 때(-1의 반환은 비정상적 종료 의미)

	}

	//전체노래 갯수 세기
	int song_num = 0;
	char chh = NULL;
	while ((chh = fgetc(fr)) != EOF)
		if (chh == '\n') song_num++;
	printf("%d\n", song_num);


	fseek(fr, 0, SEEK_SET);	//파일포인터 처음으로
	for (int i = 0; i < song_num; i++) {
		fscanf(fr, "%s %s\n", &ptr[i].title, &ptr[i].singer);
		printf("%20s %20s\n", ptr[i].title, ptr[i].singer);

		//printf("%s\n", user[i].phone2);
	}

	fclose(fr);


	FILE* fw = NULL;
	fw = fopen(filename, "w");   //입력 스트림 형성
	if (fw == NULL) {
		fprintf(stderr, "can not read file.\n");

		return -1;                //파일을 쓸 수 없을 때(-1의 반환은 비정상적 종료 의미)
	}
	char name[30];
	int i, j;

	//데이터가 있을 때만 지울 수 있음.
	if (song_num > 0) {
		printf("Input Name you want to delete. : ");
		scanf("%s", name);

		int searchIndex[40] = { 0 };
		int j = 0;
		//   i : start from 0 to MAX_NUM
		for (i = 0; i < MAX_NUM; i++) {
			// compare whether name and ptr array's current value is same
			if (strcmp(name, ptr[i].title)==0) {
				//  if same printf the value and
				printf("%d. %s\n", j + 1, ptr[i].title);
				// regist currnet index:i to searchIndex array
				searchIndex[j] = i;
				j++;
			}
		}


		printf("what do you wanna delete?\n");

		//   user will select number wanna delete
		int selected = -1;
		scanf("%d", &selected);
		if (selected == -1) {
			// throw error
		}

		//   after selecting, copy and overwrite value after user selected index
		for (j = searchIndex[selected - 1]; j < MAX_NUM; j++) {
			strcpy(ptr[j].title, ptr[j + 1].title);
			strcpy(ptr[j].singer, ptr[j + 1].singer);
		}
		// cuz one of value was Deleted and overwrited so the last value should to go away far far far from herrreee
		*ptr[MAX_NUM].title = NULL;
		*ptr[MAX_NUM].singer = NULL;
	
		song_num--;

		fseek(fw, 0, SEEK_SET);	//파일포인터 처음으로
		//파일 쓰기
		for (i = 0; i < song_num; i++) {
			printf("%s %s\n", ptr[i].title, ptr[i].singer);
			fprintf(fw, "%s %s\n", ptr[i].title, ptr[i].singer);
		}

		fclose(fw);

		return 0;
		printf("Can Not Found \n\n");


	}


	//저장된 유저 정보가 없다면

	else {
		printf("No Data \n\n");
		return 0;

	}

}



int select_play(Song* ptr) {

	char* filename[50];
	printf("Input playlist name you want to add song.\nname : ");
	scanf("%s", filename);
	char* playlist_name[50];
	strcpy(playlist_name, filename);
	strcat(filename, ".txt");


	FILE* fr = NULL;
	fr = fopen(filename, "r");   //입력 스트림 형성
	if (fr == NULL) {
		fprintf(stderr, "can not read file.\n");

		return -1;                //파일을 쓸 수 없을 때(-1의 반환은 비정상적 종료 의미)

	}

	//전체노래 갯수 세기
	int song_num = 0;
	char chh = NULL;
	while ((chh = fgetc(fr)) != EOF)
		if (chh == '\n') song_num++;
	printf("%d\n", song_num);


	fseek(fr, 0, SEEK_SET);	//파일포인터 처음으로
	for (int i = 0; i < song_num; i++) {
		fscanf(fr, "%s %s\n", &ptr[i].title, &ptr[i].singer);
		printf("%20s %20s\n", ptr[i].title, ptr[i].singer);

		//printf("%s\n", user[i].phone2);
	}

	fclose(fr);
	char name[30];
	int i;

	//저장된 데이터가 있다면
	if (song_num > 0) {
		printf("Input Name: ");
		scanf("%s", name);

		int j = 0;

		for (i = 0; i < MAX_NUM; i++) {
			//strcmp는 문자열이 일치할때 0을 반환
			//0은 C언어에서 거짓을 의미
			//그러므로 ! 을 붙여 참으로 변경하여 실행
			if (strcmp(name, ptr[i].title)==0 || strcmp(name, ptr[i].singer)==0) {

				printf("%d. %s %s %s\n", j + 1, ptr[i].title, ptr[i].singer, ptr[i].count);


				j++;

			}

		}
		printf("Match Found \n\n");
		return 0;
		printf("Not Found \n\n");
		return 0;
	}
	else {
		printf("  No Data \n\n");
		return 0;
	}
}
