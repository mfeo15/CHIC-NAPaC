package ch.epfl.chic.napac.toygether.toygether

import android.content.Context
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
            signInButtonHasBeenPressed()
        }

        button_password_forgotten.setOnClickListener {
            startActivity( Intent(this, PasswordForgottenActivity::class.java))
        }
    }

    private fun signInButtonHasBeenPressed() {
        val email = editText_signIn_email.toString()
        val password = editText_signIn_password.toString()
        val rememberAccess = checkBox_signIn_remember.isChecked

        if (email.isEmpty()) {
            editText_signIn_email.error = "Email is missing !"
            return
        }

        if (password.isEmpty()) {
            editText_signIn_password.error = "Password is missing !"
            return
        }

        checkCredentials(email, password, rememberAccess)
    }

    private fun checkCredentials(email : String, password :String, rememberAccess : Boolean) {

        if (rememberAccess) {
            val editor = getSharedPreferences(sharedPreferencesConstants.SHARED_PREFERENCES_NAME, Context.MODE_PRIVATE).edit()

            editor.putBoolean(sharedPreferencesConstants.KEY_USER_LOGGED, true)
            editor.apply()
        }

        startActivity( Intent(this, ToysEmptyActivity::class.java))
    }
}
