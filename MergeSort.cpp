﻿#include "graphics.h"
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#pragma comment(lib, "graphics.lib")
using namespace std;

// Kích thước hình chữ nhật và khoảng cách giữa các hình chữ nhật
const int RECT_WIDTH = 60; // Độ rộng hình chữ nhật
const int RECT_HEIGHT = 50; // Độ cao hình chữ nhật
const int RECT_GAP = 20; // Khoảng cách giữa các hình chữ nhật

// Hàm xóa màn hình để tránh chồng lấp
void xoaManHinh(int trai, int tren, int phai, int duoi) {
    setfillstyle(SOLID_FILL, BLACK);
    bar(trai, tren, phai, duoi);
}

// Hàm vẽ mảng
void veMang(int a[], int n, int trai, int tren, int phai, int duoi) {
    char giatri[10];
    char text[10];
    for (int i = 0; i < n; i++) {
        rectangle(trai, tren, phai, duoi);
        sprintf_s(giatri, sizeof(giatri), "%d", a[i]);
        double giatri_x = trai + (phai - trai) / 2 - textwidth(giatri) / 2;
        double giatri_y = tren + (duoi - tren) / 2 - textheight(giatri) / 2;
        outtextxy(giatri_x, giatri_y, giatri);
        sprintf_s(text, sizeof(text), "%d", i);
        int text_x = trai + (phai - trai) / 2 - textwidth(text) / 2;
        int text_y = duoi + 15;
        outtextxy(text_x, text_y, text);
        trai += (RECT_WIDTH + RECT_GAP);
        phai += (RECT_WIDTH + RECT_GAP);
    }
}

// Hàm tô màu các phần tử đã sắp xếp
void toMauDaSapXep(int trai, int tren, int phai, int duoi, int giatri) {
    char giatri_txt[10];
    sprintf_s(giatri_txt, sizeof(giatri_txt), "%d", giatri);
    double giatri_x = trai + (phai - trai) / 2 - textwidth(giatri_txt) / 2;
    double giatri_y = tren + (duoi - tren) / 2 - textheight(giatri_txt) / 2;
    setfillstyle(SOLID_FILL, GREEN);
    bar(trai, tren, phai, duoi);
    outtextxy(giatri_x, giatri_y, giatri_txt);
    rectangle(trai, tren, phai, duoi);
}

// Hàm tô màu các phần tử đang so sánh
void toMauDangSoSanh(int trai, int tren, int phai, int duoi, int giatri) {
    char giatri_txt[10];
    sprintf_s(giatri_txt, sizeof(giatri_txt), "%d", giatri);
    double giatri_x = trai + (phai - trai) / 2 - textwidth(giatri_txt) / 2;
    double giatri_y = tren + (duoi - tren) / 2 - textheight(giatri_txt) / 2;
    setfillstyle(SOLID_FILL, LIGHTBLUE);
    bar(trai, tren, phai, duoi);
    outtextxy(giatri_x, giatri_y, giatri_txt);
    rectangle(trai, tren, phai, duoi);
}

// Hàm tô màu các phần tử đang nhấp nháy
void highlightSubArray(int a[], int start, int end, int trai, int tren) {
    for (int i = 0; i < 3; i++) {  // Nhấp nháy 3 lần
        for (int j = start; j <= end; j++) {
            toMauDangSoSanh(trai + j * (RECT_WIDTH + RECT_GAP), tren,
                trai + j * (RECT_WIDTH + RECT_GAP) + RECT_WIDTH,
                tren + RECT_HEIGHT, a[j]);
        }
        delay(300);
        for (int j = start; j <= end; j++) {
            xoaManHinh(trai + j * (RECT_WIDTH + RECT_GAP), tren,
                trai + j * (RECT_WIDTH + RECT_GAP) + RECT_WIDTH,
                tren + RECT_HEIGHT);
            rectangle(trai + j * (RECT_WIDTH + RECT_GAP), tren,
                trai + j * (RECT_WIDTH + RECT_GAP) + RECT_WIDTH,
                tren + RECT_HEIGHT);
            char giatri[10];
            sprintf_s(giatri, sizeof(giatri), "%d", a[j]);
            double giatri_x = trai + j * (RECT_WIDTH + RECT_GAP) + RECT_WIDTH / 2 - textwidth(giatri) / 2;
            double giatri_y = tren + RECT_HEIGHT / 2 - textheight(giatri) / 2;
            outtextxy(giatri_x, giatri_y, giatri);
        }
        delay(300);
    }
}

// Hàm hiển thị mảng con đang được hợp nhất
void hienThiMangCon(int a[], int low, int mid, int high, int trai, int tren) {
    int trai1 = trai;
    int trai2 = trai + (mid - low + 1) * (RECT_WIDTH + RECT_GAP);
    for (int i = low; i <= mid; i++) {
        toMauDangSoSanh(trai1, tren, trai1 + RECT_WIDTH, tren + RECT_HEIGHT, a[i]);
        trai1 += (RECT_WIDTH + RECT_GAP);
    }
    for (int i = mid + 1; i <= high; i++) {
        toMauDangSoSanh(trai2, tren, trai2 + RECT_WIDTH, tren + RECT_HEIGHT, a[i]);
        trai2 += (RECT_WIDTH + RECT_GAP);
    }
    delay(1000);
}

// Hàm hợp nhất các phần tử
void merge(int a[], int l, int m, int r, bool ascending) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = a[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = a[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if ((ascending && L[i] <= R[j]) || (!ascending && L[i] >= R[j])) {
            a[k] = L[i++];
        }
        else {
            a[k] = R[j++];
        }
        k++;
        delay(500);
    }

    while (i < n1) {
        a[k++] = L[i++];
    }

    while (j < n2) {
        a[k++] = R[j++];
    }

    delete[] L;
    delete[] R;

    // Xóa màn hình trước khi vẽ lại mảng
    xoaManHinh(50 + l * (RECT_WIDTH + RECT_GAP), 100, 50 + r * (RECT_WIDTH + RECT_GAP) + RECT_WIDTH, 150);

    // Vẽ lại mảng sau khi hợp nhất
    veMang(a, r - l + 1, 50 + l * (RECT_WIDTH + RECT_GAP), 100, 50 + l * (RECT_WIDTH + RECT_GAP) + RECT_WIDTH, 150);
    for (int i = l; i <= r; i++) {
        toMauDaSapXep(50 + i * (RECT_WIDTH + RECT_GAP), 100, 50 + i * (RECT_WIDTH + RECT_GAP) + RECT_WIDTH, 150, a[i]);
    }
    delay(1000);
}

// Hàm thực hiện thuật toán merge sort
void mergeSort(int a[], int l, int r, bool ascending) {
    if (l < r) {
        int m = l + (r - l) / 2;

        // Nhấp nháy phần tử mảng con
        highlightSubArray(a, l, m, 50, 100);
        highlightSubArray(a, m + 1, r, 50, 100);

        mergeSort(a, l, m, ascending);
        mergeSort(a, m + 1, r, ascending);

        hienThiMangCon(a, l, m, r, 50 + l * (RECT_WIDTH + RECT_GAP), 100);
        merge(a, l, m, r, ascending);
    }
}

int main() {
    // Điều chỉnh kích thước cửa sổ dựa trên số phần tử
    int windowWidth = 800; // Độ rộng cửa sổ
    int windowHeight = 500; // Độ cao cửa sổ

    initwindow(windowWidth, windowHeight, "Chương trình Merge Sort");
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    char vanban[] = "Merge Sort";
    outtextxy(350, 50, vanban);

    const int n = 8;
    int a[n] = {};
    srand(time(0));
    for (int i = 0; i < n; i++) {
        a[i] = rand() % 50;
    }

    veMang(a, n, 50, 100, 50 + RECT_WIDTH, 150);
    cout << "Sap xep tang dan hay giam dan ? " << endl;
    cout << "1. Tang dan" << endl;
    cout << "2. Giam dan" << endl;
    cout << "Lua chon : ";
    int luachon;
    bool flag=false;
    cin >> luachon;
    if (luachon == 1)
    {
        flag == true;
    }
    mergeSort(a, 0, n - 1, flag);
    system("pause");
    closegraph();
    return 0;
}
