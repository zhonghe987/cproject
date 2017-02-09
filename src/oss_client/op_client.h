#ifndef OP_CLIENT_H
#define OP_CLIENT_H
#include<iostream>
#include<string>
#include<curl/curl.h>

enum HttpOp {OP_GET,OP_PUT,OP_DEL,OP_POST};

class Client
{
  public:
    Client(std::string url_base):http_base(url_base){}
    virtual ~Client(){}
    virtual int op_url(HttpOp method,char *key,char *out,char *data=NULL) = 0;
    //virtual int getUrl(char *method,char *key,char *out ) = 0;
    //virtual int postUrl(char *method,char *key,char *out) = 0;
    //virtual int delUrl(char *method,char *key,char *out) = 0;
    //virtual int putUrl(char *method,char *key,char *out) = 0;
    std::string getBase(){return http_base;}
    
 private:
    std::string http_base;
};

class OpCurlClient: public Client
{
  public:
    OpCurlClient(std::string url):Client(url){}
    ~OpCurlClient(){}
    int op_url(HttpOp method,char *key,char *out,char *data=NULL);
    //virtual int getUrl(char *method,char *key,char *out);
    //virtual int postUrl(char *method,char *key,char *out);
    //virtual int delUrl(char *method,char *key,char *out);
    //virtual int putUrl(char *method,char *key,char *out);
    
};

int op_test();

#endif


