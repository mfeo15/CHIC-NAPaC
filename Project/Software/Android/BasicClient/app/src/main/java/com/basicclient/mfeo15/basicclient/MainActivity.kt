package com.basicclient.mfeo15.basicclient

import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.widget.Toast
import kotlinx.android.synthetic.main.activity_main.*
import java.util.concurrent.Executors.newFixedThreadPool
import java.util.concurrent.ThreadPoolExecutor


class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        /*
        button_connect.setOnClickListener {
            val intent = Intent(this, ButtonsActivity::class.java)
            startActivity(intent)
        }
        */

        button_connect.setOnClickListener {
            val server_ip  = editText_IP.text.toString()
            val server_port : Int = Integer.parseInt( editText_port.text.toString() )

            Client.getInstance().setupParamters(server_ip, server_port);

            //val executor = newFixedThreadPool(128)
            //executor.execute { Client.getInstance() }
            Thread( Client.getInstance()).start()

            val intent = Intent(this, ButtonsActivity::class.java)
            startActivity(intent)
        }
    }
}
