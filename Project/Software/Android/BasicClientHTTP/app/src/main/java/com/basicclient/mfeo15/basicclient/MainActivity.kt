package com.basicclient.mfeo15.basicclient

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.widget.Toast
import com.android.volley.Request
import com.android.volley.Response
import com.android.volley.toolbox.JsonObjectRequest
import com.android.volley.toolbox.StringRequest
import com.android.volley.toolbox.Volley
import kotlinx.android.synthetic.main.activity_buttons.*
import org.json.JSONObject



class MainActivity : AppCompatActivity() {

    var red_status = 0
    var green_status = 0
    var yellow_status = 0

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_buttons)

        button_red.setOnClickListener {
            red_status = update_status(red_status)
            send(1, red_status)
        }

        button_yellow.setOnClickListener {
            yellow_status = update_status(yellow_status)
            send(2, yellow_status)
        }

        button_green.setOnClickListener {
            green_status = update_status(green_status)
            send(3, green_status)
        }
    }

    fun update_status(status : Int) : Int {

        return if(status == 0) 1 else 0
    }

    fun send(led : Int, status : Int) {

        val JSONmessage = JSONObject("{'id':1}")

        JSONmessage.put("id", 1)
        JSONmessage.put("source", "P314")
        JSONmessage.put("destination", "T123")
        JSONmessage.put("led", led)
        JSONmessage.put("status", status)

        Client.getInstance(this).pushMessage(JSONmessage)
    }
}
