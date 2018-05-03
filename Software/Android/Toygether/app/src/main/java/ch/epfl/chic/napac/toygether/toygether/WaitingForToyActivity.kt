package ch.epfl.chic.napac.toygether.toygether

import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import ch.epfl.chic.napac.toygether.toygether.connection.Client
import ch.epfl.chic.napac.toygether.toygether.connection.Message
import kotlinx.android.synthetic.main.activity_waiting_for_toy.*
import java.util.*

class WaitingForToyActivity : AppCompatActivity(), Observer {

    override fun update(o: Observable?, arg: Any?) {
        when (o) {
            is Client -> {
                if (arg is Message) {

                    Client.getInstance().deleteAnObserver(this)

                    val nextActivityIntent = Intent(this, PlayingActivity::class.java)
                    nextActivityIntent.putExtra("toy_code", intent.extras.getString("toy_code"))
                    startActivity( nextActivityIntent)
                }
            }
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_waiting_for_toy)

        button_waiting_toy_close.setOnClickListener {
            finish()
        }

        Client.getInstance().addNewObserver(this)

        val toyCode = intent.extras.getString("toy_code")
        Client.getInstance().send( Message(toyCode, "U123", "2001").toString() )
    }

    override fun onDestroy() {
        super.onDestroy()
        Client.getInstance().deleteAnObserver(this)
    }
}