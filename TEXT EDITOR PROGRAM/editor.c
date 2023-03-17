#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 100
#define NOT_FOUND -1

char *Delete (char *source, int index, int n);
char *do_edit(char *source, char command);
char get_command(void);
char *insert(char *source, const char *to_insert, int index);
int pos(const char *source, const char *to_find);

int main(void)
{
	char source[MAX_LEN];
	char command;

	printf("Enter the source string:  \n");
	gets(source);

	for(command = get_command();
		command != '!';
		command = get_command())
	{

		do_edit(source, command);
		printf("New Source:  %s\n\n", source);
	}
	printf("String after editing:  %s\n", source);
	return 0;
}

char *Delete (char *source, int index, int n)
{
	char rest_str [MAX_LEN];

	if (strlen(source) <= index + n)
	{
		source[index] = '\0';
	}
	else 
	{
		strcpy(rest_str, &source[index + n]);
		strcpy(&source[index], rest_str);
	}
	
	return (source);
}

char *do_edit(char *source, char command)
{
	char str[MAX_LEN];
	int index;


	switch (command)
	{
	
	case 'D':
		printf("String to delete:  \n");
		gets(str);
		index = pos(source, str);
		if (index == NOT_FOUND)
			printf("'%s' not found\n", str);
		else
			Delete (source, index, strlen(str));
		break;

	case 'I':
		printf("String to insert:  \n");
		gets(str);
		printf("Position of insertion:  ");
		scanf("%d", &index);
		insert(source, str, index);

		break;

	case 'F':
		printf("String to find:  \n");
		gets(str);
		index = pos(source, str);
		if (index == NOT_FOUND)
			printf("'%s' not found\n", str);
		else 
			printf("'%s' found and position %d\n", str, index);
		break;

	default:
		printf("Invalid edit command  '%c'\n", command);
	}

	return (source);
}

char get_command(void)
{
	char command;
	char ignore;

	printf("Enter D(delete), I(insert), F(Find), or Q(Quit):  ");

	do 
		ignore = getchar();
	while(ignore != '\n');

	return (toupper(command));
}

char *insert(char *source, const char *to_insert, int index)
{
	char rest_str[MAX_LEN];

	if (strlen(source) <= index) 
	{
		strcat(source, to_insert);
	}
	else
	{
		strcpy(rest_str, &source[index]);
		strcpy(&source[index], to_insert);
		strcpy(source, rest_str);
	}

	return(source);

}

int pos(const char *source, const char *to_find)

{
	int i = 0;
	int find_len;
	int found = 0;
	int position;
	char substring[MAX_LEN];	

	find_len = strlen(to_find);
	while(!found && i <= strlen(source) - find_len)
	{
		strncpy(substring, &source[i], find_len);
		substring [find_len] = '\0';

		if(strcmp(substring, to_find) == 0 )
			found = 1;
		else 
			i++;
	}
	if (found)
		position = i;
	else 
		position = NOT_FOUND;

	return (position);

}