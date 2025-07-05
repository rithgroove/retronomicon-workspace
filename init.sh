if [ ! -e "retronomicon" ]; then
    git clone git@github.com:rithgroove/retronomicon.git
elif [[ ! -d "retronomicon" ]]; then
    echo "$dir already exists but is not a directory" 
else
    cd retronomicon
    git pull
    cd ..
fi