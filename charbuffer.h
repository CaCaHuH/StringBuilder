#pragma once
#define _BUFFER_SIZE_ 500

struct CharBuffer                           // Структура буфера для char
{
    char array[_BUFFER_SIZE_];              // Массив char
    int index;                              // Индекс в текущем буфере
    CharBuffer* nextBuffer;                 // Указатель на следующий буфер
    CharBuffer* previousBuffer;             // Указатель на предыдущий буфер

    CharBuffer();                           // Конструктор

    void Add(char symbol);                  // Метод добавления символа
};

