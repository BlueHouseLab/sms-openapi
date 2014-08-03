#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include "conf.h"

static size_t write_callback(char *data, size_t size, size_t nmemb, void *ud) {
    char *responsebuf = (char*)ud;
    strncat(responsebuf, data, size*nmemb);
    return size*nmemb;
}
 
int main(void)
{
  CURL *handle;
  CURLcode res;
  char post_body[BUFSIZ] = {0, };
  char responsebuf[BUFSIZ] = {0, };
 
  curl_global_init(CURL_GLOBAL_DEFAULT);
 
  handle = curl_easy_init();
  if(handle) {
    curl_easy_setopt(handle, CURLOPT_URL, "https://api.bluehouselab.com/smscenter/v1.0/sendsms");
    curl_easy_setopt(handle, CURLOPT_USERNAME, APPID);
    curl_easy_setopt(handle, CURLOPT_PASSWORD, APIKEY);

    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, responsebuf);



    sprintf(post_body, "{\"sender\":\"%s\",\"receivers\":[\"%s\"],\"content\":\"%s\"}", SENDER, RECEIVER, CONTENT);
    curl_easy_setopt(handle, CURLOPT_POST, 1); 
    curl_easy_setopt(handle, CURLOPT_POSTFIELDS, post_body); 
    curl_easy_setopt(handle, CURLOPT_POSTFIELDSIZE, strlen(post_body));
 
    res = curl_easy_perform(handle);
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    else {
        long status_code = 0;
        curl_easy_getinfo (handle, CURLINFO_RESPONSE_CODE, &status_code);
        printf("%ld\n", status_code);
        printf("%s\n", responsebuf);

    }
 
    curl_easy_cleanup(handle);
  }
 
  curl_global_cleanup();
 
  return 0;
}
