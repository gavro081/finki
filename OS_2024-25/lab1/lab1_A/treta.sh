#! /bin/bash

if [ $# -le 2 ]; then

        echo "Not enough command line arguments"

else
        echo "Average execution time: $((($1 + $2 + $3) * 60 / 3))"

        echo "Count of excecutions: $#"

        if [ $# -ge 5 ]; then

                echo "The testing is done"
        else

                echo "More testing is needed"
        fi

fi

