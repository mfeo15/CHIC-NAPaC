package ch.epfl.chic.napac.toygether.toygether

import android.content.Context
import android.content.DialogInterface
import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.support.v7.app.AlertDialog
import ch.epfl.chic.napac.toygether.toygether.connection.DataSaver
import kotlinx.android.synthetic.main.activity_settings.*

class SettingsActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_settings)

        button_settings_close.setOnClickListener {
            finish()
        }

        button_notifications.setOnClickListener {
            startActivity( Intent(this, SettingsNotificationsActivity::class.java))
        }

        button_log_out.setOnClickListener {
            val builder = AlertDialog.Builder(this)
            builder.setTitle("Log off?")
            builder.setMessage("Are you sure to continue? By pressing yes you will need to log in again inside the app")
            builder.setPositiveButton("Yes", { dialogInterface: DialogInterface, i: Int ->
                DataSaver(this).clear()
                startActivity( Intent(this, SignInActivity::class.java))
            })
            builder.setNegativeButton("No", { dialogInterface: DialogInterface, i: Int -> })
            builder.show()
        }
    }
}
