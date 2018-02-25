#################################
#	Coding Standards	#
#################################

You are free to use any of the following programming languages for your submission : 
	- C++
	- C#
	- Java
	- Python3 (NOT Python2)
Your code must be well formatted and styled according to good coding standards, such as the MST coding standard outlined here : 
http://web.mst.edu/~cpp/cpp_coding_standard_v1_1.pdf
It is required that your code is well documented.

NOTE : Sloppy, undocumented, or otherwise unreadable code will be penalized for not following good coding standards (as laid out in the grading rubric on the course website) : 
http://web.mst.edu/~tauritzd/courses/cs5400/sp2018/ 

#################################
#          !IMPORTANT!          #
#################################

Read the README in the sub-directory corresponding to your chosen language.  

Read the chess framework's documentation for your chosen language here : http://docs.siggame.io/chess/ 

#################################
#	Submission Rules	#
#################################

Included in the top level of your repository is a file named "readyToSubmit.txt", which you will use to indicate which version of your code is the one to be graded as well as which programming language you're using; note that you may switch languages between assignments (though, it is not recommended...) . When you are ready to submit your final version, change the first line of this file to the word "yes" and the second line to your programming language, then commit and push your code. You may commit and push as much as you want, but your submission will be confirmed as "final" if the first line of "readyToSubmit.txt" is "yes" at 11:59pm on the due date. If you do not plan to submit before the deadline, then you should NOT modify "readyToSubmit.txt" until your final submission is ready. Once your final submission is ready, change the first line of "readyToSubmit.txt" to "yes", commit and push your code, and do not make any further changes to it. 

Late submissions will be penalized 5% for the first 24 hour period and an additional 10% for every 24 hour period thereafter. Any submission turned in more than 5 days late will not be graded, and will result in a score of 0 for that assignment. 

#################################
#       Compiling & Running	#
#################################

You have been provided a bash script called "play.sh", which compiles and runs your code; it also starts a game session between your AI and itself. DO NOT MODIFY THIS SCRIPT.
You can run "play.sh" using the following command format :
	./play.sh Joueur.<lang> Session_ID
Where Joueur.<lang> is the directory for the language you are coding in. An example of the above command for c++ would be :
	./play.sh Joueur.cpp AIisAwesome

#################################
#      	    OPTIONALLY		#
#################################

You have also been provided a bash script called "compress.sh", which compresses the designated directory in a way that is compatible with the Sig-Game Arena interface.
You can run "compress.sh" using the following command format :
	./compress.sh Joueur.<lang>
Where Joueur.<lang> is the directory for the language you are coding in. An example of the above command for c++ would be :
        ./compress.sh Joueur.cpp

You can register for an account and upload your Joueur.<lang>.tar.gz to the Sig-Game page here : https://chess.siggame.io

Don't forget you are limited to 150MB compressed filesize.

