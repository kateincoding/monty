#include "monty.h"
#include <stdio.h>

void initialize_stack(void);
char *handle_comment(char *str_input);
void finalize_stack(void);

/**
 * main - entry point of the program
 *
 * @argc: argc
 * @argv: arguments
 * Return: 0 or stderr
 */
int main(int argc, char **argv)
{
	size_t buff_size = 0;

	if (argc != 2)
	{
		write(2, "USAGE: monty file\n", 18);
		exit(EXIT_FAILURE);
	}
	initialize_stack();
	svar.sfd = fopen(argv[1], "r");
	check_access_rights(argv[1]);
	if (!svar.sfd)
	{
		dprintf(2, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	while (getline(&(svar.sbuff), &buff_size, svar.sfd) >= 0)
	{
		svar.nodes_number++;
		/* buff = handle_comment(buff); */
		/* line = strtok(buff, "#"); */
		svar.opcode = strtok(svar.sbuff, " \n\t");
		if (svar.opcode)
		{
			svar.after_opcode = strtok(NULL, " \n\t");
			pick_function(svar.opcode);
		}
		svar.opcode = NULL, svar.after_opcode = NULL;
	}
	finalize_stack();
	return (0);
}

/**
 * initialize_stack - initialize the stack with a global variable
 *
 * Return: void
 */
void initialize_stack(void)
{
	/* svar.type : 0 is stack ;  1 is queue */
	svar.type = 0;
	svar.head = NULL;
	svar.sbuff = NULL;
	svar.opcode = NULL;
	svar.after_opcode = NULL;
	svar.nodes_number = 0;
}

/**
 * finalize_stack - free memmory of the stack
 *
 * Return: void
 */
void finalize_stack(void)
{
	free(svar.sbuff);
	frees_stack();
	fclose(svar.sfd);
}

/**
 * handle_comment - deletes a comment from the buffer
 * @str_input: User's input
 *
 * Return: pointer to string
 */
char *handle_comment(char *str_input)
{
	char *without_comments = str_input;

	if (*str_input == '#')
	{
		*str_input = '\n';
		*(str_input + 1) = '\0';
	}
	while (str_input && *str_input)
	{
		if (*str_input == '#' && *(str_input - 1) == ' ')
		{
			*(str_input - 1) = '\n';
			*str_input = '\0';
			break;
		}
		str_input++;
	}
	return (without_comments);
}
