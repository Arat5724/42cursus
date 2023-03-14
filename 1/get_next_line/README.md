# get_next_line

## Mandatory part

```
char *get_next_line(int fd);
```
다음과 같은 `Prototype`이 주어집니다.
인자로 주어지는 fd에서 `\n` 혹은 파일의 끝까지 반환합니다.

```c
int main(void)
{
    char  *str;
    int   fd;
    
    fd = open("test", O_RDONLY);
    while (1)
    {
    	str = get_next_line(fd);
        if (str)
        {
          printf("%s", str);
          free(str);
        }
        else
        	break;
    }
}
```
위와 같이 사용합니다.

## Bonus part

다중 `fd`에도 대응할 수 있는 `get_next_line`을 만듭니다.

## Summary

시간 복잡도가 $O(n^2)$이지만, `buffer`를 스택 영역의 메모리 공간으로 사용해, 시간 복잡도가 $O(n^2)$인 `get_next_line` 중에서는 가장 빠릅니다.
더불어, 함수 제한이 10개이지만 단 2개로 구현했습니다.
