#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_NUM 50	//�뷡 �ִ� 50��


typedef struct
{
	char singer[30];
	char title[30];
	int count[30];

} Song;

Song song[MAX_NUM];
Song playlist_song[MAX_NUM];
char playlist[10][20];


void intro();	//���� ����

void song_list(Song* ptr, int* num);	//�뷡 ����Ʈ ���ĺ��� ���
void print_playlist(Song* ptr, int* num);	//�÷��̸���Ʈ ��� ���

int select_play(Song* ptr, int* num);	//����ڰ� �Է��� �뷡 �˻� �� ���
int entire_play(Song* ptr, int* num);	//����Ʈ�� ��ü �뷡�� ���

void add_playlist(int* num, char* ptr);	//�÷��̸���Ʈ �߰�
void add_song(Song* ptr, int* num, char *filename);	//�÷��̸���Ʈ�� �뷡 �߰�

int delete_playlist(Song* ptr, int* num);	//�÷��̸���Ʈ ����
int delete_song(Song* ptr, int* num);	//�÷��̸���Ʈ�� �뷡 ����

int included(char s1[40], char s2[40]);	//���ԵǾ����� �˻�



int main(void) {
	FILE* fr = NULL;
	fr = fopen("song_data.txt", "r");
	
	if (fr == NULL) {
		fprintf(stderr, "�뷡 ������ ���� �� �����ϴ�.");
		return -1;                //������ �� �� ���� ��(-1�� ��ȯ�� �������� ���� �ǹ�)
	}

	//��ü�뷡 ���� ����
	int number = 0;
	char c = NULL;
	while ((c = fgetc(fr)) != EOF)
		if (c == '\n') number++;
	printf("%d\n", number);



	fseek(fr, 0, SEEK_SET);	//���������� ó������
	for (int i = 0; i < number; i++) {
		fscanf(fr, "%s %s %s\n", &song[i].title, &song[i].singer, &song[i].count);
		printf("%20s %20s %20s\n", song[i].title, song[i].singer, song[i].count);

		//printf("%s\n", user[i].phone2);
	}
	fclose(fr);

	//�÷��̸���Ʈ �޾ƿ���
	FILE* frp = NULL;
	frp = fopen("playlist.txt", "r+");

	if (frp == NULL) {
		fprintf(stderr, "�÷��̸���Ʈ ������ ���� �� �����ϴ�.");
		return -1;                //������ �� �� ���� ��(-1�� ��ȯ�� �������� ���� �ǹ�)
	}

	//��ü�÷��̸���Ʈ ���� ����
	int playlist_number = 0;
	char ch = NULL;
	while ((ch = fgetc(frp)) != EOF)
		if (ch == '\n') playlist_number++;
	printf("%d\n", playlist_number);


	fseek(frp, 0, SEEK_SET);	//���������� ó������
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
	//���� �߰�����
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
		fp = fopen("playlist.txt", "r+");   //�Է� ��Ʈ�� ����
		if (fp == NULL) {
			fprintf(stderr, "can not read file.\n");

			return -1;                //������ �� �� ���� ��(-1�� ��ȯ�� �������� ���� �ǹ�)

		}

		fseek(fp, 0, SEEK_END);
		fputs(playlist_name, fp);
		fputs("\n", fp);
		(*num)++;

		fclose(fp);
		printf("added successfully.\n\n");
		return 0;
	}

	//���� ������ �� ����

	else
		printf("no storage.\n\n");

}

	




void print_playlist(Song* ptr, int* num) {
	//�ý����Լ� txt ���ϸ� �ҷ����� (song_data ����)
}



