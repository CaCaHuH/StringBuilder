#pragma once
#include <stdio.h>
#include "charbuffer.h"

class StringBuilder                                 // Класс стринг-билдера - построителя строк
{
    CharBuffer* firstBuffer;                        // Указатель на первый буфер
    CharBuffer* lastBuffer;                         // Указатель на второй буфер
    int length;                                     // Длина билдера

    void FreeMemory();                              // Метод высвобождения памяти

    void CreateNewBuffer();                         // Метод создания нового буфера

public:

    StringBuilder();                                // Конструктор

    ~StringBuilder();                               // Деструктор

    void Clear();                                   // Метод очистки билдера без высвобождения памяти

    int Length();                                   // Метод, возвращающий длину билдера

    void AppEnd(const char* string);                // Метод, осуществляющий добавление строки в билдер

    void AppEnd(int number);                        // Метод, осуществляющий добавление int в билдер

    void AppEnd(double number);                     // Метод, осуществляющий добавление double в билдер

    void AppEnd(bool value);                        // Метод, осуществляющий добавление bool в билдер

    char* Build();                                  // Построение из билдера стандартной строки в виде массива char

    static char* CopyString(const char* string);    // Статическая функция копирования строки
};
