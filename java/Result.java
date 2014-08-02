import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import org.apache.http.Header;
import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.auth.AuthScope;
import org.apache.http.auth.UsernamePasswordCredentials;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.client.DefaultHttpClient;


public final class Result {
    public static void main(String[] args) {
		if(args.length != 1) {
            System.err.println("Usage:");
            System.err.println("  ./result delivery-id");
			return;
		}
        String url = "https://api.bluehouselab.com/smscenter/v1.0/result/"+args[0];
        DefaultHttpClient client = new DefaultHttpClient();
        try {
            // basic authentication
            client.getCredentialsProvider().setCredentials(
                AuthScope.ANY,
                new UsernamePasswordCredentials(Config.appid, Config.apikey)
            );
            HttpGet httpGet = new HttpGet(url);

            HttpResponse httpResponse = client.execute(httpGet);
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
