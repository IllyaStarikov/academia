#!/bin/bash

#
#  homework-1.sh
#  Introduction To Operating Systems
#
#  Created by Illya Starikov on 02/02/2017
#  Copyright 2017. Illya Starikov. All rights reserved.
#

# Problem #1
ancestory_tree() {
    printf  "\n"
    printf  "%s\n" \
            "# -----------------------#" \
            "#     Ancestory Tree     #" \
            "# -----------------------#" \
            ""                           \

    tree=$(pstree --ascii -ps $$)
    output=$(echo $tree | sed 's/---/ /g' | awk '{ for (i=NF; i>1; i--) printf("%s \n\t\t|\n\t",$i); print $1; }')
    printf "\t$output\n"
}

# Problem #2
determine_users_online() {
    printf  "\n"
    printf  "%s\n" \
            "# -----------------------#" \
            "# Determine Users Online #" \
            "# -----------------------#" \
            ""                           \

    # The first awk is to only print the first column of the users
    # The second is to print in a column in a row format
    # Also, we have to remove root, so dekete the line with root, so sed
    who | awk '{ print $1 }' | sed '/root/d' | sort | uniq | awk '{printf("%s ", $0)}'
    printf "\n"
}

# Problem #3
print_user_processes() {
    printf  "\n"
    printf  "%s\n" \
            "# -----------------------#" \
            "#  Print User Processes  #" \
            "# -----------------------#" \
            ""                           \

    # Get the users in a column format
    users=`who | awk '{ print $1 }' | sort | uniq | sed '/root/d'`

    i=1
    while read -r user; do
        echo "$i. $user"
        let "i++"
    done <<< "$users"

    printf "\nOption: "
    read input

    # This just returns the input-th line of the user (non-zero index baed)
    user=`sed -n ${input}p <<< "$users"`

    ps aux | grep "$user"
}

stall() {
    printf "\n"
    read -n1 -r -p "Press Space To Continue..." key
    printf "\n"
}

main() {
    should_print_menu=true

    while [[ "$input" != "4" ]]; do
        if [[ "$should_print_menu" == true ]]; then
            printf  "\n"
            printf  "%s\n" \
                    "# -----------------------#" \
                    "#        Main Menu       #" \
                    "# -----------------------#" \
                    ""                           \
                    "1. Ancestory Tree" \
                    "2. Determine Online Users" \
                    "3. Print User Processes" \
                    "4. Quit"
        fi

        printf "\nOption: "
        read input

        reprint_menu=true

        case "$input" in
            "1")
                ancestory_tree
                stall ;;
            "2")
                determine_users_online
                stall ;;
            "3")
                print_user_processes
                stall ;;
            "4")
                printf "\nTerminating..\n\n" ;;
            *)
                printf "Invalid Option\n"
                reprint_menu=false ;;
        esac
    done
}

main "$@"
