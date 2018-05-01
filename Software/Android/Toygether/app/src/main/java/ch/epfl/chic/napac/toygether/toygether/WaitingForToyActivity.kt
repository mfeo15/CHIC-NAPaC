package ch.epfl.chic.napac.toygether.toygether

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import ch.epfl.chic.napac.toygether.toygether.connection.Client
import ch.epfl.chic.napac.toygether.toygether.connection.Message

class WaitingForToyActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_waiting_for_toy)

        val toyCode = intent.extras.getString("toy_code")
        Client.getInstance().send( Message(toyCode, "U123", "2001").toString() )
    }
}
