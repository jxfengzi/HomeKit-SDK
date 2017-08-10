package cc.arrizo.wdc;

import android.content.Context;
import android.content.Intent;
import android.net.wifi.ScanResult;
import android.support.v4.widget.SwipeRefreshLayout;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.DividerItemDecoration;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.util.TypedValue;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.oycf.rxwifi.rx.hotspot.RxWifiSearcher;

import java.util.ArrayList;
import java.util.List;

import rx.Subscriber;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = "MainActivity";
    private SwipeRefreshLayout swipeRefreshLayout;
    private LinearLayoutManager layoutManager;
    private RecyclerView recyclerView;
    private MyAdapter myAdapter;
    private List<String> accessories = new ArrayList<>();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        swipeRefreshLayout = (SwipeRefreshLayout) findViewById(R.id.swipeRefreshLayout);
        swipeRefreshLayout.setOnRefreshListener(new SwipeRefreshLayout.OnRefreshListener() {
            @Override
            public void onRefresh() {
                reload();
            }
        });

        recyclerView = (RecyclerView) findViewById(R.id.recyclerView);
        if (recyclerView != null) {
            recyclerView.setHasFixedSize(true);

            layoutManager = new LinearLayoutManager(this);
            recyclerView.setLayoutManager(layoutManager);
            recyclerView.addItemDecoration(new DividerItemDecoration(this, DividerItemDecoration.VERTICAL));

            myAdapter = new MyAdapter(this);
            recyclerView.setAdapter(myAdapter);
        }
    }

    private void reload() {
        Log.d(TAG, "reload");

        RxWifiSearcher.create(this)
                .subscribe(new Subscriber<List<ScanResult>>() {
                    @Override
                    public void onCompleted() {
                        Log.d(TAG, "onCompleted");
                        swipeRefreshLayout.setRefreshing(false);

                        runOnUiThread(new Runnable() {
                            @Override
                            public void run() {
                                myAdapter.notifyDataSetChanged();
                            }
                        });
                    }

                    @Override
                    public void onError(Throwable e) {
                        Log.d(TAG, "onError: " + e.toString());
                    }

                    @Override
                    public void onNext(List<ScanResult> scanResults) {
                        accessories.clear();

                        for (ScanResult result : scanResults) {
                            Log.d(TAG, "SSID: " + result.SSID);

                            if (result.SSID.startsWith("homekit-")) {
                                String a[] = result.SSID.split("-");
                                if (a.length == 3) {
                                    if ("homekit".equals(a[0])) {
//                                        accessories.add(a[1]);
                                        accessories.add(result.SSID);
                                    }
                                }
                            }
                        }
                    }
                });
    }

    private class ViewHolder extends RecyclerView.ViewHolder implements View.OnClickListener {
        public TextView textViewName;

        public ViewHolder(View v) {
            super(v);
            textViewName = (TextView) v.findViewById(R.id.textViewName);
            v.setOnClickListener(this);
        }

        @Override
        public void onClick(View view) {
            String ssid = accessories.get(getAdapterPosition());
            Log.d(TAG, "click: " + ssid);

            Intent intent = new Intent(MainActivity.this, ConfigurationActivity.class);
            intent.putExtra("ssid", ssid);
            startActivity(intent);
        }
    }

    public class MyAdapter extends RecyclerView.Adapter<ViewHolder> {
        private final int mBackground;
        private final TypedValue mTypedValue = new TypedValue();

        public MyAdapter(Context context) {
            context.getTheme().resolveAttribute(R.attr.selectableItemBackground, mTypedValue, true);
            mBackground = mTypedValue.resourceId;
        }

        @Override
        public ViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
            View v = LayoutInflater.from(parent.getContext()).inflate(R.layout.item_accessory, parent, false);
            v.setBackgroundResource(mBackground);

            ViewHolder vh = new ViewHolder(v);

            return vh;
        }

        @Override
        public void onBindViewHolder(final ViewHolder holder, int position) {
            String a = accessories.get(position);
            holder.textViewName.setText(a);
        }

        @Override
        public int getItemCount() {
            return accessories.size();
        }
    }
}