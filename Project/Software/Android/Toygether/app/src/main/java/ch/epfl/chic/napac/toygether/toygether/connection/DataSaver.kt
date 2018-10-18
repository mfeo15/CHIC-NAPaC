package ch.epfl.chic.napac.toygether.toygether.connection

import android.content.Context

/**
 * Created by mfeo15 on 02.05.18.
 */
class DataSaver (context: Context){


    private val prefs = context.getSharedPreferences(DataSaver.SHARED_PREFERENCES_NAME, Context.MODE_PRIVATE)


    companion object {

        const val SHARED_PREFERENCES_NAME = "toygether_prefs"

        const val KEY_USER_CODE = "user_code"

        const val KEY_USER_LOGGED = "user_logged"

        const val KEY_TOYS_COUNT = "toys_count"

        const val KEY_TOY_NAME = "toy_name"

        const val KEY_TOY_CODE = "toy_code"
    }

    var userCode : String
        get() = prefs.getString(DataSaver.KEY_USER_CODE, "")
        set(value) = prefs.edit().putString(DataSaver.KEY_USER_CODE, value).apply()

    var isUserLogged : Boolean
        get() = prefs.getBoolean(DataSaver.KEY_USER_LOGGED, false)
        set(value) = prefs.edit().putBoolean(DataSaver.KEY_USER_LOGGED, value).apply()

    var toysCount : Int
        get() = prefs.getInt(DataSaver.KEY_TOYS_COUNT, 0)
        set(value) = prefs.edit().putInt(DataSaver.KEY_TOYS_COUNT, value).apply()

    var toyName : String
        get() = prefs.getString(DataSaver.KEY_TOY_NAME, "")
        set(value) = prefs.edit().putString(DataSaver.KEY_TOY_NAME, value).apply()

    var toyCode : String
        get() = prefs.getString(DataSaver.KEY_TOY_CODE, "")
        set(value) = prefs.edit().putString(DataSaver.KEY_TOY_CODE, value).apply()


    fun storeNewToy(c : String) {

        this.storeNewToy(c, "new_toy_"+(this.toyCode+1))
    }

    fun storeNewToy(c : String, n : String) {
        this.toysCount = this.toysCount + 1
        this.toyName = n
        this.toyCode = c
    }

    fun clear() {
        val editor = prefs.edit()
        editor.clear()
        editor.apply()
    }
}