/*
 是否熟悉POSIX多线程编程技术？如熟悉，编写程序完成如下功能：
  1）有一int型全局变量g_Flag初始值为0；
  2）在主线称中起动线程1，打印“this is thread1”，并将g_Flag设置为1
  3）在主线称中启动线程2，打印“this is thread2”，并将g_Flag设置为2
  4）线程序1需要在线程2退出后才能退出
  5）主线程在检测到g_Flag从1变为2，或者从2变为1的时候退出
   */

#include <stdlib.h>//为了使用exit函数
#include <stdio.h>
#include <pthread.h>

pthread_t tid1, tid2;//线程的ID号
int g_Flag = 0;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;//初始化互斥锁
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;//初始化条件变量
void* thread1(void *);//线程1
void* thread2(void *);//线程2

int main(void)
{
//	pthread_t tid1, tid2;//线程的ID号
                             //不写在这里是因为tid2要在thread1()子函数中使用，所以要设为全局变量

	if(pthread_create(&tid2, NULL, thread2, NULL) != 0)//开线程2
		return -2;
	if(pthread_create(&tid1, NULL, thread1, &tid2) != 0)//开线程1
		return -1;

	pthread_cond_wait(&cond, &mutex);//等待条件变量满足（即第五个条件）
	exit(0);
}

void* thread1(void *arg)
{
	printf("this is thread1\n");
	pthread_mutex_lock(&mutex);//获取互斥锁
	if(g_Flag == 2)
		pthread_cond_signal(&cond);//2->1，发出条件变量满足信号
	g_Flag = 1;	
	pthread_mutex_unlock(&mutex);//释放互斥锁
	pthread_join(tid2, NULL);//等待线程2退出后，再退出线程1
	pthread_exit(0);
}

void* thread2(void *arg)
{
	printf("this is thread2\n");
	pthread_mutex_lock(&mutex);
	if(g_Flag == 1)
		pthread_cond_signal(&cond);
	g_Flag = 2;
	pthread_mutex_unlock(&mutex);
	pthread_exit(0);
}
