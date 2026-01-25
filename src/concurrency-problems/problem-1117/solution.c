/*
												1117. Building H2O

There are two kinds of threads: oxygen and hydrogen. Your goal is to group these threads to form water molecules.

There is a barrier where each thread has to wait until a complete molecule can be formed. 
Hydrogen and oxygen threads will be given releaseHydrogen and releaseOxygen methods respectively, which will allow them to pass the barrier. 
These threads should pass the barrier in groups of three, and they must immediately bond with each other to form a water molecule. 
You must guarantee that all the threads from one molecule bond before any other threads from the next molecule do.

In other words:

If an oxygen thread arrives at the barrier when no hydrogen threads are present, it must wait for two hydrogen threads.
If a hydrogen thread arrives at the barrier when no other threads are present, it must wait for an oxygen thread and another hydrogen thread.
We do not have to worry about matching the threads up explicitly; the threads do not necessarily know which other threads they are paired up with. 
The key is that threads pass the barriers in complete sets; thus, if we examine the sequence of threads that bind and divide them into groups of three, 
each group should contain one oxygen and two hydrogen threads.

Write synchronization code for oxygen and hydrogen molecules that enforces these constraints.

*/

typedef struct 
{
    size_t hydrogen_cnt;
    pthread_mutex_t mutex;
    pthread_cond_t cond;

} H2O;

void releaseHydrogen();

void releaseOxygen();

H2O* h2oCreate() 
{
    H2O *obj = (H2O*) malloc(sizeof(H2O));

    if (obj == NULL)
    {
        fprintf(stderr, "Could not allocate memory for new object!\n");
        return NULL;
    }

    obj->hydrogen_cnt = 0;

    if (pthread_mutex_init(&(obj->mutex), NULL) != 0) 
    {
		fprintf(stderr, "Could not init the mutex!\n");
		return NULL;
	}

    if (pthread_cond_init(&(obj->cond), NULL) != 0) 
    {
		pthread_mutex_destroy(&(obj->mutex));
        fprintf(stderr, "Could not init the condition!\n");
		return NULL;
	}

    return obj;
}

void hydrogen(H2O *obj) 
{
    if (obj == NULL)
        return;

    pthread_mutex_lock(&(obj->mutex));

	while (obj->hydrogen_cnt >= 2)
		pthread_cond_wait(&(obj->cond), &(obj->mutex));

    releaseHydrogen();

    obj->hydrogen_cnt += 1;

    pthread_cond_broadcast(&(obj->cond));
    pthread_mutex_unlock(&(obj->mutex));
}

void oxygen(H2O *obj) 
{
    if (obj == NULL)
        return;

    pthread_mutex_lock(&(obj->mutex));

	while (obj->hydrogen_cnt < 2)
		pthread_cond_wait(&(obj->cond), &(obj->mutex));

    releaseOxygen();

    obj->hydrogen_cnt = 0;

    pthread_cond_broadcast(&(obj->cond));
    pthread_mutex_unlock(&(obj->mutex));
}

void h2oFree(H2O *obj) 
{
    if (obj == NULL)
        return;

    if (pthread_mutex_destroy(&(obj->mutex)) != 0) 
    {
		fprintf(stderr, "Could not destroy mutex!\n");
        return;
	}

    if (pthread_cond_destroy(&(obj->cond)) != 0) 
    {
		fprintf(stderr, "Could not destroy condition!\n");
        return;	
	}
}