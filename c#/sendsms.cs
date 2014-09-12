using System;
using System.Net;

class SendSMS
{
    static void Main(string[] args)
    {
        string url = "https://api.bluehouselab.com/smscenter/v1.0/sendsms";
        string appid = "example";
        string apikey = "c5dd7e7dkjp27377l903c42c032b413b";

        string json = @"{
            ""sender"": ""01000000000"",
            ""receivers"": [""01000000000""],
            ""content"": ""나는 유리를 먹을 수 있어요. 그래도 아프지 않아요""}";

        WebClient client = new WebClient();
        NetworkCredential creds = new NetworkCredential(appid, apikey);
        client.Credentials = creds;
        client.Headers[HttpRequestHeader.ContentType] = "application/json; charset=utf-8";

        try
        {
            string response = client.UploadString(url, json);
            Console.WriteLine(response);
        }
        catch (WebException e)
        {
            HttpStatusCode status = ((HttpWebResponse)e.Response).StatusCode;
            Console.WriteLine("{0}", (int)status);
            Console.WriteLine("{0}", status.ToString());
        }
    }
}
