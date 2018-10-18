package ch.epfl.chic.napac.toygether.toygether

import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.support.v7.app.AlertDialog
import ch.epfl.chic.napac.toygether.toygether.connection.Client
import ch.epfl.chic.napac.toygether.toygether.connection.DataSaver
import kotlinx.android.synthetic.main.activity_sign_up.*
import org.json.JSONObject
import java.util.regex.Matcher
import java.util.regex.Pattern
import android.provider.SyncStateContract.Helpers.update
import java.security.MessageDigest


class SignUpActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_sign_up)

        button_signup_back.setOnClickListener {
            finish()
        }

        button_new_account.setOnClickListener{
            createButtonHasBeenPressed()
        }
    }

    fun createButtonHasBeenPressed() {
        val email = editText_signUp_email.text.toString()
        val password = editText_signUp_password.text.toString()

        if (email.isEmpty() or password.isEmpty()) {

            if (email.isEmpty())
                editText_signUp_email.error = "Email is missing !"

            if (isEmailValid(email))
                editText_signUp_email.error = "You need to insert a correct email"

            if (isPasswordValid(password))
                editText_signUp_email.error = "You need to insert a correct email"

            if (password.isEmpty())
                editText_signUp_password.error = "Password is missing !"

            return
        }

        createAccount(email, password)
    }

    fun isEmailValid(email: CharSequence): Boolean {
        return android.util.Patterns.EMAIL_ADDRESS.matcher(email).matches()
    }

    fun isPasswordValid(password : CharSequence) : Boolean {

        val PASSWORD_PATTERN = "^(?=.*[0-9])(?=.*[a-z])(?=.*[A-Z])(?=\\S+$).{4,}$"

        val pattern = Pattern.compile(PASSWORD_PATTERN)
        val matcher = pattern.matcher(password);

        return matcher.matches();
    }

    private fun createAccount(email : String, password :String) {

        val m = JSONObject()

        m.put("id", "0002")
        m.put("destination", "S001")
        m.put("email", email)
        m.put("password", hash(password))

        Client.getInstance(this).pushMessage(m,
                {response ->
                    val userCode = response["result"] as Int
                    if (userCode != 0) {
                        DataSaver(this).isUserLogged = true
                        DataSaver(this).userCode = userCode.toString()
                        startActivity( Intent(this, ToysEmptyActivity::class.java))
                    } else {
                        // Initialize a new instance of
                        val builder = AlertDialog.Builder(this)

                        // Set the alert dialog title
                        builder.setTitle("Already existing")

                        // Display a message on alert dialog
                        builder.setMessage("The email provided is already present in the DB")

                        // Display a neutral button on alert dialog
                        builder.setNeutralButton("Cancel"){_,_ -> }

                        // Finally, make the alert dialog using builder
                        val dialog: AlertDialog = builder.create()

                        // Display the alert dialog on app interface
                        dialog.show()
                    }
                })
    }

    fun hash(password : String): String {
        val bytes = password.toByteArray()
        val md = MessageDigest.getInstance("SHA-256")
        val digest = md.digest(bytes)
        return digest.fold("", { str, it -> str + "%02x".format(it) })
    }
}
