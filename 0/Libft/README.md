# Libft

C 라이브러리를 만드는 과제입니다.
`make`를 하면 아래의 함수들이 포함된 libft.a 라이브러리가 만들어집니다.

## Mandatory part

|Part 1|Libc functions|
|--------------|--------------|
|isalpha|toupper|
|isdigit|tolower|
|isalnum|strchr|
|isascii|strrchr|
|isprint|strncmp|
|strlen|memchr|
|memset|memcmp|
|bzero|strnstr|
|memcpy|atoi|
|memmove|calloc|
|strlcpy|strdup|
|strlcat|

|Part 2|Additional functions|
|--------------|--------------|
|ft_substr|ft_striteri|
|ft_strjoin|ft_putchar_fd|
|ft_strtrim|ft_putstr_fd|
|ft_split|ft_putendl_fd|
|ft_itoa|ft_putnbr_fd|
|ft_strmapi|

## Bonus part


```c
typedef struct s_list
{
void *content;
struct s_list *next;
} t_list;
```
이러한 Linked List 구조체가 주어집니다.

|Part 3|Bonus Functions|
|--------------|--------------|
|ft_lstnew|ft_lstdelone|
|ft_lstadd_front|ft_lstclear|
|ft_lstsize|ft_lstiter|
|ft_lstlast|ft_lstmap|
|ft_lstadd_back|
