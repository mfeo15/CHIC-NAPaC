package ch.epfl.chic.napac.toygether.toygether

import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import ch.epfl.chic.napac.toygether.toygether.connection.DataSaver
import kotlinx.android.synthetic.main.activity_toys_empty.*

class ToysEmptyActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_toys_empty)

        if (DataSaver(this).toysCount > 0)
            startActivity( Intent(this, ToysOneLinkedActivity::class.java))

        button_link_your_toy.setOnClickListener {
            startActivity( Intent(this, SmartConfigActivity::class.java))
        }

        button_toys_empty_settings.setOnClickListener {
            startActivity( Intent(this, SettingsActivity::class.java))
        }
    }
}
