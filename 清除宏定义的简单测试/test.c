/*
 * Author: Zhao Shulin
 * Date: 2014/06/08
 * 这是一个简单的有关C语言宏定义的操作模板。
*/

// 最简单的宏定义：
# define TRUE 1

//取消上述宏定义：
# undef TRUE

//最好不要重定义！

//可以使用ifndef命令来避免重定义：
# ifndef TRUE
# define TRUE 1
# endif
