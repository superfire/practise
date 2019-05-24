#include <stdio.h>
#include <assert.h>
#include <string.h>

void swap( char *pc1, char *pc2 )
{
    *pc1 = *pc1 + *pc2;
    *pc2 = *pc1 - *pc2;
    *pc1 = *pc1 - *pc2;
}

int is_special( char ch )
{
    if( ( ( ch >= 'a' ) && ( ch <= 'z' ) ) || \
	    ( ( ch >= 'A' ) && ( ch <= 'Z' ) ) )
	    return 1;
	else 
	    return 0;
}

void revert( char *src, char *dst, size_t size_dst )
{
    assert( src != NULL );
    assert( dst != NULL );
	assert( size_dst > strlen(src) );

	char *pcl, *pcr;

//	strncpy( dst, src, strlen( src ) );
    memmove( dst, src, strlen(src)+1 );

	pcl = dst;
	pcr = dst + strlen(dst) - 1;
	printf("\r\npcl:%p\r\npcr:%p\r\n", pcl, pcr);

#if 0
	while( pcl <= pcr )
	{
	    if( is_special( *pcl ) )
		{
//		    while( ( ( !is_special( *pcr ) ) ) && ( pcl >= pcr ) )
		    while( pcl <= pcr )
			{
			    if( is_special( *pcr ) )
				{
				    printf("\r\ntrue:%c\r\n", *pcr);
				    break;
				}

			    pcr --;
			}
			if( pcl >= pcr )
			    return;

			printf("%c, %c\n", *pcl, *pcr);
			swap( pcl, pcr );
			pcr --;
			pcl ++;
		}
		else
		    pcl ++;
	}
#endif

	while( pcl < pcr )
	{
	    if( !is_special( *pcl ) )
		    pcl ++;
	    if( !is_special( *pcr ) )
		    pcr --;
		if( ( is_special( *pcl ) ) && ( is_special( *pcr ) ) )
		{
		    swap( pcl, pcr );
		    pcl ++;
		    pcr --;
		}
	}

}

void main(void)
{
    char *src = "123ab4d5e6c678ijkt6x7y9z658";
	char dst[100] = {0};
	printf("\r\nsrc:%s\r\ndst:%s\n", src, dst);
	revert( src, dst, 100 );
	printf("\r\nsrc:%s\r\ndst:%s\n", src, dst);
}


/*
思路：

23ab4d5e6c678ijkt6x7y9z658

1.针对 char *str定义的字符串，是无法直接交换的，因为这样定义的字符串保存在常量区，是无法直接更改的，所以设计接口的时候，考虑使用一个新的缓冲区，保存交换后的结果
2.关于交换：
  定义2个指针，一个指向字符串第一个字符，pcl，另一个指向字符串最后一个字符，pcr
  pcl向右移动，寻找第一个特殊字符，找到后停止
  pcr向左移动，寻找第一个特殊字符，找到后停止
  当两边都找到特殊字符后，交换两个字符的位置，然后pcl继续相右移动，pcr继续向左移动
  直到pcl >= pcr停止
    - 这里需要注意，停止的条件为pcl>=pcr,因为当两者相等的时候不需要再交换了


错误的思路：
这是一道CSG的面试题，给15分钟做完。
记得刚开始的思路是，让pcl保持不动，然后pcr向左移动，找到特殊字符后，判断pcl和pcr都是特殊字符，然后交换,交换后pcl右移一位，pcr从字符串末尾重新开始，否则，直到pcr<=pcl截至，然后pcl向右移动一个位置，然后循环，程序如下


while( pcl != '\0' )
{
   pcr = dst + strlen(dst) - 1; 

   while( pcr != pcl )
   {
       if( is_special( *pcl ) && is_special( *pcr ) )
	   {
	      swap( pcl, pcr );
		  break;
	   }

       pcr --;
   }

   pcl ++:
}

 - 这样做的后果就是会导致特殊字符重复交换，得不到预期的结果
 - 程序执行次数变多，效率降低

 比如：123abc123，输出的结果就是：123cab123，a和c交换后，b和a又交换了一次

 */
