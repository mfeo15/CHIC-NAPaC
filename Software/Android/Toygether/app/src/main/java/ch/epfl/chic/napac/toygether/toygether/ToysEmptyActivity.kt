package ch.epfl.chic.napac.toygether.toygether

import android.content.Context
import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.view.LayoutInflater
import kotlinx.android.synthetic.main.activity_toys_empty.*
import kotlinx.android.synthetic.main.no_toy.*

class ToysEmptyActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_toys_empty)

        val prefs = getSharedPreferences(sharedPreferencesConstants.SHARED_PREFERENCES_NAME, Context.MODE_PRIVATE)
        val toysCount = prefs.getInt(sharedPreferencesConstants.KEY_TOYS_COUNT, 0)

        if (toysCount > 0)
            startActivity( Intent(this, ToysOneLinkedActivity::class.java))

        button_link_your_toy.setOnClickListener {
            startActivity( Intent(this, QRCodeActivity::class.java))
        }

        button_toys_empty_settings.setOnClickListener {
            startActivity( Intent(this, SettingsActivity::class.java))
        }
    }
}
