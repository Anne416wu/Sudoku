//
// Created by Anne Wu on 12/23/19.
//
#pragma once
#ifndef SUDOKU_GENERATOR_H
#define SUDOKU_GENERATOR_H

#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<ctime>
#include <random>
#include<iostream>
using namespace std;

#define SUDOKUPATH  "sudoku.txt"
#define QUESPATH "ques.txt"

#define MAX 200000000
static char AbsolutePath[100] = { 0 };
static char ques_board[10][20];

extern void sudoku_generate(int n);
extern void ques_generate(int ques_num);
extern int check(int m, int n);
extern void settle(int pos);
extern void settle_ques();
extern void prune(int i, int j, bool point[10]);

#endif //SUDOKU_GENERATOR_H
