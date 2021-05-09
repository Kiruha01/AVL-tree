#!/bin/bash

if [[ -f $1 ]]; then
    cat $1 > input.txt
    chmod +x AVL_tree
    ./AVL_tree
fi
