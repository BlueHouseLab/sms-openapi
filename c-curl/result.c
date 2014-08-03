#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include "conf.h"

static size_t write_callback(char *data, size_t size, size_t nmemb, void *ud) {
    char *responsebuf = (char*)ud;
    strncat(responsebuf, data, size*nmemb);
    return size*nmemb;
}
 
int main(int argc, char** argv)
{
  CURL *handle;
  CURLcode res;
  char responsebuf[BUFSIZ] = {0, };
  char url[BUFSIZ] = {0, };
  char *deliveryid = NULL;

  if(argc != 2) {
      fprintf(stderr, "Usage: \n");
      fprintf(stderr, "  %s delivery-id\n", argv[0]);
      return 1;
  }
  deliveryid = argv[1];
 
  curl_global_init(CURL_GLOBAL_DEFAULT);
 
  handle = curl_easy_init();
  if(handle) {
    sprintf(url,
            "https://api.bluehouselab.com/smscenter/v1.0/result/%s",
            deliveryid);
    curl_easy_setopt(handle, CURLOPT_URL, url);
    curl_easy_setopt(handle, CURLOPT_USERNAME, APPID);
    curl_easy_setopt(handle, CURLOPT_PASSWORD, APIKEY);

    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, responsebuf);


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
