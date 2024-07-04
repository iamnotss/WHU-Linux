    # include<unistd.h>  
    # include<stdlib.h>  
    # include<stdio.h>  
    # include<string.h>  
      
    void function(int a,int b,int c){  
           char buffer[8];  //声明一个类型为char的数组
            int *ret;    
            ret=(int*)(buffer+16);  
           (*ret)+=7;  
    }  
      
    int main(){  
       int x;  
       x=99999;  
       function(1,2,3);  
       x=1;  
       printf("%d\n",x);  
       return 0; 
    }  
