package ch.epfl.chic.napac.toygether.toygether

import android.content.Intent
import android.os.Bundle
import android.support.v7.app.AppCompatActivity

/**
 * Created by mfeo on 4/23/2018.
 */
class SplashActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        startActivity( Intent(this, SignUpActivity::class.java))
    }
}