using System;
using System.Net;
using System.Text;

class Result
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

        try
        {
            byte[] response = client.DownloadData(url);
            Console.WriteLine(Encoding.UTF8.GetString(response));
        }
        catch (WebException e)
        {
            HttpStatusCode status = ((HttpWebResponse)e.Response).StatusCode;
            Console.WriteLine("{0}", (int)status);
            Console.WriteLine("{0}", status.ToString());
        }
    }
}
