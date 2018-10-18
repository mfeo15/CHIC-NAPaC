package ch.epfl.chic.napac.toygether.toygether

import android.animation.ValueAnimator
import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import ch.epfl.chic.napac.toygether.toygether.connection.ClientTCP
import ch.epfl.chic.napac.toygether.toygether.connection.Message
import kotlinx.android.synthetic.main.activity_waiting_for_toy.*
import java.util.*
import android.animation.Animator
import android.animation.AnimatorListenerAdapter
import android.animation.AnimatorSet
import android.os.Handler
import android.widget.ImageView
import ch.epfl.chic.napac.toygether.toygether.connection.Client
import org.json.JSONObject


class WaitingForToyActivity : AppCompatActivity() {

    // TODO : Implement pooling routine

    fun withDelay(delay : Long, block : () -> Unit) {
        Handler().postDelayed(Runnable(block), delay)
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_waiting_for_toy)

        val x = imageView_red.x
        animateDot(imageView_red, x)
        withDelay(500) { animateDot(imageView_blue, x) }
        withDelay(1000) { animateDot(imageView_yellow, x) }

        button_waiting_toy_close.setOnClickListener {
            finish()
        }

        val toyCode = intent.extras.getString("toy_code")

        val m = JSONObject()
        m.put("id", "2001")
        m.put("source", "P123")
        m.put("destination", toyCode)

        Client.getInstance(this).pushMessage(m)
    }

    fun animateDot(v: ImageView?, x : Float) {

        // It's just a jump to the right ...
        val valueAnimatorRight = ValueAnimator.ofFloat(x, (x+100))
        valueAnimatorRight.addUpdateListener {
            val value = it.animatedValue as Float
            v!!.translationX = value
        }

        // And one to thhe leeeeeeft
        val valueAnimatorLeft = ValueAnimator.ofFloat((x+100), x)
        valueAnimatorLeft.addUpdateListener {
            val value = it.animatedValue as Float
            v!!.translationX = value
        }


        val animatorSet = AnimatorSet()

        animatorSet.play(valueAnimatorRight).after(valueAnimatorLeft)

        animatorSet.addListener(object : AnimatorListenerAdapter() {
            override fun onAnimationEnd(animation: Animator) {
                super.onAnimationEnd(animation)
                animatorSet.start()
            }

        })

        animatorSet.duration = 1000
        animatorSet.start()
    }
}
