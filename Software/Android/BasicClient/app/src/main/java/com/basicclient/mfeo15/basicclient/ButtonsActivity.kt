package com.basicclient.mfeo15.basicclient

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import kotlinx.android.synthetic.main.activity_buttons.*

class ButtonsActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_buttons)

        button_red.setOnClickListener {
            Client.getInstance().asyncSend("U123:P314:4242:RED1$");
        }

        button_green.setOnClickListener {
            Client.getInstance().asyncSend("U123:P314:4242:GRN1$");
        }

        button_blue.setOnClickListener {
            Client.getInstance().asyncSend("U123:P314:4242:BLE1$");
        }
    }
}
