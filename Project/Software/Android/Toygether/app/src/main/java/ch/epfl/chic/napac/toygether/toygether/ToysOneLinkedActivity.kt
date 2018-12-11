package ch.epfl.chic.napac.toygether.toygether

import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.support.v4.content.ContextCompat
import android.view.View
import ch.epfl.chic.napac.toygether.toygether.connection.DataSaver
import kotlinx.android.synthetic.main.activity_toys_one_linked.*

class ToysOneLinkedActivity : AppCompatActivity() {

    override fun onResume() {
        super.onResume()

        defaultStateApperance()
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_toys_one_linked)

        button_play_kid.text = DataSaver(this).toyName

        button_toys_one_linked_settings.setOnClickListener {
            startActivity( Intent(this, SettingsActivity::class.java))
        }

        button_play_kid.setOnClickListener {
            confirmationStateApperance()
        }

        button_play_kid_no.setOnClickListener {
            defaultStateApperance()
        }

        button_play_kid_yes.setOnClickListener {

            val toyCode = DataSaver(this).toyCode
            if (toyCode != "") {
                val nextActivityIntent = Intent(this, WaitingForToyActivity::class.java)
                //val nextActivityIntent = Intent(this, PlayingActivity::class.java)

                nextActivityIntent.putExtra("toy_code", toyCode)
                startActivity(nextActivityIntent)
            }
        }
    }

    fun defaultStateApperance() {
        button_play_kid.text = DataSaver(this).toyName
        button_play_kid.background = ContextCompat.getDrawable(this, R.drawable.kid_recently)
        button_play_kid.isClickable = true

        button_play_kid_yes.visibility = View.INVISIBLE
        button_play_kid_no.visibility = View.INVISIBLE
        textView_play_kid_info.visibility = View.VISIBLE
    }

    fun confirmationStateApperance() {
        button_play_kid_yes.visibility = View.VISIBLE
        button_play_kid_no.visibility = View.VISIBLE
        textView_play_kid_info.visibility = View.INVISIBLE

        button_play_kid.text = ""
        button_play_kid.background = ContextCompat.getDrawable(this, R.drawable.play)
        button_play_kid.isClickable = false
    }
}
