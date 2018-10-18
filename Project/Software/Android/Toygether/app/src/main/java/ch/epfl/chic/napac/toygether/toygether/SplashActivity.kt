package ch.epfl.chic.napac.toygether.toygether

import android.content.Intent
import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import ch.epfl.chic.napac.toygether.toygether.connection.DataSaver

/**
 * Created by mfeo on 4/23/2018.
 */
class SplashActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        //startActivity( Intent(this, PlayingActivity::class.java))

        if (DataSaver(this).isUserLogged) {
            startActivity( Intent(this, ToysEmptyActivity::class.java))
        } else {
            startActivity( Intent(this, IntroUserActivity::class.java))
        }
    }
}