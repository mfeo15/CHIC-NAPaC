package ch.epfl.chic.napac.toygether.toygether

import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import kotlinx.android.synthetic.main.activity_toys.*

class ToysActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_toys)

        button_link_your_toy.setOnClickListener {
            startActivity( Intent(this, QRCodeActivity::class.java))
        }
    }
}
