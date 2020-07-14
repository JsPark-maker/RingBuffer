#include <iostream>
#include <Windows.h>
#include "CRingBuffer.h"

CRingBuffer ringBuf;

int main() {
    char testBuf[] = "1234567890 abcdefghijklmnopqrstuvwxyz 1234567890 abcdefghijklmnopqrstuvwxyz 12345"; //총 81개 최대 인덱스 80
    char dest[82];
    char dest2[82];
    srand(3);
    int pos = 0;
    while (1)
    {   
        //pos = 40 , randSize = 80 , randSize = 49
        //최대 위치는 80 | 81이 되면 망함
        int randSize = rand() % 82; //이거는 복사할 사이즈이기때문에 인덱스랑은 관련없음
        int randSize2 = rand() % 82;
        if (randSize + pos > 80) //이거는 인덱스랑 관련이 있음
        {
            randSize = 81 - pos;
        }
        int inputSize = ringBuf.Enqueue((char*)testBuf + pos, randSize);
        ringBuf.Peek(dest2, randSize2);
        int retSize = ringBuf.Dequeue(dest, randSize2);
        dest[retSize] = '\0';
        if(!memcmp(dest, dest2, retSize))
        printf("%s", dest);
        pos += inputSize;
        if (pos > 80)
        {
            pos = 0;
        }
        Sleep(10);
    }
    return 0;
}


