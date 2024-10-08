#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"

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
    printf("ft_isalpha('A'): %d\n", ft_isalpha('A')); // Expected: non-zero
    printf("ft_isalpha('1'): %d\n", ft_isalpha('1')); // Expected: 0
}

void test_ft_isdigit() {
    printf("ft_isdigit('5'): %d\n", ft_isdigit('5')); // Expected: non-zero
    printf("ft_isdigit('a'): %d\n", ft_isdigit('a')); // Expected: 0
}

void test_ft_isalnum() {
    printf("ft_isalnum('a'): %d\n", ft_isalnum('a')); // Expected: non-zero
    printf("ft_isalnum('5'): %d\n", ft_isalnum('5')); // Expected: non-zero
    printf("ft_isalnum(' '): %d\n", ft_isalnum(' ')); // Expected: 0
}

void test_ft_isascii() {
    printf("ft_isascii(65): %d\n", ft_isascii(65));   // Expected: non-zero
    printf("ft_isascii(128): %d\n", ft_isascii(128)); // Expected: 0
}

void test_ft_isprint() {
    printf("ft_isprint(65): %d\n", ft_isprint(65));   // Expected: non-zero
    printf("ft_isprint(31): %d\n", ft_isprint(31));   // Expected: 0
}

void test_ft_strlen() {
    printf("ft_strlen(\"Hello\"): %lu\n", ft_strlen("Hello")); // Expected: 5
}

void test_ft_memset() {
    char buffer[10] = "abcdefghi";
    ft_memset(buffer, 'x', 5);
    printf("ft_memset(buffer, 'x', 5): %s\n", buffer); // Expected: xxxxxfghi
}

void test_ft_bzero() {
    char buffer[10] = "abcdefghi";
    ft_bzero(buffer, 5);
    printf("ft_bzero(buffer, 5): "); 
    for (int i = 0; i < 10; i++) {
        if (buffer[i] == '\0') {
            printf("\\0");
        } else {
            printf("%c", buffer[i]);
        }
    }
    printf("\n"); // Expected: \0\0\0\0\0fghi
}

void test_ft_memcpy() {
    char src[10] = "abcdefghi";
    char dest[10];
    ft_memcpy(dest, src, 10);
    printf("ft_memcpy(dest, src, 10): %s\n", dest); // Expected: abcdefghi
}

void test_ft_memmove() {
    char buffer[10] = "abcdefghi";
    ft_memmove(buffer + 2, buffer, 5);
    printf("ft_memmove(buffer + 2, buffer, 5): %s\n", buffer); // Expected: ababcdeghi
}

void test_ft_strlcpy() {
    char dest[10];
    size_t result = ft_strlcpy(dest, "Hello", 10);
    printf("ft_strlcpy(dest, \"Hello\", 10): %s, %lu\n", dest, result); // Expected: Hello, 5
}

void test_ft_strlcat() {
    char buffer[10] = "Hello";
    size_t result = ft_strlcat(buffer, "World", 10);
    printf("ft_strlcat(buffer, \"World\", 10): %s, %lu\n", buffer, result); // Expected: HelloWorld, 10
}

void test_ft_toupper() {
    printf("ft_toupper('a'): %c\n", ft_toupper('a')); // Expected: A
}

void test_ft_tolower() {
    printf("ft_tolower('A'): %c\n", ft_tolower('A')); // Expected: a
}

void test_ft_strchr() {
    printf("ft_strchr(\"Hello\", 'e'): %s\n", ft_strchr("Hello", 'e')); // Expected: ello
}

void test_ft_strrchr() {
    printf("ft_strrchr(\"Hello\", 'l'): %s\n", ft_strrchr("Hello", 'l')); // Expected: llo
}

void test_ft_strncmp() {
    printf("ft_strncmp(\"Hello\", \"Hellp\", 5): %d\n", ft_strncmp("Hello", "Hellp", 5)); // Expected: < 0
}

void test_ft_memchr() {
    printf("ft_memchr(\"Hello\", 'e', 5): %s\n", (char*)ft_memchr("Hello", 'e', 5)); // Expected: ello
}

void test_ft_memcmp() {
    printf("ft_memcmp(\"Hello\", \"Hellp\", 5): %d\n", ft_memcmp("Hello", "Hellp", 5)); // Expected: < 0
}

void test_ft_strnstr() {
    printf("ft_strnstr(\"Hello World\", \"World\", 11): %s\n", ft_strnstr("Hello World", "World", 11)); // Expected: World
}

void test_ft_atoi() {
    printf("ft_atoi(\"123\"): %d\n", ft_atoi("123")); // Expected: 123
}

void test_ft_calloc() {
    char *ptr = ft_calloc(5, sizeof(char));
    if (ptr) {
        printf("ft_calloc(5, sizeof(char)): success\n"); // Expected: success
        free(ptr);
    } else {
        printf("ft_calloc(5, sizeof(char)): fail\n");
    }
}

void test_ft_strdup() {
    char *dup = ft_strdup("Hello");
    printf("ft_strdup(\"Hello\"): %s\n", dup); // Expected: Hello
    free(dup);
}

void test_ft_substr() {
    char *sub = ft_substr("Hello", 1, 3);
    printf("ft_substr(\"Hello\", 1, 3): %s\n", sub); // Expected: ell
    free(sub);
}

void test_ft_strjoin() {
    char *join = ft_strjoin("Hello", "World");
    printf("ft_strjoin(\"Hello\", \"World\"): %s\n", join); // Expected: HelloWorld
    free(join);
}

void test_ft_strtrim() {
    char *trim = ft_strtrim("  Hello  ", " ");
    printf("ft_strtrim(\"  Hello  \", \" \"): %s\n", trim); // Expected: Hello
    free(trim);
}

void test_ft_split() {
    char **split = ft_split("Hello World", ' ');
    printf("ft_split(\"Hello World\", ' '): %s, %s\n", split[0], split[1]); // Expected: Hello, World
    free(split[0]);
    free(split[1]);
    free(split);
}

void test_ft_itoa() {
    char *itoa = ft_itoa(123);
    printf("ft_itoa(123): %s\n", itoa); // Expected: 123
    free(itoa);
}

void test_ft_strmapi() {
    char *map = ft_strmapi("Hello", increment_by_index);
    printf("ft_strmapi(\"Hello\"): %s\n", map); // Expected: Hfnos
    free(map);
}

void test_ft_striteri() {
    char str[] = "Hello";
    ft_striteri(str, increment_char_by_index);
    printf("ft_striteri(\"Hello\"): %s\n", str); // Expected: Hfnos
}

void test_ft_putchar_fd() {
    ft_putchar_fd('A', 1); // Expected: A
}

void test_ft_putstr_fd() {
    ft_putstr_fd("Hello", 1); // Expected: Hello
}

void test_ft_putendl_fd() {
    ft_putendl_fd("Hello", 1); // Expected: Hello\n
}

void test_ft_putnbr_fd() {
    ft_putnbr_fd(123, 1); // Expected: 123
}

void test_ft_lstnew() {
    t_list *node = ft_lstnew("Hello");
    printf("ft_lstnew(\"Hello\"): %s\n", (char *)node->content); // Expected: Hello
    free(node);
}

void test_ft_lstadd_front() {
    t_list *node = ft_lstnew("Hello");
    t_list *head = NULL;
    ft_lstadd_front(&head, node);
    printf("ft_lstadd_front(&head, node): %s\n", (char *)head->content); // Expected: Hello
    free(node);
}

void test_ft_lstsize() {
    t_list *node1 = ft_lstnew("Hello");
    t_list *node2 = ft_lstnew("World");
    node1->next = node2;
    printf("ft_lstsize(node1): %d\n", ft_lstsize(node1)); // Expected: 2
    free(node1);
    free(node2);
}

void test_ft_lstlast() {
    t_list *node1 = ft_lstnew("Hello");
    t_list *node2 = ft_lstnew("World");
    node1->next = node2;
    printf("ft_lstlast(node1): %s\n", (char *)ft_lstlast(node1)->content); // Expected: World
    free(node1);
    free(node2);
}

void test_ft_lstadd_back() {
    t_list *node1 = ft_lstnew("Hello");
    t_list *node2 = ft_lstnew("World");
    ft_lstadd_back(&node1, node2);
    printf("ft_lstadd_back(&node1, node2): %s\n", (char *)node1->next->content); // Expected: World
    free(node1);
    free(node2);
}

void test_ft_lstdelone() {
    char *str = strdup("Hello");
    t_list *node = ft_lstnew(str);
    ft_lstdelone(node, delete_content);
    printf("ft_lstdelone(node, delete_content): success\n"); // Expected: success (no memory leaks)
}

void test_ft_lstclear() {
    char *str1 = strdup("Hello");
    char *str2 = strdup("World");
    t_list *node1 = ft_lstnew(str1);
    t_list *node2 = ft_lstnew(str2);
    node1->next = node2;
    ft_lstclear(&node1, delete_content);
    printf("ft_lstclear(&node1, delete_content): success\n"); // Expected: success (no memory leaks)
}

void test_ft_lstiter() {
    char *str1 = strdup("Hello");
    char *str2 = strdup("World");
    t_list *node1 = ft_lstnew(str1);
    t_list *node2 = ft_lstnew(str2);
    node1->next = node2;
    ft_lstiter(node1, print_content); // Expected: Hello World
    printf("\n");
    ft_lstclear(&node1, delete_content);
}

void test_ft_lstmap() {
    char *str1 = strdup("Hello");
    char *str2 = strdup("World");
    t_list *node1 = ft_lstnew(str1);
    t_list *node2 = ft_lstnew(str2);
    node1->next = node2;
    t_list *new_list = ft_lstmap(node1, duplicate_content, delete_content);
    ft_lstiter(new_list, print_content); // Expected: Hello World
    printf("\n");
    ft_lstclear(&new_list, delete_content);
    ft_lstclear(&node1, delete_content);
}

int main() {
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

    return 0;
}
