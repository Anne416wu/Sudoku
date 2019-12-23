//
// Created by Anne Wu on 12/23/19.
//
#pragma once
#ifndef SUDOKU_GENERATOR_H
#define SUDOKU_GENERATOR_H

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<algorithm>
#include<time.h>
using namespace std;

#define SUDOKUPATH  "sudoku.txt"
#define QUESPATH "ques.txt"
#define SOLUTIONPATH "solution.txt"
#define BASEPATH "sudokubase.txt"
#define GENERATEPATH "generation.txt"
#define MAX 200000000
static char AbsolutePath[100] = { 0 };
static char ques_board[10][20];


extern void sudoku_generate(int n);
extern void ques_generate(int ques_num);


#endif //SUDOKU_GENERATOR_H
