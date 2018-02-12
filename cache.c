#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include<time.h>
#define BLOCK_SIZE 32       //make this dynamic

struct cache_line
{	
	int tag;
	char block[BLOCK_SIZE];
};

struct mm_line
{
	char block[BLOCK_SIZE];
};



int main(){
    float mm,cache,line1;      //input the size of all these -> calculate n,m,b,t from these by dividing them by 2..
    int n,m,b,t,addr;       //n,b,m,t-no. of bits
    int i=0,hit=0,miss=0,h,h1;float dmr,sar;       //dmr-direct mapped ratio sar-set associative ratio
    //need an n bit address to be generated randomly in every loop -> better to take an arr   
    printf("Enter mm, cache, line size respectively ");
    scanf("%f %f %f",&mm,&cache,&line1);
    n=log(mm)/log(2);b=log(line1)/log(2);m=log(cache)/log(2);m-=b;t=n-m-b;
    int cache_size=pow(2,m);
    //struct cache_line *cl=NULL;
    //cl=(struct cache_line*)malloc(cache_size*sizeof(struct cache_line));
    int *tl=NULL;
    tl=(int *)malloc(cache_size*sizeof(int));   //tl-tag line
    printf("\nn-%d b-%d m-%d t-%d",n,b,m,t);
    for(i=0;i<cache_size;i++){      //initializing all with -1
        tl[i]=-1;
        //printf("%d",tl[i]);
    }
    
    
    srand(1);
    h=pow(2,m)-1;
    h1=pow(2,b)-1;      //or line1-1;
    for(i=0;i<10000;i++){
		addr = rand() % (int)mm ;
		int T  = addr >> (m+b);
	    int M = (addr >> b) & h;       //want last m bits of result of ( >> )
	    int B = addr & h1;
        
        if(tl[M]!=T){
            miss++;
            tl[M]=T;
        }
        else{
            hit++;
        }
		
	}
	printf("\n\nDirect Mapped Cache:");
    printf("\nhit-%d miss-%d",hit,miss);
	dmr=(float)hit/(float)miss;
	printf("\ndmr-%f",dmr);
	
	
	//set associative:
	m--;hit=0;miss=0;
	int *tl1=NULL;
    tl1=(int *)malloc(cache_size/2*sizeof(int));   //tl-tag line
    int *tl0=NULL;
    tl0=(int *)malloc(cache_size/2*sizeof(int));   //tl-tag line
    int *lru=NULL;
    lru=(int *)malloc(cache_size/2*sizeof(int));   //tl-tag line
    for(i=0;i<cache_size/2;i++){      //initializing all with -1
        tl0[i]=-1;
        //printf("%d",tl[i]);
    }
    for(i=0;i<cache_size/2;i++){      //initializing all with -1
        tl1[i]=-1;
        //printf("%d",tl[i]);
    }
    for(i=0;i<cache_size/2;i++){      //initializing all with -1
        lru[i]=0;
        //printf("%d",tl[i]);
    }
    
    printf("\n\nSet Associative Cache:");
    int L;
    h=pow(2,m)-1;
    h1=pow(2,b)-1;      //or line1-1;
    for(i=0;i<10000;i++){
		addr = rand() % (int)mm ;
		int T  = addr >> (m+b);
	    int M = (addr >> b) & h;       //want last m bits of result of ( >> )
	    int B = addr & h1;
        
        if(tl0[M]==T){
            hit++;
        }
        else if(tl1[M]==T){
            hit++;
        }
        else if(tl0[M]!=T){
            if(tl1[M]!=T){
                miss++;
                L=lru[M];
                if(L==0){
                    tl0[M]=T;
                }
                else{
                    tl1[M]=T;
                }
                lru[M]=~L;
            }
        }
        
	}
	printf("\nhit-%d miss-%d",hit,miss);
	sar=(float)hit/(float)miss;
	printf("\nsar-%f\n",sar);
	
}