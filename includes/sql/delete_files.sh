for filename in output/build/bin/_select_*.*
do
    if [ -f "$filename" ]
    then
        rm "$filename"
    fi
done