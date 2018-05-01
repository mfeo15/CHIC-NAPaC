package ch.epfl.chic.napac.toygether.toygether

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.view.View
import android.widget.Button
import ch.epfl.chic.napac.toygether.toygether.connection.Client
import ch.epfl.chic.napac.toygether.toygether.connection.Message
import kotlinx.android.synthetic.main.activity_playing.*

class PlayingActivity : AppCompatActivity(), View.OnClickListener {

    var sequence: MutableList<String> = mutableListOf<String>()

    override fun onClick(v: View?) {

        when (v?.id) {
            R.id.button_interactive_1 -> sequence.add("1")
            R.id.button_interactive_2 -> sequence.add("2")
            R.id.button_interactive_3 -> sequence.add("3")
            R.id.button_interactive_4 -> sequence.add("4")
            R.id.button_interactive_5 -> sequence.add("5")
            R.id.button_interactive_6 -> sequence.add("6")
            R.id.button_interactive_7 -> sequence.add("7")
            R.id.button_interactive_8 -> sequence.add("8")
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_playing)

        val toyCode = intent.extras.getString("toy_code")

        button_playing_close.setOnClickListener {
            finish()
        }

        button_play.setOnClickListener {
            Client.getInstance().send(Message(toyCode, "U123", "2003", sequence.toTypedArray()).toString())
        }

        button_interactive_1.setOnClickListener(this)
        button_interactive_2.setOnClickListener(this)
        button_interactive_3.setOnClickListener(this)
        button_interactive_4.setOnClickListener(this)
        button_interactive_5.setOnClickListener(this)
        button_interactive_6.setOnClickListener(this)
        button_interactive_7.setOnClickListener(this)
        button_interactive_8.setOnClickListener(this)
    }
}
