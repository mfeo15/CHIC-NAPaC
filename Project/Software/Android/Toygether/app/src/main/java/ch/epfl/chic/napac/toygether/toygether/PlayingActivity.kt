package ch.epfl.chic.napac.toygether.toygether

import android.animation.AnimatorSet
import android.animation.ValueAnimator
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.support.v4.content.ContextCompat
import android.util.Log
import android.view.View
import ch.epfl.chic.napac.toygether.toygether.connection.Client
import ch.epfl.chic.napac.toygether.toygether.connection.Message
import kotlinx.android.synthetic.main.activity_playing.*
import java.util.*
import android.widget.RelativeLayout
import android.media.MediaPlayer

class PlayingActivity : AppCompatActivity(), View.OnClickListener, Observer {

    var toyCode = ""

    override fun update(o: Observable?, arg: Any?) {
        when (o) {
            is Client -> {
                if (arg is Message) {
                    Log.d("PLAYING", arg.toString())
                    if (arg.messageID.equals("2003")) {

                        when (arg.parameters[0].toInt()) {
                            1 -> turnON(button_interactive_1, 1, 2, 1)
                            2 -> turnON(button_interactive_2, 2, 2, 2)
                            3 -> turnON(button_interactive_3, 3, 2,3)
                            4 -> turnON(button_interactive_4, 4, 2, 4)
                            5 -> turnON(button_interactive_5, 5, 2,5)
                            6 -> turnON(button_interactive_6, 6, 2,6)
                        }
                        return
                    }

                    if (arg.messageID.equals("2004")) {

                        when (arg.parameters[0].toInt()) {
                            1 -> turnOFF(button_interactive_1, 1, 2)
                            2 -> turnOFF(button_interactive_2, 2, 2)
                            3 -> turnOFF(button_interactive_3, 3, 2)
                            4 -> turnOFF(button_interactive_4, 4, 2)
                            5 -> turnOFF(button_interactive_5, 5, 2)
                            6 -> turnOFF(button_interactive_6, 6, 2)
                        }
                    }
                }
            }
        }
    }

    override fun onClick(v: View?) {

        when (v?.id) {
            R.id.button_interactive_1 -> playSound(1)
            R.id.button_interactive_2 -> playSound(2)
            R.id.button_interactive_3 -> playSound(3)
            R.id.button_interactive_4 -> playSound(4)
            R.id.button_interactive_5 -> playSound(5)
            R.id.button_interactive_6 -> playSound(6)
        }

        if (v?.tag == 0 || v?.tag == 1 ) {

            if (v.tag == 0) animateButtonOnActivation(v)
            if (v.tag == 1) animateButtonOnretouch(v)

            when (v.id) {
                R.id.button_interactive_1 -> turnON(button_interactive_1, 1, 1, 1)
                R.id.button_interactive_2 -> turnON(button_interactive_2, 2, 1, 2)
                R.id.button_interactive_3 -> turnON(button_interactive_3, 3, 1, 3)
                R.id.button_interactive_4 -> turnON(button_interactive_4, 4, 1, 4)
                R.id.button_interactive_5 -> turnON(button_interactive_5, 5, 1, 5)
                R.id.button_interactive_6 -> turnON(button_interactive_6, 6, 1, 6)
            }

            return
        }

        if (v?.tag == 2) {

            when (v.id) {
                R.id.button_interactive_1 -> turnOFF(button_interactive_1, 1, 1)
                R.id.button_interactive_2 -> turnOFF(button_interactive_2, 2, 1)
                R.id.button_interactive_3 -> turnOFF(button_interactive_3, 3, 1)
                R.id.button_interactive_4 -> turnOFF(button_interactive_4, 4, 1)
                R.id.button_interactive_5 -> turnOFF(button_interactive_5, 5, 1)
                R.id.button_interactive_6 -> turnOFF(button_interactive_6, 6, 1)
            }
            return
        }
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
        setContentView(R.layout.activity_playing)

        button_playing_close.tag = 0

        //toyCode = intent.extras.getString("toy_code")
        toyCode = "P314"

        button_playing_close.setOnClickListener {

            if (button_playing_close.tag == 0) {
                button_playing_close.tag = 1

                button_playing_close.setLayoutParams(RelativeLayout.LayoutParams((button_playing_close.width * 2.5).toInt(), button_playing_close.height))

                button_playing_close.background = ContextCompat.getDrawable(this, R.drawable.continue_left_confirm)
            } else {
                // Button pressed the second time, therefore the tag has been raised to 1 before
                Client.getInstance().send(Message(toyCode, "U123", "2005").toString())
                finish()
            }
        }

        button_interactive_1.tag = 0
        button_interactive_2.tag = 0
        button_interactive_3.tag = 0
        button_interactive_4.tag = 0
        button_interactive_5.tag = 0
        button_interactive_6.tag = 0

        button_interactive_1.setOnClickListener(this)
        button_interactive_2.setOnClickListener(this)
        button_interactive_3.setOnClickListener(this)
        button_interactive_4.setOnClickListener(this)
        button_interactive_5.setOnClickListener(this)
        button_interactive_6.setOnClickListener(this)
    }

    private fun sendMessageForLED(messageID : String, led : String) {
        Client.getInstance().send(Message(toyCode, "U123", messageID, arrayOf(led)).toString())
    }

    private fun turnON(v: View?, led : Int, turnedONBy : Int, buttonNumber: Int) {

        //animateButtonOnActivation(v as View)
        v?.background = ContextCompat.getDrawable(this, getDrawableForButton(buttonNumber, turnedONBy))

        when (turnedONBy) {
            1 -> { // Me
                v?.tag = 1
                sendMessageForLED("2003", led.toString())
            }
            2 -> { // Toy
                v?.tag = 2
            }
        }
    }

    private fun turnOFF(v: View?, led : Int, turnedOFFBy : Int) {

        if (turnedOFFBy == 1) // I am the one requesting the turn OFF. I need to say it to the toy
            sendMessageForLED("2004", led.toString())

        //animateButtonOnDeactivation(v as View)
        v?.background = ContextCompat.getDrawable(this, R.drawable.play_off)
        v?.tag = 0
    }

    private fun playSound(num : Int) {

        if (num == 1) {
            val mp = MediaPlayer.create(this, R.raw.note_mi )
            mp.start()

            return
        }

        if (num == 2) {
            val mp = MediaPlayer.create(this, R.raw.note_fa )
            mp.start()

            return
        }

        if (num == 3) {
            val mp = MediaPlayer.create(this, R.raw.note_sol )
            mp.start()

            return
        }

        if (num == 4) {
            val mp = MediaPlayer.create(this, R.raw.note_la )
            mp.start()

            return
        }

        if (num == 5) {
            val mp = MediaPlayer.create(this, R.raw.note_si )
            mp.start()

            return
        }

        if (num == 6) {
            val mp = MediaPlayer.create(this, R.raw.note_do )
            mp.start()

            return
        }
    }

    private fun getDrawableForButton(buttonNumber : Int, by : Int): Int {

        if (buttonNumber == 1)
            return if (by == 1) R.drawable.play_blue_1_6 else R.drawable.play_yellow_1_6

        if (buttonNumber == 2)
            return if (by == 1) R.drawable.play_blue_2_5 else R.drawable.play_yellow_2_5

        if (buttonNumber == 3)
            return if (by == 1) R.drawable.play_blue_3 else R.drawable.play_yellow_3

        if (buttonNumber == 4)
            return if (by == 1) R.drawable.play_blue_4 else R.drawable.play_yellow_4

        if (buttonNumber == 5)
            return if (by == 1) R.drawable.play_blue_2_5 else R.drawable.play_yellow_2_5

        if (buttonNumber == 6)
            return if (by == 1) R.drawable.play_blue_1_6 else R.drawable.play_yellow_1_6

        return 0
    }

    private fun animateButtonOnretouch(v : View) {

        val valueAnimatorAlphaDown = ValueAnimator.ofFloat(1.0f, 0.5f)
        valueAnimatorAlphaDown.addUpdateListener {
            val value = it.animatedValue as Float
            v.alpha = value
        }

        val valueAnimatorAlphaUp = ValueAnimator.ofFloat(0.5f, 1.0f)
        valueAnimatorAlphaUp.addUpdateListener {
            val value = it.animatedValue as Float
            v.alpha = value
        }

        val valueAnimatorScaleUp = ValueAnimator.ofFloat(1.0f, 1.2f)
        valueAnimatorScaleUp.addUpdateListener {
            val value = it.animatedValue as Float
            v.scaleX = value
            v.scaleY = value
        }

        val valueAnimatorScaleDown = ValueAnimator.ofFloat(1.2f, 1.0f)
        valueAnimatorScaleDown.addUpdateListener {
            val value = it.animatedValue as Float
            v.scaleX = value
            v.scaleY = value
        }

        val animatorSet = AnimatorSet()
        val animatorSet1 = AnimatorSet()
        val animatorSet2 = AnimatorSet()

        animatorSet1.play(valueAnimatorScaleUp).with(valueAnimatorAlphaDown)
        animatorSet2.play(valueAnimatorScaleDown).with(valueAnimatorAlphaUp)

        animatorSet.play(animatorSet2).after(animatorSet1)

        animatorSet.duration = 100
        animatorSet.start()
    }

    private fun animateButtonOnActivation(v : View) {
        // Resize to a small button
        v.scaleY = 0f
        v.scaleX = 0f

        //Animate the ScaleUp
        val valueAnimatorGrowUp = ValueAnimator.ofFloat(0f, 1.2f)
        valueAnimatorGrowUp.addUpdateListener {
            val value = it.animatedValue as Float
            v.scaleX = value
            v.scaleY = value
        }

        val valueAnimatorRescaleDown = ValueAnimator.ofFloat(1.2f, 1.0f)
        valueAnimatorRescaleDown.addUpdateListener {
            val value = it.animatedValue as Float
            v.scaleX = value
            v.scaleY = value
        }

        val animatorSet = AnimatorSet()
        animatorSet.play(valueAnimatorRescaleDown).after(valueAnimatorGrowUp)
        animatorSet.duration = 100
        animatorSet.start()
    }

    private fun animateButtonOnDeactivation(v : View) {

        //Animate the ScaleUp
        val valueAnimatorDownSize = ValueAnimator.ofFloat(1.0f, 0.0f)
        valueAnimatorDownSize.addUpdateListener {
            val value = it.animatedValue as Float
            v.scaleX = value
            v.scaleY = value
        }

        valueAnimatorDownSize.duration = 100
        valueAnimatorDownSize.start()

        // Resize to a small button
        v.scaleY = 1.0f
        v.scaleX = 1.0f

        v.background = ContextCompat.getDrawable(this, R.drawable.play_off)
    }
}