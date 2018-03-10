package com.basicclient.mfeo15.basicclient

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import kotlinx.android.synthetic.main.activity_buttons.*

class ButtonsActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_buttons)

        button_red.setOnClickListener {
            Client.getInstance().asyncSend("ABCD:123456789:RED:$");
        }

        button_green.setOnClickListener {
            Client.getInstance().asyncSend("ABCD:123456789:GRN:$");
        }

        button_blue.setOnClickListener {
            Client.getInstance().asyncSend("ABCD:123456789:BLE:$");
        }
    }
}
