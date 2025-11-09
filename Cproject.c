#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define MAX_WORDS 100
#define MAX_LENGTH 50

typedef struct {
	char english[MAX_LENGTH];
	char korean[MAX_LENGTH];
}Words;

Words vocabulary[MAX_WORDS];
int word_count = 0;

void Menu()
{
	printf("1. 단어 추가\n");
	printf("2. 단어 목록 보기\n");
	printf("3. 종료\n");
}
void clearInputBuffer()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}
void addWords()
{
	if (word_count >= MAX_WORDS)
	{
		printf("더 이상 단어를 추가할 수 없습니다.\n\n");
		return;
	}

	printf("영어 단어: ");
	fgets(vocabulary[word_count].english, MAX_LENGTH, stdin);
	vocabulary[word_count].english[strcspn(vocabulary[word_count].english, "\n")] = 0;

	printf("뜻: ");
	fgets(vocabulary[word_count].korean, MAX_LENGTH, stdin);
	vocabulary[word_count].korean[strcspn(vocabulary[word_count].korean, "\n")] = 0;

	word_count++;
	printf("단어가 추가되었습니다.\n");
}
void viewWords()
{
	if (word_count == 0)
	{
		printf("저장된 단어가 없습니다.\n\n");
		return;
	}
	printf("=== 단어 목록 ===\n");
	for (int i = 0; i < word_count; i++)
		printf("%d. %s - %s\n", i + 1, vocabulary[i].english, vocabulary[i].korean);
	printf("\n");
}