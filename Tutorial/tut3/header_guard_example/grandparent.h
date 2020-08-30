// Demo the use of header guards
// Credit: https://en.wikipedia.org/wiki/Include_guard
// Written by Dylan Blecher, June 2020
// d.blecher@unsw.edu.au

struct foo {
    int member;
};












// scroll down for fixed version :)






















#ifndef GRANDPARENT_H
#define GRANDPARENT_H

struct foo {
    int member;
};

#endif /* GRANDPARENT_H */