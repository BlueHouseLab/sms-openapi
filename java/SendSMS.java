import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import org.apache.http.Header;
import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.auth.AuthScope;
import org.apache.http.auth.UsernamePasswordCredentials;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.client.DefaultHttpClient;

/* XXX didn't use org.json to be simple
import org.json.JSONObject; 
*/

public final class SendSMS {
    public static void main(String[] args) {
        String url = "https://api.bluehouselab.com/smscenter/v1.0/sendsms";
        DefaultHttpClient client = new DefaultHttpClient();
        try {
            // basic authentication
            client.getCredentialsProvider().setCredentials(
                AuthScope.ANY,
                new UsernamePasswordCredentials(Config.appid, Config.apikey)
            );
            HttpPost httpPost = new HttpPost(url);
            httpPost.setHeader("Content-type", "application/json; charset=utf-8");
            String json = "{\"sender\":\""+Config.sender+"\",\"receivers\":[\""+Config.receiver+"\"],\"content\":\""+Config.content+"\"}";
            StringEntity se = new StringEntity(json);
            httpPost.setEntity(se);

            HttpResponse httpResponse = client.execute(httpPost);
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
