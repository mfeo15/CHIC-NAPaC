package ch.epfl.chic.napac.toygether.toygether

import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import kotlinx.android.synthetic.main.activity_sign_in.*

class SignInActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_sign_in)

        button_sign_up.setOnClickListener {
            startActivity( Intent(this, SignUpActivity::class.java))
        }

        button_enter.setOnClickListener {
            startActivity( Intent(this, ToysActivity::class.java))
        }

        button_password_forgotten.setOnClickListener {
            startActivity( Intent(this, PasswordForgottenActivity::class.java))
        }
    }
}
