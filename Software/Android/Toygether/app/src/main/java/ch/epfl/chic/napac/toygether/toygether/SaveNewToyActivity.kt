package ch.epfl.chic.napac.toygether.toygether

import android.content.Context
import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import ch.epfl.chic.napac.toygether.toygether.connection.DataSaver
import kotlinx.android.synthetic.main.activity_save_new_toy.*

class SaveNewToyActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_save_new_toy)

        val toyCode = intent.extras.getString("toy_code")

        button_name_new_toy.setOnClickListener {

            DataSaver(this).storeNewToy(toyCode)

            startActivity( Intent(this, ToysEmptyActivity::class.java))
        }
    }
}
