#include "check_bytes8.h"

static void *check_bytes8(const u8 *start, u8 value, unsigned int bytes)
{
	//@ ghost u8 *ostart = start;
	//@ ghost unsigned int obytes = bytes;

	/*@ loop invariant 0 <= bytes <= obytes;
	    loop invariant ostart <= start <= ostart + obytes;
	    loop invariant start - ostart == obytes - bytes;
	    loop invariant \forall u8 *i; ostart <= i < start ==> *i == value;
	    loop invariant check_bytes8(ostart, value, obytes) == check_bytes8(start, value, bytes);
	    loop variant bytes;
	 */
	while (bytes) {
		if (*start != value)
			return (void *)start;
		start++;
		bytes--;
	}
	//@ assert bytes == 0;
	//@ assert check_bytes8(ostart, value, obytes) == \null;
	return NULL;
}


#ifdef FUZZ_MAIN

int LLVMFuzzerTestOneInput(const uint8_t *data,
                           size_t size)
{
	if (size > 1) {
		check_bytes8((const u8 *)data, data[size - 1], size - 1);
	}
	return 0;
}
#endif


#ifdef DUMMY_MAIN
#include <string.h>

#define BUFFER_SIZE 10

int main(int argc, char *argv[])
{
	const u8 value = 3;
	u8 start[BUFFER_SIZE];

	memset(start, value, BUFFER_SIZE);
	check_bytes8(start, value, BUFFER_SIZE);

	return 0;
}
#endif
