package ch.epfl.chic.napac.toygether.toygether

import android.content.Context
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

        button_toys_one_linked_play.setOnClickListener {

            val prefs = getSharedPreferences(sharedPreferencesConstants.SHARED_PREFERENCES_NAME, Context.MODE_PRIVATE)
            val toyCode = prefs.getString(sharedPreferencesConstants.KEY_TOY_CODE, null)

            if (toyCode != null) {
                val nextActivityIntent = Intent(this, WaitingForToyActivity::class.java)
                nextActivityIntent.putExtra("toy_code", toyCode)
                startActivity( nextActivityIntent)
            }
        }
    }
}
