#! /bin/bash

function calClaspD() {
    for file in `ls ../IO/*.in`
    do
        time gringo $file | claspD 0
    done
}

calClaspD