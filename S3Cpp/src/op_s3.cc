/*
 * s3.cc
 *
 *  Created on: 2017Äê2ÔÂ28ÈÕ
 *      Author: Administrator
 */



#include "op_s3.h"


std::string OpS3::authorize(const std::string request)
{
    BYTE digest[20];
    CHMAC_SHA1 hmac_sha1;
    hmac_sha1.HMAC_SHA1((BYTE*)request.c_str(), request.size(),(BYTE*)secretKey.c_str(),secretKey.size(),digest);
    std::string signature(base64_encode((unsigned char*)digest,20));
    return "AWS " + accessKey + ":" + signature;
}



std::string OpS3::listBucket()
{

	    std::vector<std::string> headers;
	    // Host URL
	    headers.push_back("Host: "+endPoint);

	    // Date
	    std::string date = getDate();
	    headers.push_back("Date: " + date);

	    // Authorize request
	    std::string request = "GET\n";
	    request += "\n";
	    request += "\n";
	    request += date + "\n";
	    request += "/";
	    headers.push_back("Authorization: " + authorize(request));
	    // Execute get operation
	    return  hs->gets1(endPoint, headers);

}


std::string OpS3::getDate()
{
    time_t lt;
    time(&lt);
    struct tm * tmTmp;
    tmTmp = gmtime(&lt);

    char * buf = new char[37];
    strftime(buf,37,"%a, %d %b  %Y %X GMT",tmTmp);

    std::string stringBuffer(buf);
    return stringBuffer;
}


size_t HttpS3::write(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

size_t HttpS3::reader(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t retcode = fread(ptr, size, nmemb, stream);
    return retcode;
}

 std::string  HttpS3::gets1(const std::string &url, const std::vector<std::string> &headers)
{
    // Initialize curl
    curl_global_init(CURL_GLOBAL_ALL);
    CURL* curlHandle = curl_easy_init();

    // Initialize headers
    curl_slist* httpHeaders = NULL;
    for(int i = 0; i < headers.size(); i++)
    {
        httpHeaders = curl_slist_append(httpHeaders, headers[i].c_str());
    }

    // Execute
    std::string output = "";
    if(curlHandle)
    {
        curl_easy_setopt(curlHandle, CURLOPT_FOLLOWLOCATION,1);//Set automaticallly redirection
        curl_easy_setopt(curlHandle, CURLOPT_MAXREDIRS,1);//Set max redirection times
        curl_easy_setopt(curlHandle, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);//Set http version 1.1fer
        curl_easy_setopt(curlHandle, CURLOPT_HEADER, true);//Set header true
        curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, httpHeaders);//Set headers
        curl_easy_setopt(curlHandle, CURLOPT_URL, url.c_str());//Set URL
        curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, write);
        curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &output);

        curl_easy_perform(curlHandle);//Perform
        curl_global_cleanup();
    }
    return output;
}
