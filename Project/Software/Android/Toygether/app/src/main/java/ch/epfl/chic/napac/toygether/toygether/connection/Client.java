package ch.epfl.chic.napac.toygether.toygether.connection;

import android.content.Context;
import android.provider.ContactsContract;
import android.util.Log;

import com.android.volley.Cache;
import com.android.volley.Network;
import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.BasicNetwork;
import com.android.volley.toolbox.DiskBasedCache;
import com.android.volley.toolbox.HurlStack;
import com.android.volley.toolbox.JsonObjectRequest;

import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;

public class Client {

    public static final long POOLING_DELAY_MS = 500;

    private static Client instance = null;
    private static Context mCtx;

	private static final String pushURL = "http://toygether.altervista.org/receive_stream.php";
    private static final String pullURL = "http://toygether.altervista.org/pooling_stream.php";

    private ArrayList<JSONObject> q;


    private Client(Context context) {
        mCtx = context;
        q = new ArrayList<>();
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
        JsonObjectRequest jsonObjectPushRequest
                = new JsonObjectRequest(Request.Method.POST, pushURL, message, listener, errorListener);

        // Access the RequestQueue through your singleton class.
        RequestHandler.getInstance(mCtx.getApplicationContext()).addToRequestQueue(jsonObjectPushRequest);
    }

    public void pullMessage() {
        this.pushMessage(null, null);
    }

    public void pullMessage(Response.Listener<JSONObject> listener) {
        this.pullMessage(listener, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                Log.e("CLIENT_PULL_MESSAGE", error.toString());
            }
        });
    }

    public void pullMessage(Response.Listener<JSONObject> listener,Response.ErrorListener errorListener) {

        // Get the personal ID to have a pull on your un-read messages
        DataSaver d = new DataSaver(mCtx);

        // Create the JSON message for the request
        JSONObject messageRequest = new JSONObject();
        try {
            messageRequest.put("source", d.getUserCode());
        } catch (JSONException e) {
            e.printStackTrace();
        }

        // Create the JSON Request
        JsonObjectRequest jsonObjectPullRequest
                = new JsonObjectRequest(Request.Method.POST, pullURL, messageRequest, listener, errorListener);

        // Access the RequestQueue through your singleton class.
        RequestHandler.getInstance(mCtx.getApplicationContext()).addToRequestQueue(jsonObjectPullRequest);
    }
}