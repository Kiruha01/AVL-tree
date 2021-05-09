#!/bin/bash

if [[ -f $1 ]]; then
    cat $1 > input.txt
    sudo ./AVL_tree
fi
