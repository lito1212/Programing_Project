#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define MAX_WORDS 100
#define MAX_LENGTH 50

typedef struct {
	char english[MAX_LENGTH];
	char korean[MAX_LENGTH];
}Words;

int main()
{
	int choice;
	printf("=== 영단어 암기 프로그램 ===\n");

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
			printf("프로그램을 종료합니다.");
			return 0;
		default:
			printf("1~3 사이의 숫자를 입력하세요.\n");
		}
	}
	return 0;
}