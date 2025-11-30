#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "Cproject.h"

#define MAX_WORDS 100
#define MAX_LENGTH 50
#define FILENAME "vocabulary.txt"
#define STATS_FILENAME "stats.txt"

typedef struct {
	char english[MAX_LENGTH];
	char korean[MAX_LENGTH];
	int wrongcount;
}Words;

typedef struct {
	int totalTests;
	int totalQuestions;
	int totalCorrect;
}Statistics;

int main()
{
	int choice;
	srand(time(NULL));
	printf("=== 영단어 암기 프로그램 ===\n");

	loadWords();

	while (1)
	{

		Menu();
		printf("선택: ");

		if (scanf("%d", &choice) != 1)
		{
			clearInputBuffer();
			printf("\n잘못된 입력입니다.\n\n");
			continue;
		}
		clearInputBuffer();
		printf("\n");

		switch (choice)
		{
		case 1:
			addWords();
			break;
		case 2:
			viewWords();
			break;
		case 3:
			searchWord();
			break;
		case 4:
			deleteWords();
			break;
		case 5:
			Test();
			break;
		case 6:
			reviewWrongWords();
			break;
		case 7:
			saveWords();
			printf("저장 완료! 프로그램을 종료합니다.\n");
			return 0;
		default:
			printf("1~8 사이의 숫자를 입력하세요.\n");
		}
	}
	return 0;
}
