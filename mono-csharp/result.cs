using System;
using System.Net;
using System.Text;

class SendSMS
{
    static void Main(string[] args)
    {
        if(args.Length != 1)
        {
            Console.WriteLine("Usage:");
            Console.WriteLine("  result.exe deliveryid");
            return;
        }
        string url = "https://api.bluehouselab.com/smscenter/v1.0/result/"+args[0];
        string appid = "example";
        string apikey = "c5dd7e7dkjp27377l903c42c032b413b";

        WebClient client = new WebClient();
        NetworkCredential creds = new NetworkCredential(appid, apikey);
        client.Credentials = creds;
        byte[] response = client.DownloadData(url);
        Console.WriteLine(Encoding.UTF8.GetString(response));
    }
}
