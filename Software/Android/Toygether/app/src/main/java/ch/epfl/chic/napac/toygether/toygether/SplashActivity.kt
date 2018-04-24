package ch.epfl.chic.napac.toygether.toygether

import android.content.Context
import android.content.Intent
import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import ch.epfl.chic.napac.toygether.toygether.connection.Client

/**
 * Created by mfeo on 4/23/2018.
 */
class SplashActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        Client.getInstance().setupParamters("192.168.1.105", 6789)
        //Thread( Client.getInstance()).start()

        val prefs = getSharedPreferences(sharedPreferencesConstants.SHARED_PREFERENCES_NAME, Context.MODE_PRIVATE)
        val userLogged = prefs.getBoolean(sharedPreferencesConstants.KEY_USER_LOGGED, false)

        if (userLogged) {
            startActivity( Intent(this, ToysEmptyActivity::class.java))
        } else {
            startActivity( Intent(this, SignInActivity::class.java))
        }
    }
}