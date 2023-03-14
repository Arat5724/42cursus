# push_swap

주어진 자료구조를 이용해 인자로 주어지는 숫자들을 정렬하는 명령어를 출력하는 프로그램을 만듭니다.

1. 2개의 스택 a, b가 주어집니다.
2. 인자로 주어진 숫자들이 스택 a에 들어가있습니다.
스택 b는 비어있습니다.
3. 아래의 명령어들을 이용해 정렬합니다.

|Operations|	Description|
|----|----------------------------------|
|sa|swap first 2 elements at the top of stack a|
|sb|swap first 2 elements at the top of stack b|
|ss|sa and sb at the same time|
|pa|Take the first element at the top of b and put it at the top of a|
|pb| Take the first element at the top of a and put it at the top of b|
|ra|Shift up all elements of stack a by 1|
|rb|Shift up all elements of stack b by 1|
|rr|ra and rb at the same time|
|rra|Shift down all elements of stack a by 1|
|rrb|Shift down all elements of stack b by 1|
|rrr|rra and rrb at the same time|

### Example

```
> ./push_swap 2 1 4 3
pb
pb
ra
sb
pa
pa
```

## summary

![image](https://user-images.githubusercontent.com/79699284/224953433-a53a3173-f8a7-4148-8b6e-6ca3e8cf894e.png)
![3694](https://user-images.githubusercontent.com/79699284/224953979-3a0e397d-239c-4484-a49a-c943606f5631.gif)


인자로 숫자가 500개 주어졌을 때 명령어가 5500개 이하로 출력되야 만점인 과제이며

제가 작성한 프로그램은 평균 3720개 정도가 출력됩니다. 

아직 저보다 명령어가 적게 출력되게 만든 사람은 못 봤습니다.

블로그에 최적화 기법 중 하나를 설명한 글이 있습니다.

https://velog.io/@arat5724/42-pushswap-%EC%B5%9C%EC%A0%81%ED%99%94
