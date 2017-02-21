#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <time.h>
#include <assert.h>

#define glib_log_file_path "/root/gib_test.txt"
static FILE *g_glib_log_file = NULL;
static void log_init(void)
{
	g_glib_log_file = fopen(glib_log_file_path, "awt");
	return;
}

#define PRITN_LOG(format, ...) \
		do {\
			if(NULL == g_glib_log_file)\
			{\
				log_init();\
			}\
			if (1)\
				{\
				char janus_log_ts[64] = ""; \
				char janus_log_src[128] = ""; \
				if (1) { \
					struct tm janustmresult; \
					time_t janusltime = time(NULL); \
					localtime_r(&janusltime, &janustmresult); \
					strftime(janus_log_ts, sizeof(janus_log_ts), \
							 "[%a %b %e %T %Y] ", &janustmresult); \
				} \
					snprintf(janus_log_src, sizeof(janus_log_src), \
							  "[%s:%s:%d] ",__FILE__,__FUNCTION__,__LINE__); \
				fprintf(g_glib_log_file,"%s%s" format, \
					janus_log_ts, \
					janus_log_src, \
##__VA_ARGS__); \
				fflush(g_glib_log_file);\
}\
		} while (0)
		
#define TIMES 1
static void free_data(gpointer hash_data)
{
    g_free(hash_data);
    hash_data = NULL;
}


void print_key_value(gpointer key, gpointer value ,gpointer user_data)
{
    PRITN_LOG("%4s -------------------->%s\n",(char*)key,(char*)value);
}

int hash_test_2()
{
     GHashTable* dictionary = NULL;
     PRITN_LOG("start\n");
     dictionary = g_hash_table_new_full(g_str_hash,g_str_equal,free_data,free_data);
  
     if(dictionary == NULL)
     {
         fprintf(stderr,"create hash table failed\n");
         return -1;
     }

     srandom(time(NULL));

     int i = 0;
     int ret = 0;
     char key[64] ;
     char value[64] ;
     for(i = 0; i< TIMES;i++)
     {
         snprintf(key,sizeof(key),"%d",i);
         snprintf(value,sizeof(value), "%d", random());
         
         char* key_in_hash = strdup(key);
         char* value_in_hash = strdup(value);

         if( value_in_hash == NULL || key_in_hash == NULL)
         {
             ret = -2;
             PRITN_LOG("key or value malloc failed\n");
             goto exit;
         }

	#if 0
         if(strcmp(key_in_hash,"10") == 0)
         {
             printf("before insert key(10) address(%p) : value(%s) address(%p)\n",key_in_hash,value_in_hash,value_in_hash);
         }
	 #endif
         g_hash_table_insert(dictionary, key_in_hash,value_in_hash);

     }

    g_hash_table_foreach(dictionary,print_key_value,NULL);
    PRITN_LOG("there are %d records in dictory\n",(unsigned int) g_hash_table_size(dictionary));


#if 0
    char* key_10 = NULL;
    char* value_10 = NULL; 
    ret = g_hash_table_lookup_extended(dictionary,"10",(void **)&key_10, (void **)&value_10);
    if(ret==FALSE)
    {
        fprintf(stderr, "can not the key 10\n");
        goto exit;
    }
    else
    {
        fprintf(stderr,"In dictionary, key(%s) address(%p) : value (%s) address(%p)\n",key_10,key_10,value_10,value_10);
    }

    char* key_10_new = strdup("10");
    char* value_10_new = strdup("new 10 value");

    g_hash_table_replace(dictionary,key_10_new,value_10_new);


    ret = g_hash_table_lookup_extended(dictionary,"10",(void **)&key_10,(void**)&value_10);
    if(ret == FALSE)
    {
        fprintf(stderr, "found failed after modify\n");
        
    }
    else
        printf("After replace In dictionary, key(%s) address(%p) : value (%s) address(%p)\n",key_10,key_10,value_10,value_10);
    
    g_hash_table_remove(dictionary,"10");
    value_10 = g_hash_table_lookup(dictionary,"10");
    assert(value_10 == NULL);
#endif
    ret = 0;
exit:
    g_hash_table_destroy(dictionary);
    return ret;
}

int main()
{
     hash_test_2();
}
