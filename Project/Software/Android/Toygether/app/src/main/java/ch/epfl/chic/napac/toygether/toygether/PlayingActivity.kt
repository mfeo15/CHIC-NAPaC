package ch.epfl.chic.napac.toygether.toygether

import android.animation.AnimatorSet
import android.animation.ValueAnimator
import android.content.Context
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.support.v4.content.ContextCompat
import android.view.View
import kotlinx.android.synthetic.main.activity_playing.*
import java.util.*
import android.widget.RelativeLayout
import android.media.MediaPlayer
import android.support.constraint.ConstraintLayout
import android.util.Log
import android.widget.Button
import ch.epfl.chic.napac.toygether.toygether.connection.Client
import ch.epfl.chic.napac.toygether.toygether.connection.DataSaver
import ch.epfl.chic.napac.toygether.toygether.connection.JSONMessage

class PlayingActivity : AppCompatActivity(), View.OnClickListener {

    enum class Actor { PARENT, TOY }

    enum class ButtonMode(val cardinal : Int) { OFF(0), ON_PARENT(1), ON_TOY(2) }

    enum class Status(val value : String) { ON("ON"), OFF("OFF") }

    var context : Context? = null

    var toyCode = ""

    var buttons = arrayOfNulls<Button>(6)

    var timer = Timer()
    var myTask: TimerTask = object : TimerTask() {
        override fun run() {

            Client.getInstance(context).pullMessage()
            { response ->
                //Log.i("AAA", response.toString())

                if (response["id"] as String == "2003") {

                    when (response["status"]) {
                        Status.ON.value    ->  turnON(Actor.TOY, (response["zone"] as String).toInt() )
                        Status.OFF.value   ->  turnOFF(Actor.TOY, (response["zone"] as String).toInt() )
                    }
                }
            }
        }
    }

    override fun onClick(v: View?) {

        playSound( getZoneOrdinal(v) )

        if (v?.tag == ButtonMode.OFF || v?.tag == ButtonMode.ON_PARENT ) {

            //if (v?.tag == 0) animateButtonOnActivation(v)
            //if (v?.tag == 1) animateButtonOnRetouch(v)

            turnON(Actor.PARENT, getZoneOrdinal(v) )
            return
        }

        if (v?.tag == ButtonMode.ON_TOY) {

            turnOFF(Actor.PARENT, getZoneOrdinal(v) )
            return
        }
    }

    override fun onResume() {
        super.onResume()

        // TODO: check un-pause the pooling
        timer = Timer()
        timer.schedule(myTask, 500, Client.POOLING_DELAY_MS)
    }

    override fun onPause() {
        super.onPause()

        // TODO: check pause the pooling
        timer.cancel()
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_playing)

        context = this

        button_playing_close.tag = 0

        //toyCode = intent.extras.getString("toy_code")
        toyCode = "T314"

        button_playing_close.setOnClickListener {

            if (button_playing_close.tag == 0) {
                button_playing_close.tag = 1

                button_playing_close.setLayoutParams(RelativeLayout.LayoutParams((button_playing_close.width * 2.5).toInt(), button_playing_close.height))

                button_playing_close.background = ContextCompat.getDrawable(this, R.drawable.continue_left_confirm)
            } else {
                // Button pressed the second time, therefore the tag has been raised to 1 before
                Client.getInstance(this).pushMessage(JSONMessage(this, "2005", toyCode).toJSON())
                finish()
            }
        }

        buttons[0] = button_interactive_1
        buttons[1] = button_interactive_2
        buttons[2] = button_interactive_3
        buttons[3] = button_interactive_4
        buttons[4] = button_interactive_5
        buttons[5] = button_interactive_6

        for (b in buttons) {
            b?.tag = ButtonMode.OFF
            b?.setOnClickListener(this)
        }

        DataSaver(this).userCode = "P123"
    }

    private fun sendMessageForLED(zone : String, status : String) {

        val m = JSONMessage(this,"2003", toyCode, arrayOf("zone", "status"), arrayOf(zone, status))
        Client.getInstance(this).pushMessage( m.toJSON() )
    }

    private fun turnON(turnedONBy : Actor, zoneNumber: Int) {

        if (buttons[zoneNumber - 1]?.tag == ButtonMode.OFF)
            animateButtonOnActivation(buttons[zoneNumber - 1] as View)

        if (buttons[zoneNumber - 1]?.tag == ButtonMode.ON_PARENT)
            animateButtonOnRetouch(buttons[zoneNumber - 1] as View)


        buttons[zoneNumber - 1]?.background = ContextCompat.getDrawable(this, getDrawableForButton(zoneNumber, turnedONBy))

        when (turnedONBy) {
            Actor.PARENT -> { // Me
                buttons[zoneNumber - 1]?.tag = ButtonMode.ON_PARENT
                sendMessageForLED(zoneNumber.toString(), Status.ON.value)
            }
            Actor.TOY -> { // Toy
                buttons[zoneNumber - 1]?.tag = ButtonMode.ON_TOY
            }
        }
    }

    private fun turnOFF(turnedOFFBy : Actor, zoneNumber : Int) {

        if (turnedOFFBy == Actor.PARENT) // I am the one requesting the turn OFF. I need to say it to the toy
            sendMessageForLED(zoneNumber.toString(), Status.OFF.value)

        animateButtonOnDeactivation(buttons[zoneNumber - 1] as View)

        //buttons[zoneNumber - 1]?.setLayoutParams(ConstraintLayout.LayoutParams(200, 200))
        //buttons[zoneNumber - 1]?.background = ContextCompat.getDrawable(this, R.drawable.play_off)

        buttons[zoneNumber - 1]?.background = ContextCompat.getDrawable(this, R.drawable.play_off)
        buttons[zoneNumber - 1]?.tag = ButtonMode.OFF
    }

    // TODO: check and fix
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

    private fun getDrawableForButton(buttonNumber : Int, by : Actor): Int {

        if (buttonNumber == 1)
            return if (by == Actor.PARENT) R.drawable.play_blue_1_6 else R.drawable.play_yellow_1_6

        if (buttonNumber == 2)
            return if (by == Actor.PARENT) R.drawable.play_blue_2_5 else R.drawable.play_yellow_2_5

        if (buttonNumber == 3)
            return if (by == Actor.PARENT) R.drawable.play_blue_3 else R.drawable.play_yellow_3

        if (buttonNumber == 4)
            return if (by == Actor.PARENT) R.drawable.play_blue_4 else R.drawable.play_yellow_4

        if (buttonNumber == 5)
            return if (by == Actor.PARENT) R.drawable.play_blue_2_5 else R.drawable.play_yellow_2_5

        if (buttonNumber == 6)
            return if (by == Actor.PARENT) R.drawable.play_blue_1_6 else R.drawable.play_yellow_1_6

        return 0
    }

    private fun animateButtonOnRetouch(v : View) {

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
        val valueAnimatorDownSize = ValueAnimator.ofFloat(1.0f, 0.2f)
        valueAnimatorDownSize.addUpdateListener {
            val value = it.animatedValue as Float
            v.scaleX = value
            v.scaleY = value
        }

        val valueAnimatorRegrow = ValueAnimator.ofFloat(0.2f, 1.0f)
        valueAnimatorRegrow.addUpdateListener {
            val value = it.animatedValue as Float
            v.scaleX = value
            v.scaleY = value
        }

        val animatorSet = AnimatorSet()
        animatorSet.play(valueAnimatorRegrow).after(valueAnimatorDownSize)
        animatorSet.duration = 150
        animatorSet.start()

        //valueAnimatorDownSize.duration = 100
        //valueAnimatorDownSize.start()

        // Resize to a small button
        //v.scaleY = 100.0f
        //v.scaleX = 100.0f
    }

    private fun getLastChar(str : String) : String {
        return str.substring(str.length - 1)
    }

    private fun getZoneOrdinal(b : View?) : Int {

        when (b?.id) {
            R.id.button_interactive_1 -> return 1
            R.id.button_interactive_2 -> return 2
            R.id.button_interactive_3 -> return 3
            R.id.button_interactive_4 -> return 4
            R.id.button_interactive_5 -> return 5
            R.id.button_interactive_6 -> return 6
        }

        return -1
    }
}