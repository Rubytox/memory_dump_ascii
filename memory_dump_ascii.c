#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Converts a character to the hexadecimal value it represents.
 * Ex: 'a' => 0xA
 *
 * @param   hex     A character representing a text hex value.
 *
 * @return  The corresponding numeric value.
 */
int hex_to_int(char hex)
{
    if (hex >= '0' && hex <= '9') {
        return hex - '0';
    }
    if (hex >= 'a' && hex <= 'f') {
        return hex - 'a' + 0xa;
    }
    if (hex >= 'A' && hex <= 'F') {
        return hex - 'A' + 0xa;
    }

    printf("The provided character %c is not a valid hexadecimal character.\n", hex);
    exit(-1);
}

/**
 * An implementation of strtol that works on two characters-hex
 * strings.
 *
 * @param   hex     Two hexadecimal characters that represent a byte.
 *
 * @return  The corresponding byte.
 */
int my_strtol16(char hex[2])
{
    return hex_to_int(hex[0]) * 16 + hex_to_int(hex[1]);
}

/**
 * Converts an hexadecimal string to an ASCII string.
 * For instance:
 * '414243' ==> 'ABC'
 *
 * @param   hexstring   An hexadecimal string (e.g. a hash).
 *
 * @return  A string composed of the ASCII values of the bytes of the string.
 */
char *to_ascii(char *hexstring)
{
    int len = strlen(hexstring);
    char *result = calloc(len / 2 + 1, sizeof(char));
    for (int i = 0; i < len; i += 2) {
        char byte[3] = { hexstring[i], hexstring[i + 1], '\0' };
        result[i / 2] = my_strtol16(byte);
    }
    return result;
}

/**
 * Prints an hexdump of the stack of size 32 in ASCII.
 * It works in the following way:
 * - it takes a string of the form 12345678.12345678. ... 12345678,
 * - it splits the string around the '.' character and for each subsequent word 12345678:
 *   > the bytes of the word are reversed because of little endian convention: 78563412,
 *   > the resulting hex string is converted to four ASCII characters using _to_ascii_ function,
 *   > the resulting ASCII string is appended to the previously computed ASCII strings.
 *
 * @param   hexdump     Dump of the memory in the format:
 *                      %08x.%08x. ... %08x
 * @return  An ASCII string representing the memory dump.
 */
char *ascii_memory_dump(char *hexdump)
{
    int nb_words = (strlen(hexdump) + 1) / 9;  // It is XXXXXXXX. and +1 dot at the end
    char *res = calloc(nb_words, 4 * sizeof(char));

    /*
     * Split, invert and convert
     */
    char *word = strtok(hexdump, ".");
    while (word != NULL) {
        char inverted_word[9] = { 0 };
        inverted_word[0] = word[6];
        inverted_word[1] = word[7];
        inverted_word[2] = word[4];
        inverted_word[3] = word[5];
        inverted_word[4] = word[2];
        inverted_word[5] = word[3];
        inverted_word[6] = word[0];
        inverted_word[7] = word[1];

        char *ascii = to_ascii(inverted_word);
        strncat(res, ascii, 8);
        free(ascii);

        word = strtok(NULL, ".");
    }
    return res;
}


int main(int argc, char *argv[])
{
    char *result = ascii_memory_dump(argv[1]);
    printf("%s\n", result);
    free(result);

    return 0;
}
