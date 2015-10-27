#Specify the version being used aswell as the language
cmake_minimum_required(VERSION 2.6)

#Name your project here
project(maze)

#Sends the -std=c11 flag to the gcc compiler
add_definitions(-std=c++0x)

add_executable(maze main.c++)
