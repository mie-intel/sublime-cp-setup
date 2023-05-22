#include "abc.h"

// you may find the definitions useful
const int OP_ZERO    = 0;  // f(OP_ZERO,    x0, x1) = 0
const int OP_NOR     = 1;  // f(OP_NOR,     x0, x1) = !(x0 || x1)
const int OP_GREATER = 2;  // f(OP_GREATER, x0, x1) = (x0 > x1)
const int OP_NOT_X1  = 3;  // f(OP_NOT_X1,  x0, x1) = !x1
const int OP_LESS    = 4;  // f(OP_LESS,    x0, x1) = (x0 < x1)
const int OP_NOT_X0  = 5;  // f(OP_NOT_X0,  x0, x1) = !x0
const int OP_XOR     = 6;  // f(OP_XOR,     x0, x1) = (x0 ^ x1)
const int OP_NAND    = 7;  // f(OP_NAND,    x0, x1) = !(x0 && x1)
const int OP_AND     = 8;  // f(OP_AND,     x0, x1) = (x0 && x1)
const int OP_EQUAL   = 9;  // f(OP_EQUAL,   x0, x1) = (x0 == x1)
const int OP_X0      = 10; // f(OP_X0,      x0, x1) = x0
const int OP_GEQ     = 11; // f(OP_GEQ,     x0, x1) = (x0 >= x1)
const int OP_X1      = 12; // f(OP_X1,      x0, x1) = x1
const int OP_LEQ     = 13; // f(OP_LEQ,     x0, x1) = (x0 <= x1)
const int OP_OR      = 14; // f(OP_OR,      x0, x1) = (x0 || x1)
const int OP_ONE     = 15; // f(OP_ONE,     x0, x1) = 1

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define fi first
#define se second

map <string, int> sender;
map <string, int> add;
const int mod = 65536;
vector <pair <string, string>> letter;

int pp;
// Alice
int // returns la
alice(
    /*  in */ const int n,
    /*  in */ const char names[][5],
    /*  in */ const unsigned short numbers[],
    /* out */ bool outputs_alice[]
) {
    pp = n;
    // outputs_alice[0] = 1;
    // outputs_alice[1] = 0;
    // for(int a = 0; a < n; ++a) sender[names[a]] = numbers[a];
    // for(auto [p, q] : sender){
    //     cout << p << " " << q << '\n';
    // }
    for(int a = 0; a < n; ++a) outputs_alice[a] = 0;
    return n;
}


// Bob
int // returns lb
bob(
    /*  in */ const int m,
    /*  in */ const char senders[][5],
    /*  in */ const char recipients[][5],
    /* out */ bool outputs_bob[]
) {
    for(int a = 0; a < 100; ++a) outputs_bob[a] = 0;
    // outputs_bob[0] = 1;
    // outputs_bob[1] = 1;
    // outputs_bob[2] = 0;
    return 100;
}


// Circuit
int // returns l
circuit(
    /*  in */ const int la,
    /*  in */ const int lb,
    /* out */ int operations[],
    /* out */ int operands[][2],
    /* out */ int outputs_circuit[][16]
) {
    int l = 100 + pp;
    for(int a = 0; a < 1; ++a){
        operations[a] = -1;
        operands[a][0] = operands[a][1] = -1;
    }
    // vector <int> final_results;
    for(int i = 0; i < pp; ++i)
        for(int j = 0; j < 16; ++j)
            outputs_circuit[i][j] = 0;
    return l;
}
