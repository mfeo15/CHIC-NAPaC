package ch.epfl.chic.napac.toygether.toygether

import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.support.v4.content.ContextCompat
import android.util.Log
import android.view.View
import android.widget.Button
import ch.epfl.chic.napac.toygether.toygether.connection.Client
import ch.epfl.chic.napac.toygether.toygether.connection.Message
import kotlinx.android.synthetic.main.activity_playing.*
import java.util.*

class PlayingActivity : AppCompatActivity(), View.OnClickListener, Observer {

    var sequence: MutableList<String> = mutableListOf<String>()

    override fun update(o: Observable?, arg: Any?) {
        when (o) {
            is Client -> {
                if (arg is Message) {

                }
            }
        }
    }

    override fun onClick(v: View?) {

        v?.background = ContextCompat.getDrawable(this, R.drawable.pressed)

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

    override fun onResume() {
        super.onResume()

        Client.getInstance().addNewObserver(this)
    }

    override fun onPause() {
        super.onPause()

        Client.getInstance().deleteAnObserver(this)
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_playing)

        val toyCode = intent.extras.getString("toy_code")

        button_playing_close.setOnClickListener {
            Client.getInstance().send(Message(toyCode, "U123", "2005").toString())
            finish()
        }

        button_play.setOnClickListener {
            button_interactive_1.setBackgroundResource(0)
            button_interactive_2.setBackgroundResource(0)
            button_interactive_3.setBackgroundResource(0)
            button_interactive_4.setBackgroundResource(0)
            button_interactive_5.setBackgroundResource(0)
            button_interactive_6.setBackgroundResource(0)
            button_interactive_7.setBackgroundResource(0)
            button_interactive_8.setBackgroundResource(0)

            Client.getInstance().send(Message(toyCode, "U123", "2003", sequence.toTypedArray()).toString())
            sequence.clear()
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
