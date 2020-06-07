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
