﻿#include "graphics.h"
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#pragma comment(lib, "graphics.lib")
using namespace std;

// Hàm vẽ mảng
void veMang(int a[], int n, int trai, int tren, int phai, int duoi) {
    char giatri[10];
    char text[10];
    for (int i = 0; i < n; i++) {
        rectangle(trai, tren, phai, duoi);
        sprintf_s(giatri, sizeof(giatri), "%d", a[i]);
        double giatri_x = trai + (phai - trai) / 2 - 5;
        double giatri_y = tren + (duoi - tren) / 2.5;
        outtextxy(giatri_x, giatri_y, giatri);
        sprintf_s(text, sizeof(text), "%d", i);
        int text_x = trai + (phai - trai) / 2 - 5;
        int text_y = duoi + 10;
        outtextxy(text_x, text_y, text);
        trai += 100;
        phai += 100;
    }
}

// Hàm nhấp nháy hình chữ nhật
void nhapNhayHinhChuNhat(int trai, int tren, int phai, int duoi, int giatri) {
    char giatri_txt[10];
    sprintf_s(giatri_txt, sizeof(giatri_txt), "%d", giatri);
    double giatri_x = trai + (phai - trai) / 2 - 5;
    double giatri_y = tren + (duoi - tren) / 2.5;

    for (int k = 0; k < 3; k++) {
        setfillstyle(SOLID_FILL, YELLOW);
        bar(trai, tren, phai, duoi);
        outtextxy(giatri_x, giatri_y, giatri_txt);
        rectangle(trai, tren, phai, duoi);
        delay(150);
        setfillstyle(SOLID_FILL, BLACK);
        bar(trai, tren, phai, duoi);
        outtextxy(giatri_x, giatri_y, giatri_txt);
        rectangle(trai, tren, phai, duoi);
        delay(150);
    }
}

// Hàm tô màu các phần tử đã sắp xếp
void toMauDaSapXep(int trai, int tren, int phai, int duoi, int giatri) {
    char giatri_txt[10];
    sprintf_s(giatri_txt, sizeof(giatri_txt), "%d", giatri);
    double giatri_x = trai + (phai - trai) / 2 - 5;
    double giatri_y = tren + (duoi - tren) / 2.5;
    setfillstyle(SOLID_FILL, GREEN);
    bar(trai, tren, phai, duoi);
    outtextxy(giatri_x, giatri_y, giatri_txt);
    rectangle(trai, tren, phai, duoi);
}

// Hàm tô màu các phần tử đang so sánh
void toMauDangSoSanh(int trai, int tren, int phai, int duoi, int giatri) {
    char giatri_txt[10];
    sprintf_s(giatri_txt, sizeof(giatri_txt), "%d", giatri);
    double giatri_x = trai + (phai - trai) / 2 - 5;
    double giatri_y = tren + (duoi - tren) / 2.5;
    setfillstyle(SOLID_FILL, RED);
    bar(trai, tren, phai, duoi);
    outtextxy(giatri_x, giatri_y, giatri_txt);
    rectangle(trai, tren, phai, duoi);
}

// Hàm thực hiện thuật toán sắp xếp chèn với minh họa
void sapXepChen(int a[], int n) {
    int trai = 50, tren = 100;
    int phai = 150, duoi = 150;
    char giatri[10];
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;

        // Làm nổi bật phần tử được chèn
        nhapNhayHinhChuNhat(50 + i * 100, tren, 150 + i * 100, duoi, key);

        while (j >= 0 && a[j] > key) {
            // Tô màu các phần tử đang so sánh
            toMauDangSoSanh(50 + j * 100, tren, 150 + j * 100, duoi, a[j]);
            toMauDangSoSanh(50 + (j + 1) * 100, tren, 150 + (j + 1) * 100, duoi, a[j + 1]);

            // Di chuyển các phần tử lớn hơn một vị trí về phía trước
            a[j + 1] = a[j];

            // Vẽ lại phần tử đã di chuyển
            setfillstyle(SOLID_FILL, BLACK);
            bar(50 + (j + 1) * 100, tren, 150 + (j + 1) * 100, duoi);
            sprintf_s(giatri, sizeof(giatri), "%d", a[j + 1]);
            double giatri_x = 50 + (j + 1) * 100 + (150 - 50) / 2 - 5;
            double giatri_y = tren + (duoi - tren) / 2.5;
            outtextxy(giatri_x, giatri_y, giatri);
            rectangle(50 + (j + 1) * 100, tren, 150 + (j + 1) * 100, duoi);

            j = j - 1;
            delay(500);
        }
        a[j + 1] = key;

        // Vẽ lại phần tử đã chèn vào đúng vị trí
        setfillstyle(SOLID_FILL, BLACK);
        bar(50 + (j + 1) * 100, tren, 150 + (j + 1) * 100, duoi);
        sprintf_s(giatri, sizeof(giatri), "%d", a[j + 1]);
        double giatri_x = 50 + (j + 1) * 100 + (150 - 50) / 2 - 5;
        double giatri_y = tren + (duoi - tren) / 2.5;
        outtextxy(giatri_x, giatri_y, giatri);
        rectangle(50 + (j + 1) * 100, tren, 150 + (j + 1) * 100, duoi);

        // Tô màu phần tử đã sắp xếp
        toMauDaSapXep(50 + (j + 1) * 100, tren, 150 + (j + 1) * 100, duoi, a[j + 1]);
        delay(500);
    }

    // Tô màu tất cả các phần tử đã sắp xếp
    for (int i = 0; i < n; i++) {
        toMauDaSapXep(50 + i * 100, tren, 150 + i * 100, duoi, a[i]);
    }
}

int main() {
    initwindow(1000, 500, "Chương trình sắp xếp chèn");
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    char vanban[] = "Minh họa sắp xếp chèn";
    outtextxy(350, 50, vanban);

    const int n = 8;
    int a[n] = {};
    srand(time(0));
    for (int i = 0; i < n; i++) {
        a[i] = rand() % 50;
    }

    veMang(a, n, 50, 100, 150, 150);

    sapXepChen(a, n);

    getch();
    closegraph();
    return 0;
}
