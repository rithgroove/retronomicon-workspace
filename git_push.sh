if [ ! -e "retronomicon" ]; then
    echo "no retronomicon directory" 
else
    cd retronomicon
    git add -A
    git commit
    git push
    cd ..
fi

if [ ! -e "retronomicon-platformer" ]; then
    echo "no retronomicon-platformer directory" 
else
    cd retronomicon-platformer
    git add -A
    git commit
    git push
    cd ..
fi

if [ ! -e "retronomicon-platformer-demo" ]; then
    echo "no retronomicon-platformer-demo directory" 
else
    cd retronomicon-platformer-demo
    git add -A
    git commit
    git push
    cd ..
fi


git add -A
git commit
git push 