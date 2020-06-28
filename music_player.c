#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_NUM 50	//�뷡 �ִ� 50��
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


void intro();	//���� ����

//�÷��̸���Ʈ ���� �Լ�
void print_playlist(Song *ptr,int *num);	//�÷��̸���Ʈ ��� ���
void add_playlist(Song* ptr,int *num);	//�÷��̸���Ʈ �߰�
int delete_playlist(Song* ptr, int *num);	//�÷��̸���Ʈ ����

//�뷡 ���� �Լ�
void song_list(Song* ptr, int* num);	//�뷡 ����Ʈ ���ĺ��� ���
void add_song(Song* ptr);	//�÷��̸���Ʈ�� �뷡 �߰�
int delete_song(Song* ptr);	//�÷��̸���Ʈ�� �뷡 ����

//��� �Լ�
int select_play(Song* ptr);	//����ڰ� �Է��� �뷡 �˻� �� ���
int entire_play(Song* ptr, int* num);	//����Ʈ�� ��ü �뷡�� ���






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


	if (*num < LIST_NUM) {	//�÷��̸���Ʈ�� ������ �ִ� 10���� �����Ѵ�. 
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
	for (int i = 0; i < *num; i++) {
		printf("%s\n", ptr[i].title);
	}
}

//�÷��̸���Ʈ�� �����ϴ� �Լ�
int delete_playlist(Song* ptr, int* num) {
	char name[30];
	int i,j;

	FILE* fp = NULL;
	fp = fopen("playlist.txt", "w");   //�Է� ��Ʈ�� ����
	if (fp == NULL) {
		fprintf(stderr, "can not read file.\n");
		return -1;                //������ �� �� ���� ��(-1�� ��ȯ�� �������� ���� �ǹ�)
	}

	//�����Ͱ� ���� ���� ���� �� ����.
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


		//���� ����
		for (i = 0; i < *num; i++) {
			fprintf(fp, "%s\n", ptr[i].title);
		}

		fclose(fp);

		return 0;
		printf("Can Not Found \n\n");


	}


	//����� ���� ������ ���ٸ�

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
	fw = fopen(filename, "r+");   //�Է� ��Ʈ�� ����
	if (fw == NULL) {
		fprintf(stderr, "can not read file.\n");

		return -1;                //������ �� �� ���� ��(-1�� ��ȯ�� �������� ���� �ǹ�)

	}

	//��ü�뷡 ���� ����
	int song_num = 0;
	char chh = NULL;
	while ((chh = fgetc(fw)) != EOF)
		if (chh == '\n') song_num++;
	printf("%d\n", song_num);


	fseek(fw, 0, SEEK_SET);	//���������� ó������
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

	//���� ������ �� ����

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
	fr = fopen(filename, "r");   //�Է� ��Ʈ�� ����
	if (fr == NULL) {
		fprintf(stderr, "can not read file.\n");

		return -1;                //������ �� �� ���� ��(-1�� ��ȯ�� �������� ���� �ǹ�)

	}

	//��ü�뷡 ���� ����
	int song_num = 0;
	char chh = NULL;
	while ((chh = fgetc(fr)) != EOF)
		if (chh == '\n') song_num++;
	printf("%d\n", song_num);


	fseek(fr, 0, SEEK_SET);	//���������� ó������
	for (int i = 0; i < song_num; i++) {
		fscanf(fr, "%s %s\n", &ptr[i].title, &ptr[i].singer);
		printf("%20s %20s\n", ptr[i].title, ptr[i].singer);

		//printf("%s\n", user[i].phone2);
	}

	fclose(fr);


	FILE* fw = NULL;
	fw = fopen(filename, "w");   //�Է� ��Ʈ�� ����
	if (fw == NULL) {
		fprintf(stderr, "can not read file.\n");

		return -1;                //������ �� �� ���� ��(-1�� ��ȯ�� �������� ���� �ǹ�)
	}
	char name[30];
	int i, j;

	//�����Ͱ� ���� ���� ���� �� ����.
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

		fseek(fw, 0, SEEK_SET);	//���������� ó������
		//���� ����
		for (i = 0; i < song_num; i++) {
			printf("%s %s\n", ptr[i].title, ptr[i].singer);
			fprintf(fw, "%s %s\n", ptr[i].title, ptr[i].singer);
		}

		fclose(fw);

		return 0;
		printf("Can Not Found \n\n");


	}


	//����� ���� ������ ���ٸ�

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
	fr = fopen(filename, "r");   //�Է� ��Ʈ�� ����
	if (fr == NULL) {
		fprintf(stderr, "can not read file.\n");

		return -1;                //������ �� �� ���� ��(-1�� ��ȯ�� �������� ���� �ǹ�)

	}

	//��ü�뷡 ���� ����
	int song_num = 0;
	char chh = NULL;
	while ((chh = fgetc(fr)) != EOF)
		if (chh == '\n') song_num++;
	printf("%d\n", song_num);


	fseek(fr, 0, SEEK_SET);	//���������� ó������
	for (int i = 0; i < song_num; i++) {
		fscanf(fr, "%s %s\n", &ptr[i].title, &ptr[i].singer);
		printf("%20s %20s\n", ptr[i].title, ptr[i].singer);

		//printf("%s\n", user[i].phone2);
	}

	fclose(fr);
	char name[30];
	int i;

	//����� �����Ͱ� �ִٸ�
	if (song_num > 0) {
		printf("Input Name: ");
		scanf("%s", name);

		int j = 0;

		for (i = 0; i < MAX_NUM; i++) {
			//strcmp�� ���ڿ��� ��ġ�Ҷ� 0�� ��ȯ
			//0�� C���� ������ �ǹ�
			//�׷��Ƿ� ! �� �ٿ� ������ �����Ͽ� ����
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
