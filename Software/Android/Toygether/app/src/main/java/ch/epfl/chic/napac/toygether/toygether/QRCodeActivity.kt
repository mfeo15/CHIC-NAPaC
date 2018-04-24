package ch.epfl.chic.napac.toygether.toygether

import android.content.Context
import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import kotlinx.android.synthetic.main.activity_qrcode.*
import com.google.android.gms.common.api.CommonStatusCodes
import com.google.android.gms.vision.barcode.Barcode
import ch.epfl.chic.napac.toygether.toygether.barcode.BarcodeCaptureActivity

class QRCodeActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_qrcode)

        button_scan.setOnClickListener {
            val intent = Intent(applicationContext, BarcodeCaptureActivity::class.java)
            startActivityForResult(intent, BARCODE_READER_REQUEST_CODE)
        }
    }

    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        if (requestCode == BARCODE_READER_REQUEST_CODE) {
            if (resultCode == CommonStatusCodes.SUCCESS) {
                if (data != null) {
                    val barcode = data.getParcelableExtra<Barcode>(BarcodeCaptureActivity.BarcodeObject)
                    val p = barcode.cornerPoints
                    //textView_result.text = barcode.displayValue
                    parseQRCodeResult(barcode.displayValue)
                } else
                    textView_result.setText(R.string.no_barcode_captured)
            } else
                Log.e(LOG_TAG, String.format(getString(R.string.barcode_error_format),
                        CommonStatusCodes.getStatusCodeString(resultCode)))
        } else
            super.onActivityResult(requestCode, resultCode, data)
    }

    private fun parseQRCodeResult(value: String) {

        val prefs = getSharedPreferences(sharedPreferencesConstants.SHARED_PREFERENCES_NAME, Context.MODE_PRIVATE)
        val editor = prefs.edit()
        editor.putInt(sharedPreferencesConstants.KEY_TOYS_COUNT, prefs.getInt(sharedPreferencesConstants.KEY_TOYS_COUNT, 0) + 1)
        editor.putString(sharedPreferencesConstants.KEY_TOY_CODE, value)
        editor.apply()

        startActivity( Intent(this, SaveNewToyActivity::class.java))
    }

    companion object {
        private val LOG_TAG = QRCodeActivity::class.java.simpleName
        private val BARCODE_READER_REQUEST_CODE = 1
    }
}
