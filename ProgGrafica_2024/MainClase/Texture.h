//
// Created by Rodrigo on 13/04/2026.
//
#pragma once
#include "common.h"
using namespace std;

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;


}pixel_t;


class Texture {
    int w=0, h=0;
    string fileName = "";
    vector <pixel_t> rawImage;

    void updateTexture();
public:
    unsigned int GLid = 0xFFFFFFFF;

    Texture(int w, int h, pixel_t color={0xFF, 0, 0, 0xFF});
    Texture(string fileName);
};