package ch.epfl.chic.napac.toygether.toygether.connection;

import android.content.Context;

import org.json.JSONException;
import org.json.JSONObject;

public class JSONMessage {

    private Context ctx;

    private String id;
    private String source;
    private String destination;

    private String[] fields;
    private String[] values;

    public JSONMessage(Context ctx, String id, String destination) {

        this(ctx, id, destination, new String[0], new String[0]);
    }

    public JSONMessage(Context ctx, String id, String destination, String[] fields, String[] values) {

        this.ctx = ctx;

        this.id = id;
        this.destination = destination;
        this.source = (new DataSaver(ctx)).getUserCode();

        this.fields = fields;
        this.values = values;
    }

    public Context getCtx() {
        return this.ctx;
    }

    public void setCtx(Context ctx) {
        this.ctx = ctx;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getSource() {
        return source;
    }

    public void setSource(String source) {
        this.source = source;
    }

    public String getDestination() {
        return destination;
    }

    public void setDestination(String destination) {
        this.destination = destination;
    }

    public String[] getFields() {
        return fields;
    }

    public void setFields(String[] fields) {
        this.fields = fields;
    }

    public String[] getValues() {
        return values;
    }

    public void setValues(String[] values) {
        this.values = values;
    }

    public JSONObject toJSON() {

        JSONObject o = new JSONObject();

        try {
            o.put("id", this.id);
            o.put("source", this.source);
            o.put("destination", this.destination);

            for (int i = 0; i < this.fields.length; i++) {
                o.put(this.fields[i], this.values[i]);
            }

            return o;

        } catch (JSONException e) {
            e.printStackTrace();
        }

        return null;
    }
}
