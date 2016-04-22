/*
 * File_test.cc -- 
 *
 * Authors:
 *     shuidu(942838030@qq.com), 2016年04月21日 20时29分05秒
 *
 */

#include "File.h"

using namespace Common;
using namespace std;

int main(int argc, char *argv[])
{
    File file("./test.h");
    file.Append("asd", 4);
    cout << file.WrittenBytes() <<endl;
    return 0;
}
