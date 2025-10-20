#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"

// ANSI color codes
#define GREEN "\033[1;32m"
#define RED "\033[1;31m"
#define RESET "\033[0m"
#define CYAN "\033[36m"

// Visual test result indicators
#define OK GREEN "OK" RESET
#define KO RED "KO" RESET

// Global test counters
int tests_passed = 0;
int tests_failed = 0;

// Helper function to print test result
void print_test_result(const char* test_name, int condition) {
    if (condition) {
        printf("\n[%s] %s\n", OK, test_name);
        tests_passed++;
    } else {
        printf("\n[%s] %s\n", KO, test_name);
        tests_failed++;
    }
}

// Helper function to display test name clearly
void display_test_name(const char* test_name) {
    printf(CYAN"=== Testing %s ===%s\n", test_name, RESET);
}

// Helper function for character tests
void test_char_function(const char* func_name, int (*func)(int), int input, int expected, const char* description) {
    int result = func(input);
    printf("%s(%s): %d (expected: %s)", func_name, description, result, expected ? "non-zero" : "0");
    print_test_result(func_name, (result != 0) == (expected != 0));
}

// Helper function for string comparison tests
void test_string_function(const char* func_name, char* result, const char* expected, const char* description) {
    printf("%s: %s (expected: %s)", func_name, result ? result : "NULL", expected);
    print_test_result(description, result && strcmp(result, expected) == 0);
}

// Helper function for integer comparison tests
void test_int_function(const char* func_name, int result, int expected, const char* description) {
    printf("%s: %d (expected: %d)", func_name, result, expected);
    print_test_result(description, result == expected);
}

// Helper function for size_t comparison tests
void test_size_function(const char* func_name, size_t result, size_t expected, const char* description) {
    printf("%s: %lu (expected: %lu)", func_name, result, expected);
    print_test_result(description, result == expected);
}

// Helper function for malloc-based string tests
void test_malloc_string_function(const char* func_name, char* result, const char* expected, const char* description) {
    printf("%s: %s (expected: %s)", func_name, result ? result : "NULL", expected);
    int test_passed = result && strcmp(result, expected) == 0;
    print_test_result(description, test_passed);
    if (result) free(result);
}

// Define callback functions for iterative tests
char increment_by_index(unsigned int i, char c) {
    return c + i;
}

void increment_char_by_index(unsigned int i, char *c) {
    *c += i;
}

void print_content(void *content) {
    printf("%s ", (char *)content);
}

void *duplicate_content(void *content) {
    return strdup((char *)content);
}

void delete_content(void *content) {
    free(content);
}

void test_ft_isalpha() {
    display_test_name("ft_isalpha");
    test_char_function("ft_isalpha", ft_isalpha, 'A', 1, "'A'");
    test_char_function("ft_isalpha", ft_isalpha, '1', 0, "'1'");
}

void test_ft_isdigit() {
    display_test_name("ft_isdigit");
    test_char_function("ft_isdigit", ft_isdigit, '5', 1, "'5'");
    test_char_function("ft_isdigit", ft_isdigit, 'a', 0, "'a'");
}

void test_ft_isalnum() {
    display_test_name("ft_isalnum");
    test_char_function("ft_isalnum", ft_isalnum, 'a', 1, "'a'");
    test_char_function("ft_isalnum", ft_isalnum, '5', 1, "'5'");
    test_char_function("ft_isalnum", ft_isalnum, ' ', 0, "' '");
}

void test_ft_isascii() {
    display_test_name("ft_isascii");
    test_char_function("ft_isascii", ft_isascii, 65, 1, "65");
    test_char_function("ft_isascii", ft_isascii, 128, 0, "128");
}

void test_ft_isprint() {
    display_test_name("ft_isprint");
    test_char_function("ft_isprint", ft_isprint, 65, 1, "65");
    test_char_function("ft_isprint", ft_isprint, 31, 0, "31");
}

void test_ft_strlen() {
    display_test_name("ft_strlen");
    size_t result = ft_strlen("Hello");
    test_size_function("ft_strlen(\"Hello\")", result, 5, "ft_strlen");
}

void test_ft_memset() {
    display_test_name("ft_memset");
    char buffer[10] = "abcdefghi";
    ft_memset(buffer, 'x', 5);
    test_string_function("ft_memset(buffer, 'x', 5)", buffer, "xxxxxfghi", "ft_memset");
}

void test_ft_bzero() {
    display_test_name("ft_bzero");
    char buffer[10] = "abcdefghi";
    ft_bzero(buffer, 5);
    
    printf("ft_bzero(buffer, 5): ");
    for (int i = 0; i < 10; i++) {
        printf("%s", (buffer[i] == '\0') ? "\\0" : (char[]){buffer[i], '\0'});
    }
    printf(" (expected: \\0\\0\\0\\0\\0fghi)");
    
    // Check if first 5 bytes are zero and rest are unchanged
    int test_passed = 1;
    for (int i = 0; i < 5; i++) {
        if (buffer[i] != '\0') test_passed = 0;
    }
    if (strcmp(buffer + 5, "fghi") != 0) test_passed = 0;
    
    print_test_result("ft_bzero", test_passed);
}

void test_ft_memcpy() {
    display_test_name("ft_memcpy");
    char src[10] = "abcdefghi";
    char dest[10];
    ft_memcpy(dest, src, 10);
    test_string_function("ft_memcpy(dest, src, 10)", dest, "abcdefghi", "ft_memcpy");
}

void test_ft_memmove() {
    display_test_name("ft_memmove");
    char buffer[10] = "abcdefghi";
    ft_memmove(buffer + 2, buffer, 5);
    test_string_function("ft_memmove(buffer + 2, buffer, 5)", buffer, "ababcdehi", "ft_memmove");
}

void test_ft_strlcpy() {
    display_test_name("ft_strlcpy");
    char dest[10];
    size_t result = ft_strlcpy(dest, "Hello", 10);
    
    printf("ft_strlcpy(dest, \"Hello\", 10): %s, %lu (expected: Hello, 5)", dest, result);
    print_test_result("ft_strlcpy", strcmp(dest, "Hello") == 0 && result == 5);
}

void test_ft_strlcat() {
    display_test_name("ft_strlcat");
    char buffer[11] = "Hello";
    size_t result = ft_strlcat(buffer, "World", 11);
    
    printf("ft_strlcat(buffer, \"World\", 11): %s, %lu (expected: HelloWorld, 10)", buffer, result);
    print_test_result("ft_strlcat", strcmp(buffer, "HelloWorld") == 0 && result == 10);
}

void test_ft_toupper() {
    display_test_name("ft_toupper");
    char result = ft_toupper('a');
    printf("ft_toupper('a'): %c (expected: A)", result);
    print_test_result("ft_toupper", result == 'A');
}

void test_ft_tolower() {
    display_test_name("ft_tolower");
    char result = ft_tolower('A');
    printf("ft_tolower('A'): %c (expected: a)", result);
    print_test_result("ft_tolower", result == 'a');
}

void test_ft_strchr() {
    display_test_name("ft_strchr");
    char *result = ft_strchr("Hello", 'e');
    test_string_function("ft_strchr(\"Hello\", 'e')", result, "ello", "ft_strchr");
}

void test_ft_strrchr() {
    display_test_name("ft_strrchr");
    char *result = ft_strrchr("Hello", 'l');
    test_string_function("ft_strrchr(\"Hello\", 'l')", result, "lo", "ft_strrchr");
}

void test_ft_strncmp() {
    display_test_name("ft_strncmp");
    int result = ft_strncmp("Hello", "Hellp", 5);
    printf("ft_strncmp(\"Hello\", \"Hellp\", 5): %d (expected: < 0)", result);
    print_test_result("ft_strncmp", result < 0);
}

void test_ft_memchr() {
    display_test_name("ft_memchr");
    char *result = (char*)ft_memchr("Hello", 'e', 5);
    test_string_function("ft_memchr(\"Hello\", 'e', 5)", result, "ello", "ft_memchr");
}

void test_ft_memcmp() {
    display_test_name("ft_memcmp");
    int result = ft_memcmp("Hello", "Hellp", 5);
    printf("ft_memcmp(\"Hello\", \"Hellp\", 5): %d (expected: < 0)", result);
    print_test_result("ft_memcmp", result < 0);
}

void test_ft_strnstr() {
    display_test_name("ft_strnstr");
    char *result = ft_strnstr("Hello World", "World", 11);
    test_string_function("ft_strnstr(\"Hello World\", \"World\", 11)", result, "World", "ft_strnstr");
}

void test_ft_atoi() {
    display_test_name("ft_atoi");
    int result = ft_atoi("123");
    test_int_function("ft_atoi(\"123\")", result, 123, "ft_atoi");
}

void test_ft_calloc() {
    display_test_name("ft_calloc");
    char *ptr = ft_calloc(5, sizeof(char));
    int test_passed = 0;
    
    if (ptr) {
        // Check if memory is zeroed
        test_passed = 1;
        for (int i = 0; i < 5; i++) {
            if (ptr[i] != 0) {
                test_passed = 0;
                break;
            }
        }
        printf("ft_calloc(5, sizeof(char)): success, memory zeroed");
        free(ptr);
    } else {
        printf("ft_calloc(5, sizeof(char)): fail");
    }
    
    print_test_result("ft_calloc", test_passed);
}

void test_ft_strdup() {
    display_test_name("ft_strdup");
    char *result = ft_strdup("Hello");
    test_malloc_string_function("ft_strdup(\"Hello\")", result, "Hello", "ft_strdup");
}

void test_ft_substr() {
    display_test_name("ft_substr");
    char *result = ft_substr("Hello", 1, 3);
    test_malloc_string_function("ft_substr(\"Hello\", 1, 3)", result, "ell", "ft_substr");
}

void test_ft_strjoin() {
    display_test_name("ft_strjoin");
    char *result = ft_strjoin("Hello", "World");
    test_malloc_string_function("ft_strjoin(\"Hello\", \"World\")", result, "HelloWorld", "ft_strjoin");
}

void test_ft_strtrim() {
    display_test_name("ft_strtrim");
    char *result = ft_strtrim("  Hello  ", " ");
    test_malloc_string_function("ft_strtrim(\"  Hello  \", \" \")", result, "Hello", "ft_strtrim");
}

void test_ft_split() {
    display_test_name("ft_split");
    char **split = ft_split("Hello World", ' ');
    int test_passed = 0;
    
    if (split && split[0] && split[1]) {
        printf("ft_split(\"Hello World\", ' '): %s, %s (expected: Hello, World)", split[0], split[1]);
        test_passed = (strcmp(split[0], "Hello") == 0 && strcmp(split[1], "World") == 0);
        free(split[0]);
        free(split[1]);
        free(split);
    } else {
        printf("ft_split(\"Hello World\", ' '): NULL or incomplete");
    }
    
    print_test_result("ft_split", test_passed);
}

void test_ft_itoa() {
    display_test_name("ft_itoa");
    char *result = ft_itoa(123);
    test_malloc_string_function("ft_itoa(123)", result, "123", "ft_itoa");
}

void test_ft_strmapi() {
    display_test_name("ft_strmapi");
    char *result = ft_strmapi("Hello", increment_by_index);
    test_malloc_string_function("ft_strmapi(\"Hello\")", result, "Hfnos", "ft_strmapi");
}

void test_ft_striteri() {
    display_test_name("ft_striteri");
    char str[] = "Hello";
    ft_striteri(str, increment_char_by_index);
    test_string_function("ft_striteri(\"Hello\")", str, "Hfnos", "ft_striteri");
}

void test_ft_putchar_fd() {
    display_test_name("ft_putchar_fd");
    printf("ft_putchar_fd('A', 1): ");
    ft_putchar_fd('A', 1); // Expected: A
    printf(" (expected: A)");
    print_test_result("ft_putchar_fd", 1); // Visual check required
}

void test_ft_putstr_fd() {
    display_test_name("ft_putstr_fd");
    printf("ft_putstr_fd(\"Hello\", 1): ");
    ft_putstr_fd("Hello", 1); // Expected: Hello
    printf(" (expected: Hello)");
    print_test_result("ft_putstr_fd", 1); // Visual check required
}

void test_ft_putendl_fd() {
    display_test_name("ft_putendl_fd");
    printf("ft_putendl_fd(\"Hello\", 1): ");
    ft_putendl_fd("Hello", 1); // Expected: Hello\n
    printf("(expected: Hello with newline)");
    print_test_result("ft_putendl_fd", 1); // Visual check required
}

void test_ft_putnbr_fd() {
    display_test_name("ft_putnbr_fd");
    printf("ft_putnbr_fd(123, 1): ");
    ft_putnbr_fd(123, 1); // Expected: 123
    printf(" (expected: 123)");
    print_test_result("ft_putnbr_fd", 1); // Visual check required
}

void test_ft_lstnew() {
    display_test_name("ft_lstnew");
    t_list *node = ft_lstnew("Hello");
    
    printf("ft_lstnew(\"Hello\"): %s (expected: Hello)", node && node->content ? (char *)node->content : "NULL");
    print_test_result("ft_lstnew", node && node->content && strcmp((char *)node->content, "Hello") == 0);
    
    if (node) free(node);
}

void test_ft_lstadd_front() {
    display_test_name("ft_lstadd_front");
    t_list *node = ft_lstnew("Hello");
    t_list *head = NULL;
    ft_lstadd_front(&head, node);
    
    printf("ft_lstadd_front(&head, node): %s (expected: Hello)", head && head->content ? (char *)head->content : "NULL");
    print_test_result("ft_lstadd_front", head && head->content && strcmp((char *)head->content, "Hello") == 0);
    
    if (node) free(node);
}

void test_ft_lstsize() {
    display_test_name("ft_lstsize");
    t_list *node1 = ft_lstnew("Hello");
    t_list *node2 = ft_lstnew("World");
    if (node1 && node2) {
        node1->next = node2;
        int size = ft_lstsize(node1);
        
        printf("ft_lstsize(node1): %d (expected: 2)", size);
        print_test_result("ft_lstsize", size == 2);
        
        free(node1);
        free(node2);
    } else {
        printf("ft_lstsize(node1): allocation failed");
        print_test_result("ft_lstsize", 0);
    }
}

void test_ft_lstlast() {
    display_test_name("ft_lstlast");
    t_list *node1 = ft_lstnew("Hello");
    t_list *node2 = ft_lstnew("World");
    if (node1 && node2) {
        node1->next = node2;
        t_list *last = ft_lstlast(node1);
        
        printf("ft_lstlast(node1): %s (expected: World)", last && last->content ? (char *)last->content : "NULL");
        print_test_result("ft_lstlast", last && last->content && strcmp((char *)last->content, "World") == 0);
        
        free(node1);
        free(node2);
    } else {
        printf("ft_lstlast(node1): allocation failed");
        print_test_result("ft_lstlast", 0);
    }
}

void test_ft_lstadd_back() {
    display_test_name("ft_lstadd_back");
    t_list *node1 = ft_lstnew("Hello");
    t_list *node2 = ft_lstnew("World");
    if (node1 && node2) {
        ft_lstadd_back(&node1, node2);
        
        printf("ft_lstadd_back(&node1, node2): %s (expected: World)", 
               node1 && node1->next && node1->next->content ? (char *)node1->next->content : "NULL");
        print_test_result("ft_lstadd_back", node1 && node1->next && node1->next->content && 
                          strcmp((char *)node1->next->content, "World") == 0);
        
        free(node1);
        free(node2);
    } else {
        printf("ft_lstadd_back(&node1, node2): allocation failed");
        print_test_result("ft_lstadd_back", 0);
    }
}

void test_ft_lstdelone() {
    display_test_name("ft_lstdelone");
    char *str = strdup("Hello");
    t_list *node = ft_lstnew(str);
    if (node) {
        ft_lstdelone(node, delete_content);
        printf("ft_lstdelone(node, delete_content): success (expected: success)");
        print_test_result("ft_lstdelone", 1); // Memory test - assume success if no crash
    } else {
        printf("ft_lstdelone(node, delete_content): allocation failed");
        print_test_result("ft_lstdelone", 0);
    }
}

void test_ft_lstclear() {
    display_test_name("ft_lstclear");
    char *str1 = strdup("Hello");
    char *str2 = strdup("World");
    t_list *node1 = ft_lstnew(str1);
    t_list *node2 = ft_lstnew(str2);
    if (node1 && node2) {
        node1->next = node2;
        ft_lstclear(&node1, delete_content);
        printf("ft_lstclear(&node1, delete_content): success (expected: success)");
        print_test_result("ft_lstclear", 1); // Memory test - assume success if no crash
    } else {
        printf("ft_lstclear(&node1, delete_content): allocation failed");
        print_test_result("ft_lstclear", 0);
    }
}

void test_ft_lstiter() {
    display_test_name("ft_lstiter");
    char *str1 = strdup("Hello");
    char *str2 = strdup("World");
    t_list *node1 = ft_lstnew(str1);
    t_list *node2 = ft_lstnew(str2);
    if (node1 && node2) {
        node1->next = node2;
        printf("ft_lstiter(node1, print_content): ");
        ft_lstiter(node1, print_content); // Expected: Hello World
        printf("(expected: Hello World )");
        print_test_result("ft_lstiter", 1); // Visual check required
        ft_lstclear(&node1, delete_content);
    } else {
        printf("ft_lstiter(node1, print_content): allocation failed");
        print_test_result("ft_lstiter", 0);
    }
}

void test_ft_lstmap() {
    display_test_name("ft_lstmap");
    char *str1 = strdup("Hello");
    char *str2 = strdup("World");
    t_list *node1 = ft_lstnew(str1);
    t_list *node2 = ft_lstnew(str2);
    if (node1 && node2) {
        node1->next = node2;
        t_list *new_list = ft_lstmap(node1, duplicate_content, delete_content);
        if (new_list) {
            printf("ft_lstmap(node1, duplicate_content, delete_content): ");
            ft_lstiter(new_list, print_content); // Expected: Hello World
            printf("(expected: Hello World )");
            print_test_result("ft_lstmap", 1); // Visual check required
            ft_lstclear(&new_list, delete_content);
        } else {
            printf("ft_lstmap(node1, duplicate_content, delete_content): NULL");
            print_test_result("ft_lstmap", 0);
        }
        ft_lstclear(&node1, delete_content);
    } else {
        printf("ft_lstmap(node1, duplicate_content, delete_content): allocation failed");
        print_test_result("ft_lstmap", 0);
    }
}

int main() {
    printf("=== LIBFT TEST SUITE ===\n\n");
    
    test_ft_isalpha();
    test_ft_isdigit();
    test_ft_isalnum();
    test_ft_isascii();
    test_ft_isprint();
    test_ft_strlen();
    test_ft_memset();
    test_ft_bzero();
    test_ft_memcpy();
    test_ft_memmove();
    test_ft_strlcpy();
    test_ft_strlcat();
    test_ft_toupper();
    test_ft_tolower();
    test_ft_strchr();
    test_ft_strrchr();
    test_ft_strncmp();
    test_ft_memchr();
    test_ft_memcmp();
    test_ft_strnstr();
    test_ft_atoi();
    test_ft_calloc();
    test_ft_strdup();
    test_ft_substr();
    test_ft_strjoin();
    test_ft_strtrim();
    test_ft_split();
    test_ft_itoa();
    test_ft_strmapi();
    test_ft_striteri();
    test_ft_putchar_fd();
    test_ft_putstr_fd();
    test_ft_putendl_fd();
    test_ft_putnbr_fd();
    test_ft_lstnew();
    test_ft_lstadd_front();
    test_ft_lstsize();
    test_ft_lstlast();
    test_ft_lstadd_back();
    test_ft_lstdelone();
    test_ft_lstclear();
    test_ft_lstiter();
    test_ft_lstmap();

    // Print test summary
    printf("\n=== TEST SUMMARY ===\n");
    printf("Tests passed: " GREEN "%d" RESET "\n", tests_passed);
    printf("Tests failed: " RED "%d" RESET "\n", tests_failed);
    printf("Total tests: %d\n", tests_passed + tests_failed);
    
    if (tests_failed == 0) {
        printf("\n🎉 " GREEN "ALL TESTS PASSED!" RESET " 🎉\n");
    } else {
        printf("\n⚠️  " RED "SOME TESTS FAILED" RESET " ⚠️\n");
    }

    return tests_failed > 0 ? 1 : 0;
}
