package ch.epfl.chic.napac.toygether.toygether;

import android.app.ProgressDialog;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.DialogInterface;
import android.content.DialogInterface.OnCancelListener;
import android.content.Intent;
import android.content.IntentFilter;
import android.net.NetworkInfo;
import android.net.wifi.WifiManager;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.text.TextUtils;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import com.espressif.iot.esptouch.EsptouchTask;
import com.espressif.iot.esptouch.IEsptouchResult;
import com.espressif.iot.esptouch.IEsptouchTask;
import com.espressif.iot.esptouch.task.__IEsptouchTask;
import com.espressif.iot.esptouch.util.EspAES;

import java.util.List;

public class SmartConfigActivity extends AppCompatActivity implements OnClickListener {

    private static final String TAG = "SmartConfigActivity";

    private TextView mTvApSsid;

    private EditText mEdtApPassword;

    private Button mBtnConfirm;

    private Button mButtonClose;

    private Button mButtonDEBUGSKIP;

    private EspWifiAdminSimple mWifiAdmin;

    private EsptouchAsyncTask3 mTask;

    private BroadcastReceiver mReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            String action = intent.getAction();
            if (action == null) {
                return;
            }

            switch (action) {
                case WifiManager.NETWORK_STATE_CHANGED_ACTION:
                    NetworkInfo ni = intent.getParcelableExtra(WifiManager.EXTRA_NETWORK_INFO);
                    if (ni != null && !ni.isConnected()) {
                        if (mTask != null) {
                            mTask.cancelEsptouch();
                            mTask = null;
                            new AlertDialog.Builder(SmartConfigActivity.this)
                                    .setMessage("Wifi disconnected or changed")
                                    .setNegativeButton(android.R.string.cancel, null)
                                    .show();
                        }
                    }
                    break;
            }
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_smartconfig);

        mWifiAdmin = new EspWifiAdminSimple(this);
        mTvApSsid = findViewById(R.id.tvApSssidConnected);
        mEdtApPassword = findViewById(R.id.edtApPassword);
        mBtnConfirm = findViewById(R.id.btnConfirm);
        mBtnConfirm.setOnClickListener(this);
        mButtonClose = findViewById(R.id.button_smartConfig_close);
        mButtonClose.setOnClickListener(this);

        mButtonDEBUGSKIP = findViewById(R.id.button_smartconfig_skip);
        mButtonDEBUGSKIP.setOnClickListener(this);

        IntentFilter filter = new IntentFilter(WifiManager.NETWORK_STATE_CHANGED_ACTION);
        registerReceiver(mReceiver, filter);
    }
    
    @Override
    protected void onResume() {
        super.onResume();
        // display the connected ap's ssid
        String apSsid = mWifiAdmin.getWifiConnectedSsid();
        if (apSsid != null) {
            mTvApSsid.setText(apSsid);
        } else {
            mTvApSsid.setText("");
        }
        // check whether the wifi is connected
        boolean isApSsidEmpty = TextUtils.isEmpty(apSsid);
        mBtnConfirm.setEnabled(!isApSsidEmpty);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();

        unregisterReceiver(mReceiver);
    }

    @Override
    public void onClick(View v) {
        if (v == mBtnConfirm) {
            String apSsid = mTvApSsid.getText().toString();
            String apPassword = mEdtApPassword.getText().toString();
            String apBssid = mWifiAdmin.getWifiConnectedBssid();
            String taskResultCountStr = Integer.toString(1);
            if (__IEsptouchTask.DEBUG) {
                Log.d(TAG, "mBtnConfirm is clicked, mEdtApSsid = " + apSsid
                        + ", " + " mEdtApPassword = " + apPassword);
            }
            if(mTask != null) {
                mTask.cancelEsptouch();
            }
            mTask = new EsptouchAsyncTask3();
            mTask.execute(apSsid, apBssid, apPassword, taskResultCountStr);

        } else if (v == mButtonDEBUGSKIP) {
            SmartConfigActivity.this.startActivity( new Intent(SmartConfigActivity.this, QRCodeActivity.class));
        } else if (v == mButtonClose) {
            finish();
        }
    }
    
    private class EsptouchAsyncTask3 extends AsyncTask<String, Void, List<IEsptouchResult>> {

        // without the lock, if the user tap confirm and cancel quickly enough,
        // the bug will arise. the reason is follows:
        // 0. task is starting created, but not finished
        // 1. the task is cancel for the task hasn't been created, it do nothing
        // 2. task is created
        // 3. Oops, the task should be cancelled, but it is running
        private final Object mLock = new Object();
        private ProgressDialog mProgressDialog;
        private IEsptouchTask mEsptouchTask;

        public void cancelEsptouch() {
            cancel(true);
            if (mProgressDialog != null) {
                mProgressDialog.dismiss();
            }
            if (mEsptouchTask != null) {
                mEsptouchTask.interrupt();
            }
        }

        @Override
        protected void onPreExecute() {
            mProgressDialog = new ProgressDialog(SmartConfigActivity.this);
            mProgressDialog
                    .setMessage("Let me find your Plush toy... \n\nBe sure to have it close by during this process !");
            mProgressDialog.setCanceledOnTouchOutside(false);
            mProgressDialog.setOnCancelListener(new OnCancelListener() {
                @Override
                public void onCancel(DialogInterface dialog) {
                    synchronized (mLock) {
                        if (__IEsptouchTask.DEBUG) {
                            Log.i(TAG, "progress dialog is canceled");
                        }
                        if (mEsptouchTask != null) {
                            mEsptouchTask.interrupt();
                        }
                    }
                }
            });
            mProgressDialog.setButton(DialogInterface.BUTTON_POSITIVE,
                    "Waiting...", new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(DialogInterface dialog, int which) {
                            SmartConfigActivity.this.startActivity( new Intent(SmartConfigActivity.this, QRCodeActivity.class));
                        }
                    });
            mProgressDialog.show();
            mProgressDialog.getButton(DialogInterface.BUTTON_POSITIVE)
                    .setEnabled(false);
        }

        @Override
        protected List<IEsptouchResult> doInBackground(String... params) {
            int taskResultCount = -1;
            synchronized (mLock) {
                // !!!NOTICE
                String apSsid = mWifiAdmin.getWifiConnectedSsidAscii(params[0]);
                String apBssid = params[1];
                String apPassword = params[2];
                String taskResultCountStr = params[3];
                taskResultCount = Integer.parseInt(taskResultCountStr);
                boolean useAes = false;
                if (useAes) {
                    byte[] secretKey = "1234567890123456".getBytes(); // TODO modify your own key
                    EspAES aes = new EspAES(secretKey);
                    mEsptouchTask = new EsptouchTask(apSsid, apBssid, apPassword, aes, SmartConfigActivity.this);
                } else {
                    mEsptouchTask = new EsptouchTask(apSsid, apBssid, apPassword, null, SmartConfigActivity.this);
                }
            }
            List<IEsptouchResult> resultList = mEsptouchTask.executeForResults(taskResultCount);
            return resultList;
        }

        @Override
        protected void onPostExecute(List<IEsptouchResult> result) {
            mProgressDialog.getButton(DialogInterface.BUTTON_POSITIVE)
                    .setEnabled(true);
            mProgressDialog.getButton(DialogInterface.BUTTON_POSITIVE).setText(
                    "OK");

            if (result == null) {
                mProgressDialog.setMessage("Create Esptouch task failed, the esptouch port could be used by other thread");
                return;
            }

            IEsptouchResult firstResult = result.get(0);
            // check whether the task is cancelled and no results received
            if (!firstResult.isCancelled()) {
                int count = 0;
                // max results to be displayed, if it is more than maxDisplayCount,
                // just show the count of redundant ones
                final int maxDisplayCount = 5;
                // the task received some results including cancelled while
                // executing before receiving enough results
                if (firstResult.isSuc()) {
                    StringBuilder sb = new StringBuilder();
                    for (IEsptouchResult resultInList : result) {
                        sb.append("Success ! Your new Plush toy is now connected to your WiFi \n");
                        count++;
                        if (count >= maxDisplayCount) {
                            break;
                        }
                    }
                    if (count < result.size()) {
                        sb.append("\nthere's " + (result.size() - count)
                                + " more result(s) without showing\n");
                    }
                    mProgressDialog.setMessage(sb.toString());
                } else {
                    mProgressDialog.setMessage("Esptouch fail");
                }
            }
        }
    }
}
