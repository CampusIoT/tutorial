#!/bin/bash

echo Killing $(cat *.pid)
kill -9 $(cat *.pid)
rm -f *.pid
