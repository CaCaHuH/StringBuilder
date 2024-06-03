#include "stringbuilder.h"

void StringBuilder::FreeMemory()                                // Метод высвобождения памяти
{
    while (lastBuffer->previousBuffer != 0)                     // Цикл по буферам начиная с конца
    {
        lastBuffer = lastBuffer->previousBuffer;                // Переход к более раннему буферу
        delete lastBuffer->nextBuffer;                          // Высвобождение буфера от которого только что перешли
    }
    delete lastBuffer;                                          // Высвобождение последнего буфера
}

void StringBuilder::CreateNewBuffer()                           // Метод создания нового буфера
{
    if (lastBuffer->nextBuffer == 0)                            // Если указатель на следующий буфер равен нулю (буфер не выделен)
    {
        CharBuffer* buffer = new CharBuffer();                  // Выделяется новый буфер
        lastBuffer->nextBuffer = buffer;                        // Устанавливаются указатели
        buffer->previousBuffer = lastBuffer;                    // Устанавливаются указатели
        lastBuffer = buffer;                                    // Последним устанавливается только что выделенный буфер
    }
    else                                                        // Если следующий буфер уже выделен
    {
        lastBuffer = lastBuffer->nextBuffer;                    // Простой переход к следующему буферу
    }
}

StringBuilder::StringBuilder()                                  // Конструктор
{
    firstBuffer = new CharBuffer();                             // Выделяется начальный буфер
    lastBuffer = firstBuffer;                                   // Последний равен первому, т.к. буфер один
    lastBuffer->array[0] = '\0';                                // Первым элементом устанавливается символ окончания строки
    length = 0;                                                 // Сумма символов равна нулю
}

StringBuilder::~StringBuilder()                                 // Деструктор
{
    FreeMemory();                                               // Вызывается метод высвобождения памяти
}

void StringBuilder::Clear()                                     // Метод очистки билдера без высвобождения памяти
{
    length = 0;                                                 // Общая длина устанавливается в ноль
    while (lastBuffer->previousBuffer != 0)                     // Цикл по всем буферам, начиная с конца
    {
        lastBuffer = lastBuffer->previousBuffer;                // Переход к более раннему буферу
        lastBuffer->nextBuffer->index = 0;                      // Индекс буфера от которого только что перешли устанавливается в ноль
        lastBuffer->nextBuffer->array[0] = '\0';                // В начало буфера от которого только что перешли устанавливается символ окончания строки
    }
    lastBuffer->array[0] = '\0';                                // В последний буфер устанавливается символ окончания строки
    lastBuffer->index = 0;                                      // В индекс последнего буфера записывается ноль
}

int StringBuilder::Length()                                     // Метод, возвращающий длину билдера
{
    return length;
}

void StringBuilder::AppEnd(const char* string)                  // Метод добавления строки в билдер
{
    int sizeString = 0;                                         // Переменная длины строки
    while (string[sizeString] != '\0') sizeString++;            // Вычисление длины строки: двигаемся, пока не найдем символ окончания строки

    for (int i = 0; i < sizeString; i++)                        // Цикл по длине строки
    {
        if (lastBuffer->index == _BUFFER_SIZE_)                 // Если индекс последнего буфера равен размеру буфера
            CreateNewBuffer();                                  // Создается новый буфер
        lastBuffer->Add(string[i]);                             // Символ добавляется в буфер
        length++;                                               // Увеличивается длина билдера
    }
    if (lastBuffer->index == _BUFFER_SIZE_)                     // Если индекс последнего буфера равен размеру буфера
        CreateNewBuffer();                                      // Создается новый буфер
    lastBuffer->Add('\0');                                      // Устанавливается символ окончания строки
    lastBuffer->index--;                                        // Индекс уменьшается на 1, т.к символ окончания строки не является "реальным" символом
}

void StringBuilder::AppEnd(int number)                          // Добавление int в билдер
{
    char string[50];                                            // Выделяется массив char
    for (int i = 0; i < 50; i++)                                // Проходим по массиву
        string[i] = 0;                                          // Зануляем
    sprintf_s(string, 50, "%i", number);                        // Преобразуем int в массив char
    AppEnd(string);                                             // Добавляем этот массив в билдер
}

void StringBuilder::AppEnd(double number)                       // Добавление double в билдер
{
    char string[50];                                            // Выделяется массив char
    for (int i = 0; i < 50; i++)                                // Проходим по массиву
        string[i] = 0;                                          // Зануляем
    sprintf_s(string, 50, "%1.10f", number);                    // Преобразуем double в массив char
    AppEnd(string);                                             // Добавляем этот массив в билдер
}

void StringBuilder::AppEnd(bool value)                          // Добавление bool в билдер
{
    AppEnd(value ? "true" : "false");
}

char* StringBuilder::Build()                                    // Построение из билдера стандартной строки в виде массива char
{
    char* result = new char[length + 1];                        // Выделяется память под результирующую строку
    CharBuffer* buffer = firstBuffer;                           // Копируется указатель на первый буфер
    for (int i = 0; i < length; i++)                            // Цикл по количеству символов в билдере
    {
        if (i != 0 && i % _BUFFER_SIZE_ == 0)                   // Если индекс будет кратным размеру буфера
            buffer = buffer->nextBuffer;                        // Осуществляется переход к следующему буферу
        result[i] = buffer->array[i % _BUFFER_SIZE_];           // Копирование символов из буфера в результирующую строку
    }
    result[length] = '\0';                                      // Запись в конец строки символа конца строки
    return result;                                              // Возвращение реузльтирующей строки
}

char* StringBuilder::CopyString(const char *string)             // Статическая функция копирования строки
{
    int sizeString = 0;                                         // Переменная длины строки
    while (string[sizeString] != '\0') sizeString++;            // Вычисление длины строки: двигаемся, пока не найдем символ окончания строки
    char* copy = new char[sizeString + 1];                      // Выделение памяти под копию строки
    for (int i = 0; i < sizeString; i++)                        // Цикл для копирования строки
        copy[i] = string[i];
    copy[sizeString] = '\0';                                    // Установка символа окончания строки
    return copy;                                                // Возвращаем копию строки
}
