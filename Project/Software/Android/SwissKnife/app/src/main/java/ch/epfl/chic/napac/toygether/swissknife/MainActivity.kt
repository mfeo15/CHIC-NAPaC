package ch.epfl.chic.napac.toygether.swissknife

import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)


        button_smartconfig.setOnClickListener {
            val intent = Intent(this, EsptouchDemoActivity::class.java)
            startActivity(intent)
        }

        button_qrcode.setOnClickListener {
            val intent = Intent(this, QRcodeActivity::class.java)
            startActivity(intent)
        }
    }
}
