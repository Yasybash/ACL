#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <windows.h>
void read_file(); //чтение файла
void write_to_file(); //запись в файл
void correct_input(char* mass); //редактирование массива
void create_file(); //создание файла
void attribut();//изменение атрибутов безопасности
int main() {
	int choice;
	FILE* file = NULL;
	while (1) {
		printf("1 - create a file, 2 - read file, 3 - write to file, 4 - changing attributes, 0 - exit: ");
		int a = scanf("%d", &choice);
		while (getchar() != '\n');
		if (!(choice)) break; 
		switch (choice) {
		case 1:
			create_file();
			break;
		case 2:
			read_file();
			break;
		case 3:
			write_to_file();
			break;
		case 4:
			attribut();
			break;
		default:
			printf("Invalid input\n");
			exit(0);
			break;
		}
	}
}
//создание файла
void create_file() {
	FILE* file = NULL;
	char name[100];
	printf("Enter filename:\n");
	fgets(name, 100, stdin);
	correct_input(name);
	file = fopen(name, "wb");
	if (file == NULL) {
		printf("Error creating file!\n\n");
		fclose(file);
		return;
	}
	printf("Successfully!\n");
	fclose(file);
}
//убираем переход на новую строку при вводе
void correct_input(char* mass) {
	int i;
	for (i = 0; mass[i] != '\n'; i++);
	mass[i] = '\0';
}
//чтение файла  
void read_file() {
	FILE* file = NULL;
	char name[100];
	printf("Enter filename:\n");
	fgets(name, 100, stdin);
	correct_input(name);
	file = fopen(name, "rb");
	if (file == NULL) {
		printf("Error opening file!\n\n");
		fclose(file);
		return;
	}
	char text[1000];
	int ch, i;
	ch = getc(file);
	for (i = 0; ch != EOF; i++) {
		text[i] = ch;
		ch = getc(file);
	}
	text[i] = '\0';
	printf("File text: %s\n", text);
	fclose(file);
}
//запись в файл
void write_to_file() {
	FILE* file = NULL;
	char name[100];
	printf("Enter filename:\n");
	fgets(name, 100, stdin);
	correct_input(name);
	file = fopen(name, "wb");
	if (file == NULL) {
		printf("Error creating/opening file!\n\n");
		fclose(file);
		return;
	}
	char text[1000];
	printf("Enter the string:\n");
	fgets(text, 1000, stdin);
	if (fwrite(text, sizeof(char), strlen(text), file) != NULL) printf("Well done!\n");
	else printf("Write error!\n");
	fclose(file);
}
//изменение атрибутов
void attribut()
{
	char name[50];
	int a = 0;
	while (a != 4) {
		printf("1 - make read-only\n2 - make hidden\n3 - make read/write\n4 - exit\n");
		scanf("%d", &a);
		switch (a)
		{
		case 1: {
			char filename[50];
			printf("Enter filename\n");
			scanf("%s", &filename);
			wchar_t wtext[50]; 
			mbstowcs(wtext, filename, strlen(filename) + 1);//переделываем строку char в тип LWSTR
			LPWSTR NAME = wtext;
			if (SetFileAttributes(NAME, FILE_ATTRIBUTE_READONLY) == 0)
			{
				printf("File not found\n");
				break;
			}
			else {
				printf("Mode changed to read-only\n");
				break;
			}

		}

		case 2: {
			char filename[50];
			printf("Enter the name of file\n");
			scanf("%s", &filename);
			wchar_t wtext[50];
			mbstowcs(wtext, filename, strlen(filename) + 1);
			LPWSTR NAME = wtext;
			if (SetFileAttributes(NAME, FILE_ATTRIBUTE_HIDDEN) == 0) //скрываем файл из каталогов
			{
				perror("File not found\n");
				break;
			}
			else
			{
				printf("Mode changed to hidden\n");
				break;
			}
		}

		case 3: {
			char filename[50];
			printf("Enter the name of file\n");
			scanf("%s", &filename);
			wchar_t wtext[50];
			mbstowcs(wtext, filename, strlen(filename) + 1);
			LPWSTR NAME = wtext;
			if (SetFileAttributes(NAME, FILE_ATTRIBUTE_NORMAL) == 0)
			{
				perror("File not found\n");
				break;
			}
			else
			{
				printf("Mode changed to read and write\n");
				break;
			}
		}

		default: 
			printf("Programm shutdown\n");
		}
	}

}
