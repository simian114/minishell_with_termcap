# minishell_with_termcap
### bash 쉘 처럼 다양한 키보드 입력 받을 수 있게 minishell 수정 중...
-----
### How to compile?
- linux

  ```
    1. sudo apt-get install libncurses5-dev
    2. make
  ```

- Mac

  ```
    make
  ```
-----

### Implmented
- Move cursor Left and Right using :arrow_left:, :arrow_right:
- Move cursor Up and down using **Ctrl + :arrow_up:, Ctrl + :arrow_down:**
- Move cursor Home and End of the command line using **HOME, END**
- Edit the line where the cursor is located
- Command history navigating using :arrow_up:, :arrow_down:

-----
### Not Implemented
- ctrl + :arrow_left:
- tab
- Cut, Copy, Paste

-----
### BUG
- 입력줄 중간으로 커서 옮긴 후 입력 쫙 하면 다음 줄로 넘어갈 때 심각한 오류 발생

-----
### :heavy_exclamation_mark: termcap과 get_line
- 터미널의 설정 바꿨으면 함수가 끝날 때 원상복구 시켜주자.

- 기존의 터미널은 Canonical 입력 상태. 이 상태일 때 read(0, buf, 1000) 이런 함수가 있으면 EOF가 되거나 1000개의 입력을 받으면
read가 끝난다. 그리고 입력이 끝나면 그제서야 buf에 입력이 시작된다. minishell에서 화살표 등의 다른 키가 먹히지 않는 이유가 이거 때문인듯.
따라서 하나의 입력이 들어올 때 마다 바로 read가 종료되고 그 다음 작업을 진행할 수 있도록 Canonical 설정을 꺼주자.

- termcap으로 입력을 받는 함수를 만들 때, 눈에 보이는 커서의 위치와 실제 메모리 상의 커서 위치가 다를 수 있다.
그럼 바로.. 끔찍한 일 발생. 따라서 커서의 위치를 추적하는 변수를 꼭 하나 만들어 두자.

- Canonical 모드를 껐으므로 하나의 입력이 들어올 때 마다 각 입력에 해당하는 함수가 동작한다.
  ```
  - 새로운 문자를 추가하는 함수(Insert)
    - command line의 끝
    - command line의 중간
  - Delete 함수
  - 커서를 움직이는 함수
  - Command History navigating
  - Signal
  - Ctrl + d (End Of Transmission)
  ```
- 모든 입력들은 ***커서가 움직인다*** 라는 하나의 공통점을 갖는다. 따라서 아래와 같은 방법으로 함수를 만들면 좋을거 같다.(나는 멍청해서 이렇게 안했다..)
  - 커서의 위치를 추적하는 변수 두 개 선언.
    - ex_cursor_pos
    - cur_cursor_pos
  - 입력에 대한 함수들은 실제 커서를 움직이지 않고 cursor_pos들의 값들만 수정한다.
    - ex_cursor_pos = cur_cursor_pos
    - cur_cursor_pos = new cursor pos
  - 입력 함수가 종료 되면 이제 move_cursor 함수가 동작한다. 이 함수는 아래와 같이 3 가지 경우의 수가 존재한다.
    - ex_cursor_pos == cur_cursor_pos
    - ex_cursor_pos > cur_cursor_pos
    - ex_cursor_pos < cur_cursor_pos
  - :heavy_exclamation_mark: ***커서가 다음 줄 또는 이전 줄로 넘어가는 경우 주의하자.***  

- Signal을 minishell의 main에도 설치하고 get_line 함수에도 따로 설치하자.
- man termcap, man terminfo 등을 해보면 capability 뭐시기 뭐시기 말이 많다. capability는 기능이라고 생각하면 된다.
이 녀석들을 tputs, tgetstr 등의 함수들을 이용해서 터미널을 조작할 수 있다. 몇 가지 예를 살펴보면
  ```    
    nd : 커서를 오른쪽으로 움직인다.
    le : 커서를 왼쪽으로 움직인다.
    do : 커서를 아래로 움직인다. (확실히 기억은 안나는데, 이 녀석은 아마 커서를 아래로 내리고 Col 0으로 움직인다.)
    up : 커서를 위로 움직인다. (do랑 다르게 이 녀석은 Col은 그대로 유지하면서 위로 이동한다.)
    sc : 현재 커서 위치를 저장한다.
    rc : 커서 위치를 sc로 저장했던 곳으로 되돌린다.
    dc : 커서가 위치한 곳의 문자 하나를 지운다.
    dl : 커서가 위치한 줄을 지운다.
    cr : 커서가 위치한 줄의 Col 0으로 커서를 움직인다.
    ===============================================
    사용 예시
    ***********************************************
    tputs(tgetstr(nd, NULL), 1, &ft_putchar_fd);
    ***********************************************
  ```
