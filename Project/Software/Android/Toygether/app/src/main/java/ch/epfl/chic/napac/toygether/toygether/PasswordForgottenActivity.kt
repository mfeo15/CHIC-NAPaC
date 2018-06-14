package ch.epfl.chic.napac.toygether.toygether

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import kotlinx.android.synthetic.main.activity_password_forgotten.*

class PasswordForgottenActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_password_forgotten)

        button_password_forgotten_close.setOnClickListener {
            finish()
        }
    }
}
