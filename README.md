# 🕹Mine-Sweeper-Game💣💥
🌞 Used by : <img src="https://img.shields.io/badge/c++-00599C?style=flat-square&logo=c%2B%2B&logoColor=white"/> 

## 📖 21년도 2학기 객체지향프로그래밍(2) 과제

>  <span style = "color :Blue">**2021.09.20 ~ 2021.09.27**</span>

> >**In this task, you are required to write a console-based 2d game called 'mine sweeper'. In the task, you need to support the followings:**
> >
> >1️⃣ generate `10x10` 2d grid space. [✔]
> >
> >2️⃣ spot n (10 to 20) number of mines in the space. Of course, you need to hide them. [✔]
> >
> >3️⃣ Using a mouse click, a grid near mines show number of neighboring mines. [✔]
> >
> >4️⃣ If you uncover all mines, your mission will be cleared. [✔]

## 📝 mine-sweeper-game 구조

![이미지](https://user-images.githubusercontent.com/63442636/134887511-392f7356-72b2-457a-b255-4863304873f7.png)

```markdown
main.cpp 및 main()함수를 최대한 깔끔하게 만들기 위해서, 게임엔진과 비슷한 기능을 하는 `Game2D`라는 클래스를 따로 만들어 `상속`받아 사용하였습니다.
따라서, main.cpp의 class MineSweeperGame은 별도의 public 멤버변수를 갖고, Game2D의 update함수와 gameclear함수를 오버라이드합니다.
추가적으로 교수님이 주신 Utils.h와 mouse/keyboard 입력 코드를 제외하고는 직접 구상하여 만들었습니다!
```



## 🎖 배운점



\1. rand() 함수는 srand()를 사용하면 매 빌드마다 다른 시퀀스의 값을 반환하지만, 반환 값들이 중복 될 수 있어서, 따로 중복처리를 해주어야 한다. <span style = "color :Green">ISSUE</span> [#3](https://github.com/Yeram522/OPP-Mine-Sweeper-Game/issues/3)

\2. static함수 내에서는 static함수만 불러올 수 있다.  <span style = "color :Green">ISSUE</span> [#7](https://github.com/Yeram522/OPP-Mine-Sweeper-Game/issues/7)

\3. 부모클래스의 함수를 virtual로 두고, 자식클래스에서 override할 때 매개변수의 자료형도 부모함수와 동일해야한다. <span style = "color :Green">ISSUE</span> [#8](https://github.com/Yeram522/OPP-Mine-Sweeper-Game/issues/8)

\4. 동적할당으로 변수를 사용 할 때 초기화로 정해진  크기보다 초과하여 메모리가 담기면 , 나중에 delte로 해제할 때 다른 메모리의 부분까지 해제하려 하기 때문에, 힙 충돌 오류가 생긴다. <span style = "color :Green">ISSUE</span> [#11](https://github.com/Yeram522/OPP-Mine-Sweeper-Game/issues/11)

\5. static 전역변수는 선언된 파일 내부에서만 전역으로 사용 된다. 외부 파일에서 불러오는 것은 불가능하다. Pull [#12](https://github.com/Yeram522/OPP-Mine-Sweeper-Game/pull/12)



## ✨Result

>  📋 Project Board  [Go](https://github.com/Yeram522/OPP-Mine-Sweeper-Game/projects/1)
>
> 🎬 YouTube Video [Go]()



💛 last update : 2021.09.27(20:30pm)
