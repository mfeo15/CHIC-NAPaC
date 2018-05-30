package ch.epfl.chic.napac.toygether.toygether

import android.animation.ValueAnimator
import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.view.animation.LinearInterpolator
import ch.epfl.chic.napac.toygether.toygether.connection.Client
import ch.epfl.chic.napac.toygether.toygether.connection.Message
import kotlinx.android.synthetic.main.activity_waiting_for_toy.*
import java.util.*
import android.animation.Animator
import android.animation.AnimatorListenerAdapter
import android.animation.AnimatorSet


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

    override fun onResume() {
        super.onResume()

        // 1
        val valueAnimatorRight = ValueAnimator.ofFloat(imageView3.x, (imageView3.x+50))

        //2
        valueAnimatorRight.addUpdateListener {
            val value = it.animatedValue as Float
            imageView3.translationX = value
        }


        val valueAnimatorLeft = ValueAnimator.ofFloat((imageView3.x+50), imageView3.x)

        //2
        valueAnimatorLeft.addUpdateListener {
            val value = it.animatedValue as Float
            imageView3.translationX = value
        }

// 4
        val animatorSet = AnimatorSet()
// 5
        animatorSet.play(valueAnimatorRight).after(valueAnimatorLeft)

        animatorSet.addListener(object : AnimatorListenerAdapter() {

            override fun onAnimationEnd(animation: Animator) {
                super.onAnimationEnd(animation)
                animatorSet.start()
            }

        })

// 6

        animatorSet.duration = 1000
        animatorSet.start()




        Client.getInstance().addNewObserver(this)
    }

    override fun onPause() {
        super.onPause()

        Client.getInstance().deleteAnObserver(this)
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_waiting_for_toy)

        button_waiting_toy_close.setOnClickListener {
            finish()
        }

        val toyCode = intent.extras.getString("toy_code")
        Client.getInstance().send( Message(toyCode, "U123", "2001").toString() )
    }

    fun animateDot() {

        // It's just a jump to the right ...
        val valueAnimatorRight = ValueAnimator.ofFloat(imageView3.x, (imageView3.x+50))
        valueAnimatorRight.addUpdateListener {
            val value = it.animatedValue as Float
            imageView3.translationX = value
        }

        // And one to thhe leeeeeeft
        val valueAnimatorLeft = ValueAnimator.ofFloat((imageView3.x+50), imageView3.x)
        valueAnimatorLeft.addUpdateListener {
            val value = it.animatedValue as Float
            imageView3.translationX = value
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
