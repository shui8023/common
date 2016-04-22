/*
 * Buffer_test.cc -- 
 *
 * Authors:
 *     shuidu(942838030@qq.com), 2016年04月21日 11时33分15秒
 *
 */

#include "Buffer.h"
#include <iostream>

using namespace std;
using namespace Common;
const int a = 1024;

int main(int argc, char *argv[])
{
    Buffer<a> buffer;
    Buffer<a> buff;
    buffer.Append("asdasd", 6);
    buff = buffer;
    Buffer<a> buffe(buffer);
    cout << buffer.Data() << endl;
    cout << buff.Data() << endl;
    cout << buffe.Data() << endl;
    cout << buffer.Current() << endl;
    cout << buffer.GetSize() << endl;
    cout << buffer.GetLength() << endl;
    cout << buffer.Data() << endl;
    cout << buffer.GetLength() << endl;
    cout << buffer.Avail() << endl;
    buffer.Append("asd", 4);
    string str = buffer.ToString();
    cout << buffer.Data() << endl;
    cout << str << endl;
    return 0;
}
