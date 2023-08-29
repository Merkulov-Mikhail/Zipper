struct StringPosition
{
    int offset;
    int length;
};


/*!
    Содержит одну запись алгоритма LZ77
    \ref StringPosition описывает, насколько надо вернуться по строке назад и сколько символов скопировать
    next - следующий символ после "вставленных" элементов
*/
struct Node
{
    struct StringPosition* position;
    char next;
};

/*!
    Функция сжатия строки по алгоритму LZ77

    @param[in] str -> Строка, которую необходимо сжать

    @return массив указателей на структуру \ref Node.

*/
struct Node* encodeLZ77(const char* str);

void findPrefix(const char* haystack, const char* needle, StringPosition* StrPos, int n);
