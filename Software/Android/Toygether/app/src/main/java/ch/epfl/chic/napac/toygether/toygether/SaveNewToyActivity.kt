package ch.epfl.chic.napac.toygether.toygether

import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import kotlinx.android.synthetic.main.activity_save_new_toy.*

class SaveNewToyActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_save_new_toy)

        button_name_new_toy.setOnClickListener {
            startActivity( Intent(this, ToysEmptyActivity::class.java))
        }
    }
}
