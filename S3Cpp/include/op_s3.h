/*
 * s3.h
 *
 *  Created on: 2017Äê2ÔÂ28ÈÕ
 *      Author: Administrator
 */

#ifndef OP_S3_H_
#define OP_S3_H_

#include <string>
#include <vector>
#include <curl/curl.h>
#include <time.h>
#include "HMAC_SHA1.h"
#include "base64.h"


class HttpS3
{
public:
	static size_t write(void *contents, size_t size, size_t nmemb, void *userp);
	static size_t reader(void *ptr, size_t size, size_t nmemb, FILE *stream);
	std::string get(const std::string &url,const std::vector<std::string> &headers);
	std::string put(const std::string &url,const std::vector<std::string> &headers);

};

class OpS3
{
public:
	OpS3(const std::string ak,const std::string sk,const std::string ep,HttpS3 *s3):accessKey(ak),secretKey(sk),endPoint(ep),hs(s3){}
    ~OpS3(){}
    std::string getDate();
	std::string authorize(const std::string requset);

	//bucket
	std::string listBucket(std::string prefix);
	std::string createBucket(std::string name,std::string acl);

private:
	std::string accessKey;
	std::string secretKey;
	std::string endPoint;
	HttpS3 *hs;
};





#endif /* S3_H_ */
