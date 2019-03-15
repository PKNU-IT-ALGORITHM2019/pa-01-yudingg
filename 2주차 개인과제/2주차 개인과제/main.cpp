#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 5000
#define WORD 180000

char *list[WORD];
int n = 0;

void load();
void size();
void find(char str[]);
int search(int begin, int end, char str[], int*ptr);
int compare(char a[], char b[]);
int howmany(int index, int *ptr);
int main() {

	char buffer[MAX];
	char word[MAX];

	while (1) {
		printf("$ ");
		scanf("%s", buffer);
		if (strcmp(buffer, "read") == 0) load();
		else if (strcmp(buffer, "size") == 0) size();
		else if (strcmp(buffer, "find") == 0) {
			char tmp = fgetc(stdin);
			fgets(word, MAX, stdin);
			find(word);
		}
		else if (strcmp(buffer, "exit") == 0) break;
	}
	return 0;
}

void load() {

	char fileName[MAX];
	char buf[MAX];

	scanf("%s", fileName);
	FILE*fp = fopen(fileName, "r");
	while (!feof(fp)) {
		if (fgets(buf, MAX, fp) <= 0||strcmp(buf,"\n")==0)
			continue;
		list[n++] = strdup(buf);
	}
	fclose(fp);

}

void size() {
	printf("%d\n", n);
}

void find(char str[]) {
	
	int exis, num, start;
	char before[MAX], after[MAX];
	char *buf;

	int index = search(0, n - 1, str, &exis);

	if (exis > 0) {
		num = howmany(index, &start);
		printf("Found %d items.\n", num);
		for (int i = start; i < start + num; i++) {
			printf("%s", list[i]);
		}
	}
	else if (index==-1){
		strcpy(after, list[index + 1]);
		buf = strtok(after, ")");
		printf("Not found.\n");
		printf("- - -\n");
		printf("%s)", buf);
	}
	else {
		strcpy(before, list[index]);
		strcpy(after, list[index + 1]);
		printf("Not found.\n");
		buf = strtok(before, ")");
		printf("%s)\n", buf);
		printf("- - -\n");
		if (index + 1 < n) {
			buf = strtok(after, ")");
			printf("%s)\n", buf);
		}
	}

}

int howmany(int index, int *ptr) {
	int a = 1, re = 1;
	while (index+a<n&&compare(list[index], list[index + a]) == 0) {
		re++;
		a++;
	}
	a = 1;
	while (index-a>=0&&compare(list[index], list[index - a]) == 0) {
		re++;
		a++;
	}
	*ptr = index - a + 1;
	return re;
}



int search(int begin, int end, char str[], int*ptr) {

	int middle = (begin + end) / 2;

	if (begin > end) {
		*ptr = 0;
		return end;
	}

	int confirm = compare(list[middle], str);

	if (confirm == 1)
		search(middle + 1, end, str, ptr);
	else if (confirm == -1)
		search(begin, middle - 1, str, ptr);
	else if (confirm == 0) {
		*ptr = 1;
		return middle;
	}

}

int compare(char a[], char b[]) {
	int i = 0, j = 0, stri = 0, strj = 0;
	char str1[MAX], str2[MAX];
	while (a[i] != '('&&a[i]!='\n'&&a[i]!='\0') {
		if (!isalpha(a[i])) {
			i++;
			continue;
		}
		str1[stri++] = tolower(a[i]);
		i++;
	}
	str1[stri] = '\0';
	while (b[j] != '('&&b[j]!='\n'&&b[j]!='\0') {
		if (!isalpha(b[j])) {
			j++;
			continue;
		}
		str2[strj++] = tolower(b[j]);
		j++;
	}
	str2[strj] = '\0';

	if (strcmp(str1, str2) < 0)
		return 1;
	if (strcmp(str1, str2) > 0)
		return -1;

	return 0;
}
