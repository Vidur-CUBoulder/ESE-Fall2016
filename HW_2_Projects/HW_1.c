#include "HW_1.h"

char reverse(char *str, uint8_t length)
{
	char *string_start = str; 

	/* Adding checks for corner cases */
	if ( length <= 0) {
		return -1;
	}

	if ( str == NULL ) {
		return -1;
	}

	int8_t rev_iter = 0;
	for(rev_iter=(length); rev_iter>=0; rev_iter--) {
		/* Bypassing escape sequences */
		if ( *(string_start+rev_iter) == '\n' || \
		*(string_start+rev_iter) == '\t') {
			continue;
		}
		printf("%c", *(string_start+rev_iter));
	}

	printf("\n");

	return 0;
}

int main()
{

	char *string_1 = "This is a string";
	uint8_t length_1 = 15;
	char *string_2 = "some NUMmbers12345";
	uint8_t length_2 = 17;
	char *string_3 = "Does it reverse \n\0\t correctly?";
	uint8_t length_3 = 28;

	int8_t ret = 0;
	printf("Reversed Strings:\n");
	ret = reverse(string_1,length_1);
	if(ret == -1) {
		printf("failed!\n");
	}
	printf("\n"); 

	ret = reverse(string_2,length_2);
	if(ret == -1) {
		printf("failed!\n");
	}
	printf("\n"); 

	ret = reverse(string_3,length_3);
	if(ret == -1) {
		printf("failed!\n");
	}

	int8_t cntr = 0;
	printf("Original Strings:\n");
	while(length_1 >= cntr) {
		printf("%c", *(string_1+cntr));
		cntr++;
	}
	printf("\n\n");

	cntr = 0;
	while(length_2 >= cntr) {
		printf("%c", *(string_2+cntr));
		cntr++;
	}
	printf("\n\n");

	cntr = 0;
	while(length_3 >= cntr) {
		printf("%c", *(string_3+cntr));
		cntr++;
	}

	printf("\n");

	return 0;
}
