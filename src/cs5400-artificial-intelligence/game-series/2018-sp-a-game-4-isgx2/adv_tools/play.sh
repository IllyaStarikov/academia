#!/bin/bash

LOOP=0
#Make given path absolute if not already
if [[ $1 = /* ]]
then
	DIR="$1"
else
	DIR="$PWD/$1"
fi

#Collect required variables
PREFIX="$2"
SESSION="$3"
LOOP=$4

#Check for required variables, or help
if [ $# -lt 3 ] || [[ "$@" =~ "-h" ]] || [[ "$@" =~ "--help" ]]
then
	echo -e "\nUSAGE: play [PATH TO MAKEFILE] [cpp|cs|java|py] [SESSION NAME] [NUMBER OF GAMES TO PLAY] [FLAGS]"
	echo -e "\nFLAGS:"
	echo -e "\n\t-mc, -make-clean:\n\t\tRemove previous build files in [PATH TO MAKEFILE] and automatically make and run whether or not -m or -make is set." | fmt | sed '2,$s/^/ /'
	echo -e "\n\t-m, -make:\n\t\tRun make in [PATH TO MAKEFILE]." | fmt | sed '2,$s/^/ /'
	echo -e "\n\t-p, -parallel:\n\t\tRun the games in parallel." | fmt | sed '2,$s/^/ /'
	echo -e "\n\t-s=[1|2|3], -silent==[1|2|3]:\n\t\tSupress the output of the 1st player, 2nd player, or both players." | fmt | sed '2,$s/^/ /'
	echo -e "\n\t-tra, -testRun-arguments:\n\t\tThis flag runs any allowed arguments one would normally be able to pass into gameSettings or aiSettings to specify things like FEN strings and maximum depth. See siggame documentation for allowed settings. This argument needs to be wrapped in quotes to function properly, and if you have multiple arguments to pass, those need to be wrapped in escaped quotes." | fmt | sed '2,$s/^/ /'
	echo -e "\n\t-oc=[PATH TO ANOTHER MAKEFILE], -other-client=[PATH TO ANOTHER MAKEFILE]:\n\t\tRun the chess AI in the current directory against a different AI in a different specified directory. Requires the other client language flag." | fmt | sed '2,$s/^/ /'
	echo -e "\n\t-ocl=[cpp|cs|java|py], -other-language=[cpp|cs|java|py]:\n\t\tThe language used by the other client. Only required if using the other client flag." | fmt | sed '2,$s/^/ /'
	echo -e "\n\t-l=[PATH TO CERVEAU], -local=[PATH TO CERVEAU]:\n\t\tSpecify a local game server in order to potentially run games faster" | fmt | sed '2,$s/^/ /'
	echo -e "\n\t-la, -local-address:\n\t\tSpecify an address for a local server. Use this if automatic detection of your IP and port are not working. The format for specifying an address is IP:PORT" | fmt | sed '2,$s/^/ /'
	echo -e "\n\t-nic, -forge:\n\t\tRun the games on the campus cluster. The script must be run from the forge, and if running the server on the forge, node.js must be installed. Output will be directed to .out files, but if you want to check output, continue to use the file output flag. The games will run in parallel regardless of whether -p is set." | fmt | sed '2,$s/^/ /'
	echo -e "\n\t-fo, -file-output:\n\t\tRedirect game output to files. The files will be named chess-GAME# in the directory of testRun. It is required that the silent flag not be used." | fmt | sed '2,$s/^/ /'
	echo -e "\n\t-co, -check-output:\n\t\tCheck the output of generated files for any invalid moves, draws, or timeouts. It is required that the file output flag be used." | fmt | sed '2,$s/^/ /'
	exit
#Check that language specification is valid.
elif ! [ "$PREFIX" == "cpp" ] && ! [ "$PREFIX" == "cs" ] && ! [ "$PREFIX" == "java" ] && ! [ "$PREFIX" == "py" ]
then
	echo "You must specify a language, being one of the following values [cpp|cs|java|py]."
	exit
#Check the given directory for validity
elif [ ! -e "$DIR" ]
then
	echo "Directory does not exist!"
	exit
elif [ ! -d "$DIR" ]
then
	echo "Given path is not a directory"
	exit
#Check the loop value for validity
elif [ -z "${LOOP##*[!0-9]*}" ]
then
	echo "Number of games invalid or not specified."
	exit
elif [ $LOOP -lt 1 ]
then
	echo "Number of games invalid or not specified."
	exit
#Check that the session name is not empty
elif [ -z "SESSION" ]
then
	echo "NO SESSION SPECIFIED"
	exit
#Move to the language's directory
else
	cd "$DIR"
fi

#Function to handle exits cleanly, and end any process this script may have started.
exit_script() {
	trap - SIGINT
	trap - EXIT
	
	#End running games
	if [ -n "$NIC" ]
	then
		scancel -u $USER > /dev/null 2>&1
	else
		pkill -f "$PREFIX"-client > /dev/null 2>&1
	fi
	
	#Find and kill the local server
	if [[ -n "$LOCAL" ]]
	then
		pkill -f "Cerveau" > /dev/null 2>&1
	fi
	echo "EXITING PLAY.SH"
	exit
}
trap exit_script SIGINT EXIT

#Initialize variables
MAKESTAT=0
PARALLEL=""
MADE=0
OUTPUT1=""
OUTPUT2=""
NIC=""
FILEOUT=""
CHECKOUT=""
if [ "$PREFIX" == "py" ]
then
	TESTRUNPREFIX="python3 -u ./main.py"
elif [ "$PREFIX" == "java" ]
then
	TESTRUNPREFIX=".java -jar target/java-client-jar-with-dependencies.jar"
else
	TESTRUNPREFIX="./build/$PREFIX-client"
fi
TESTRUN=" Chess -s game.siggame.io -r"
TESTRUNARGS=""
lAddr=""

#Loop through given arguments
for arg in "$@"
do
	case "$arg" in
		-mc|-make-clean)
			#Make clean and make, if make wasn't already run.
			if [ "$MADE" -eq "0" ]
			then
				#Load compilers on the forge
				if [[ "$@" =~ "-nic" ]] || [[ "$@" =~ "-forge" ]]
				then
					module load gnu/7.2.0 && module load cmake/3.9.4
				fi
				make clean
				CC=gcc CXX=g++ make
				MAKESTAT=$?
				MADE=1
			fi
			;;
		-m|-make)
			#Make if make wasn't already run.
			if [ "$MADE" -eq "0" ]
			then
				if [ -n "$NIC" ]
				then
					module load gnu/7.2.0 && module load cmake/3.9.4
				fi
				CC=gcc CXX=g++ make
				MAKESTAT=$?
				MADE=1
			fi
			;;
		-p|-parallel)
			#Set the parallel string for use with eval.
			PARALLEL="&"
			;;
		-s=*|-silent=*)
			#Get string after the equals sign
			SILENT=${arg#*=}
			#Set the output strings for use with eval.
			if [ "$SILENT" -eq "1" ]
			then
				OUTPUT1="> /dev/null 2>&1"
			elif [ "$SILENT" -eq "2" ]
			then
				OUTPUT2="> /dev/null 2>&1"
			elif [ "$SILENT" -eq "3" ]
			then
				OUTPUT1="> /dev/null 2>&1"
				OUTPUT2="> /dev/null 2>&1"
			fi
			;;
		-oc=*|-other-client=*)
			#Get string after the equals sign
			OC=../${arg#*=}
			if ! [[ "$@" =~ "-ocl=" ]] && ! [[ "$@" =~ "-other-language=" ]]
			then
				echo "You need to specify the other client's language when using the -oc option."
				exit
			fi
			#Check the validity of the other client directory
			if [ ! -e "$OC" ]
			then
				echo "Other client directory does not exist!"
				exit
			elif [ ! -d "$OC" ]
			then
				echo "Other client path is not a directory"
				exit
			fi
			
			#Make the path absolute, if not already
			if [[ $OC = /* ]]
			then
				OTHERCLIENT="$OC"
			else
				OTHERCLIENT="$PWD/$OC"
			fi
			;;
		-ocl=*|-other-language=*)
			#Collect the other client language
			OCPREFIX=${arg#*=}
			if [ "$OCPREFIX" == "py" ]
			then
				TESTRUNPREFIXOC="python3 -u ./main.py"
			elif [ "$OCPREFIX" == "java" ]
			then
				TESTRUNPREFIXOC=".java -jar target/java-client-jar-with-dependencies.jar"
			else
				TESTRUNPREFIXOC="./build/$OCPREFIX-client"
			fi
			;;
		-l=*|-local=*)
			#Get string after the equals sign
			lPath=../${arg#*=}
			
			#Check the validity of the path.
			if [ ! -e "$lPath" ]
			then
				echo "Cerveau client directory does not exist!"
				exit
			elif [ ! -d "$lPath" ]
			then
				echo "Cerveau client path is not a directory"
				exit
			fi
			
			#Make the path absolute, if not already
			if [[ $lPath = /* ]]
			then
				LOCAL="$lPath"
			else
				LOCAL="$PWD/$lPath"
			fi
			;;
		-la=*|-local-address=*)
			#Change the run command to use the specified address.
			lAddr=${arg#*=}
			TESTRUN=" Chess -s $lAddr -r"
			;;
		-nic|-forge)
			#Set the NIC flag
			NIC=1
			;;
		-tra=*|-testRun-arguments=*)
			#Get string after the equals sign
			tra=${arg#*=}
			
			#Check the validity of the argument
			if ! [[ $tra =~ " " ]]
			then
				echo "Your arguments must be in quotes and there must be a space in your command. EXAMPLE: -tra=\"--gameSettings fen=VALID FEN\""
				exit
			fi
			TESTRUNARGS=$tra
			;;
		-fo|-file-output)
			#Check the validity of the argument
			if [[ "$@" =~ "-s" ]] || [[ "$@" =~ "-silent" ]]
			then
				echo "You cannot use the file output flag in conjunction with the silent flag."
				exit
			fi
			FILEOUT="&>> $PWD/chess-"
			;;
		-co|-check-output)
			#Check the validity of the argument
			if ! [[ "$@" =~ "-fo" ]] && ! [[ "$@" =~ "-file-output" ]] && ! [[ "$@" =~ "-nic" ]] && ! [[ "$@" =~ "-forge" ]]
			then
				echo "You must use the file output flag or nic/forge flag in order to use the check output flag flag."
				exit
			fi
			CHECKOUT=1
			;;
	esac
done

#Check that clients are built
if [ ! -e "$PWD/build" ] && ! [ "$PREFIX" == "py" ]
then
	echo "Build directory does not exist! Exiting..."
	exit
elif [ ! -f "$PWD/build/$PREFIX-client" ] && ! [ "$PREFIX" == "py" ]
then
	echo "$PREFIX-client does not exist in the build directory! Exiting..."
	exit
elif [[ -n "$OC" ]] && [[ ! -e "$OC/build" ]] && ! [[ "$PREFIX" == "py" ]]
then
	echo "Build directory does not exist! Exiting..."
	exit
elif [[ -n "$OC" ]] && [[ ! -f "$OC/build/$OCPREFIX-client" ]] && ! [[ "$PREFIX" == "py" ]]
then
	echo "$OCPREFIX-client does not exist in the build directory! Exiting..."
	exit
fi

if [[ -n "$LOCAL" ]]
then
	#Change to the server directory
	LOCATION=$PWD
	cd $LOCAL
	SERVERARGS=""
	
	#Collect network information of local server, if address not specified
	if [ -z "$lAddr" ]
	then
		ADDRESS="$(curl ipinfo.io/ip 2>/dev/null)"
		PORT="$(ss -atu | awk '{print $5}' | awk -F: '{print $NF}' | grep -Eo '[0-9]{4,6}' | awk 'NR==1')"
		TESTRUN=" Chess -s $ADDRESS -p $PORT -r"
		fuser -k $PORT 2>/dev/null
		
		if [ -z $ADDRESS ] || [ -z $PORT ]
		then
			echo "Could not get network information. Exiting..."
			exit
		fi
		
		SERVERARGS=" --tcp-port $PORT"
	fi
	
	#Add locally installed node to the path
	if [ -n $NIC ]
	then
		PATH=~/node/bin:$PATH
	fi
	
	#Run the server with optional arguments in the background.
	(node ./main.js$SERVERARGS) &
	
	#Exit if the server failed to start
	if [ "$?" -ne "0" ]
	then
		echo "Running local server failed!"
		exit
	fi
	
	#Change back to the makefile directory, and wait breifly for the server.
	sleep .5
	cd $LOCATION
fi

COUNTER=0
IDS=()

#Remove previous output
if [ -n "$FILEOUT" ]
then
	rm -f chess-*.txt
fi

if [ $MAKESTAT -eq 0 ]
then
	while [ $COUNTER -lt $LOOP ]
	do
		COUNTER=$[$COUNTER+1]
		
		#Create output filename
		FILEOUTFINAL=""
		if [ -n "$FILEOUT" ]
		then
			FILEOUTFINAL="$FILEOUT$COUNTER.txt"
		fi
		
		if [ -n "$NIC" ]
		then
			#Create submission file
			TEMPJOB=$(mktemp)
			cat << EOF > $TEMPJOB
#!/bin/bash
#SBATCH --job-name=chess-$COUNTER
#SBATCH --output=chess-$COUNTER.out
#SBATCH --time=1-16:00:00
#SBATCH --mem=2000
#SBATCH --partition=free

module load gnu/7.2.0
module load python/3.6.4
echo "game starting"
(eval $TESTRUNPREFIX$TESTRUN "$SESSION$COUNTER $TESTRUNARGS" $FILEOUTFINAL $OUTPUT1) &
if [ -n "$OTHERCLIENT" ]
then
	cd $OTHERCLIENT
	(eval $TESTRUNPREFIXOC$TESTRUN "$SESSION$COUNTER $TESTRUNARGS" $FILEOUTFINAL $OUTPUT2)
else
	(eval $TESTRUNPREFIX$TESTRUN "$SESSION$COUNTER $TESTRUNARGS" $FILEOUTFINAL $OUTPUT2)
fi
echo "game ended"

exit \$?
EOF
		
			#Run submission.
			OUT=$(sbatch $TEMPJOB)

			#Ensure job was submitted successfully and collect its ID.
			rc=$?
			if [[ $rc == 0 ]]; then
				PRE="Submitted batch job "
				JOBID=${OUT#$PRE}
				if ! [[ "$JOBID" =~ ^[_-.@0-9A-Za-z]+$ ]] ; then
					echo "cannot parse jobID from the output of sbatch!"
				fi
				rm -f $TEMPJOB
				IDS+=("$JOBID")
			else
				error "$0: sbatch failed!"
			fi
		else
			#Run games with collected arguments
			(eval $TESTRUNPREFIX$TESTRUN "$SESSION$COUNTER $TESTRUNARGS" $FILEOUTFINAL $OUTPUT1) &
			if [ -n "$OTHERCLIENT" ]
			then
				cd $OTHERCLIENT
				(eval $TESTRUNPREFIXOC$TESTRUN "$SESSION$COUNTER $TESTRUNARGS" $FILEOUTFINAL $OUTPUT2)
			else
				(eval $TESTRUNPREFIX$TESTRUN "$SESSION$COUNTER $TESTRUNARGS" $FILEOUTFINAL $OUTPUT2)
			fi
		fi	
	done
else
	echo "BUILD ERROR! EXITING PLAY.SH"
	exit
fi

echo "Games are starting..."

if [ -n "$NIC" ]
then
	#Query the job queue to ascertain how many jobs remain and wait for them to finish, so the user can always send a SIGINT.
	FLAG=1
	OUT="$(squeue -u $USER)"
	GAMESLEFT=$(echo -n "$OUT" | grep -c '^')
	GAMESLEFT=$[$GAMESLEFT-2]
	while [ $FLAG -eq 1 ]
	do
		OUT="$(squeue -u $USER)"
		OLDGAMESLEFT=$GAMESLEFT
		GAMESLEFT=$(echo -n "$OUT" | grep -c '^')
		GAMESLEFT=$[$GAMESLEFT-2]
		if [ $GAMESLEFT -lt 0 ]
		then
			GAMESLEFT=0
		fi
		if [ $OLDGAMESLEFT -gt $GAMESLEFT ]
		then
			echo "$GAMESLEFT/$LOOP games still running."
		fi
		FLAG=0
		for i in "${IDS[@]}"
		do
			if [[ "$OUT" =~ "$i" ]]
			then
				FLAG=1
			fi
		done
		sleep .5
	done
else
	#Grep processes to ascertain how many processes remain and wait for them to finish, so the user can always send a SIGINT.
	COUNTER=0
	PID="$(pgrep $PREFIX-client)"
	while [ -z "$PID" ]
	do
		sleep 1
		COUNTER=$[$COUNTER+1]
		if [ $COUNTER -gt 20 ]
		then
			echo "TIMEOUT waiting for $PREFIX-client!"
			exit
		fi
		PID="$(pgrep $PREFIX-client)"
	done
	GAMESLEFT=$LOOP
	PID="$(echo "$PID" | head -n1)"
	while [ -e /proc/$PID ]
	do
		sleep .6
		PID="$(pgrep $PREFIX-client)"
		OLDGAMESLEFT=$GAMESLEFT
		GAMESLEFT="$(echo "$PID" | wc -l)"
		DIVIDEBY=2
		if [ -n "$OCPREFIX" ] && ! [[ "$OCPREFIX" == "$PREFIX" ]]
		then
			DIVIDEBY=1
		fi
		GAMESLEFT=$(( $GAMESLEFT / $DIVIDEBY ))
		if [ $OLDGAMESLEFT -gt $GAMESLEFT ]
		then
			echo "$GAMESLEFT/$LOOP games still running."
		fi
		
		if [ -z "$PID" ]
		then
			exit
		fi
		PID="$(echo "$PID" | head -n1)"
	done
fi

#Check the output for undesirable states.
if [ -n "$CHECKOUT" ]
then
	for log in chess-*.txt; do
		INV="0"
		MOVE="0"
		DC="0"
		TO="0"
		REP="0"
		FIFTY="0"
		STALE="0"
		MAT="0"
		RANDERR="0"

		INV=$(grep -F 'Invalid' $log)
		if [ -n "$INV" ]
		then
			echo "$log has an invalid"
		fi
		
		MOVE=$(grep -F 'Did not make a move' $log)
		if [ -n "$MOVE" ]
		then
			echo "$log Did not make a move"
		fi

		DC=$(grep -F 'disconnected' $log)
		if [ -n "$DC" ]
		then
			echo "$log Disconnected"
		fi

		TO=$(grep -F 'timed' $log)
		if [ -n "$TO" ]
		then
			echo "$log timed out"
		fi

		REP=$(grep -F 'repetition' $log)
		if [ -n "$REP" ]
		then
			echo "$log repetition"
		fi

		FIFTY=$(grep -F '50-move' $log)
		if [ -n "$FIFTY" ]
		then
			echo "$log 50-move"
		fi

		STALE=$(grep -F 'Stalemate' $log)
		if [ -n "$STALE" ]
		then
			echo "$log stalemate"
		fi

		MAT=$(grep -F 'material' $log)
		if [ -n "$MAT" ]
		then
			echo "$log insufficient material"
		fi

		RANDERR=$(grep -F 'RANDCHESS' $log)
		if [ -n "$RANDERR" ]
		then
			echo "$log's error was due to randChess"
		fi
	done
fi

exit
