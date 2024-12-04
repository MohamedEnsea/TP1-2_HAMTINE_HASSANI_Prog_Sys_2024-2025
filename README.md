# ENSEASH
As part of our synthesis practical work, our aim is to create a micro shell, displaying the output codes and execution times of the programs we run.

## Organisation
This project was carried out by Mohamed HAMTINE and Wilal HASSANI (2G2/TD1/TP1) and covers two 8-hour sessions. We have structured the project so that each file corresponds to a different question.

## How it works
Before executing the code, it's important to ensure that the path is correctly defined, to check that we're in the right working directory to execute our code. To do this, use the “pwd” command. If you're not in the right directory, use the following command: cd /workspaces/codespaces-blank/enseash.

To check that you're in the right directory, you can use the “ls” command, which lists the contents of the current directory, including files and sub-directories.

Then, to execute the code for each file (each question), simply write :
- make (to compile everything)
- gcc -o enseash question1.c (example for file question1.c)
- ./enseash

## For question 2
In our tests, we used commands such as "date", "cal" or "clear". Please note that the "fortune" command does not work on this IDE.

## For question 5
To test the time count, we used the sleep 5 command, which causes the program to pause for 5s. The execution time displayed is indeed 5s "[exit:0|5002ms]".

## For question 6
To test time counting, we opened a new terminal. In the main terminal, after executing a command, the child's PID is displayed.

We then executed the "sleep 100" command to make the child process sleep (pause) for 100 seconds. 

In the second terminal, we used the "kill -9 [son's PID]" command to kill the child process. 

Returning to the main terminal, we found that the child process had indeed been killed and that the prompt displayed "[sign:9|64545ms]", indicating when it had been killed.