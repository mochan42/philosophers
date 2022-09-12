# philosophers

- 42 Core Curriculum - Level 2
- Level 3 in the Holy Graph
- Passed with 100% (mandatory part) on 11th Sep 2022.

## Use

Clone the repository in your terminal and create a folder named philosophers (or the name you prefer):<br>
`git clone https://github.com/mochan42/push_swap.git philosophers`

Enter into the directory `philosophers` (or type in the name of the folder you created):<br>
`cd philosophers`

Then, enter into the sub-directory `philo`
`cd philo`

Run the Makefile:<br>
`make` for mandatory part<br>
`make DEBUG=ON` for mandatory using the thread sanitizer flag :  `-fsanitize=thread -g`

To run the programme :<br>
`./philo 5 800 200 100 2`<br>

where :<br>
- 5   : is the number of philosophers,<br>
- 800 : is the time to die in ms,<br>
- 200 : is the time to eat in ms,<br>
- 100 : is the time to sleep in ms,<br>
- 2   : is the number of times each philosoper must eat.
