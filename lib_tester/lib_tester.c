#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_atoi() {
    // Test cases for atoi
    char numStr[] = "12345";
    int result = ft_atoi(numStr);
    printf("atoi Test: %s -> %d\n", numStr, result);
}

void test_calloc() {
    // Test cases for calloc
    int *arr = (int *)ft_calloc(5, sizeof(int));
    
    if (arr != NULL) {
        printf("calloc Test: Allocated memory successfully\n");
        // Additional tests or operations on the allocated memory can be added here
        free(arr); // Free the allocated memory
    } else {
        printf("calloc Test: Memory allocation failed\n");
    }
}

void test_memcpy() {
    // Test cases for memcpy
    char source[] = "Hello";
    char destination[10];
    
    ft_memcpy(destination, source, ft_strlen(source) + 1); // +1 to copy the null terminator
    printf("memcpy Test: %s -> %s\n", source, destination);
}

void test_strchr() {
    // Test cases for strchr
    const char str[] = "Hello, World!";
    char target = 'W';
    char *result = ft_strchr(str, target);

    if (result != NULL) {
        printf("strchr Test: '%c' found at index %ld\n", target, result - str);
    } else {
        printf("strchr Test: '%c' not found\n", target);
    }
}

void test_strnstr() {
    // Test cases for strnstr
    const char haystack[] = "Hello, World!";
    const char needle[] = "World";
    char *result = ft_strnstr(haystack, needle, ft_strlen(haystack));

    if (result != NULL) {
        printf("strnstr Test: '%s' found at index %ld\n", needle, result - haystack);
    } else {
        printf("strnstr Test: '%s' not found\n", needle);
    }
}

int main() {
    // Run test functions
    test_atoi();
    test_calloc();
    test_memcpy();
    test_strchr();
    test_strnstr();

    return 0;
}
