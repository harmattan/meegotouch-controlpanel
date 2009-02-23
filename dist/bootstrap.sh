#!/bin/bash

echo "Creating project file..."
qmake -project -o duicontrolpanel.pro
echo "CONFIG += $1" >>duicontrolpanel.pro

cat duicontrolpanel.pro.in >>duicontrolpanel.pro

echo "Creating Makefile..."
qmake duicontrolpanel.pro

echo "Do not forget a \"make clean\" if you changed release/debug."

