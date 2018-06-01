package ch.epfl.chic.napac.toygether.toygether

import android.animation.ValueAnimator
import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import ch.epfl.chic.napac.toygether.toygether.connection.Client
import ch.epfl.chic.napac.toygether.toygether.connection.Message
import kotlinx.android.synthetic.main.activity_waiting_for_toy.*
import java.util.*
import android.animation.Animator
import android.animation.AnimatorListenerAdapter
import android.animation.AnimatorSet
import android.os.Handler
import android.widget.ImageView


class WaitingForToyActivity : AppCompatActivity(), Observer {

    override fun update(o: Observable?, arg: Any?) {
        when (o) {
            is Client -> {
                if (arg is Message) {
                    val nextActivityIntent = Intent(this, PlayingActivity::class.java)
                    nextActivityIntent.putExtra("toy_code", intent.extras.getString("toy_code"))
                    startActivity( nextActivityIntent)
                }
            }
        }
    }

    fun withDelay(delay : Long, block : () -> Unit) {
        Handler().postDelayed(Runnable(block), delay)
    }

    override fun onResume() {
        super.onResume()

        Client.getInstance().addNewObserver(this)
    }

    override fun onPause() {
        super.onPause()

        Client.getInstance().deleteAnObserver(this)
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
        Client.getInstance().send( Message(toyCode, "U123", "2001").toString() )
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
