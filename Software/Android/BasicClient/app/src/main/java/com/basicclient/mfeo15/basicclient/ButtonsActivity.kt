package com.basicclient.mfeo15.basicclient

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import kotlinx.android.synthetic.main.activity_buttons.*

class ButtonsActivity : AppCompatActivity() {

    var red_status = 1
    var green_status = 1
    var yellow_status = 1

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_buttons)

        button_red.setOnClickListener {
            //red_status = update_status(red_status)
            Client.getInstance().asyncSend("P314:U123:4242:RED$red_status$");
        }

        button_yellow.setOnClickListener {
            //yellow_status = update_status(yellow_status)
            Client.getInstance().asyncSend("P314:U123:4242:YEL$yellow_status$");
        }

        button_green.setOnClickListener {
            //green_status = update_status(green_status)
            Client.getInstance().asyncSend("P314:U123:4242:GRN$green_status$");
        }
    }

    fun update_status(status : Int) : Int {

        if (status == 0)
            return 1

        return 0
    }
}
