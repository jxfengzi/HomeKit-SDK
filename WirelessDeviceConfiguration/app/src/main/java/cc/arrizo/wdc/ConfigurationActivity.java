package cc.arrizo.wdc;

import android.content.Context;
import android.content.DialogInterface;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.DividerItemDecoration;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.EditText;

import com.oycf.rxwifi.rx.hotspot.RxWifiStation;

import java.nio.charset.Charset;

import cc.arrizo.wdc.keyvalue.KeyValueAdapter;
import cc.arrizo.wdc.keyvalue.KeyValueBean;
import cc.arrizo.wdc.keyvalue.KeyValueListener;

import io.netty.buffer.ByteBuf;
import io.netty.handler.logging.LogLevel;
import io.reactivex.netty.protocol.http.client.HttpClient;
import io.reactivex.netty.protocol.http.client.HttpClientResponse;
import rx.Observable;
import rx.Subscriber;
import rx.functions.Action1;
import rx.functions.Func1;

public class ConfigurationActivity extends AppCompatActivity implements KeyValueListener {

    private static final String TAG = "ConfigurationActivity";
    private LinearLayoutManager layoutManager;
    private RecyclerView recyclerView;
    private KeyValueAdapter myAdapter;
    private String ssid;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_configuration);

        ssid = getIntent().getStringExtra("ssid");

        recyclerView = (RecyclerView) findViewById(R.id.recyclerView);
        if (recyclerView != null) {
            recyclerView.setHasFixedSize(true);

            layoutManager = new LinearLayoutManager(this);
            recyclerView.setLayoutManager(layoutManager);
            recyclerView.addItemDecoration(new DividerItemDecoration(this, DividerItemDecoration.VERTICAL));
            initializeAdapter(this);
        }

        if (getSupportActionBar() != null) {
            getSupportActionBar().setHomeButtonEnabled(true);
            getSupportActionBar().setDisplayHomeAsUpEnabled(true);
            getSupportActionBar().setTitle(ssid);
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_config, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case android.R.id.home:
                finish();
                break;

            case R.id.action_configuration:
                doConfiguration();
                break;
        }

        return super.onOptionsItemSelected(item);
    }

    private void doConfiguration() {
        Log.d(TAG, "doConfiguration");

        RxWifiStation.connect(this, ssid, null)
                .subscribe(new Subscriber<Object>() {
                    @Override
                    public void onCompleted() {
                        Log.e(TAG, "onCompleted");

                        setConfiguration();
                    }

                    @Override
                    public void onError(Throwable e) {
                        Log.e(TAG, "onError: " + e);
                    }

                    @Override
                    public void onNext(Object o) {
                        Log.e(TAG, "onNext: " + o);
                    }
                });
    }

    private void setConfiguration() {
        String uri = "/wdc?ssid=" +  myAdapter.getList().get(0).getValue() + "&password=" + myAdapter.getList().get(1).getValue();
        Log.d(TAG, "GET: " + uri);

        try {
            Thread.sleep(100 * 5);

            HttpClient.newClient("192.168.5.1", 80)
                    .enableWireLogging("hello-client", LogLevel.ERROR)
                    .createGet(uri)
                    .doOnNext(new Action1<HttpClientResponse<ByteBuf>>() {
                        @Override
                        public void call(HttpClientResponse<ByteBuf> resp) {
                            Log.d(TAG, resp.toString());
                        }
                    })
                    .flatMap(new Func1<HttpClientResponse<ByteBuf>, Observable<?>>() {
                        @Override
                        public Observable<?> call(HttpClientResponse<ByteBuf> resp) {
                            return resp.getContent().map(new Func1<ByteBuf, Object>() {
                                @Override
                                public Object call(ByteBuf bb) {
                                    return bb.toString(Charset.defaultCharset());
                                }
                            });
                        }
                    })
                    .toBlocking()
                    .forEach(new Action1<Object>() {
                        @Override
                        public void call(Object o) {
                            Log.d(TAG, o.toString());
                        }
                    });
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void initializeAdapter(Context context) {
        myAdapter = new KeyValueAdapter(context, this);
        myAdapter.getList().add(new KeyValueBean(0, "SSID", "airport"));
        myAdapter.getList().add(new KeyValueBean(1, "PASSWORD", "hello"));
        recyclerView.setAdapter(myAdapter);
    }

    private void showSSIDEditor() {
        final EditText editText = new EditText(this);
        editText.setText(myAdapter.getList().get(0).getValue());

        AlertDialog.Builder inputDialog = new AlertDialog.Builder(this);
        inputDialog.setTitle("SSID").setView(editText);
        inputDialog.setPositiveButton("OK",
                new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        myAdapter.getList().get(0).setValue(editText.getText().toString());
                        myAdapter.notifyDataSetChanged();
                    }
                });
        inputDialog.setNegativeButton("Cancel",
                new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {
                    }
                });
        inputDialog.show();
    }

    private void showPasswordEditor() {
        final EditText editText = new EditText(this);
        editText.setText(myAdapter.getList().get(1).getValue());

        final AlertDialog.Builder inputDialog = new AlertDialog.Builder(this);
        inputDialog.setTitle("PASSWORD").setView(editText);
        inputDialog.setPositiveButton("OK",
                new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        myAdapter.getList().get(1).setValue(editText.getText().toString());
                        myAdapter.notifyDataSetChanged();
                    }
                });
        inputDialog.setNegativeButton("Cancel",
                new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {
                    }
                });

        inputDialog.show();
    }

    @Override
    public void onClick(KeyValueBean bean) {
        switch (bean.getType()) {
            case 0:
                showSSIDEditor();
                break;

            case 1:
                showPasswordEditor();
                break;
        }
    }
}
