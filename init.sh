if [ ! -e "retronomicon" ]; then
    git clone git@github.com:rithgroove/retronomicon.git
    cd retronomicon
    USE_LUA=ON USE_PYTHON=ON  ./init.sh
    cd ..
elif [ ! -d "retronomicon" ]; then
    echo "retronomicon already exists but is not a directory" 
else
    cd retronomicon
    git pull
    cd ..
fi

if [ ! -e "retronomicon-platformer" ]; then
    git clone git@github.com:rithgroove/retronomicon-platformer.git
elif [ ! -d "retronomicon-platformer" ]; then
    echo "retronomicon-platformer already exists but is not a directory" 
else
    cd retronomicon-platformer
    git pull
    cd ..
fi


if [ ! -e "retronomicon-platformer-demo" ]; then
    git clone git@github.com:rithgroove/retronomicon-platformer-demo.git
elif [ ! -d "retronomicon-platformer-demo" ]; then
    echo "retronomicon-platformer-demo already exists but is not a directory" 
else
    cd retronomicon-platformer-demo
    git pull
    cd ..
fi
