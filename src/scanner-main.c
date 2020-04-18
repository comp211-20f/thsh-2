#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Str.h"
#include "Scanner.h"

#define BUFF_SIZE 80 

#define CHILD 0

/**
 * This program reads an input line from stdin and prints textual
 * representations of the tokens read in as inputs.
 */

size_t read_line(FILE *stream, Str *line);

int main()
{
    Str line;
    size_t bytes;
    do {
        printf("scanner> ");

        bytes = read_line(stdin, &line);

        Scanner scanner = Scanner_value(CharItr_of_Str(&line));
        while (Scanner_has_next(&scanner)) {
            Token next = Scanner_next(&scanner);
            switch (next.type) {
                case END_TOKEN: 
                    printf("END\n");
                    break;
                case WORD_TOKEN:
                    printf("WORD(%s)\n", Str_cstr(&next.lexeme));
                    break;
                case PIPE_TOKEN:
                    printf("PIPE\n");
                    break;
            }
            Str_drop(&next.lexeme);
        }
        Str_drop(&line);

    } while (bytes > 0);
    return EXIT_SUCCESS;
}

size_t read_line(FILE *stream, Str *line) {
    static char buffer[BUFF_SIZE];
    *line = Str_value(BUFF_SIZE);
    while (fgets(buffer, BUFF_SIZE, stream) != NULL) {
        Str_append(line, buffer);
        if (strchr(buffer, '\n') != NULL) {
            break;
        }
    }
    return Str_length(line);
}
