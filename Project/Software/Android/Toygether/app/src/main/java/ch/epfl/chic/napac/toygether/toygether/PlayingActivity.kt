package ch.epfl.chic.napac.toygether.toygether

import android.animation.ObjectAnimator
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

    var toyCode = ""

    override fun update(o: Observable?, arg: Any?) {
        when (o) {
            is Client -> {
                if (arg is Message) {
                    Log.d("PLAYING", arg.toString())
                    if (arg.messageID.equals("2003")) {

                        when (arg.parameters[0].toInt()) {
                            1 -> turnON(button_interactive_1, 1, 2)
                            2 -> turnON(button_interactive_2, 2, 2)
                            3 -> turnON(button_interactive_3, 3, 2)
                            4 -> turnON(button_interactive_4, 4, 2)
                            5 -> turnON(button_interactive_5, 5, 2)
                            6 -> turnON(button_interactive_6, 6, 2)
                            7 -> turnON(button_interactive_7, 7, 2)
                            8 -> turnON(button_interactive_8, 8, 2)
                        }
                        return
                    }

                    if (arg.messageID.equals("2004")) {

                        when (arg.parameters[0].toInt()) {
                            1 -> turnOFF(button_interactive_1, 1, 2)
                            2 -> turnOFF(button_interactive_2, 2, 2)
                            3 -> turnOFF(button_interactive_3, 3, 2)
                            4 -> turnOFF(button_interactive_4, 4, 2)
                            5 -> turnOFF(button_interactive_5, 5, 2)
                            6 -> turnOFF(button_interactive_6, 6, 2)
                            7 -> turnOFF(button_interactive_7, 7, 2)
                            8 -> turnOFF(button_interactive_8, 8, 2)
                        }
                    }
                }
            }
        }
    }

    override fun onClick(v: View?) {

        if (v?.tag == 0 || v?.tag == 1 ) {

            when (v?.id) {
                R.id.button_interactive_1 -> turnON(button_interactive_1, 1, 1)
                R.id.button_interactive_2 -> turnON(button_interactive_2, 2, 1)
                R.id.button_interactive_3 -> turnON(button_interactive_3, 3, 1)
                R.id.button_interactive_4 -> turnON(button_interactive_4, 4, 1)
                R.id.button_interactive_5 -> turnON(button_interactive_5, 5, 1)
                R.id.button_interactive_6 -> turnON(button_interactive_6, 6, 1)
                R.id.button_interactive_7 -> turnON(button_interactive_7, 7, 1)
                R.id.button_interactive_8 -> turnON(button_interactive_8, 8, 1)
            }
            return
        }

        if (v?.tag == 2) {

            when (v?.id) {
                R.id.button_interactive_1 -> turnOFF(button_interactive_1, 1, 1)
                R.id.button_interactive_2 -> turnOFF(button_interactive_2, 2, 1)
                R.id.button_interactive_3 -> turnOFF(button_interactive_3, 3, 1)
                R.id.button_interactive_4 -> turnOFF(button_interactive_4, 4, 1)
                R.id.button_interactive_5 -> turnOFF(button_interactive_5, 5, 1)
                R.id.button_interactive_6 -> turnOFF(button_interactive_6, 6, 1)
                R.id.button_interactive_7 -> turnOFF(button_interactive_7, 7, 1)
                R.id.button_interactive_8 -> turnOFF(button_interactive_8, 8, 1)
            }
            return
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

        toyCode = intent.extras.getString("toy_code")

        button_playing_close.setOnClickListener {
            Client.getInstance().send(Message(toyCode, "U123", "2005").toString())
            finish()
        }

        button_interactive_1.tag = 0
        button_interactive_2.tag = 0
        button_interactive_3.tag = 0
        button_interactive_4.tag = 0
        button_interactive_5.tag = 0
        button_interactive_6.tag = 0
        button_interactive_7.tag = 0
        button_interactive_8.tag = 0

        button_interactive_1.setOnClickListener(this)
        button_interactive_2.setOnClickListener(this)
        button_interactive_3.setOnClickListener(this)
        button_interactive_4.setOnClickListener(this)
        button_interactive_5.setOnClickListener(this)
        button_interactive_6.setOnClickListener(this)
        button_interactive_7.setOnClickListener(this)
        button_interactive_8.setOnClickListener(this)
    }

    fun sendMessageForLED(messageID : String, led : String) {
        Client.getInstance().send(Message(toyCode, "U123", messageID, arrayOf(led)).toString())
    }

    fun turnON(v: View?, led : Int, turnedONBy : Int) {

        when (turnedONBy) {
            1 -> { // Me
                v?.background = ContextCompat.getDrawable(this, R.drawable.ball_azure)
                v?.tag = 1
                sendMessageForLED("2003", led.toString())
            }
            2 -> { // Toy
                v?.background = ContextCompat.getDrawable(this, R.drawable.ball_gold)
                v?.tag = 2
            }
        }
    }

    fun turnOFF(v: View?, led : Int, turnedOFFBy : Int) {

        if (turnedOFFBy == 1) // I am the one requesting the turn OFF. I need to say it to the toy
            sendMessageForLED("2004", led.toString())

        v?.background = ContextCompat.getDrawable(this, R.drawable.ball_dark)
        v?.tag = 0
    }
}
