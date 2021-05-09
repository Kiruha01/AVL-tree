#!/bin/bash

if [[ -f $1 ]]; then
    cat $1 > input.txt
    ./AVL_tree
fi
