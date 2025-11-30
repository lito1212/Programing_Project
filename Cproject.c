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

Words vocabulary[MAX_WORDS];
int word_count = 0;
Statistics stats = { 0,0,0 };

void Menu()
{
	printf("1. 단어 추가\n");
	printf("2. 단어 목록 보기\n");
	printf("3. 단어 검색\n");
	printf("4. 단어 삭제\n");
	printf("5. 단어 시험\n");
	printf("6. 틀린 단어 복습\n");
	printf("7. 종료\n");
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

	printf("=== 단어 추가 ===\n");
	printf("영어 단어: ");
	fgets(vocabulary[word_count].english, MAX_LENGTH, stdin);
	vocabulary[word_count].english[strcspn(vocabulary[word_count].english, "\n")] = 0;

	printf("뜻: ");
	fgets(vocabulary[word_count].korean, MAX_LENGTH, stdin);
	vocabulary[word_count].korean[strcspn(vocabulary[word_count].korean, "\n")] = 0;

	if (strlen(vocabulary[word_count].korean) == 0)
	{
		printf("단어를 입력해주세요.\n\n");
		return;
	}

	if (strlen(vocabulary[word_count].korean) == 0) 
	{
		printf("뜻을 입력해주세요.\n\n");
		return;
	}

	vocabulary[word_count].wrongcount = 0;
	word_count++;
	saveWords(); 
	printf("\n단어가 추가되었습니다! (총 %d개)\n\n", word_count);
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
	{
		printf("%2d. %-20s %-20s %d\n", i + 1, vocabulary[i].english,
			vocabulary[i].korean,
			vocabulary[i].wrongcount);
	}
	printf("\n");
}
void loadWords()
{
	FILE* file = fopen(FILENAME, "r");

	if (file == NULL)
	{
		printf("저장된 파일이 없습니다. \n\n");
		return;
	}

	word_count = 0;

	while (fscanf(file, "%[^|]|%[^|]|%d\n",
		            vocabulary[word_count].english,
		            vocabulary[word_count].korean,
		            &vocabulary[word_count].wrongcount) == 3)
	{
		word_count++;
		if (word_count >= MAX_WORDS)
			break;
	}
	fclose(file);
	printf("저장된 단어 %d개를 불러왔습니다.\n\n", word_count);
}
void saveWords() 
{
	FILE* file = fopen(FILENAME, "w");

	if (file == NULL) 
	{
		printf("오류: 파일 저장에 실패했습니다.\n");
		return;
	}

	for (int i = 0; i < word_count; i++) 
	{
		fprintf(file, "%s|%s|%d\n", vocabulary[i].english, vocabulary[i].korean, vocabulary[i].wrongcount);
	}

	fclose(file);
	printf("단어 %d개가 저장되었습니다.\n", word_count);
}
void deleteWords() 
{
	if (word_count == 0) {
		printf("삭제할 단어가 없습니다.\n\n");
		return;
	}

	viewWords();

	int num;
	printf("삭제할 단어 번호: ");

	if (scanf("%d", &num) != 1) {
		clearInputBuffer();
		printf("잘못된 입력입니다.\n\n");
		return;
	}
	clearInputBuffer();

	if (num < 1 || num > word_count) {
		printf("잘못된 번호입니다.\n\n");
		return;
	}

	// 삭제할 단어 정보 저장
	char deletedWords[MAX_LENGTH];
	strcpy(deletedWords, vocabulary[num - 1].english);

	// 배열에서 삭제 (뒤 요소들을 앞으로 이동)
	for (int i = num - 1; i < word_count - 1; i++)
		vocabulary[i] = vocabulary[i + 1];
	word_count--;

	saveWords();  // 삭제 후 자동 저장
	printf("\n'%s' 단어가 삭제되었습니다. (남은 단어: %d개)\n\n", deletedWords, word_count);
}

void toLowerCase(char* str)
{
	for (int i = 0; str[i]; i++)
		str[i] = tolower(str[i]);
}
void searchWord()
{
	if (word_count == 0)
	{
		printf("저장된 단어가 없습니다. \n\n");
		return;
	}
	char keyword[MAX_LENGTH];
	printf("=== 단어 검색 ===\n");
	printf("검색 (영어/한글): ");
	fgets(keyword, MAX_LENGTH, stdin);
	keyword[strcspn(keyword, "\n")] = 0;

	if (strlen(keyword) == 0)
	{
		printf("검색을 해주세요.\n\n");
		return;
	}

	toLowerCase(keyword);
	int found = 0;

	printf("=== 검색 결과 ===\n");
	for (int i = 0; i < word_count; i++)
	{
		char tempENG[MAX_LENGTH], tempKOR[MAX_LENGTH];
		strcpy(tempENG, vocabulary[i].english);
		strcpy(tempKOR, vocabulary[i].korean);
		toLowerCase(tempENG);
		toLowerCase(tempKOR);

		if (strstr(tempENG, keyword) != NULL || strstr(tempKOR, keyword) != NULL)
		{
			printf("%2d. %-20s : %s\n", i + 1, vocabulary[i].english, vocabulary[i].korean);
			found++;
		}
	}
	if (found == 0)
		printf("검색 결과가 없습니다.\n");
	else
		printf("총 %d개의 단어를 찾았습니다.\n", found);
	printf("\n");
}
void Test()
{
	if (word_count == 0) {
		printf("저장된 단어가 없습니다. 먼저 단어를 추가하세요.\n\n");
		return;
	}

	int numQuestions;
	printf("=== 단어 시험 ===\n");
	printf("문제 수 (1-%d, 0=전체): ", word_count);

	if (scanf("%d", &numQuestions) != 1) 
	{
		clearInputBuffer();
		printf("잘못된 입력입니다.\n\n");
		return;
	}
	clearInputBuffer();

	if (numQuestions <= 0 || numQuestions > word_count)
		numQuestions = word_count;

	int* used = (int*)calloc(word_count, sizeof(int));
	if (used == NULL) 
	{
		printf("메모리 할당 실패!\n\n");
		return;
	}

	int correct = 0;

	printf("=== 시험 시작 ===\n");
	printf("(대소문자 구분하지 않음)\n\n");

	for (int i = 0; i < numQuestions; i++) {
		int index;
		do {
			index = rand() % word_count;
		} while (used[index]);

		used[index] = 1;

		char answer[MAX_LENGTH];
		char correctAnswer[MAX_LENGTH];

		printf("문제 %d: %s\n", i + 1, vocabulary[index].korean);
		printf("정답: ");
		fgets(answer, MAX_LENGTH, stdin);
		answer[strcspn(answer, "\n")] = 0;

		strcpy(correctAnswer, vocabulary[index].english);
		toLowerCase(answer);
		toLowerCase(correctAnswer);

		if (strcmp(answer, correctAnswer) == 0) {
			printf("✓ 정답입니다!\n\n");
			correct++;
		}
		else {
			printf("✗ 틀렸습니다. 정답: %s\n\n", vocabulary[index].english);
			vocabulary[index].wrongcount++;  // 틀린 횟수 증가
		}
	}

	free(used);

	saveWords();  // 틀린 횟수 저장

	float percentage = (float)correct / numQuestions * 100;

	printf("===================================\n");
	printf("        시험 결과\n");
	printf("===================================\n");
	printf("총 문제: %d\n", numQuestions);
	printf("맞은 개수: %d\n", correct);
	printf("틀린 개수: %d\n", numQuestions - correct);
	printf("정답률: %.1f%%\n", percentage);

	if (percentage >= 90) 
		printf("평가: 훌륭합니다!\n");
	else if (percentage >= 70)
		printf("평가: 잘했습니다!\n");
	else if (percentage >= 50)
		printf("평가: 조금 더 노력하세요!\n");
	else
		printf("평가: 복습이 필요합니다!\n");

	printf("===================================\n\n");
}
void reviewWrongWords() {
	if (word_count == 0) {
		printf("저장된 단어가 없습니다.\n\n");
		return;
	}

	// 틀린 단어만 필터링
	int wrongIndices[MAX_WORDS];
	int wrongcount = 0;

	for (int i = 0; i < word_count; i++) {
		if (vocabulary[i].wrongcount > 0) {
			wrongIndices[wrongcount++] = i;
		}
	}

	if (wrongcount == 0) {
		printf("틀린 단어가 없습니다. 완벽합니다!\n\n");
		return;
	}

	printf("--- 틀린 단어 목록 (총 %d개) ---\n", wrongcount);
	for (int i = 0; i < wrongcount; i++) {
		int idx = wrongIndices[i];
		printf("%2d. %-20s : %-20s (틀린 횟수: %d)\n",
			i + 1,
			vocabulary[idx].english,
			vocabulary[idx].korean,
			vocabulary[idx].wrongcount);
	}

	printf("\n이 단어들로 시험을 볼까요? (y/n): ");
	char choice;
	scanf("%c", &choice);
	clearInputBuffer();

	if (choice != 'y' && choice != 'Y') {
		printf("\n");
		return;
	}

	// 틀린 단어로 시험
	int correct = 0;

	printf("\n========== 복습 시험 시작 ==========\n\n");

	for (int i = 0; i < wrongcount; i++) {
		int idx = wrongIndices[i];
		char answer[MAX_LENGTH];
		char correctAnswer[MAX_LENGTH];

		printf("문제 %d: %s\n", i + 1, vocabulary[idx].korean);
		printf("정답: ");
		fgets(answer, MAX_LENGTH, stdin);
		answer[strcspn(answer, "\n")] = 0;

		strcpy(correctAnswer, vocabulary[idx].english);
		toLowerCase(answer);
		toLowerCase(correctAnswer);

		if (strcmp(answer, correctAnswer) == 0) {
			printf("✓ 정답입니다!\n\n");
			correct++;
		}
		else {
			printf("✗ 틀렸습니다. 정답: %s\n\n", vocabulary[idx].english);
		}
	}

	float percentage = (float)correct / wrongcount * 100;

	printf("===================================\n");
	printf("복습 결과: %d / %d (%.1f%%)\n", correct, wrongcount, percentage);
	printf("===================================\n\n");
}
