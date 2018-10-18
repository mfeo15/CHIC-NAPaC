package ch.epfl.chic.napac.toygether.toygether.connection;

import android.content.Context;
import android.util.Log;

import com.android.volley.Request;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonObjectRequest;

import org.json.JSONObject;

public class Client {

    private static Client instance = null;
    private static Context mCtx;

	private static final String pushURL = "http://toygether.altervista.org/receive_stream.php";
    private static final String pullURL = "";


    private Client(Context context) {
        mCtx = context;
    }

    public static synchronized Client getInstance(Context context) {
        if (instance == null)
            instance = new Client(context);

        return instance;
    }

    /*
    fun send(led : Int, status : Int) {
        // Instantiate the RequestQueue.
        val queue = Volley.newRequestQueue(this)
        val url = "http://toygether.altervista.org/receive_stream.php"

        val JSONmessage = JSONObject("{'id':1}")

        JSONmessage.put("id", 1)
        JSONmessage.put("source", "P314")
        JSONmessage.put("destination", "T123")
        JSONmessage.put("led", led)
        JSONmessage.put("status", status)

        // Request a string response from the provided URL.
        val jsonObjectRequest = JsonObjectRequest(Request.Method.POST, url, JSONmessage,
                Response.Listener { response ->
            //Toast.makeText(this, response.toString(), Toast.LENGTH_LONG).show()

        },
        Response.ErrorListener { error -> Toast.makeText(this, error.toString(), Toast.LENGTH_LONG).show() })

        // Add the request to the RequestQueue.
        queue.add(jsonObjectRequest)
    }
    */

    public void pushMessage(JSONObject message) {
        this.pushMessage(message, null, null);
    }

    public void pushMessage(JSONObject message, Response.Listener<JSONObject> listener) {
        this.pushMessage(message, listener, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                Log.e("CLIENT_PUSH_MESSAGE", error.toString());
            }
        });
    }

    public void pushMessage(JSONObject message,
                            Response.Listener<JSONObject> listener,Response.ErrorListener errorListener) {

        // Create the JSON Request
        JsonObjectRequest jsonObjectRequest
                = new JsonObjectRequest(Request.Method.POST, pushURL, message, listener, errorListener);

        // Access the RequestQueue through your singleton class.
        RequestHandler.getInstance(mCtx).addToRequestQueue(jsonObjectRequest);
    }

    public void pullMessage() {

    }
}