import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import org.apache.http.HttpResponse;
import org.apache.http.auth.AuthScope;
import org.apache.http.auth.UsernamePasswordCredentials;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.client.CredentialsProvider;
import org.apache.http.impl.client.BasicCredentialsProvider;
import org.apache.http.impl.client.BasicAuthCache;
import org.apache.http.impl.auth.BasicScheme;
import org.apache.http.client.AuthCache;
import org.apache.http.HttpHost;
import org.apache.http.client.protocol.HttpClientContext;



/* XXX didn't use org.json to be simple
import org.json.JSONObject; 
*/

public final class SendSMS {
    public static void main(String[] args) {
        String hostname = "api.bluehouselab.com";
        String url = "https://"+hostname+"/smscenter/v1.0/sendsms";

        CredentialsProvider credsProvider = new BasicCredentialsProvider();
        credsProvider.setCredentials(
            new AuthScope(hostname, 443, AuthScope.ANY_REALM),
            new UsernamePasswordCredentials(Config.appid, Config.apikey)
        );

        // Create AuthCache instance
        AuthCache authCache = new BasicAuthCache();
        authCache.put(new HttpHost(hostname, 443, "https"), new BasicScheme());

        // Add AuthCache to the execution context
        HttpClientContext context = HttpClientContext.create();
        context.setCredentialsProvider(credsProvider);
        context.setAuthCache(authCache);

        DefaultHttpClient client = new DefaultHttpClient();

        try {
            HttpPost httpPost = new HttpPost(url);
            httpPost.setHeader("Content-type", "application/json; charset=utf-8");
            String json = "{\"sender\":\""+Config.sender+"\",\"receivers\":[\""+Config.receiver+"\"],\"content\":\""+Config.content+"\"}";

            StringEntity se = new StringEntity(json, "UTF-8");
            httpPost.setEntity(se);

            HttpResponse httpResponse = client.execute(httpPost, context);
            System.out.println(httpResponse.getStatusLine().getStatusCode());

            InputStream inputStream = httpResponse.getEntity().getContent();
            if(inputStream != null) {
                BufferedReader bufferedReader = new BufferedReader( new InputStreamReader(inputStream));
                String line = "";
                while((line = bufferedReader.readLine()) != null)
                    System.out.println(line);
                inputStream.close();
            }
        } catch (Exception e) {
            System.err.println("Error: "+e.getLocalizedMessage());
        } finally {
            client.getConnectionManager().shutdown();
        }

    }
}
