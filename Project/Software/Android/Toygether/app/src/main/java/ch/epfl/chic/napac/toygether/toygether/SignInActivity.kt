package ch.epfl.chic.napac.toygether.toygether

import android.content.Context
import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import ch.epfl.chic.napac.toygether.toygether.connection.DataSaver
import kotlinx.android.synthetic.main.activity_sign_in.*

class SignInActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_sign_in)

        button_back.setOnClickListener {
            finish()
        }

        button_enter.setOnClickListener {
            signInButtonHasBeenPressed()
        }

        button_password_forgotten.setOnClickListener {
            startActivity( Intent(this, PasswordForgottenActivity::class.java))
        }
    }

    private fun signInButtonHasBeenPressed() {
        val email = editText_signIn_email.text.toString()
        val password = editText_signIn_password.text.toString()
        //val rememberAccess = checkBox_signIn_remember.isChecked
        val rememberAccess = true

        if (email.isEmpty() or password.isEmpty()) {

            if (email.isEmpty())
                editText_signIn_email.error = "Email is missing !"

            if (isEmailValid(email))
                editText_signIn_email.error = "You need to insert a correct email"

            if (password.isEmpty())
                editText_signIn_password.error = "Password is missing !"

            return
        }

        checkCredentials(email, password, rememberAccess)
    }

    fun isEmailValid(email: CharSequence): Boolean {
        return android.util.Patterns.EMAIL_ADDRESS.matcher(email).matches()
    }

    private fun checkCredentials(email : String, password :String, rememberAccess : Boolean) {

        if (rememberAccess)
            DataSaver(this).isUserLogged = true

        startActivity( Intent(this, ToysEmptyActivity::class.java))
    }
}
