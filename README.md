# :pineapple:***minishell_with_termcap***
***minishell by [gmoon](https://github.com/moon9ua) and termcap by [sanam](https://github.com/simian114).***<br>
***@ 42 Seoul***

-----
### bash 쉘 처럼 다양한 키보드 입력 받을 수 있게 minishell 수정 중...

-----
![Demon..](demonstration.gif)

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
- **Ctrl + :arrow_up:, :arrow_down:** 에 문제 있는듯..

-----
### :heavy_exclamation_mark: termcap과 get_line
- get_line 함수를 만들 때 가장 먼저 해야하는건 현재 터미널의 width를 구하는 것. icotl 라이브러리와 함수를 이용하면 된다.  

- 터미널의 설정 바꿨으면 함수가 끝날 때 원상복구 시켜주자.  

- 기존의 터미널은 Canonical 입력 상태. 이 상태일 때 read(0, buf, 1000) 이런 함수가 있으면 EOF가 되거나 1000개의 입력을 받으면
read가 끝난다. 그리고 입력이 끝나면 그제서야 buf에 입력이 시작된다. minishell에서 화살표 등의 다른 키가 먹히지 않는 이유가 이거 때문인듯.
따라서 하나의 입력이 들어올 때 마다 바로 read가 종료되고 그 다음 작업을 진행할 수 있도록 Canonical 설정을 꺼주자.(Ctrl + d가 EOF가 아니라 EOT로 바뀐다)  

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

- terminal을 다루기 위해서는 Capability를 이용해야한다. Capability는 세 종류가 있다. (man termcap, man terminfo, [gnu 문서](https://www.gnu.org/software/termutils/manual/termcap-1.3/html_node/termcap_5.html))
  - Boolean   -> int tgetnum(char \*name)
  - Numeric   -> int tgetflag(char \*name)
  - String    -> char \*tgetstr(char \*name)
- -> 뒤에 있는 함수들은 각 Capability를 사용하기 위한 함수다. 인자로 알맞은 Capability를 넣어주면 된다.  

- 아래는 내가 사용한 String Capability 종류와 사용 예. (참고로 나는 String 만 사용했다. 영어 해석이 잘 안되서,,,)
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
    tputs(tgetstr(nd, NULL), 1, &ft_putchar_fd); // 커서를 오른쪽으로 움직임
    ***********************************************
    char *tgetstr(char *name)함수는 뭔가를 가져온다! 라는 느낌이고
    가져오는걸 쓰는 함수는 tputs인듯. 정확히는 모르겠다.
    
    나는 string만 사용했는데, Numeric에도 쓸만한 Capability가 보인다.
    "co"는 눈에 보이는 커서의 Numbers of Col을 return 하는것 같다. 아래 처럼 쓰면 될듯.
        int cur_col = tgetnum("co");
    Boolean에는 "hc"가 있는데 설명에 hardcopy라고 써있다. copy를 해주는 녀석일까? 나중에 알아보자.
  ```
