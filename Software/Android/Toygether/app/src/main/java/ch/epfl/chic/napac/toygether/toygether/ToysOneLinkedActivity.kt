package ch.epfl.chic.napac.toygether.toygether

import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import kotlinx.android.synthetic.main.activity_toys_one_linked.*

class ToysOneLinkedActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_toys_one_linked)

        button_toys_one_linked_settings.setOnClickListener {
            startActivity( Intent(this, SettingsActivity::class.java))
        }
    }
}
