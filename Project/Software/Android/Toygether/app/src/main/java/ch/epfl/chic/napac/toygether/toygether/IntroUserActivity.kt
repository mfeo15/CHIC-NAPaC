package ch.epfl.chic.napac.toygether.toygether

import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import kotlinx.android.synthetic.main.activity_intro_user.*

class IntroUserActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_intro_user)

        button_new_user.setOnClickListener{
            startActivity( Intent(this, SignUpActivity::class.java))
        }

        button_old_user.setOnClickListener{
            startActivity( Intent(this, SignInActivity::class.java))
        }
    }
}
