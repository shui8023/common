#!/bin/bash  
#
# complier.sh -- 
# 
# Authors: 
#     shuidu(942838030@qq.com)  2016年04月20日  11:21


sed -i 's/aaaaaa/'"$1"'/' Makefile
make
sed -i 's/'"$1"'/aaaaaa/' Makefile
