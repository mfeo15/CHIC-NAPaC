package ch.epfl.chic.napac.toygether.toygether

import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.support.v7.app.AlertDialog
import android.util.Log
import ch.epfl.chic.napac.toygether.toygether.connection.Client
import ch.epfl.chic.napac.toygether.toygether.connection.DataSaver
import kotlinx.android.synthetic.main.activity_sign_in.*
import org.json.JSONObject
import java.security.MessageDigest

class SignInActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_sign_in)

        button_signin_back.setOnClickListener {
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
        val email = editText_signUp_email.text.toString()
        val password = editText_signUp_password.text.toString()

        if (email.isEmpty() or password.isEmpty()) {

            if (email.isEmpty())
                editText_signUp_email.error = "Email is missing !"

            if (isEmailValid(email))
                editText_signUp_email.error = "You need to insert a correct email"

            if (password.isEmpty())
                editText_signUp_password.error = "Password is missing !"

            return
        }

        checkCredentials(email, password)
    }

    fun isEmailValid(email: CharSequence): Boolean {
        return android.util.Patterns.EMAIL_ADDRESS.matcher(email).matches()
    }

    private fun checkCredentials(email : String, password :String) {

        val m = JSONObject()

        m.put("id", "0001")
        m.put("destination", "S001")
        m.put("email", email)
        m.put("password", hash(password))

        Client.getInstance(this).pushMessage(m)
                {response ->
                    Log.i("AAA", response.toString())
                    if (response["id"] as String == "1") {
                        DataSaver(this).isUserLogged = true
                        // TODO: Check if PID is saved correctly
                        DataSaver(this).userCode = response["value"].toString()

                        downloadPreviousAssociatedToys(response["value"].toString() )

                        //startActivity( Intent(this, ToysEmptyActivity::class.java))
                    } else {
                        // Initialize a new instance of
                        val builder = AlertDialog.Builder(this)

                        // Set the alert dialog title
                        builder.setTitle("Error login")

                        // Display a message on alert dialog
                        builder.setMessage("Wrong email or password :-(")

                        // Display a neutral button on alert dialog
                        builder.setNeutralButton("Cancel"){_,_ -> }

                        // Finally, make the alert dialog using builder
                        val dialog: AlertDialog = builder.create()

                        // Display the alert dialog on app interface
                        dialog.show()
                    }
                }
    }

    fun hash(password : String): String {
        val bytes = password.toByteArray()
        val md = MessageDigest.getInstance("SHA-256")
        val digest = md.digest(bytes)
        return digest.fold("", { str, it -> str + "%02x".format(it) })
    }

    // TODO: Awful method
    fun downloadPreviousAssociatedToys(userCode : String) {
        // Download from server previously associated toys
        val m = JSONObject()

        m.put("id", "0003")
        m.put("destination", "S001")
        m.put("source", userCode)

        Client.getInstance(this).pushMessage(m)
        { response ->
            Log.i("AAA", response.toString())
            if (response["id"] as String == "1") {

                Client.getInstance(this)
                        .pushMessage(JSONObject().apply
                        {
                            put("id", "0005")
                            put("destination", "S001")
                            put("toy", response["value"].toString())
                        })
                        { response ->
                            Log.i("BBB", response.toString())
                            if (response["id"] as String == "1") {
                                val toy = response["value"] as JSONObject
                                DataSaver(this).storeNewToy(toy["tid"].toString(), toy["child_name"].toString())
                            }

                            startActivity( Intent(this, ToysEmptyActivity::class.java))
                        }
            }
        }

    }

}
