#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <deque>
#include <bitset>
#include <iterator>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <utility>
#include <limits>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

void printBoard(vector<vector<int>> board)
{
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0) {
            cout << "-----------" << "\n";
        }
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0 && j != 0) {
                cout << "|";
            }
            if (board[i][j] == 0) {
                cout << "_";
            }
            else {
                cout << board[i][j];
            }
        }
        cout << "\n";
    }
    cout << "-----------" << "\n";
}
bool checkFull(vector<vector<int>> board)
{
    bool flag = true;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (board[i][j] == 0)
            {
                flag = false;
                break;
            }
        }
        if (!flag) {break;}
    }
    return flag;
}
vector<bool> resetCheck(vector<bool> checker)
{
    for (int i = 0; i < checker.size(); i++)
    {
        checker[i] = true;
    }
    return checker;
}
bool checkValid(vector<vector<int>> board)
{
    // ! May be inefficient C++ code.
    // TODO: Improve with Pointers.
    vector<bool> checker(10), vhecker(10), shecker(10);
    vhecker = resetCheck(vhecker);
    checker = resetCheck(checker);
    shecker = resetCheck(shecker);
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j< 9; j++)
        {
            if (board[i][j] != 0) {
                if (checker[board[i][j]]) {checker[board[i][j]] = false; } 
                else { return false; }
            }
            if (board[j][i] != 0) {
                if (vhecker[board[j][i]]) {vhecker[board[j][i]] = false; } 
                else { return false; }
            }
            if (i % 3 == 0 && j % 3 == 0)
            {
                // Start shecker
                for (int iX = i; iX < i + 3; iX++)
                {
                    for (int jX = j; jX < j+3; jX++)
                    {
                        if (board[iX][jX] != 0){
                            if (shecker[board[iX][jX]]) {shecker[board[iX][jX]] = false;}
                            else {return false; }
                        }
                    }
                }
                shecker = resetCheck(shecker);
            }
        }
        checker = resetCheck(checker);
        vhecker = resetCheck(vhecker);
    }
    return true;
}
vector<int> incPair(vector<int> pair)
{
    pair[1] += 1;
    if (pair[1] > 8)
    {
        pair[1] = 0;
        pair[0] += 1;
    }
    return pair;
}

vector<vector<int>> solve(vector<vector<int>> board, vector<int> pairState)
{
    vector<vector<int>> neg = {{-1}};
    if (checkValid(board))
    {
        if (checkFull(board)) {return board;}
    }
    else 
    {
        return neg;
    }

    vector<vector<vector<int>>> passedBoards;
    vector<vector<int>> tempHolder;
    if (board[pairState[0]][pairState[1]] == 0)
    {
        for (int i = 1; i < 10; i++)
        {
            tempHolder = board;
            tempHolder[pairState[0]][pairState[1]] = i;
            passedBoards.push_back(solve(tempHolder,incPair(pairState)));
        }
        for (int i = 0; i < passedBoards.size(); i ++)
        {
            if (passedBoards[i] != neg)
            {
                return passedBoards[i];
            }
        }
        return neg;
    }
    else
    {
        return solve(board, incPair(pairState));
    }
    return neg;
}


int main()
{
    clock_t start;
    double duration;
    vector<vector<int>> board(9);
    vector<int> curRow(9);
    int cur;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cin >> cur;
            curRow[j] = cur;
        }
        board[i] = curRow;
    }
    cout << "----------------" << "\n";
    vector<int> pair = {0,0};
    start = clock();

    printBoard(solve(board,pair));

    duration = (clock() - start ) / (double) CLOCKS_PER_SEC;
    cout<< "Time: "<< duration <<'\n';
}
