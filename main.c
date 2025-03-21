#include <stdio.h>
#include <stdlib.h>

#define SURROGATE_LOW_BITS 0x7FF
#define MAX_SURROGATE     0xDFFF
#define MAX_FOUR_BYTE   0x10FFFF
#define ONE_BYTE_BITS          7
#define TWO_BYTE_BITS         11
#define TWO_BYTE_PREFIX     0xC0
#define THREE_BYTE_BITS       16
#define THREE_BYTE_PREFIX   0xE0
#define FOUR_BYTE_PREFIX    0xF0
#define CONTINUATION_BYTE   0x80
#define CONTINUATION_MASK   0x3F

/**
 * Ensure that buffer has space for AT LEAST 4 bytes before calling this function,
 *   or a buffer overrun will occur.
 * Returns the number of bytes written to buffer (0-4).
 * If scalar is a surrogate value, or is out of range for a Unicode scalar,
 *   writes nothing and returns 0.
 * Surrogate values are integers from 0xD800 to 0xDFFF, inclusive.
 * Valid Unicode scalar values are non-surrogate integers between
 *   0 and 1_114_111 decimal (0x10_FFFF hex), inclusive.
 */
int encode_utf_8(unsigned long scalar, char* buffer) {
	if ((scalar | SURROGATE_LOW_BITS) == MAX_SURROGATE || scalar > MAX_FOUR_BYTE) {
		return 0;
	}

	int bytes_written = 0;

	if ((scalar >> ONE_BYTE_BITS) == 0) {
		*buffer++ = scalar;
		bytes_written = 1;
	}
	else if ((scalar >> TWO_BYTE_BITS) == 0) {
		*buffer++ = TWO_BYTE_PREFIX | (scalar >> 6);
		bytes_written = 2;
	}
	else if ((scalar >> THREE_BYTE_BITS) == 0) {
		*buffer++ = THREE_BYTE_PREFIX | (scalar >> 12);
		bytes_written = 3;
	}
	else {
		*buffer++ = FOUR_BYTE_PREFIX | (scalar >> 18);
		bytes_written = 4;
	}
	// Intentionally falling through each case
	switch (bytes_written) {
		case 4: *buffer++ = CONTINUATION_BYTE | ((scalar >> 12) & CONTINUATION_MASK);
		case 3: *buffer++ = CONTINUATION_BYTE | ((scalar >>  6) & CONTINUATION_MASK);
		case 2: *buffer++ = CONTINUATION_BYTE |  (scalar        & CONTINUATION_MASK);
		default: return bytes_written;
	}
}

void printbinchar(char character) {
    char output[9];
    itoa(character, output, 2);
    printf("0b%s\n", output);
}

int main(void) {
	
}
