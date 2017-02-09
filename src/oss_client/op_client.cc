#include<string>
#include<iostream>
#include<curl/curl.h>
//#include <curl/types.h>  
#include <curl/easy.h>
#include"op_client.h"
#include<sstream>


int OpCurlClient::op_url(HttpOp method,char *key,char *out,char *data)
{
  curl_global_init(CURL_GLOBAL_ALL);
  CURL *curl;
  CURLcode res;
  struct curl_slist *headers = NULL;
  curl_slist_append(headers,"Accept:text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8");
  curl_slist_append( headers, "Content-Type: application/json");
  curl_slist_append( headers, "charsets: utf-8"); 
  curl = curl_easy_init();
  if(curl){
    std::string base_url = getBase();
    std::stringstream ss;
    std::string target;
    ss << &key;
    ss >> target;
    std::string url = base_url;
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_URL,url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPGET,1); 
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); 
    res = curl_easy_perform(curl);
    if(res != 0){
      curl_slist_free_all(headers);
      curl_easy_cleanup(curl);
      return -1;
    }
    char *ct;
    res = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct);
    out=ct;
  }
  curl_slist_free_all(headers);
  curl_easy_cleanup(curl);
  return 0;
}


int op_test()
{
  return 1;
}

