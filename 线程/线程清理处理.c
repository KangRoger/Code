#include<pthread.h>
void cleanup(void *arg)
{
	printf("cleanup:%s\n",(char *)arg);
}
void* thr_fn1(void *arg)
{
	printf("thread 1 start\n");
	pthread_cleanup_push(cleanup,"thread 1 first handler");
	pthread_cleanup_push(cleanup,"thread 1 second handler");
	printf("thread 1 push complete\n");
	
	if(arg)
		pthread_exit((void*)1);
	
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
		pthread_exit((void*)1);
}

void* thr_fn2(void *arg)
{
	printf("thread 2 start\n");
	pthread_cleanup_push(cleanup,"thread 2 first handler");
	pthread_cleanup_push(cleanup,"thread 2 second handler");
	printf("thread 2 push complete\n");
	
	if(arg)
		return (void*)2;
	
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	return (void*)2;
}

int main(void)
{
	pthread_t tid1, tid2;
	void *tret;
	
	pthread_create(&tid1,NULL,thr_fn1, (void *)1);//创建线程1
	pthread_create(&tid2,NULL,thr_fn2, (void *)1);//创建线程2
	
	//获取线程退出状态
	pthread_join(tid1, &tret);//阻塞，直到线程1退出
	printf("thread 1 exit code %d\n", (int)tret);//直接把指针转换为int
	
	pthread_join(tid2, &tret);//阻塞，直到线程2退出
	printf("thread 2 exit code %d\n", (int)tret);
	
	exit(0);
}
