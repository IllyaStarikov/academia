#################################
#	Coding Standards	#
#################################

You are free to use any of the following programming languages for your submission : 
	- C++
	- C#
	- Java
	- Python
	- Go
Your code must be well formatted and styled according to good coding standards, such as the MST coding standard outlined here : 
http://web.mst.edu/~cpp/cpp_coding_standard_v1_1.pdf
It is required that your code is well documented.

NOTE : Sloppy, undocumented, or otherwise unreadable code will be penalized for not following good coding standards (as laid out in the grading rubric on the course website) : 
http://web.mst.edu/~tauritzd/courses/cs5400/sp2018/ 

#################################
#       Compiling & Running	#
#################################

You will find a "run.sh" script in your repository which will compile and run the AI_help.cpp file also located in your repo. You are not required to use the provided run.sh or AI_helper.cpp, they are intended to provide a level of guidance to anyone struggling with the concepts of bash scripting and/or taking command line arguments to your programs.

While you are not required to use any part of the provided run.sh script, your final submission must include a script "run.sh" which should compile and run your code.

Your run.sh script should generate solutions for each puzzle instance associated with that assignment.
	Assignment 1 - puzzle1.txt --> solution1.txt
	Assignment 2 - puzzle1.txt & puzzle2.txt --> solution1.txt & solution2.txt
	Assignment 3 - puzzle1.txt, puzzle2.txt, & puzzle3.txt --> solution1.txt, solution2.txt, & solution3.txt
	Assignment 4 - puzzle1.txt, puzzle2.txt, puzzle3.txt, &  puzzle4.txt --> solution1.txt, solution2.txt, solution3.txt, &  solution4.txt

Your script should run on the campus linux machines with the following command : 
	./run.sh

To run your script with the above command, you will need to give your script execution permissions using the following command :
  chmod +x run.sh
  
#################################
#  Submission Rules  #
#################################
  
  Included in your repository is a file named "readyToSubmit.txt", which you will use to indicate which version of your code is the one to be graded. When you are ready to submit your final version, change the first line of this file to the word "yes", then commit and push your code. You may commit and push as much as you want, but your submission will be confirmed as "final" if the first line of "readyToSubmit.txt" is "yes" at 11:59pm on the due date. If you do not plan to submit before the deadline, then you should NOT modify "readyToSubmit.txt" until your final submission is ready. Once your final submission is ready, change the first line of "readyToSubmit.txt" to "yes", commit and push your code, and do not make any further changes to it.
  
  When you are ready to submit, your repository must (at the very least) contain the following items :
  - Source Code Files
  - run.sh
  - puzzle1.txt, puzzle2.txt, etc.
  - solution1.txt, solution2.txt, etc.
  
Note that the contents of the solution file must be formatted as described on the puzzle page. (http://web.mst.edu/~tauritzd/courses/cs5400/sp2018/puzzle.html)
  
  Late submissions will be penalized 5% for the first 24 hour period and an additional 10% for every 24 hour period thereafter.

