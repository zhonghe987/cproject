#include<iostream>
#include<unistd.h>
#include<string>
//#include<curl/curl.h>
#include"oss_client/op_client.h"
using namespace std;

int main(int argc, char *argv[])
{
  int opt;
  extern char *optarg;
  string user;
  string http_base;
  while((opt = getopt(argc,argv,"u:h:"))!= -1){
       switch(opt){
         case 'u':
            user = optarg;
            break;
         case 'h':
            http_base = optarg;
            break;
         default:
           return -1;
       }
  }
  
  OpCurlClient op(http_base);
  cout<<op_test()<<endl; 
  char s = ' ';
  char *key=&s;
  char *out=NULL;
  char *data=NULL;
  op.op_url(OP_GET,key,out);
  cout<<out<<endl;
  return 0;
}
